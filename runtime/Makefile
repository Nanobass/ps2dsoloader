EE_BIN = runtime.elf

EE_INCS = -I$(PROJECT_SRC)/dl/ee/include -I$(PROJECT_SRC)/filer/ee/include
EE_LIBS = -L$(PROJECT_SRC)/dl/ -ldl

EE_STD_LIBS = libatomic.a libc.a libcdvd.a libcglue.a libg.a libkernel.a libm.a libprofglue.a libpthread.a libpthreadglue.a

#EE_LDFLAGS += -nodefaultlibs -Wl,--whole-archive $(addprefix $(PS2DEV)/ee/mips64r5900el-ps2-elf/lib/, $(EE_STD_LIBS)) -Wl,--no-whole-archive
EE_LDFLAGS += -Wl,-allow-multiple-definition -Wl,--whole-archive -lc -lcdvd -lcglue -lkernel -lm -lprofglue -lpthreadglue -Wl,--no-whole-archive

EE_WARNFLAGS += -Wall 

all: $(EE_BIN)
#	$(EE_STRIP) $(EE_BIN)
clean: 
	rm -rf $(EE_OBJ) $(EE_BIN)

include ../Makefile.project