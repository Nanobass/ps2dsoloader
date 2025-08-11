PROJECT_SRC=$(CURDIR)

EXECUTABLE = runtime

SUBDIRS = dl/ filer/

# main executable
SUBDIRS += $(EXECUTABLE)

MODULE_DIR=irx
MODULES=audsrv.irx libsd.irx sio2man.irx padman.irx ps2dev9.irx ps2atad.irx ps2hdd.irx ps2fs.irx smap.irx netman.irx audsrv.irx iomanX.irx fileXio.irx mcman.irx mcserv.irx poweroff.irx smbman.irx ps2ip.irx cdvdfsv.irx cdvdman.irx cdfs.irx

PACKAGE_DIR=project
PACKAGE_CONTENT=$(EXECUTABLE).elf $(patsubst %.irx,$(MODULE_DIR)/%.irx,$(MODULES))
PACKAGE_FILES=$(patsubst %,$(PACKAGE_DIR)/%,$(PACKAGE_CONTENT))

#
# PACKAGE RULES
#

$(PACKAGE_DIR)/$(MODULE_DIR)/%.irx: $(PS2SDK)/iop/irx/%.irx
	@mkdir -p $(dir $@)
	cp $< $@

$(PACKAGE_DIR)/$(EXECUTABLE).elf: $(EXECUTABLE)/$(EXECUTABLE).elf
	@mkdir -p $(dir $@)
	cp $< $@

#
# BUILD PROCESS
#

.DEFAULT_GOAL := build

build: 
	make all
	make package

rebuild: 
	make clean
	make all
	make package


all: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)):
	@+$(MAKE) -j -r -C $(patsubst _dir_%, %, $@) all PROJECT_SRC=$(PROJECT_SRC)

clean: $(patsubst %, _cleandir_%, $(SUBDIRS))
	rm -rf $(PACKAGE_FILES)

$(patsubst %, _cleandir_%, $(SUBDIRS)):
	@+$(MAKE) -j -C $(patsubst _cleandir_%, %, $@) clean PROJECT_SRC=$(PROJECT_SRC)

#
# PACKAGE PROCESS
#

package: $(PACKAGE_FILES)
	cp filer/libfiler.so $(PACKAGE_DIR)/libfiler.so