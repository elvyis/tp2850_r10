#$language = "VBScript"
#$interface = "1.0"

crt.Screen.Synchronous = True

' This automatically generated script may need to be
' edited in order to work correctly.

Sub Main
	crt.Screen.Send "scanoff" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 40 00" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 4e 00" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 40 08" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 01 f8" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 02 01" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 08 03" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 20 12" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 39 00" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 23 02" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 13 04" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 14 46" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 15 09" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 25 08" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 26 01" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 27 0e" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 10 88" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 10 08" & chr(13)
	crt.Screen.WaitForString "I2C[88]>"
	crt.Screen.Send "w 23 00" & chr(13)
End Sub
