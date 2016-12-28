;this file for FamiTone2 library generated by text2data tool

music_music_data:
	.byte 3
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256
	.word @song1ch0,@song1ch1,@song1ch2,@song1ch3,@song1ch4,307,256
	.word @song2ch0,@song2ch1,@song2ch2,@song2ch3,@song2ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env2,@env0,@env0
	.byte $00
	.byte $30 ;instrument $01
	.word @env1,@env0,@env14
	.byte $00
	.byte $70 ;instrument $02
	.word @env5,@env0,@env0
	.byte $00
	.byte $30 ;instrument $04
	.word @env6,@env12,@env0
	.byte $00
	.byte $30 ;instrument $05
	.word @env10,@env0,@env0
	.byte $00
	.byte $30 ;instrument $06
	.word @env7,@env0,@env0
	.byte $00
	.byte $30 ;instrument $07
	.word @env1,@env11,@env0
	.byte $00
	.byte $70 ;instrument $08
	.word @env3,@env0,@env15
	.byte $00
	.byte $70 ;instrument $09
	.word @env4,@env0,@env15
	.byte $00
	.byte $30 ;instrument $0a
	.word @env3,@env0,@env15
	.byte $00
	.byte $70 ;instrument $0c
	.word @env8,@env13,@env0
	.byte $00
	.byte $70 ;instrument $0d
	.word @env9,@env13,@env0
	.byte $00

@samples:
@env0:
	.byte $c0,$00,$00
@env1:
	.byte $ca,$00,$00
@env2:
	.byte $cf,$00,$00
@env3:
	.byte $cc,$cb,$ca,$ca,$c9,$03,$c8,$03,$c7,$07,$c6,$08,$c5,$0a,$c4,$0c
	.byte $c3,$0c,$c2,$12,$c1,$19,$c0,$00,$16
@env4:
	.byte $c4,$02,$c3,$0c,$c2,$0b,$c1,$12,$c0,$00,$08
@env5:
	.byte $c9,$07,$c6,$05,$c9,$07,$c9,$00,$06
@env6:
	.byte $cb,$c8,$c6,$c5,$c2,$c0,$00,$05
@env7:
	.byte $c7,$c2,$c0,$00,$02
@env8:
	.byte $c8,$c8,$c7,$c7,$c6,$c6,$c5,$c5,$c4,$c4,$c3,$c2,$c1,$00,$0c
@env9:
	.byte $c6,$02,$c5,$02,$c4,$02,$c3,$c3,$c1,$00,$08
@env10:
	.byte $cc,$ca,$c8,$c6,$c4,$c3,$c2,$c1,$c0,$00,$08
@env11:
	.byte $c0,$05,$bf,$be,$bd,$bc,$bb,$ba,$b9,$b8,$b7,$b6,$b5,$b4,$b3,$b2
	.byte $b1,$b0,$af,$ae,$ad,$ac,$ab,$aa,$a9,$a8,$a8,$a7,$a7,$a6,$a6,$a5
	.byte $a5,$a4,$a4,$a3,$a3,$a2,$a2,$a1,$a1,$00,$28
@env12:
	.byte $c7,$c3,$c0,$bd,$00,$02
@env13:
	.byte $c0,$c0,$c4,$c4,$c7,$c7,$00,$00
@env14:
	.byte $c0,$0e,$bf,$be,$bd,$bc,$bd,$be,$bf,$c0,$00,$02
@env15:
	.byte $c0,$0f,$c1,$02,$c2,$02,$c1,$02,$c0,$c0,$c0,$00,$02


@song0ch0:
	.byte $fb,$04
@ref0:
	.byte $83,$90,$46,$83,$47,$46,$83,$38,$85,$38,$85,$34,$85,$39,$fb,$06
	.byte $83,$3e,$99,$fb,$09,$8f
@song0ch0loop:
@ref1:
	.byte $00
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@ref2:
	.byte $8e,$46,$85,$47,$47,$38,$85,$38,$85,$34,$85,$38,$85,$3e,$ad
@song0ch1loop:
@ref3:
	.byte $00
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@ref4:
	.byte $80,$46,$85,$38,$85,$34,$85,$38,$85,$3e,$8d,$42,$ad
@song0ch2loop:
@ref5:
	.byte $00
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@ref6:
	.byte $af,$8c,$08,$ad
@song0ch3loop:
@ref7:
	.byte $00
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@ref8:
	.byte $df
@song0ch4loop:
@ref9:
	.byte $81
	.byte $fd
	.word @song0ch4loop


@song1ch0:
	.byte $fb,$04
@ref10:
	.byte $00,$f9,$83
