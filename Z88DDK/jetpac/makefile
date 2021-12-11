APP=jetpac

SOURCE_DIR=src
OBJECT_DIR=obj
PRAGMA_FILE=$(SOURCE_DIR)\zpragma.inc

CC=zcc
TARGET=+zx
VERBOSITY=-vn
CLIB=sdcc_iy
CRT=31

CFLAGS=$(TARGET) $(VERBOSITY) -clib=$(CLIB) -compiler sdcc -c -O3 -pragma-include:$(PRAGMA_FILE)
LFLAGS=$(TARGET) $(VERBOSITY) -clib=$(CLIB) -m -startup=$(CRT) -create-app -pragma-include:$(PRAGMA_FILE)

BINARY=$(APP).tap

all: create_dirs $(BINARY)

# Create output directories.
create_dirs:
	@if not exist $(OBJECT_DIR) mkdir $(OBJECT_DIR)
 
OBJECTS = $(OBJECT_DIR)\game.o \
          $(OBJECT_DIR)\globals.o \
          $(OBJECT_DIR)\main.o \
          $(OBJECT_DIR)\spritedata.o \
          $(OBJECT_DIR)\utils.o

{$(SOURCE_DIR)\}.c{$(OBJECT_DIR)\}.o:
	$(CC) $(CFLAGS) -o $@ $**

$(BINARY): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(APP)
	@copy /y $(APP)*.bin $(OBJECT_DIR) >NUL
	@del /q /f $(APP)*.bin >NUL
	@copy /y zcc_opt.def $(OBJECT_DIR) >NUL
	@del /q /f zcc_opt.def >NUL

.PHONY: clean
clean:
	@if exist $(OBJECT_DIR) del /q /f $(OBJECT_DIR)\*.o >NUL
	@if exist $(OBJECT_DIR) del /q /f $(OBJECT_DIR)\*.bin >NUL
	@if exist $(OBJECT_DIR) del /q /f $(OBJECT_DIR)\zcc_opt.def >NUL
    @if exist $(OBJECT_DIR) rd /q $(OBJECT_DIR) >NUL
	@if exist $(APP).tap del /q /f $(APP).tap >NUL
	@if exist $(APP).map del /q /f $(APP).map >NUL
