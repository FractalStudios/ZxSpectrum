@echo off
zcc +zx -vn -m -startup=31 -clib=sdcc_iy test.c circle_sprite_masked.asm -o test -create-app
