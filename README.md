LSS
===
A small C program to list simple solutions (LSS) for the sums of three cubes:

**x³ + y³ + z³ = n**

See https://en.wikipedia.org/wiki/Sums_of_three_cubes and https://en.wikipedia.org/wiki/Diophantine_equation for details.


🔧 Installation
----------------
Just a **C/C++ compiler** and **git** is needed. Then execute in a terminal window:
```
$ git clone https://github.com/fleschutz/LSS; cd LSS
$ gcc -O3 -fopenmp main.c     (when using the GCC compiler)
$ clang -O3 -fopenmp main.c   (when using the CLANG compiler)
$ ./a.out 
```

1️⃣ No solutions
----------------
No solution exists for n equal 4 or 5 modulo 9. See the [no_solutions.txt](Results/no_solutions.txt) in the [Results/](Results/) folder generated by this program (for n < 100000).


2️⃣ Primitive solutions for positive numbers
--------------------------------------------
See the [text file](Results/primitive_addition_solutions.txt) and [CSV file](Results/primitive_addition_solutions.csv) generated by this program (for n < 100000 and solutions formatted to be: x <= y <= z).


3️⃣ Primitive solutions
-----------------------
See the [primitive_solutions.txt](Results/primitive_solutions.txt) and [primitive_solutions.csv](Results/primitive_solutions.csv) generated by this program (for n < 1000 and x,y,z < 100000 and solutions formatted to be: x <= y <= z).


4️⃣ Nontrivial solutions already solved
---------------------------------------
* 30 = 3 982 933 876 681³ + (−636 600 549 515)³ + (−3 977 505 554 546)³
* 33 = 88 661 289 752 875 283³ + (−87 784 054 428 622 393)³ + (−27 361 114 688 070 403)³   (solved 2019 by Andrew Booker)
* **42** = (-80 538 738 812 075 974)³ + 80 435 758 145 817 515³ + 1 260 212 329 733 563³  (solved 2019 by Andrew Booker and Andrew Sutherland)
* 52 = 60 702 901 317³ + 23 961 292 454³ + (−61 922 712 865)³
* 74 = (-284 650 292 555 885)³ + 66 229 832 190 556³ + 283 450 105 697 727³     (solved 2016 by Sander G. Huisman)
* 165 = (-385 495 523 231 271 884)³ + 383 344 975 542 639 445³ + 98 422 560 467 622 814³
* 795 = (-14 219 049 725 358 227)³ + 14 197 965 759 741 573³ + 2 337 348 783 323 923³
* 906 = (−74 924 259 395 610 397)³ + 72 054 089 679 353 378³ + 35 961 979 615 356 503³


5️⃣ Nontrivial solutions still unsolved
---------------------------------------
The only remaining unsolved cases up to 1,000 are the following seven numbers:

* 114 = ?
* 390 = ?
* 627 = ?
* 633 = ?
* 732 = ?
* 921 = ?
* 975 = ?

Want to get famous? Go ahead and solve one of the seven numbers.

Feedback
--------
Send your email feedback to: markus [at] fleschutz [dot] de


License & Copyright
-------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
