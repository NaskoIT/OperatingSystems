# Editors files and streams
1.	```cp /etc/services .```
2.	``` grep ^# services > services_comments.txt```
3.	```grep -E ^[^#] services > services_wo_comments.txt```
4.	```grep -E ^[^#] services | grep udp > services_udp.txt```
5.	```vi services_wo_comments.txt```
6.	```/socks```
7.	```dG```
8.	```:w well-known-ports.txt```
9.	```:q!```
10.	```sed -n '1,100s/\//-/pg' well-known-ports.txt > 100-well-known-ports.txt```
11.	```cat > doc1.txt << EOF```
``` 10-IT-HQ
> 20-Accounting-HQ
> 30-Help-Desk-Remote
> 40-Sales-HQ
> EOF
```
12. ```echo "10-B.Thomas" > doc2.txt ; echo "20-J.Foster" >> doc2.txt ; echo "30-G.Smith" >> doc2.txt ; echo "40-F.Hudson" >> doc2.txt```
13. ```join -t - -j 1 doc1.txt doc2.txt > doc3.txt```
14. ```cut -d - -f 3 doc3.txt | sort | uniq > locations.txt```
15. ```cut -d - -f 3 doc3.txt | sort -u | wc -l```
16. ```sudo find /etc -type f -size -200c -exec ls {} \; | sort > small-etc-files.txt```
