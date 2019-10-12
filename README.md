LSS
===

A small C program to list simple solutions (LSS) for the sum of three cubes: x³ + y³ + z³ = n (for n < 1000 and x,y,z < 100000, solutions formatted for: x <= y <= z)

Perform the following steps, please:

1. git clone https://github.com/fleschutz/LSS.git

2. cd LSS

3. gcc -O3 main.c (for GCC compiler) or: clang -O3 main.c (for CLANG compiler)

4. ./a.out > out.txt

5. sort -g out.txt > list.txt

Now, see list.txt for the resulting simple solutions.


Currently known complicated solutions
-------------------------------------
* 33 = 88661289752875283³ − 87784054428622393³ − 27361114688070403³
* 42 = -80538738812075974³ + 80435758145817515³ + 1260212329733563³ 
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

