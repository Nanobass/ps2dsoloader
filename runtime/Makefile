EE_BIN = runtime.elf

EE_INCS = -I$(PROJECT_SRC)/dl/ee/include -I$(PROJECT_SRC)/filer/ee/include -I$(PROJECT_SRC)/lua/ee/include
EE_LIBS = -L$(PROJECT_SRC)/dl/ -ldl -L$(PROJECT_SRC)/lua/ -llua

EE_STD_LIBS = libc.a libcdvd.a libcglue.a libkernel.a libm.a libpthread.a libpthreadglue.a

#EE_LDFLAGS += -Wl,-allow-multiple-definition -Wl,--whole-archive $(addprefix $(PS2DEV)/ee/mips64r5900el-ps2-elf/lib/, $(EE_STD_LIBS)) -Wl,--no-whole-archive
EE_LDFLAGS += -Wl,-allow-multiple-definition -Wl,--whole-archive -lc -lm -lcglue -lcdvd -lkernel -Wl,--no-whole-archive
EE_WARNFLAGS += -Wall 
EE_OPTFLAGS = -O0

all: $(EE_BIN)
#	$(EE_STRIP) $(EE_BIN)
clean: 
	rm -rf $(EE_OBJ) $(EE_BIN)

include ../Makefile.project