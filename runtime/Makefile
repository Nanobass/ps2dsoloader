EE_BIN = runtime.elf

EE_INCS = -I$(PROJECT_SRC)/dl/ee/include -I$(PROJECT_SRC)/lua/ee/include
EE_LIBS = -L$(PROJECT_SRC)/dl/ -ldl -L$(PROJECT_SRC)/lua/ -llua -lpad

EE_WARNFLAGS += -Wall 
EE_OPTFLAGS = -O2

all: $(EE_BIN) $(PROJECT_SRC)/dl/libdl.a $(PROJECT_SRC)/lua/liblua.a
	$(EE_STRIP) $(EE_BIN)
clean: 
	rm -rf $(EE_OBJ) $(EE_BIN)

include ../Makefile.project