 # Awk cheat sheet

### Simple examples
* Just try the examples by yourself
```bash
awk -F ":" '{print $1}' /etc/passwd # print all the usernames 
awk -F ":" '{print $1 " -> " $3 " with home directory: " $6 }' /etc/passwd
# FS - File separator, OFS - Output file separator
awk 'BEGIN {FS=":"; OFS="_"} {print $1, $3}' /etc/passwd

# print username and shell ($NF - get the last column) of the lines starting with s625
awk -F ":" '/^s625/ {print $1, $NF}' /etc/passwd 

# get all the shells of the users, $NF ~ /^\// - the last column match the pattern (the last column starts with \), NF - Number of fields
awk -F ":" '$NF ~ /^\// {print $NF}' /etc/passwd | sort | uniq 

# we can make arithmetic operations in awk ($2 + $3)
df | awk '/^\/dev/ {print $1 " -> " $2 + $3}'

# skip comments and get all the shells witch path length is more than 8 symbols
awk '$0 !~ /^#/ && length($0) > 8 {print}' /etc/shells | sort | uniq

awk -F "/" '$0 !~ /^#/ && length($NF) > 3 {print $0 " -> " $NF}' /etc/shells | sort | uniq

# the first column match the regex pattern (starts with s625[5 or 7][any digit][5, 6 or 7])
awk '$1 ~ /s62[57][0-9][5-7]/ {print $0}' /etc/passwd

# substring example
awk '{print substr($0, 2, 5)}' /etc/passwd

# RSTART - the place of the first match (the leftmost)
awk 'match($1, /0/) {print $0 " has \"0\" at " RSTART}' /etc/passwd

# NR - Number of records
awk 'NR == 7, NR == 11 {print NR, $0}' /etc/passwd

# print the number of records
awk 'END { print NR }' /etc/passwd

awk 'BEGIN {printf("Arguments count: %s\nFirst argument: %s\nSecond argument: %s\n", ARGC, ARGV[0], ARGV[1])}' /etc/passwd
```

### If statements
* !~ /pattern/ - not matched by the pattern
* <, >, <=, >=, ==, !=, !variable 
```bash
echo -e "45\n0\n-45" | awk '{
    message = ""; 
    if ($0 > 0) message = "Positive"; 
    else if ($0 < 0) message = "Negative"; 
    else message = "Zero"; 
    printf("%d -> %s\n", $0, message) 
}' numbers.txt
awk 'BEGIN {
    msg = "message";
    empty = "";
    zero = 0;
    nonZero = 1; 
    if (msg) print msg; 
    if (empty) print empty; 
    if (zero) print "zero"; 
    if (nonZero) print awk"non-nero"
}'
```

### Loops
```bash
awk 'BEGIN { for(i = 1; i <= 10; i++) printf("Square root of: %d is: %d\n", i, i * i) }'
```

### Set external variables
```bash
condition=45
message="Awk is very powerful"
# define variable from the environment in awk (how to use $condition and $message in the awk code)
awk -v "value=${condition}" -v "msg=${message}" '{ if(value == 45) print msg }' file_path # Awk is very powerful
```
### Built-in constants
* FS - file separator
* OFS - output file separator
* NF - number of fields
* NR - number of records
* ARGC - number of command line arguments
* ARGV - array of command line arguments
* RLENGTH - length if the matched string
* RS - control the input records separator
* RSTART - start of the matched string
```bash
awk -F ":" 'BEGIN { print "FS " FS ", OFS:" OFS ", ARGC: " ARGC} match($1, /s62577/) {print RLENGTH, RSTART}' /etc/passwd
awk 'BEGIN {RS=":"} {print $0}' /etc/passwd
```

