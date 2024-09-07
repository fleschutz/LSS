Sum-of-Three-Cubes Solver
=========================
This repo contains a C program to list simple solutions (LSS) for the equation: **x³ + y³ + z³ = n**

The sums of three cubes is a hard math problem, see https://en.wikipedia.org/wiki/Sums_of_three_cubes and https://en.wikipedia.org/wiki/Diophantine_equation for details. For a C# program please visit: https://github.com/mill1/SumOfThreeCubesSolver.


🔧 Installation
----------------
Requires a **C/C++ compiler** only. Then execute in a terminal window: 
```
> git clone https://github.com/fleschutz/LSS  # or download and unzip the ZIP file (click green button)
> cd LSS
> cc -O3 -fopenmp main.c -o mode              # compiles with OpenMP API for multi-threading
> ./mode <NUMBER>                             # replace <NUMBER> by the mode number (see below)
```

Mode 1 - Calculate a solution
-----------------------------
This mode calculates the result of: x³ + y³ + z³ for the given values of x, y, z.

For example executing: `./mode 1  1 2 3` returns: 1³ + 2³ + 3³ = 36). It also supports BIG numbers, e.g. executing: `./mode 1 -80538738812075974 80435758145817515 12602123297335631` returns: -80538738812075974³ + 80435758145817515³ + 12602123297335631³ = 42.


Mode 2 - List no solutions
--------------------------
This mode calculates and lists all non-existing solutions. No solution exists for: n equal 4 or 5 modulo 9.

`./mode 2` returns: [no_solutions.txt](Solutions/no_solutions.txt). This mode uses function listNoSolutions() and took 0.116s.


Mode 3 - List solutions for positive numbers only
-------------------------------------------------
This mode calculates and lists all solutions for positive numbers of x, y, z only.

`./mode 3` returns: [solutions_for_positive_numbers_only.txt](Solutions/solutions_for_positive_numbers_only.txt). It uses the function listSolutionsForPositiveNumbersOnly() and took 0.037s.


Mode 4 - List trivial solutions for negative numbers
----------------------------------------------------
This mode calculates and lists trivial solutions for x, y, z with at least one negative number.

`./mode 4` returns: [trivial_for_negative_numbers.txt](Solutions/trivial_for_negative_numbers.txt). It uses the function listTrivialSolutionsForNegativeNumbers() and took 4h.


Mode 5 - List trivial solutions
-------------------------------
This mode combines mode 2, mode 3, and mode 4.

`./mode 5` returns: [trivial_solutions.txt](Solutions/trivial_solutions.txt) and took 4h.


Mode 6 - List nontrivial solutions
----------------------------------
This mode calculates and lists nontrivial solutions by using a 'shotgun' algorithm in function listNontrivialSolutions(). The additional argument is an exponent defining a value range for x, e.g. the default value of 6 means: x=[10^6..10^7].

* `./mode 6 3` returns: [solutions_for_10^3_range.txt](Solutions/solutions_for_10^3_range.txt) (took 0.042s on a Core i9).
* `./mode 6 4` returns: [solutions_for_10^4_range.txt](Solutions/solutions_for_10^4_range.txt) (took 3.4s on a Core i9).
* `./mode 6 5` returns: [solutions_for_10^5_range.txt](Solutions/solutions_for_10^5_range.txt) (took 5min 23s on a Core i9).
* `./mode 6 6` returns: [solutions_for_10^6_range.txt](Solutions/solutions_for_10^6_range.txt) (took 2h on a Core i9).
* `./mode 6 7` returns: [solutions_for_10^7_range.txt](Solutions/solutions_for_10^7_range.txt) (took 13h on a Core i9).
* `./mode 6 8` returns: [solutions_for_10^8_range.txt](Solutions/solutions_for_10^8_range.txt).
* `./mode 6 9` returns: [solutions_for_10^9_range.txt](Solutions/solutions_for_10^9_range.txt).
* `./mode 6 12` returns: [solutions_for_10^12_range.txt](Solutions/solutions_for_10^12_range.txt).

NOTE: for readability the files have been numerically sorted with: `sort -g < infile > outfile`.

🏆 Nontrivial Solutions
------------------------
The following nontrivial solutions have been solved already in the past:

* **30** = *3982933876681³ + (-636600549515)³ + (-3977505554546)³* (solved 1999 by Beck, Pine, Tarrant, and Yarbrough Jensen)
* **33** = *88661289752875283³ + (-87784054428622393)³ + (-27361114688070403)³* (solved 2019 by Andrew Booker)
* **42** = *(-80538738812075974)³ + 80435758145817515³ + 12602123297335631³* (solved 2019 by Andrew Booker and Andrew Sutherland)
* **52** = *60702901317³ + 23961292454³ + (-61922712865)³*
* **74** = *(-284650292555885)³ + 66229832190556³ + 283450105697727³* (solved 2016 by Sander G. Huisman)
* **165** = *(-385495523231271884)³ + 383344975542639445³ + 98422560467622814³*
* **795** = *(-14219049725358227)³ + 14197965759741573³ + 2337348783323923³* (solved by Andrew Booker)
* **906** = *(-74924259395610397)³ + 72054089679353378³ + 35961979615356503³* (solved by Andrew Booker)
* **NOTE:** Use [WolframAlpha](https://www.wolframalpha.com) or `./mode 1 <x> <y> <z>` with copy & paste to check the results.

The only remaining unsolved cases up to 1,000 are the following seven numbers:

* **114** = ?
* **390** = ?
* **627** = ?
* **633** = ?
* **732** = ?
* **921** = ?
* **975** = ?
* **NOTE:** Want to get famous? Just solve one of these numbers. May the force be with you 🖖


📧 Feedback
------------
Send your email feedback to: markus.fleschutz [at] gmail.com


🤝 License & Copyright
-----------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
