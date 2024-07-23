default:
	mos-cx16-clang -o TEST.PRG file-test.c
	x16emu -rtc -ram 2048 -scale 2 -prg TEST.PRG -run -debug

clean:
	rm -f *.PRG
	rm -f *.o
	rm -f *.elf
	rm -f *.bin