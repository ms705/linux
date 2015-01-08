#include <uapi/linux/elf.h>
#include <asm/current.h>
#include <linux/dios.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/slab.h>

#include <dios/task.h>

int dios_load_elf(const char*   filename,
                  unsigned char osabi,
                  unsigned char abiversion) {
	/* The DIOS ABI requires additional setup */
	if (osabi == ELFOSABI_DIOS) {
		struct file* console;

		switch (abiversion) {
		case ELFABIVERSION_DIOS_PURE:
			/* Must be invoked from dios_run so everything DIOS
			   should be already setup by UMH */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("ELF is pure DIOS\n");
#endif
			if (!current->is_pure_dios) {
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
				printk("ELF: pure DIOS but not dios_run'd\n");
#endif
				return -ENOEXEC;
			}
			break;

		case ELFABIVERSION_DIOS_LIMBO:
			/* Must be invoked from DIOS run but is allowed to make
			   legacy syscalls by unsetting is_pure_dios */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("ELF is DIOS limbo\n");
#endif
			if (!current->is_pure_dios) {
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
				printk("ELF: DIOS limbo but not dios_run'd\n");
#endif
				return -ENOEXEC;
			}

#ifdef CONFIG_DIOS_RESTRICT_LIMBO
			/* Remain a pure DIOS task */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("Limbo restricted: Still a pure DIOS task\n");
#endif
#else
			/* Allow legacy syscalls as allowing limbo */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("Allowing legacy syscalls in DIOS task\n");
#endif
			current->is_pure_dios = 0;
				
			/* Also need to install std{in,out,err} */
			console = filp_open("/dev/console", O_RDWR, 0);
			fd_install(0, console);
			fd_install(1, console);
			fd_install(2, console);
#endif
			break;

		case ELFABIVERSION_DIOS_LEGACY:
			/* Must be invoked from exec() but prepare as a DIOS
			   task to allow for DIOS syscalls */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("ELF is legacy limbo\n");
#endif
			if (current->is_pure_dios) {
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
				printk("ELF: legacy limbo from dios_run'\n");
#endif
				return -ENOEXEC;
			}

#ifdef CONFIG_DIOS_RESTRICT_LIMBO
				/* Remain a legacy process */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("Remaining a legacy process\n");
#endif
#else
				/* Allow DIOS syscalls as allowing limbo */
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			printk("Can use DIOS syscalls from legacy process\n");
#endif
			current->is_dios_task = 1;
			/* Make sure the task info is allocated */
			current->dios_task_info =
			  kzalloc(sizeof(dios_task_info_t), GFP_KERNEL);
			if (!current->dios_task_info)
				return -ENOMEM;
#endif
			break;

		default:
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
			if (current->is_pure_dios) {
				printk("Unknown ABI version."
				       " Defaulting to pure DIOS task\n");
			} else {
				printk("Unknown ABI version."
				       " Defaulting to legacy process\n");
			}
#endif
			break;
		}
	}

	if (current->is_dios_task) {
        	/* Prepare the DIOS task */
		dios_init_task(current, filename);
	} else {
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
		printk("ELF loading as legacy process. No DIOS allowed!\n");
#endif
	}

	return 0;
}
