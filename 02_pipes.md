03-a-0200.txt:
Сортирайте /etc/passwd лексикографски по поле UserID.
```cat /etc/passwd | sort -t ":" -k 3```

03-a-0200.txt:
Сортирайте /etc/passwd числово по поле UserID.
```cat /etc/passwd | sort -t ":" -nk 3```

03-a-0210.txt:
Изведете само 1-ва и 5-та колона на файла /etc/passwd спрямо разделител ":".
```cat /etc/passwd | cut -d ":" -f 1,5```

03-a-0211.txt:
Изведете съдържанието на файла /etc/passwd от 2-ри до 6-ти символ.
```cat /etc/passwd | head -c 7 | tail -c 6```

03-a-0212.txt:
Отпечатайте потребителските имена и техните home директории от /etc/passwd
```cat /etc/passwd | cut -d ":" -f 1,6 | tr ":" "\t"```

03-a-0213.txt:
Отпечатайте втората колона на /etc/passwd, разделена спрямо символ '/'.
```cat /etc/passwd | cut -d "/" -f 2``` 

03-a-1500.txt:
3 lines (3 sloc)  197 Bytes
Изведете броя на байтовете в /etc/passwd.
Изведете броя на символите в /etc/passwd.
Изведете броя на редовете  в /etc/passwd.
```cat /etc/passwd | wc -cml```

03-a-2000.txt: 
С отделни команди, извадете от файл /etc/passwd:
- първите 12 реда
- първите 26 символа
- всички редове, освен последните 4
- последните 17 реда
- 151-я ред (или друг произволен, ако нямате достатъчно редове)
- последните 4 символа от 13-ти ред (символът за нов ред не е част от реда)
```
cat /etc/passwd | head -n 12
cat /etc/passwd | head -c 26
cat /etc/passwd | head -n -4
cat /etc/passwd | tail -n 4
cat /etc/passwd | head -n 151 | tail -n 1
cat /etc/passwd | head -n 13 | tail -n 1 | tail -c 4
```

03-a-3000.txt: 
Запаметете във файл в своята home директория резултатът от командата `df -P`.
Напишете команда, която извежда на екрана съдържанието на този файл, без първия ред (хедъра), сортирано по второ поле (numeric).
```
df -P > 03-a-3000
cat 03-a-3000 | tail -n +2 | sort -n -k 2
```

03-a-3100.txt
Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.
```cat /etc/passwd | cut -d ":" -f 1```

               
03-a-5000.txt: 
Изведете реда от /etc/passwd, на който има информация за вашия потребител.
Изведедете този ред и двата реда преди него.
Изведете този ред, двата преди него, и трите след него.
Изведете *само* реда, който се намира 2 реда преди реда, съдържащ информация за вашия потребител.
```
grep "$(whoami)" /etc/passwd
egrep -n "$(whoami)" /etc/passwd | cut -d ":" -f 1 | xargs -I {} expr {} - 1 | xargs -I {} head -n {} /etc/passwd | tail -2
egrep -n "$(whoami)" /etc/passwd | cut -d ":" -f 1 | xargs -I {} expr {} + 3 | xargs -I {} head -n {} /etc/passwd | tail -6
egrep -n "$(whoami)" /etc/passwd | cut -d ":" -f 1 | xargs -I {} expr {} - 1 | xargs -I {} head -n {} /etc/passwd | tail -1
```
               
03-a-5001.txt:
Изведете колко потребители не изпозват /bin/bash за login shell според /etc/passwd
(hint: 'man 5 passwd' за информация какъв е форматът на /etc/passwd)
```cat /etc/passwd | cut -d ":" -f 7 | egrep -v "/bin/bash" | wc -l```

03-a-5002.txt:
Изведете само имената на хората с второ име по-дълго от 6 (>6) символа според /etc/passwd
```cat /etc/passwd | cut -d ":" -f 5 | egrep -o " [^,]*" | tr -d " " | egrep "^.{7,}$"```

03-a-5003.txt:
Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?
```cat /etc/passwd | cut -d ":" -f 5 | egrep -o " [^,]*" | tr -d " " | egrep -v "^.{,7}$"```

03-a-5004.txt
Изведете целите редове от /etc/passwd за хората от 03-a-5003
```cat /etc/passwd | cut -d : -f 5 | egrep -o " [^,]*" | egrep "^.{8,}$" | xargs -I {} grep "{}" /etc/passwd```

03-b-0300.txt:
Намерете само Group ID-то си от файлa /etc/passwd.
```egrep "$(whoami)" /etc/passwd | cut -d ":" -f 4```

03-b-3400.txt
Колко коментара има във файла /etc/services ? Коментарите се маркират със символа #, след който всеки символ на реда се счита за коментар.
```grep "^#" /etc/services | wc -l```

03-b-3500.txt
Колко файлове в /bin са 'shell script'-oве? (Колко файлове в дадена директория са ASCII text?)
```find ~ -type f 2>/dev/null | xargs egrep "^#!" | wc -l```

03-b-3600.txt:
Направете списък с директориите на вашата файлова система, до които нямате достъп. Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина.
```find / -maxdepth 3 -type d 2>/dev/null | cut -d ":" -f 2```

03-b-4000.txt:
Изведете на екрана:
	* статистика за броя редове, думи и символи за всеки един файл
	* статистика за броя редове и символи за всички файлове
	* общия брой редове на трите файла
```wc file{1..3}```

03-b-4001.txt
Във file2 (inplace) подменете всички малки букви с главни.
```cat file2 | tr [a-z] [A-Z]```

