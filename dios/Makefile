#
# Makefile for the DIOS extension to the Linux kernel.
#

KBUILD_EXTRA_SYMBOLS=$(CURDIR)/../src/Module.symvers
#KBUILD_EXTMOD=/home/malte/Projects/dios/src

obj-$(CONFIG_DIOS) := syscalls.o utils.o task.o elf.o

ccflags-y += -D__DIOS_ON_LINUX__

# TODO: should this be an config option?
ccflags-y += -I../../include/ -I../../include/uapi

