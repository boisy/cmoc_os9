CC = cmoc
OS9FLAGS = --os9 -nodefaultlibs
OPT = -O0
LFLAGS = -I../include -I../cgfx/include $(OS9FLAGS)

%: %.c
	$(CC) $(LFLAGS) $^ $(OBJS) -L../lib -lc -L../cgfx -lcgfx


TESTS	= timetest fiotest iotest osiotest syscalltest memtest wintest forktest printtest maze utimetest ctype string

all:	$(TESTS)

dsk:	all
	os9 format -e -q -ds -dd -t80 test.dsk
	os9 makdir test.dsk,CMDS
	os9 copy $(TESTS) test.dsk,CMDS
	$(foreach file, $(TESTS), os9 attr -q -epe test.dsk,CMDS/$(file);)
	echo "chx /d1/cmds; chd /d1" > go
	$(foreach file, $(TESTS), echo $(file) >> go;)
	os9 copy -l go test.dsk,


run:	dsk
	mame64 -inipath ~/Documents/mame -video opengl -window coco3 -flop1 nos9.dsk -flop2 test.dsk -speed 4 &

clean:
	-rm $(TESTS) test.dsk go