### Built-in functions
* int(x) - get the integer part of x
* rand() -  random number r, where 0 <= r < 1
* sqrt(x)
* gsub(r, s) - substitute s for r globally in $0
* gsub(r, s, t) - substitute s for r globally in t
* index(s, t) - return first position of t in s or 0 if not present
* length(s)
* match (s, r) - return index or 0; set RSTART  and RLENGTH
* split (s, a) - split s  into array a on FS; return the number of fields
* split (s, a, fs) - splts s into array a on fs; return the number of fields
* sprintf (fmt, expr-list) - format the string and returns the result
* sub(r, s) - substitute s for the leftmost longest substring of $0 matched by r; return number of substitutions made
* substr (s, p, n)
```bash
echo "replace me" | awk '{ gsub("replace", "insert"); print $0}'
awk 'BEGIN { print int(5.5), int(5.25), int (5.6)}'
awk 'BEGIN {print index("awk is powerful", "is"), index("awk", "it")}'
awk 'BEGIN {print length("nasko.it")}'
awk 'BEGIN {print match("nasko.it", /\.it/)}'
# index starts from 1 (the only thing I do not like in awk :))
awk 'BEGIN { 
    len = split("Atanas Biserov Vasilev", name); 
    for (i = 1; i <= len; i++) print name[i]
}'
awk 'BEGIN { 
    len = split("10,20,30,40,50", num, ","); 
    sum=0; 
    for (i = 1; i <= len; i++) 
        sum += num[i]; 
    print sum
}'
awk 'BEGIN {grade = 5.2; message = sprintf("%s has %.2f", "Pesho", grade);} $0=="no match" {print} END {print message}' /etc/passwd
awk 'BEGIN {print substr("nasko.it", 7)}'
awk 'BEGIN {print substr("nasko.it", 1, 5)}'
awk '{gsub(/s[0-9]{5}/, "******"); print}' /etc/passwd
```

### Common utilities
* print expression, expression - separated by OFS and terminated by ORS
* printf(format, expression, expression) > fileName
* %c - character
* %d - decimal integer
* % f - floating-point number
```bash
# remove leading whitespace
echo -e "20\n50\n20" | uniq -c | awk '{$1=$1; print}'
# предпоследната колона
awk -F ":" '{print $(NF + 1)}' /etc/passwd
```

### Execute commands
```bash
# print how many active processes has each of the users
awk -F ":" '{
    cmd = "ps -u "$1 " | wc -l"; 
    cmd | getline processesCount; 
    close(cmd); 
    print $1 " -> " processesCount}' /etc/passwd

# execute system call -> 0 if successful and 1 if not successful
awk 'BEGIN { 
    result = system("echo 45 | egrep -q \"^[0-9]+$\""); 
    print result 
}'

awk 'BEGIN {
       cmd = "date -j -f %s"
       cmd | getline mydate
       close(cmd)
}'

awk 'BEGIN { 
    result = system("test -d /home/students/s62577/"); 
    print result
}'

find /home/students -type l 2>/dev/null | xargs ls -l | awk '
{
    res=system("test -e " $11); 
    if (res != 0) 
    print $9
}'
```

### Functions
```bash
awk -F ":" '
function getUser(username, id) { 
    return username " -> " id } 
    BEGIN {
        print "Username Id"
    } 
    {
        print getUser($1, $3)
    } 
    END {
        print "All printed"
}' /etc/passwd
```

### Arrays
* associative arrays
* arr["key"] = "value"
* arr[1] = 45
* for (key in arr) ...
* if(key in arr) ...
* delete arr[key]
```bash
awk -F ":" '{used[$1] = 1} END {print length(used)}' /etc/passwd

awk '
function getName(first, last) { 
    return sprintf("%s_%s", first, last) 
} 
BEGIN {
    duplicates = 0 
} 
$1 != "FirstName" { 
    key=getName($1, $2); 
    if (key in used) {
        duplicates++; 
    } 
    else { 
        used[key]=1
    } 
} END {
    message = duplicates > 0 ? "Yes" : "No"; 
    printf("%s. There are %d people out of %d with identical names\n", message, duplicates, NR)
}' payroll.tsv 
```