@ref11:
	.byte $01,$90,$3e,$83,$3f,$3e,$83,$38,$85,$38,$85,$34,$85,$34,$85,$38
	.byte $85,$38,$85,$3e,$85,$3e,$83,$39,$39,$34,$87,$3e,$85,$42,$85,$3e
	.byte $85,$38,$81
@ref12:
	.byte $83,$3e,$83,$3f,$3e,$83,$38,$85,$38,$85,$34,$85,$34,$85,$39,$39
	.byte $38,$8d,$38,$83,$39,$39,$34,$87,$3e,$85,$42,$85,$46,$85,$3e,$81
@song1ch0loop:
@ref13:
	.byte $92,$3e,$85,$38,$85,$34,$85,$38,$85,$3e,$85,$42,$85,$3e,$85,$38
	.byte $85,$3e,$85,$38,$85,$34,$85,$38,$85,$3e,$85,$42,$85,$46,$85,$3e
	.byte $85
@ref14:
	.byte $3e,$85,$38,$85,$34,$85,$38,$85,$3e,$85,$42,$85,$3e,$85,$38,$85
	.byte $90,$38,$8d,$38,$8d,$94,$39,$39,$3e,$85,$43,$43,$96,$42,$85
	.byte $ff,$20
	.word @ref13
	.byte $ff,$1c
	.word @ref14
@ref17:
	.byte $82,$2e,$95,$2e,$85,$34,$95,$34,$85,$38,$95,$38,$85,$3e,$95,$3e
	.byte $85
@ref18:
	.byte $3e,$8d,$38,$8d,$34,$85,$38,$8d,$38,$8d,$38,$8d,$38,$a5
@ref19:
	.byte $2e,$95,$2e,$85,$34,$95,$34,$85,$38,$95,$38,$85,$3e,$95,$3e,$85
	.byte $ff,$0e
	.word @ref18
@ref21:
	.byte $8e,$3f,$01,$3f,$00,$89,$3f,$3f,$3f,$01,$3f,$00,$89,$3f,$3f,$39
	.byte $01,$39,$01,$34,$85,$38,$8d,$3e,$95
@ref22:
	.byte $35,$01,$35,$00,$89,$35,$35,$35,$01,$35,$00,$89,$35,$35,$39,$01
	.byte $39,$01,$34,$85,$38,$8d,$3e,$85,$42,$85,$3e,$85
@ref23:
	.byte $3f,$01,$3f,$00,$89,$3f,$3f,$3f,$01,$3f,$00,$89,$3f,$3f,$39,$01
	.byte $39,$01,$34,$85,$38,$8d,$3e,$95
	.byte $ff,$1c
	.word @ref22
@ref25:
	.byte $82,$2e,$95,$2e,$85,$26,$95,$26,$85,$2a,$95,$2a,$85,$26,$95,$26
	.byte $85
@ref26:
	.byte $1c,$95,$1c,$85,$20,$95,$20,$85,$26,$85,$20,$95,$26,$8d,$2a,$8d
@ref27:
	.byte $2e,$95,$2e,$85,$26,$95,$26,$85,$2a,$95,$2a,$85,$26,$95,$26,$85
	.byte $ff,$10
	.word @ref26
	.byte $ff,$22
	.word @ref11
	.byte $fd
	.word @song1ch0loop

@song1ch1:
@ref30:
	.byte $8e,$3e,$85,$3f,$3f,$38,$85,$38,$85,$34,$85,$34,$85,$38,$85,$38
	.byte $85,$3e,$85,$3e,$85,$39,$39,$34,$85,$3e,$85,$42,$85,$3e,$85,$38
	.byte $85
@ref31:
	.byte $3e,$85,$3f,$3f,$38,$85,$38,$85,$34,$85,$34,$85,$38,$85,$38,$85
	.byte $3e,$85,$3e,$85,$39,$39,$34,$85,$3e,$85,$42,$85,$3e,$85,$38,$85
@ref32:
	.byte $3e,$85,$3f,$3f,$38,$85,$38,$85,$34,$85,$34,$85,$39,$39,$38,$8d
	.byte $38,$85,$39,$39,$34,$85,$3e,$85,$42,$85,$46,$85,$3e,$85
@song1ch1loop:
@ref33:
	.byte $8e,$3e,$8d,$38,$8d,$34,$85,$38,$8d,$3e,$8d,$42,$8d,$3e,$8d,$38
	.byte $95
@ref34:
	.byte $3e,$8d,$38,$8d,$34,$85,$38,$8d,$38,$8d,$38,$8d,$84,$34,$85,$8e
	.byte $38,$85,$84,$3e,$85,$8e,$42,$8d
