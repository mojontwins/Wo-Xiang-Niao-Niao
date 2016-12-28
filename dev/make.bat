@echo off

echo MAKING GRAPHICS
cd ..\gfx

echo Making palettes
..\utils\mkts.exe mode=pals pals=pal1.png out=..\dev\work\palts0.h label=pal_bg_0 silent
..\utils\mkts.exe mode=pals pals=pal2.png out=..\dev\work\palts1.h label=pal_bg_1 silent
..\utils\mkts.exe mode=pals pals=pal3.png out=..\dev\work\palts2.h label=pal_bg_2 silent
..\utils\mkts.exe mode=pals pals=pal4.png out=..\dev\work\palts3.h label=pal_bg_3 silent
..\utils\mkts.exe mode=pals pals=pal5.png out=..\dev\work\palts4.h label=pal_bg_4 silent
..\utils\mkts.exe mode=pals pals=pal6.png out=..\dev\work\palts5.h label=pal_bg_5 silent
..\utils\mkts.exe mode=pals pals=pal7.png out=..\dev\work\palts6.h label=pal_bg_6 silent
..\utils\mkts.exe mode=pals pals=pal8.png out=..\dev\work\palts7.h label=pal_bg_7 silent
..\utils\mkts.exe mode=pals pals=palbonus.png out=..\dev\work\palts8.h label=pal_bg_8 silent

..\utils\mkts.exe mode=pals pals=palt1.png out=..\dev\work\paltst0.h label=pal_bg_t0 silent

..\utils\mkts.exe mode=pals pals=pals0.png out=..\dev\work\palss0.h label=pal_fg_0 silent
..\utils\mkts.exe mode=pals pals=pals1.png out=..\dev\work\palss1.h label=pal_fg_1 silent
..\utils\mkts.exe mode=pals pals=palsbonus.png out=..\dev\work\palss2.h label=pal_fg_2 silent

copy /b ..\dev\work\palts0.h + ..\dev\work\palts1.h + ..\dev\work\palts2.h + ..\dev\work\palts3.h + ..\dev\work\palts4.h + ..\dev\work\palts5.h + ..\dev\work\palts6.h + ..\dev\work\palts7.h + ..\dev\work\palts8.h + ..\dev\work\paltst0.h + ..\dev\work\palss0.h + ..\dev\work\palss1.h + ..\dev\work\palss2.h ..\dev\assets\palettes.h > nul

echo Making bg charset
..\utils\mkts.exe mode=chars in=font.png pals=pal1.png out=chrts1.bin size=32,2 silent
..\utils\mkts.exe mode=coltiles in=pongpong.png pals=pal1.png out=chrts2.bin mode=tiles size=16,3 tsmap=..\dev\assets\tspals.h label=ts silent
copy /b chrts1.bin + chrts2.bin chrts.bin > nul
del chrts1.bin > nul
del chrts2.bin > nul

echo Making obj charset
..\utils\mkts.exe mode=sprites in=sprites.png pals=pals0.png out=chrss1.bin tsmap=..\dev\assets\sspl.h offset=0,0 size=8,3 max=22 metasize=2,3 sprorg=-4,-8 label=spr_player genflipped silent
..\utils\mkts.exe mode=sprites in=sprites.png pals=pals0.png out=chrss2.bin tsmap=..\dev\assets\ssen1.h offset=0,12 size=8,1 metasize=2,3 sprorg=0,-8 label=spr_enems1 tmapoffset=103 genflipped silent
..\utils\mkts.exe mode=sprites in=sprites.png pals=pals0.png out=chrss3a.bin tsmap=..\dev\assets\ssen2.h offset=0,15 size=8,2 metasize=2,2 sprorg=0,0 label=spr_enems2 tmapoffset=149 genflipped silent
..\utils\mkts.exe mode=sprites in=sprites.png pals=pals0.png out=chrss3b.bin tsmap=..\dev\assets\ssen3.h offset=0,19 size=8,2 max=10 metasize=2,2 sprorg=0,0 label=spr_enems3 tmapoffset=199 silent
..\utils\mkts.exe mode=sprites in=sprites.png pals=pals0.png out=chrss4a.bin tsmap=..\dev\assets\ssplend1.h offset=2,9 size=4,1 metasize=2,3 sprorg=-4,-8 label=spr_player_ending1 tmapoffset=228 silent
..\utils\mkts.exe mode=sprites in=sprites.png pals=pals0.png out=chrss4b.bin tsmap=..\dev\assets\ssplend2.h offset=10,9 size=1,1 metasize=2,3 sprorg=-4,-8 label=spr_player_ending2 tmapoffset=246 genflipped silent

copy /b chrss1.bin + chrss2.bin + chrss3a.bin + chrss3b.bin + chrss4a.bin + chrss4b.bin chrss.bin > nul
del chrss1.bin > nul
del chrss2.bin > nul
del chrss3a.bin > nul
del chrss3b.bin > nul
del chrss4a.bin > nul
del chrss4b.bin > nul
..\utils\fillto.exe chrss.bin 4080

..\utils\mkts.exe mode=chars in=sprite0.png pals=pals0.png out=sprite0.bin size=1,1 silent

echo Building chr
copy /b chrts.bin + chrss.bin + sprite0.bin ..\dev\tileset.chr > nul
del chrts.bin > nul
del chrss.bin > nul
del sprite0.bin > nul

echo BUILDING MAP
cd ..\map 
..\utils\mapcnv2tpb.exe pongpong.map 256 5 noattrs
copy map.h ..\dev\assets > nul
copy precalcs.h ..\dev\assets\precalc_attr_bits.h
del map.h > nul
del map.bin > nul

echo BUILDING ENEMS
cd ..\enems 
..\utils\eneexp3.exe enems.ene ..\dev\assets\enems.h ROM 2 nohotspots

echo Compiling
cd ..\dev

cc65 -Oi pongpong.c --add-source
ca65 crt0.s
ca65 pongpong.s

ld65 -C nes.cfg -o pongpong.nes crt0.o pongpong.o runtime.lib  -Ln labels.txt

del pongpong.s > nul
del pongpong.o > nul
del crt0.o > nul
