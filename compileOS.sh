# fill file with a floppy's worth of zeros
dd if=/dev/zero of=floppya.img bs=512 count=2880
# copy bootloader into secter 0 of disk
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc

# compile kernel
bcc -ansi -c -o kernel.o kernel.c

# link kernel to interrupt library
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o

# copy kernel into sector 3 of disk
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3
