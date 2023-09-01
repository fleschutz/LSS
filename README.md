Solutions for the Sums of Three Cubes
=====================================
This repo contains a small C program to list simple solutions (LSS) for: **x³ + y³ + z³ = n**

The sums of three cubes is a hard math problem, see https://en.wikipedia.org/wiki/Sums_of_three_cubes and https://en.wikipedia.org/wiki/Diophantine_equation for details. For a C# program please visit: https://github.com/mill1/SumOfThreeCubesSolver


🔧 Installation
----------------
Execute in a terminal window: (requires a C/C++ compiler only)
```
> git clone https://github.com/fleschutz/LSS    # Or download and unzip the ZIP file (click green button)
> cd LSS
> cc -O3 -fopenmp main.c 
> ./a.out <MODE>                                # Replace <MODE> by the mode number (see below)
```

Mode 1 - Calculate a single solution
-------------------------------------
This mode calculates x³ + y³ + z³ for the given x,y,z parameters.

Executing: `./a.out 1  1 2 3` returns: `1³ + 2³ + 3³ = 36`. Note that big numbers are supported, e.g.: `./a.out 1 -80538738812075974 80435758145817515 1260212329733563` returns: `3982933876681³ + -636600549515³ + -3977505554546³ = 30`.


Mode 2 - List no solutions
--------------------------
No solution exists for: n equal 4 or 5 modulo 9.

Executing: `./a.out 2` (for n = [0..100000]) returns the following output: [no_solutions.txt](Solutions/no_solutions.txt) (uses function listNoSolutions(), took 0.116s total).


Mode 3 - List solutions for positive numbers of x,y,z
-----------------------------------------------------
Finding solutions for positive numbers of x,y,z is quite fast.

Executing: `./a.out 3` (for n = [0..100000]) returns the following output: [solutions_for_positive_xyz.txt (TXT file)](Solutions/solutions_for_positive_xyz.txt) or [solutions_for_positive_xyz.csv (CSV file)](Solutions/solutions_for_positive_xyz.csv) (uses function listSolutionsForPositiveXYZ(), took 0.037s total).


Mode 4 - List solutions for negative numbers of x,y,z
-----------------------------------------------------
Finding solutions for negative numbers of x,y,z is quite slow.

Executing: `./a.out 4` (for n = [0..100 000]) returns the following output: [solutions_for_negative_xyz.txt (TXT file)](Solutions/solutions_for_negative_xyz.txt) or [solutions_for_negative_xyz.csv (CSV file)](Solutions/solutions_for_negative_xyz.csv) (uses function listSolutionsForNegativeXYZ(), took 4h total).


Mode 5 - List trivial solutions
-------------------------------
This is mode 2 + 3 + 4 combined.

Executing: `./a.out 5` (for n = [0..1000] and x,y,z = [0..100000] and line-sorted afterwards) returns the following output: [trivial_solutions.txt](Solutions/trivial_solutions.txt) (TXT file) or [trivial_solutions.csv](Results/trivial_solutions.csv) (CSV file) which took 4h.


Mode 6 - List nontrivial solutions
----------------------------------
This mode lists nontrivial solutions by using a shotgun algorithm with a start value of **x** (1 million by default).

Executing: `./a.out 6` (for n = [0..1000]) returns the following output: [nontrivial_solutions.txt](Solutions/nontrivial_solutions.txt) (uses function listNontrivialSolutions(), took hours and hours).

🏆 Nontrivial Solutions
------------------------
The following nontrivial solutions have been solved already:

* **30** = 3 982 933 876 681³ + (−636 600 549 515)³ + (−3 977 505 554 546)³ (solved 1999 by Beck, Pine, Tarrant, and Yarbrough Jensen)
* **33** = 88 661 289 752 875 283³ + (−87 784 054 428 622 393)³ + (−27 361 114 688 070 403)³   (solved 2019 by Andrew Booker)
* **42** = (-80 538 738 812 075 974)³ + 80 435 758 145 817 515³ + 1 260 212 329 733 563³  (solved 2019 by Andrew Booker and Andrew Sutherland)
* **52** = 60 702 901 317³ + 23 961 292 454³ + (−61 922 712 865)³
* **74** = (-284 650 292 555 885)³ + 66 229 832 190 556³ + 283 450 105 697 727³     (solved 2016 by Sander G. Huisman)
* **165** = (-385 495 523 231 271 884)³ + 383 344 975 542 639 445³ + 98 422 560 467 622 814³
* **795** = (-14 219 049 725 358 227)³ + 14 197 965 759 741 573³ + 2 337 348 783 323 923³
* **906** = (−74 924 259 395 610 397)³ + 72 054 089 679 353 378³ + 35 961 979 615 356 503³

The only remaining unsolved cases up to 1,000 are the following seven numbers:

* **114** = ?
* **390** = ?
* **627** = ?
* **633** = ?
* **732** = ?
* **921** = ?
* **975** = ?

Want to get famous? Just solve one of these numbers. May the force be with you 🖖

Furthermore, there are also nontrivial solutions additionally to trivial solutions:

* **3** = 569 936 821 221 962 380 720³ + (−569 936 821 113 563 493 509)³ + (−472 715 493 453 327 032)³ (solved 2019 by Andrew Booker and Andrew Sutherland)

📧 Feedback
------------
Send your email feedback to: markus.fleschutz [at] gmail.com


🤝 License & Copyright
-----------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
