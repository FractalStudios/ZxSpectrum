@echo off
zcc +zx -vn -m -startup=31 -clib=sdcc_iy jetman.c -o jetman -create-app
