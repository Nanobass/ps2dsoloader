EE_SHARED = libfiler.so

EE_CFLAGS += -fvisibility=hidden
EE_CXXFLAGS += -fvisibility=hidden
EE_LDFLAGS += -Wl,-soname,$(EE_SHARED)

all: $(EE_SHARED)
	$(EE_STRIP) --strip-unneeded $(EE_SHARED)
clean: 
	rm -rf $(EE_OBJ) $(EE_SHARED)

include ../Makefile.project