
#include "include/dal_linux.h"

#define DIOS_MODULE_NAME "dios"


bool dios_module_loaded(void) {
  /* check if DIOS module is loaded */
  struct module *mod;

  if (mutex_lock_interruptible(&module_mutex) != 0)
    return -EINTR;
  mod = find_module(DIOS_MODULE_NAME);

  if (!mod) {
    printk("DIOS module NOT loaded.\n");
    goto out;
  } else {
    printk("DIOS module loaded! :)\n");
    goto out; 
  }

out:
  mutex_unlock(&module_mutex);
  return (mod != 0);
}