@ref35:
	.byte $3e,$8d,$38,$8d,$34,$85,$38,$8d,$3e,$8d,$42,$8d,$3e,$8d,$38,$95
	.byte $ff,$14
	.word @ref34
@ref37:
	.byte $84,$46,$95,$46,$85,$4c,$95,$4c,$85,$50,$95,$50,$85,$56,$95,$56
	.byte $85
@ref38:
	.byte $56,$8d,$50,$8d,$4c,$85,$50,$8d,$38,$8d,$38,$8d,$38,$a5
@ref39:
	.byte $46,$95,$46,$85,$4c,$95,$4c,$85,$50,$95,$50,$85,$56,$95,$56,$85
	.byte $ff,$0e
	.word @ref38
@ref41:
	.byte $82,$3e,$8d,$42,$85,$3e,$8d,$38,$8d,$34,$85,$3e,$85,$3e,$85,$42
	.byte $85,$3e,$8d,$38,$95
@ref42:
	.byte $34,$85,$38,$8d,$34,$8d,$38,$8d,$3e,$8d,$38,$8d,$3e,$8d,$42,$95
@ref43:
	.byte $3e,$8d,$42,$85,$3e,$8d,$38,$8d,$34,$85,$3e,$85,$3e,$85,$42,$85
	.byte $3e,$8d,$38,$95
	.byte $ff,$10
	.word @ref42
@ref45:
	.byte $84,$46,$85,$48,$8d,$46,$a5,$46,$85,$48,$8d,$46,$8d,$42,$8d,$3e
	.byte $85
@ref46:
	.byte $87,$34,$8d,$38,$8d,$3e,$95,$3e,$85,$34,$8d,$38,$85,$42,$8d,$3e
	.byte $8d
@ref47:
	.byte $46,$85,$48,$8d,$46,$a5,$46,$85,$48,$8d,$46,$8d,$42,$8d,$3e,$85
	.byte $ff,$11
	.word @ref46
	.byte $ff,$20
	.word @ref30
	.byte $fd
	.word @song1ch1loop

@song1ch2:
@ref50:
	.byte $00,$f9,$83
@ref51:
	.byte $80,$3e,$85,$56,$85,$3e,$85,$56,$85,$3e,$85,$57,$57,$3e,$85,$57
	.byte $3f,$38,$85,$50,$85,$38,$85,$50,$85,$38,$85,$51,$51,$39,$39,$51
	.byte $38,$81
@ref52:
	.byte $34,$85,$4c,$85,$34,$85,$4c,$85,$34,$85,$4d,$4d,$34,$85,$4d,$35
	.byte $38,$85,$50,$85,$38,$85,$51,$39,$3e,$85,$57,$57,$3f,$3f,$57,$3e
	.byte $81
@song1ch2loop:
	.byte $ff,$21
	.word @ref51
	.byte $ff,$21
	.word @ref52
@ref55:
	.byte $3e,$85,$56,$85,$3e,$85,$56,$85,$3e,$85,$57,$57,$3e,$85,$57,$3f
	.byte $38,$85,$50,$85,$38,$85,$50,$85,$38,$85,$51,$51,$39,$39,$51,$38
	.byte $81
	.byte $ff,$21
	.word @ref52
@ref57:
	.byte $46,$85,$42,$85,$3e,$85,$38,$85,$3e,$85,$42,$85,$3e,$85,$38,$85
	.byte $46,$85,$42,$85,$3e,$85,$38,$85,$3e,$85,$42,$85,$46,$85,$42,$85
	.byte $ff,$20
	.word @ref57
	.byte $ff,$20
	.word @ref57
	.byte $ff,$20
	.word @ref57
	.byte $ff,$21
	.word @ref55
	.byte $ff,$21
	.word @ref52
	.byte $ff,$21
	.word @ref55
	.byte $ff,$21
	.word @ref52
	.byte $ff,$21
	.word @ref55
	.byte $ff,$21
	.word @ref52
	.byte $ff,$21
	.word @ref55
	.byte $ff,$21
	.word @ref52
@ref69:
	.byte $56,$85,$57,$57,$50,$85,$50,$85,$4c,$85,$4c,$85,$50,$85,$50,$85
	.byte $56,$85,$56,$85,$51,$51,$4c,$85,$6e,$85,$72,$85,$6e,$85,$68,$85
	.byte $fd
	.word @song1ch2loop

@song1ch3:
@ref70:
	.byte $f9,$85
