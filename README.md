Solutions for: x³ + y³ + z³ = n
===============================
This repo contains a small C program to list simple solutions (LSS) for the sums of three cubes.

See https://en.wikipedia.org/wiki/Sums_of_three_cubes and https://en.wikipedia.org/wiki/Diophantine_equation for details. For a C# program please visit: https://github.com/mill1/SumOfThreeCubesSolver


🔧 Installation
----------------
Execute in a terminal window: (requires a C/C++ compiler only)
```
> git clone https://github.com/fleschutz/LSS    # Or download and unzip the ZIP file (click green button)
> cd LSS
> cc -O3 -fopenmp main.c 
> ./a.out <MODE>                                # Replace <MODE> by the mode number (see below)
```

Mode 1 - List no solutions
--------------------------
No solution exists for: n equal 4 or 5 modulo 9. See the [no_solutions.txt](Solutions/no_solutions.txt) in the [📂Solutions](Solutions) subfolder (generated by executing: `./a.out 1` for n = [0..100000], it took 0.116s).

Mode 2 - List solutions for positive numbers of x,y,z
-----------------------------------------------------
See the [solutions_for_positive_xyz.txt](Solutions/solutions_for_positive_xyz.txt) (text file) and [solutions_for_positive_xyz.csv](Solutions/solutions_for_positive_xyz.csv) (CSV file) in the 📂Solutions subfolder (generated by executing: `./a.out 2` for n = [0..100000], it took 0.037s).

Mode 3 - List solutions for negative numbers of x,y,z
-----------------------------------------------------
See the [solutions_for_negative_xyz.txt](Solutions/solutions_for_negative_xyz.txt) (text file) and [solutions_for_negative_xyz.csv](Solutions/solutions_for_negative_xyz.csv) (CSV file) in the 📂Solutions subfolder (generated by executing: `./a.out 3` for n = [0..100 000], it took 3h).

Mode 4 - List all trivial solutions
-------------------------------------
This is mode 1 + 2 + 3 combined. See the [trivial_solutions.txt](Solutions/trivial_solutions.txt) (text file) and [trivial_solutions.csv](Results/trivial_solutions.csv) (CSV file) in the 📂Solutions subfolder (generated by executing: `./a.out 4`, for n = [0..1000] and x,y,z = [0..100000] and line-sorted afterwards).


🏆 Nontrivial Solutions
------------------------
The following nontrivial solutions have been solved already:

* **30** = 3 982 933 876 681³ + (−636 600 549 515)³ + (−3 977 505 554 546)³
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

📧 Feedback
------------
Send your email feedback to: markus.fleschutz [at] gmail.com


🤝 License & Copyright
-----------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
