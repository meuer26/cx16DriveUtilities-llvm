default:
	mos-cx16-clang -o DRVUTILS.PRG main.c menu.c screen.c disk.c
	x16emu -rtc -ram 2048 -scale 2 -prg DRVUTILS.PRG -run -debug

clean:
	rm -f *.PRG
	rm -f *.o
	rm -f *.elf
	rm -f *.bin