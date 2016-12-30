' MAPCNV NES
' Converts a Mappy layer to a suitable-scrollable, Churrera-NES map.
'
' Format is:
' Map is divided in "MapChunks". 
' Each MapChunk is 15 bytes:
' 10 bytes for 20 tiles:
' 0001  00
' 0203  01
' 0405  02
' 0607  03
' 0809  04
' 0A0B  05
' 0C0D  06
' 0E0F  07
' 1011  08
' 1213  09

' ...
' 5 bytes for 5 attributes [optional]
' Each attribute contains palettes for 4 tiles, top to bottom
'
' Each tile palete is stored in pallist.txt

Type BOLT
    x as Integer
    y as Integer
End Type

Type OBJ
    x as integer
    y as integer
    t as integer
end type

Dim As Integer x, y, xx, yy, f1, f2, i, j, k
Dim As Integer wt, hs, rhs, rws
Dim As String mapFileName, palString, o
Dim As uByte orgMap(512, 512), d, by
Dim As uByte pal(127)
Dim As BOLT bolts(10,512)
Dim As OBJ objs(10,512)

If Command(1) = "" Or _
    Val(Command(2)) = 0 Or Val(Command(3))=0 Then
    Print "mapcnvnes mapfile w_t h_s [noattrs]"
    Print "   w_t: Width in tiles."
    Print "   h_s: Height in stripes."
    Print "Produces map.bin and map.h"
    System
End If

for y = 0 to 10: for x = 0 To 512
    objs(y,x).x=255
    bolts(y,x).x=255
    objs(y,x).y=255
    bolts(y,x).y=255
next x: next y

' Read pal
f1 = FreeFile
Open "pallist.txt" For Input as #f1
    Line Input #f1, palString
    For i = 1 To Len(palString)
        pal (i-1) = val (Mid (palString, i, 1))
    Next i
Close #f1

If Command (4) = "noattrs" Then
    f1 = FreeFile
    Open "precalcs.h" For Output As #f1
    Print #f1, "const unsigned char precalc_attr_bits [] = {"
    For i = 0 To Len (palString) - 1 Step 16
        For j = 0 To 3
            Print #f1, "    ";
            For k = 0 To 15
                Print #f1, "0x" & Hex (pal (i + k) Shl (j + j), 2);
                If k < 15 Or j < 3 Or i < (Len (palString) - 16) Then
                    Print #f1, ", ";
                End If
            Next k
            Print #f1, ""
        Next j
    Next i
    Print #f1, "};"
    Close #f1
End If

mapFileName = Command(1)
wt = Val (Command(2)) - 1
hs = Val (Command(3)) - 1
rhs = (10 * Val (Command(3))) - 1

f1 = FreeFile
Open mapFileName For Binary as #f1

' First read map
For y = 0 to rhs
    For x = 0 To wt
        Get #f1, , d
        orgMap (y, x) = d
    
    Next x
Next y

Close #f1

f2 = FreeFile
Open "map.bin" For Binary as #f2

For y = 0 to hs

    For x = 0 To wt Step 2
        ' Chunk. First, 20 tiles:    
        ' Column 1
        For yy = 0 To 9
            d = orgMap (10 * y + yy, x) And 15
            by = d Shl 4
        
            ' Column 2
            d = orgMap (10 * y + yy, x + 1) And 15
            by = by Or d
            Put #f2, , by
        Next yy
        
        If Command (4) = "noattrs" Then
        Else
            ' Next, 5 attributes
            For yy = 0 To 9 Step 2
                ' ab
                ' cd
                ' attr = dcba
                d = 0
                d = d + pal (orgMap (10 * y + yy, x))
                d = d + (pal (orgMap (10 * y + yy, x + 1)) Shl 2)
                d = d + (pal (orgMap (10 * y + yy + 1, x)) Shl 4)
                d = d + (pal (orgMap (10 * y + yy + 1, x + 1)) Shl 6)
                Put #f2, , d
            Next yy
        End If
    Next x

Next y

Close #f2

Print "map.bin generated."

' Generate map.h
f1 = FreeFile
Open "map.bin" For Binary as #f1
f2 = FreeFile
Open "map.h" For Output as #f2

i = 0
o = ""
Print #f2, "const unsigned char map[] = {"
While Not Eof (f1)
    i = i + 1
    Get #f1, , d
    o = o + "0x" + Hex (d, 2)
    o = o + ", "
    If i = 15 Then 
        If Eof (f1) Then o = left(o, len(o)-2)
        Print #2, "    " + o
        o = ""
        i = 0
    End If
Wend
If o <> "" Then o = left(o, len(o)-2):Print #2, "    " + o
Print #f2, "};"
Print "map.h generated."

Close #f1, #f2

