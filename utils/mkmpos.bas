Dim As String list
Dim Shared As String tokens (15)
Dim As Integer i

Sub parseList (list As String) 
	Dim As Integer ti, i
	Dim As String m
	ti = 0
	list = list & ","
	For i = 1 To Len (list)
		m = Mid (list, i, 1)
		If m = "," Then
			If tokens (ti) = "" Then tokens (ti) = "0"
			If ti < 15 Then ti = ti + 1: tokens (ti) = ""
		Else
			tokens (ti) = tokens (ti) & m
		End If
	Next i
End Sub

? "This simple program outputs a 16 array of tile offsets from a list of tiles"
? "you enter. Tiles must be 0-47, comma separated."
? "Copy/Paste the printout, directly usable by the Vostok Engine MK2."
Line Input list

parseList (list)

For i = 0 To 15
	Print "0x" & Hex ((Val (tokens (i)) + 16) * 4, 2);
	If i < 15 Then Print ", ";
Next i
Print
