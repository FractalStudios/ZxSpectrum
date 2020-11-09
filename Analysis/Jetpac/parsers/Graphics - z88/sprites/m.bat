@echo off
del /q spritedata.h
REM Jetman
..\Release\parser j 7aa2_7ad4.bmp 7ad5_7b07.bmp 7b08_7b52.bmp 7b53_7b9d.bmp 79a6_79d8.bmp 79d9_7a0b.bmp 7a0c_7a56.bmp 7a57_7aa1.bmp 7796_77c8.bmp 77c9_7813.bmp 7814_785e.bmp 785f_78a9.bmp 78aa_78dc.bmp 78dd_790f.bmp 7910_795a.bmp 795b_79a5.bmp
REM Meteor
..\Release\parser m 7b9e_7bb4.bmp 7bb5_7bcb.bmp
REM Cloud
..\Release\parser 7bcc_7bfe.bmp 7bff_7c31.bmp 7c32_7c64.bmp
REM Rocket U1
..\Release\parser r 7CCE_7CF0.bmp 7CF1_7D13.bmp 7D14_7d36.bmp
REM Rocket U2
..\Release\parser r 7D37_7d59.bmp 7D5A_7d7c.bmp 7D7D_7d9f.bmp
REM Rocket U3
..\Release\parser r 7c65_7c87.bmp 7c88_7caa.bmp 7cab_7ccd.bmp
REM Rocket U4
..\Release\parser r 7DA0_7dc2.bmp 7DC3_7de5.bmp 7DE6_7e08.bmp
REM Gold bar
..\Release\parser 7e09_7e1b.bmp
REM Fuel
..\Release\parser 7e1c_7e34.bmp
REM Radiation canister
..\Release\parser 7e35_7e4d.bmp
REM Triangle
..\Release\parser 7e4e_7e6a.bmp
REM Dome
..\Release\parser 7e6b_7e7f.bmp
REM Crystal
..\Release\parser 7e80_7e9a.bmp
REM Furball
..\Release\parser m 7e9b_7eb7.bmp 7eb8_7ed4.bmp
REM Plane
..\Release\parser m 7ed5_7ee3.bmp
REM Flying saucer
..\Release\parser 7ee4_7ef4.bmp
REM Ball
..\Release\parser 7ef5_7f15.bmp 7f16_7f32.bmp
REM Satellite
..\Release\parser 7f33_7f51.bmp
REM Millenium falcon
..\Release\parser m 7f52_7f6e.bmp
REM Blob
..\Release\parser 7f6f_7f8b.bmp
REM Rocket smoke trail
..\Release\parser 7f8c_7fac.bmp 7faf_7fcf.bmp
pause


