EE_BIN = runtime.elf

EE_INCS = -I$(PROJECT_SRC)/dl/ee/include -I$(PROJECT_SRC)/filer/ee/include
EE_LIBS = -L$(PROJECT_SRC)/dl/ -ldl

EE_WARNFLAGS += -Wall 

all: $(EE_BIN)
#	$(EE_STRIP) $(EE_BIN)
clean: 
	rm -rf $(EE_OBJ) $(EE_BIN)

include ../Makefile.project