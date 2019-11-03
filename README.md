# NoteCompress
A Project trying to make text unreadable for Humans and shorter but eas to Read with Tricks.
It uses a custom Base64 Algorithm.
## Encode
To encode a String make every char to a binary

Char | Binary | Decimal
--- | --- | ---
' ' | 00000 | 0
'A' | 00000 | 1
'B' | 00001 | 2
'C' | 00010 | 3
'D' | 00011 | 4
...
'Z' | 11010 | 26
'0' | 11011 | 27
'1' | 11100 | 28
'2' | 11101 | 29
'3' | 11110 | 30
'.' | 11111 | 31

Put the binary numbers Together
With 'WITHS' you have something like:

10111 01001 10100 01000 10011

Then Look at this Base64 Table and translate every 6 Bits to a Letter.

Char | Binary | Decimal
--- | --- | ---
'A' | 000000 | 0
'B' | 000001 | 1
'C' | 000010 | 2
...
'X' | 010111 | 23
'Y' | 011000 | 24
'Z' | 011001 | 25
'a' | 011010 | 26
'b' | 011011 | 27
'c' | 011100 | 28
...
'x' | 110010 | 49
'y' | 110011 | 50
'z' | 110100 | 51
'0' | 110101 | 52
'1' | 110110 | 53
...
'8' | 111100 | 60
'9' | 111101 | 61
'-' | 111110 | 62
'/' | 111111 | 63
 
101110 | 100110 | 100010 | 001001 | 1*00000*
--- | --- | --- | --- | ---
u | m | i | J | g

Fill the rest with Zeros if you add 5 Zeros add a '=' to the and to indicate that you have added a Letter.

You have encoded the String to **umiJg=**
## Decode
Make the Encode Section Backwards.