@ref71:
	.byte $88,$21,$8a,$1b,$1b,$1b,$88,$21,$8a,$1b,$1b,$1b,$88,$21,$8a,$1b
	.byte $1b,$1b,$88,$21,$8a,$1b,$88,$21,$8a,$1b,$88,$21,$8a,$1b,$1b,$1b
	.byte $88,$21,$8a,$1b,$1b,$1b,$88,$21,$8a,$1b,$1b,$1b,$88,$21,$8a,$1b
	.byte $88,$21,$8a,$1a,$81
	.byte $ff,$21
	.word @ref71
@song1ch3loop:
@ref73:
	.byte $88,$21,$8a,$1b,$88,$21,$8a,$1b,$86,$21,$8a,$1b,$88,$21,$8a,$1b
	.byte $88,$21,$8a,$1b,$88,$21,$21,$86,$21,$8a,$1b,$88,$21,$8a,$1b,$88
	.byte $21,$8a,$1b,$88,$21,$8a,$1b,$86,$21,$8a,$1b,$88,$21,$8a,$1b,$86
	.byte $21,$21,$88,$21,$21,$86,$21,$21,$21,$20,$81
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
@ref81:
	.byte $88,$21,$8a,$1b,$1b,$1b,$88,$21,$8a,$1b,$1b,$1b,$86,$20,$85,$8a
	.byte $1b,$1b,$88,$21,$8a,$1b,$88,$21,$8a,$1b,$88,$21,$8a,$1b,$1b,$1b
	.byte $88,$21,$8a,$1b,$88,$21,$8a,$1b,$86,$21,$8a,$1b,$1b,$1b,$86,$21
	.byte $21,$21,$20,$81
	.byte $ff,$21
	.word @ref81
	.byte $ff,$21
	.word @ref81
	.byte $ff,$21
	.word @ref81
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
	.byte $ff,$21
	.word @ref73
@ref89:
	.byte $f9,$85
	.byte $fd
	.word @song1ch3loop

@song1ch4:
@ref90:
	.byte $f9,$85
@ref91:
	.byte $f9,$85
@ref92:
	.byte $f9,$85
@song1ch4loop:
@ref93:
	.byte $f9,$85
@ref94:
	.byte $f9,$85
@ref95:
	.byte $f9,$85
@ref96:
	.byte $f9,$85
@ref97:
	.byte $f9,$85
@ref98:
	.byte $f9,$85
@ref99:
	.byte $f9,$85
@ref100:
	.byte $f9,$85
@ref101:
	.byte $f9,$85
@ref102:
	.byte $f9,$85
@ref103:
	.byte $f9,$85
@ref104:
	.byte $f9,$85
@ref105:
	.byte $f9,$85
@ref106:
	.byte $f9,$85
@ref107:
	.byte $f9,$85
@ref108:
	.byte $f9,$85
@ref109:
	.byte $f9,$85
	.byte $fd
	.word @song1ch4loop


@song2ch0:
	.byte $fb,$06
@song2ch0loop:
@ref110:
	.byte $01,$90,$43,$43,$47,$47,$49,$49,$47,$47,$43,$43,$47,$47,$49,$49
	.byte $47,$47,$43,$43,$47,$47,$49,$49,$47,$47,$43,$43,$47,$47,$49,$49
	.byte $4c,$81
@ref111:
	.byte $4d,$43,$43,$47,$47,$49,$49,$47,$47,$43,$43,$47,$47,$49,$49,$47
	.byte $47,$43,$43,$47,$47,$49,$49,$47,$47,$43,$46,$85,$48,$85,$46,$85
@ref112:
	.byte $92,$4d,$43,$43,$4d,$43,$43,$4d,$43,$47,$43,$43,$47,$43,$43,$47
	.byte $43,$49,$43,$43,$49,$43,$43,$49,$43,$47,$43,$43,$47,$43,$43,$47
	.byte $42,$81
@ref113:
	.byte $49,$43,$43,$49,$43,$43,$49,$43,$49,$43,$43,$49,$43,$43,$49,$43
	.byte $4d,$43,$43,$4d,$43,$43,$4d,$43,$51,$43,$43,$51,$43,$43,$51,$42
	.byte $81
@ref114:
	.byte $2b,$2b,$2f,$30,$85,$2e,$85,$2f,$2b,$2b,$2f,$30,$85,$2e,$85,$2b
	.byte $2f,$2f,$31,$34,$85,$30,$85,$2b,$2f,$2f,$31,$34,$85,$30,$89
@ref115:
	.byte $82,$38,$89,$34,$b1,$38,$89,$3a,$89,$38,$a5
