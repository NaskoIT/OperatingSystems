 # Awk cheat sheet

### Set external variables
```bash
condition=45
message="Awk is very powerful"
# define variable from the environment in awk (how to use $condition and $message in the awk code)
awk -v "value=${condition}" -v "msg=${message}" '{ if(value == 45) print msg }' file_path # Awk is very powerful
```
// TODO: to be continued