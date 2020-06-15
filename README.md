LSS
===

A small C program to list simple solutions (LSS) for the sum of three cubes: x³ + y³ + z³ = n

NOTE: n < 1000 and x,y,z < 100000, solutions formatted to be: x <= y <= z

Installation
------------
Perform the following steps, please:

1. git clone https://github.com/fleschutz/LSS ; cd LSS

2. gcc -O3 -fopenmp main.c (for GCC compiler) or: clang -O3 -fopenmp main.c (for CLANG compiler)

3. ./a.out > out.txt

4. sort -g out.txt > list.txt

Now, see list.txt for the resulting simple solutions.


Currently known complicated solutions
-------------------------------------
* 30 = 3982933876681³ − 636600549515³ − 3977505554546³
* 33 = 88661289752875283³ − 87784054428622393³ − 27361114688070403³
* 42 = -80538738812075974³ + 80435758145817515³ + 1260212329733563³ 
* 52 = 60702901317³ + 23961292454³ − 61922712865³
* 165 = (-385495523231271884)³ + 383344975542639445 + 98422560467622814³
* 906 = (−74924259395610397)³ + 72054089679353378³ + 35961979615356503³


Currently unsolved solutions
----------------------------
* 114 = ?
* 390 = ?
* 579 = ?
* 627 = ?
* 633 = ?
* 732 = ?
* 795 = ?
* 921 = ?
* 975 = ?

Links
-----
* [More interesting projects](http://www.fleschutz.de/Service.html)

Feedback
--------
Send your email feedback to: markus [at] fleschutz [dot] de

License & Copyright
-------------------
This open source release is licensed under the CC0 license. All trademarks are the property of their respective owners.
