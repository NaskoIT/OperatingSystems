### VI cheat cheat
G - go to the end
gg - go to the beginning
150G - go to line 150
: set number - номериране на редовете в редактора
: set nonumber - махане на номерата на редовете в редактора
/ pattern - търсене
n - go to the next match
:q - close the editor
vi +4801 services - go directly to a particular row
vi +/VNC services - go directly to a particular row containing the string
:%s/tcp/TCP/g - change all occurrences of tcp to TCP
u - undo change
:w services-modified.txt - Save the modified file to another file, like save as
:r /etc/hostname - insert the contents of external file. For example, insert the /etc/hostname file
:r ! uname -a - insert the result from a command’s execution
:1,100w services-100.txt - save the first 100 lines in a separate file
:q! - close the file without saving the changes
