@echo off
skool2ctl.py aticatac\aticatac.skl > aticatac\aticatac.ctl
sna2skool.py -H -c aticatac\aticatac.ctl aticatac\aticatac.z80 > aticatac\aticatac.skl
skool2html.py -a aticatac\aticatac.skl
REM skool2asm.py -H aticatac\aticatac.skl > aticatac\aticatac.asm
REM skool2bin.py -i aticatac\aticatac.skl  aticatac\aticatac.bin
REM bin2sna.py aticatac\aticatac.bin  aticatac\new_aticatac.z80 
