# NoteCompress
A Project trying to make text unreadable for Humans and shorter but eas to Read with Tricks.

It uses a custom Base64 Algorithm.
To encode a String make every char to a binary
' ' to 00000
'A' to 00001
'B' to 00010
'C' to 00011
...
'Z' to 11010
'0' to 11011 //Reserved 0-3
'1' to 11100
'2' to 11101
'3' to 11110
'.' to 11111
Put the binary numbers Together
With 'WITH' you have something like:
10111 01001 10100 01000

Then Look at this Base64 Table and translate every 6 Bizs to a Letter.
| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

 
 Then encode this binary
