LSS
===
A small C program to list simple solutions (LSS) for the sum of three cubes: x³ + y³ + z³ = n

NOTE: n < 1000 and x,y,z < 100000 and the solutions are formatted to be: x <= y <= z

See https://en.wikipedia.org/wiki/Sums_of_three_cubes and https://en.wikipedia.org/wiki/Diophantine_equation for more information.


🔧 Installation
----------------
Just a **C++ compiler** and **git** is needed. Then execute:
```
$ git clone https://github.com/fleschutz/LSS; cd LSS
$ gcc -O3 -fopenmp main.c     (when using a GCC compiler)
$ clang -O3 -fopenmp main.c   (when using a CLANG compiler)
$ ./a.out > out.txt
$ sort -g out.txt > list.txt
```

1️⃣ List of simple solutions
----------------------------
See the generated [list.txt](list.txt) generated by this program.


2️⃣ List of complicated solutions currently known
-------------------------------------------------
* 30 = 3982933876681³ − 636600549515³ − 3977505554546³
* 33 = 88661289752875283³ − 87784054428622393³ − 27361114688070403³
* 42 = -80538738812075974³ + 80435758145817515³ + 1260212329733563³ 
* 52 = 60702901317³ + 23961292454³ − 61922712865³
* 165 = (-385495523231271884)³ + 383344975542639445³ + 98422560467622814³
* 906 = (−74924259395610397)³ + 72054089679353378³ + 35961979615356503³


3️⃣ List of complicated solutions currently unsolved
----------------------------------------------------
* 114 = ?
* 390 = ?
* 579 = ?
* 627 = ?
* 633 = ?
* 732 = ?
* 795 = ?
* 921 = ?
* 975 = ?


Feedback
--------
Send your email feedback to: markus [at] fleschutz [dot] de


License & Copyright
-------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
