PROJECT_SRC=$(CURDIR)

EXECUTABLE = runtime

SUBDIRS = dl/ filer/

# main executable
SUBDIRS += $(EXECUTABLE)

MODULE_DIR=irx
MODULES=audsrv.irx libsd.irx sio2man.irx padman.irx ps2dev9.irx ps2atad.irx ps2hdd.irx ps2fs.irx smap.irx netman.irx audsrv.irx iomanX.irx fileXio.irx mcman.irx mcserv.irx poweroff.irx smbman.irx ps2ip.irx cdvdfsv.irx cdvdman.irx cdfs.irx

ERL_DIR=erl
ERL_MODULES=libahx.erl libaudsrv.erl libcdvd.erl libcglue.erl libdebug.erl libdma.erl libdraw.erl libdummy.erl libeedebug.erl libelf-loader.erl libelf-loader-nocolour.erl liberl.erl libfileXio.erl libfont.erl libgraph.erl libgs.erl libhdd.erl libinput.erl libinputx.erl libiopreboot.erl libkbd.erl libkernel.erl libmath3d.erl libmc.erl libmouse.erl libmpeg.erl libmtap.erl libnetman.erl libpacket2.erl libpacket.erl libpad.erl libpadx.erl libpatches.erl libpoweroff.erl libprofglue.erl libps2cam.erl libps2ip.erl libps2ips.erl libps2snd.erl libpthreadglue.erl librm.erl libsbus.erl libsecr.erl libsior.erl libsocket.erl libvux.erl libxcdvd.erl

PACKAGE_DIR=project
PACKAGE_CONTENT=$(EXECUTABLE).elf $(patsubst %.irx,$(MODULE_DIR)/%.irx,$(MODULES)) $(patsubst %.erl,$(ERL_DIR)/%.erl,$(ERL_MODULES))
PACKAGE_FILES=$(patsubst %,$(PACKAGE_DIR)/%,$(PACKAGE_CONTENT))

#
# PACKAGE RULES
#

$(PACKAGE_DIR)/$(MODULE_DIR)/%.irx: $(PS2SDK)/iop/irx/%.irx
	@mkdir -p $(dir $@)
	cp $< $@

$(PACKAGE_DIR)/$(ERL_DIR)/%.erl: $(PS2SDK)/ee/lib/%.erl
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
	cp filer/libfiler.so $(PACKAGE_DIR)/erl/libfiler.so