@ref116:
	.byte $92,$2b,$2b,$2f,$30,$85,$2e,$85,$2f,$2b,$2b,$2f,$30,$85,$2e,$85
	.byte $2b,$2f,$2f,$31,$34,$85,$30,$85,$2b,$2f,$2f,$31,$34,$85,$30,$89
	.byte $ff,$0a
	.word @ref115
	.byte $fd
	.word @song2ch0loop

@song2ch1:
@song2ch1loop:
@ref118:
	.byte $8e,$43,$43,$47,$47,$49,$49,$47,$47,$43,$43,$47,$47,$49,$49,$47
	.byte $47,$43,$43,$47,$47,$49,$49,$47,$47,$43,$43,$47,$47,$49,$49,$4d
	.byte $4c,$81
@ref119:
	.byte $43,$43,$47,$47,$49,$49,$47,$47,$43,$43,$47,$47,$49,$49,$47,$47
	.byte $43,$43,$47,$47,$49,$49,$47,$47,$43,$46,$85,$48,$85,$46,$89
@ref120:
	.byte $43,$01,$43,$01,$47,$43,$01,$43,$01,$43,$01,$43,$47,$43,$47,$43
	.byte $43,$01,$43,$01,$47,$43,$01,$43,$01,$43,$01,$43,$47,$43,$47,$48
	.byte $81
	.byte $ff,$21
	.word @ref120
@ref122:
	.byte $42,$8d,$43,$46,$85,$48,$89,$46,$85,$43,$46,$85,$42,$91,$43,$46
	.byte $85,$48,$89,$46,$85,$49,$4c,$89
@ref123:
	.byte $50,$89,$4c,$b1,$50,$89,$52,$89,$50,$a5
	.byte $ff,$18
	.word @ref122
	.byte $ff,$0a
	.word @ref123
	.byte $fd
	.word @song2ch1loop

@song2ch2:
@song2ch2loop:
@ref126:
	.byte $80,$43,$5b,$5b,$43,$5b,$5b,$43,$5b,$47,$47,$5f,$47,$47,$5f,$47
	.byte $5f,$49,$49,$61,$49,$49,$61,$49,$61,$4d,$4d,$65,$4d,$4d,$65,$4d
	.byte $64,$81
@ref127:
	.byte $43,$5b,$5b,$43,$5b,$5b,$43,$5b,$47,$47,$5f,$47,$47,$5f,$47,$5f
	.byte $49,$49,$61,$49,$49,$61,$49,$61,$4d,$4d,$65,$4d,$4d,$65,$4d,$64
	.byte $81
@ref128:
	.byte $2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$2b,$43,$2b
	.byte $2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$2f,$47,$2e
	.byte $81
@ref129:
	.byte $31,$31,$31,$31,$31,$31,$31,$31,$31,$31,$31,$31,$31,$31,$49,$31
	.byte $35,$35,$35,$35,$35,$35,$35,$35,$35,$35,$4d,$35,$35,$4d,$35,$4c
	.byte $81
	.byte $ff,$21
	.word @ref128
	.byte $ff,$21
	.word @ref129
	.byte $ff,$21
	.word @ref128
	.byte $ff,$21
	.word @ref129
	.byte $fd
	.word @song2ch2loop

@song2ch3:
@song2ch3loop:
@ref134:
	.byte $f9,$85
@ref135:
	.byte $f9,$85
@ref136:
	.byte $88,$21,$21,$86,$21,$8a,$1b,$88,$21,$8a,$1b,$86,$21,$8a,$1b,$88
	.byte $21,$8a,$1b,$86,$21,$88,$20,$20,$86,$21,$21,$88,$21,$8a,$1b,$88
	.byte $21,$8a,$1b,$86,$21,$88,$20,$20,$86,$21,$8a,$1b,$88,$21,$21,$86
	.byte $21,$21,$88,$21,$21,$86,$21,$21,$21,$20,$81
	.byte $ff,$23
	.word @ref136
	.byte $ff,$23
	.word @ref136
	.byte $ff,$23
	.word @ref136
	.byte $ff,$23
	.word @ref136
	.byte $ff,$23
	.word @ref136
	.byte $fd
	.word @song2ch3loop

@song2ch4:
@song2ch4loop:
@ref142:
	.byte $f9,$85
@ref143:
	.byte $f9,$85
@ref144:
	.byte $f9,$85
@ref145:
	.byte $f9,$85
@ref146:
	.byte $f9,$85
@ref147:
	.byte $f9,$85
@ref148:
	.byte $f9,$85
@ref149:
	.byte $f9,$85
	.byte $fd
	.word @song2ch4loop