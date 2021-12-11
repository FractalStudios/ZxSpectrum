@echo off
skool2ctl.py jetpac\jetpac.skl > jetpac\jetpac.ctl
sna2skool.py -H -c jetpac\jetpac.ctl jetpac\jetpac.z80 > jetpac\jetpac.skl
skool2html.py -a jetpac\jetpac.skl
REM skool2asm.py -H jetpac\jetpac.skl > jetpac\jetpac.asm
REM skool2bin.py -i jetpac\jetpac.skl  jetpac\jetpac.bin
REM bin2sna.py jetpac\jetpac.bin  jetpac\new_jetpac.z80 

