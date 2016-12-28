Dim i As Integer
Dim d As uByte

'' Fixes this - temporal
open "pongpong.map" for binary as #1
open "pongfix.map" for binary as #2

' first three strips as is
for i=1 to 256*10*3
	Get #1,,d
	Put #2,,d
Next i

' Fourth strip, 12345 -> +48
For i=1 to 256*10
	Get #1,,d
	If d=14 Or (d>=0 And d<=5) Then d=d+48
	Put #2,,d
Next i
Close
? "DONE"
