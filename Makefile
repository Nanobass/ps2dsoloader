PROJECT_SRC=$(CURDIR)

EXECUTABLE = runtime

SUBDIRS += dl/
SUBDIRS += lua/

SUBDIRS += luasystem/
SUBDIRS += luagraphics/
SUBDIRS += luainput/

# main executable
SUBDIRS += $(EXECUTABLE)

MODULE_DIR=irx
MODULES=audsrv.irx libsd.irx sio2man.irx padman.irx ps2dev9.irx ps2atad.irx ps2hdd.irx ps2fs.irx smap.irx netman.irx audsrv.irx iomanX.irx fileXio.irx mcman.irx mcserv.irx poweroff.irx smbman.irx ps2ip.irx cdvdfsv.irx cdvdman.irx cdfs.irx

ERL_DIR=erx
ERL_MODULES=libahx.erl libaudsrv.erl libcdvd.erl libcglue.erl libdebug.erl libdma.erl \
libdraw.erl libdummy.erl libeedebug.erl libelf-loader.erl libelf-loader-nocolour.erl \
liberl.erl libfileXio.erl libfont.erl libgraph.erl libgs.erl libhdd.erl libinput.erl \
libinputx.erl libiopreboot.erl libkbd.erl libkernel.erl libmath3d.erl libmc.erl libmouse.erl \
libmpeg.erl libmtap.erl libnetman.erl libpacket2.erl libpacket.erl libpad.erl libpadx.erl \
libpatches.erl libpoweroff.erl libprofglue.erl libps2cam.erl libps2ip.erl libps2ips.erl \
libps2snd.erl libpthreadglue.erl librm.erl libsbus.erl libsecr.erl libsior.erl libsocket.erl \
libvux.erl libxcdvd.erl libgskit.erl libdmakit.erl libgskit_toolkit.erl libpng.erl libjpeg.erl libtiff.erl liblzma.erl libz.erl

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

libgskit-erl-support.c: 
	echo "char* erl_id = \"libgskit\"; char* erl_dependancies[] = { \"libc\", \"libdmakit\", 0 }; " > $@

libdmakit-erl-support.c: 
	echo "char* erl_id = \"libdmakit\"; char* erl_dependancies[] = { \"libc\", 0 }; " > $@

libgskit_toolkit-erl-support.c: 
	echo "char* erl_id = \"libgskit_toolkit\"; char* erl_dependancies[] = { \"libgskit\", 0 }; " > $@

libpng-erl-support.c: 
	echo "char* erl_id = \"libpng\"; char* erl_dependancies[] = { \"libc\", \"libz\", 0 }; " > $@
	
libjpeg-erl-support.c: 
	echo "char* erl_id = \"libjpeg\"; char* erl_dependancies[] = { \"libc\", 0 }; " > $@
		
libtiff-erl-support.c: 
	echo "char* erl_id = \"libtiff\"; char* erl_dependancies[] = { \"libc\", \"liblzma\", 0 }; " > $@

liblzma-erl-support.c: 
	echo "char* erl_id = \"liblzma\"; char* erl_dependancies[] = { \"libc\", 0 }; " > $@

libz-erl-support.c: 
	echo "char* erl_id = \"libz\"; char* erl_dependancies[] = { \"libc\", 0 }; " > $@

# generate gsKit erls
$(PACKAGE_DIR)/$(ERL_DIR)/%.erl: $(PS2DEV)/gsKit/lib/%.a %-erl-support.c
	mips64r5900el-ps2-elf-gcc -G0 -o $*-erl-support.o -c $*-erl-support.c
	mips64r5900el-ps2-elf-gcc -G0 -O2 -nodefaultlibs -nostdlib -nostartfiles -o $@ -Wl,-whole-archive $< $*-erl-support.o -Wl,-r -Wl,-d
	mips64r5900el-ps2-elf-strip --strip-unneeded -R .mdebug.eabi64 -R .reginfo -R .comment $@
	rm $*-erl-support.o $*-erl-support.c
	
# generate ports erls
$(PACKAGE_DIR)/$(ERL_DIR)/%.erl: $(PS2DEV)/ps2sdk/ports/lib/%.a %-erl-support.c
	mips64r5900el-ps2-elf-gcc -G0 -o $*-erl-support.o -c $*-erl-support.c
	mips64r5900el-ps2-elf-gcc -G0 -O2 -nodefaultlibs -nostdlib -nostartfiles -o $@ -Wl,-whole-archive $< $*-erl-support.o -Wl,-r -Wl,-d
	mips64r5900el-ps2-elf-strip --strip-unneeded -R .mdebug.eabi64 -R .reginfo -R .comment $@
	rm $*-erl-support.o $*-erl-support.c

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

package: $(PACKAGE_FILES) copy_libs

copy_libs:
	cp luasystem/luasystem.so $(PACKAGE_DIR)/$(ERL_DIR)/luasystem.so
	cp luagraphics/luagraphics.so $(PACKAGE_DIR)/$(ERL_DIR)/luagraphics.so
	cp luainput/luainput.so $(PACKAGE_DIR)/$(ERL_DIR)/luainput.so