03-b-4002.txt:
Във file3 (inplace) изтрийте всички "1"-ци.
```cat file3 | sed -e 's/1//g;/^$/d'```

03-b-4003.txt:
Изведете статистика за най-често срещаните символи в трите файла.
```cat file{1..3} | sed -e "s/./\0\n/g" | sed "/^$/d" | sort | uniq -c```

03-b-4004.txt:
Направете нов файл с име по ваш избор, чието съдържание е конкатенирани
съдържанията на file{1,2,3}.
```cat file{1..3} > concat_file.txt```

03-b-4005.txt:
Прочетете текстов файл file1 и направете всички главни букви малки като
запишете резултата във file2.
```cat file1 | tr [a-z] [A-Z] >> file2```

03-b-5200.txt:
Намерете броя на символите, различни от буквата 'а' във файла /etc/passwd
```cat /etc/passwd | tr -d "a" | wc -m```

03-b-5300.txt
Намерете броя на уникалните символи, използвани в имената на потребителите от
/etc/passwd.
```cat /etc/passwd | cut -d : -f 5 | sed 's/./\0\n/g' | sort -u | wc -l```

03-b-5400.txt:
Отпечатайте всички редове на файла /etc/passwd, които не съдържат символния низ 'ов'.
```egrep --color -v "ov" /etc/passwd```

03-b-6100.txt
Отпечатайте последната цифра на UID на всички редове между 28-ми и 46-ред в /etc/passwd.
```cat /etc/passwd | head -n 46 | tail -n 18 | cut -d : -f 3 | grep -o "[[:digit:]]$"```

03-b-6700.txt
Отпечатайте правата (permissions) и имената на всички файлове, до които имате
read достъп, намиращи се в директорията /tmp. (hint: 'man find', вижте -readable)
find /tmp -type f -printf "%m %p\n" -readable 2>/dev/null

03-b-6900.txt:
Намерете имената на 10-те файла във вашата home директория, чието съдържание е
редактирано най-скоро. На първо място трябва да бъде най-скоро редактираният
файл. Намерете 10-те най-скоро достъпени файлове. (hint: Unix time)
```find ~ -type f -printf "%A@ %p \n" | sort -nr | tail -10 | cut -d " " -f 2```

03-b-7000.txt
да приемем, че файловете, които съдържат C код, завършват на `.c` или `.h`.
Колко на брой са те в директорията `/usr/include`?
Колко реда C код има в тези файлове?
```
find /usr/include -type f -name *.[ch] 2>/dev/null | wc -l
find /usr/include -type f -name *.[ch] 2>/dev/null | xargs cat | wc -c
```

03-b-7500.txt
Даден ви е ASCII текстов файл - /etc/services. Отпечатайте хистограма на 10-те най-често срещани думи.
Дума наричаме непразна последователност от букви. Не правим разлика между главни и малки букви.
Хистограма наричаме поредица от редове, всеки от които има вида:
<брой срещания> <какво се среща толкова пъти>
```grep -oE "[a-zA-Z]+" /etc/services | sort | uniq -c | sort -nr | head -n 10```

03-b-8000.txt
Вземете факултетните номера на студентите (описани във файла
https://github.com/avelin/fmi-os/blob/master/exercises/exercises/data/mypasswd.txt) от СИ и ги запишете във файл si.txt сортирани.
Студент е част от СИ, ако home директорията на този потребител (според
https://github.com/avelin/fmi-os/blob/master/exercises/exercises/data/mypasswd.txt) се намира в /home/SI директорията.

```grep "/home/SI" users.txt | cut -d ":" -f 1 | grep -o "[[:digit:]]*" | sort -n > si.txt```

03-b-8500.txt
За всяка група от /etc/group изпишете "Hello, <група>", като ако това е вашата група, напишете "Hello, <група> - I am here!".
```cut -d : -f 1 /etc/group | awk -v group=students '{if($0 != group) print "Hello, "$0; else print "Hello, "$0" - it is me!"}'```

03-b-8600.txt
Shell Script-овете са файлове, които по конвенция имат разширение .sh. Всеки
такъв файл започва с "#!<interpreter>" , където <interpreter> указва на
операционната система какъв интерпретатор да пусне (пр: "#!/bin/bash",
"#!/usr/bin/python3 -u").

Намерете всички .sh файлове в директорията `/usr` и нейните поддиректории, и
проверете кой е най-често използваният интерпретатор.
```find /usr -type f -name "*.sh" 2>/dev/null | xargs -I {} head {} -n 1 | egrep "^#!" | sed "s/#\!//g;s/^ //g" | sort | uniq -c```

03-b-8700.txt
1. Изведете GID-овете на 5-те най-големи групи спрямо броя потребители, за които
съответната група е основна (primary).

2. (*) Изведете имената на съответните групи.

Hint: /etc/passwd
```cat /etc/passwd | cut -d : -f 4 | sort -n | uniq -c | sort -nrk 1 | head -n 5 | awk -F " " '{print $2}' | xargs -I @ egrep "^([^:]*:){2}@:" /etc/group | cut -d ":" -f 1```

03-b-9000.txt
Направете файл eternity. Намерете всички файлове, намиращи се във вашата home
директория и нейните поддиректории, които са били модифицирани в последните
15мин (по възможност изключете .).  Запишете във eternity името (път) на
файла и времето (unix time) на последната промяна.
```find ~ -type f -mmin 15 2>/dev/null```

