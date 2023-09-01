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
This mode lists nontrivial solutions by using a shotgun algorithm. The argument is an exponent defining a value range for x, the default value of 6 means: x=[10^6..10^7].

Executing: `./a.out 6` (for n = [0..1000]) returns the following output: [nontrivial_solutions.txt](Solutions/nontrivial_solutions.txt) (uses function listNontrivialSolutions(), took hours and hours).

🏆 Nontrivial Solutions
------------------------
The following nontrivial solutions have been solved already:

* **30** = `3982933876681³ + (−636600549515)³ + (−3977505554546)³` (solved 1999 by Beck, Pine, Tarrant, and Yarbrough Jensen)
* **33** = `88661289752875283³ + (−87784054428622393)³ + (−27361114688070403)³` (solved 2019 by Andrew Booker)
* **42** = `(-80538738812075974)³ + 80435758145817515³ + 1260212329733563³` (solved 2019 by Andrew Booker and Andrew Sutherland)
* **52** = `60702901317³ + 23961292454³ + (−61922712865)³`
* **74** = `(-284650292555885)³ + 66229832190556³ + 283450105697727³` (solved 2016 by Sander G. Huisman)
* **165** = `(-385495523231271884)³ + 383344975542639445³ + 98422560467622814³`
* **795** = `(-14219049725358227)³ + 14197965759741573³ + 2337348783323923³`
* **906** = `(−74924259395610397)³ + 72054089679353378³ + 35961979615356503³`
* HINT: Use [WolframAlpha](https://www.wolframalpha.com) with copy&paste to check the results.

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
