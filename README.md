# NoteCompress
A Project trying to make text unreadable for Humans and shorter but eas to Read with Tricks.
It uses a custom Base64 Algorithm.
To encode a String make every char to a binary

Char | Binär | Dezimal
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
With 'WITH' you have something like:
10111 01001 10100 01000

Then Look at this Base64 Table and translate every 6 Bizs to a Letter.

Markdown | Less | Pretty
--- | --- | ---
*Still* | `renders` | **nicely**
1 | 2 | 3
 
 Then encode this binary
