#
# Makefile for the DIOS extension to the Linux kernel.
#

KBUILD_EXTRA_SYMBOLS=$(CURDIR)/../src/Module.symvers
#KBUILD_EXTMOD=/home/malte/Projects/dios/src

obj-$(CONFIG_DIOS) := syscalls.o utils.o task.o elf.o

# TODO: should this be an config option?
ccflags-y += -I../../include/ -I../../include/uapi

