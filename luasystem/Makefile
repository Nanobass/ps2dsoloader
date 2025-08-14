EE_SHARED = luasystem.so

EE_INCS = -I$(PROJECT_SRC)/lua/ee/include

EE_CFLAGS += -fvisibility=hidden
EE_CXXFLAGS += -fvisibility=hidden
EE_LDFLAGS += -Wl,-soname,luasystem/liblua/libc/libstd++/libkernel

all: $(EE_SHARED)
	$(EE_STRIP) --strip-unneeded $(EE_SHARED)
clean: 
	rm -rf $(EE_OBJ) $(EE_SHARED)

include ../Makefile.project