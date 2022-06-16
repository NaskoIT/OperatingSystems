### Establish SSH connection with other machine
```ssh -p 22 username@server_name```

### Transfer file from remote server to the local computer
```scp -P 22 s62577@astero.openfmi.net:/home/students/s62577 source_file_path destination_path```

### Transfer file from local computer to remote server
```scp -P 22 readme.txt s62577@astero.openfmi.net:/home/students/s62577```

### Shortcuts
Alt + D - delete the rest of the current word
Alt + Backspace - delete the whole previous word
Ctrl + U - erase from cursor to beginning of the line
Ctrl + K - erase from cursor to end on the line
Ctrl + A or Home - Move to the beginning of the line
Ctrl + E or End - Move the cursor to the end of the line
Alt + B - move left (backward) one word
Alt + F - move right (forward) one word