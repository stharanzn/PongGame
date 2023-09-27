ASM = nasm

Build = build

$(Build)/input_floppy.img: $(Build)/input.bin
	cp $(Build)/input.bin $(Build)/input_floppy.img
	truncate -s 1440k $(Build)/input_floppy.img

$(Build)/input.bin: input.asm
	$(ASM) -f bin input.asm -o $(Build)/input.bin
