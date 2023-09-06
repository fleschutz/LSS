Sums of Three Cubes Solver
==========================
This repo contains a small C program to list simple solutions (LSS) for: **x³ + y³ + z³ = n**

The sums of three cubes is a hard math problem, see https://en.wikipedia.org/wiki/Sums_of_three_cubes and https://en.wikipedia.org/wiki/Diophantine_equation for details. For a C# program please visit: https://github.com/mill1/SumOfThreeCubesSolver


🔧 Installation
----------------
Execute in a terminal window: (requires a C or C++ compiler only)
```
> git clone https://github.com/fleschutz/LSS    # Or download and unzip the ZIP file (click green button)
> cd LSS
> cc -O3 -fopenmp main.c -o mode                # Uses OpenMP API for multi-threading
> ./mode <NUMBER>                               # Replace <NUMBER> by the mode number (see below)
```

Mode 1 - Calculate a solution
-----------------------------
This mode calculates the result of: x³ + y³ + z³ for the given values of x,y,z (e.g. executing: `./mode 1  1 2 3` returns: `1³ + 2³ + 3³ = 36`).

Note that big numbers are supported, e.g.: `./mode 1 -80538738812075974 80435758145817515 1260212329733563` returns: `3982933876681³ + -636600549515³ + -3977505554546³ = 30`.


Mode 2 - List no solutions
--------------------------
No solution exists for: n equal 4 or 5 modulo 9.

`./mode 2` returns the following: [no_solutions.txt](Solutions/no_solutions.txt) (for n = [0..100000]). It uses function listNoSolutions() and took 0.116s total.


Mode 3 - List trivial solutions for positive x,y,z
--------------------------------------------------
This mode lists trivial solutions for positive numbers of x,y,z.

`./mode 3` returns the following: [trivial_for_positive_xyz.txt](Solutions/trivial_for_positive_xyz.txt) (text file) or [trivial_for_positive_xyz.csv](Solutions/trivial_for_positive_xyz.csv) (CSV file) for n = [0..100000]. It uses function listTrivialSolutionsForPositiveXYZ() and took 0.037s total.


Mode 4 - List trivial solutions for negative x,y,z
--------------------------------------------------
This mode lists trivial solutions for negative numbers of x,y,z.

`./mode 4` returns the following: [trivial_for_negative_xyz.txt](Solutions/trivial_for_negative_xyz.txt) (text file) or [trivial_for_negative_xyz.csv](Solutions/trivial_for_negative_xyz.csv) (CSV file) for n = [0..100 000]. It uses function listTrivialSolutionsForNegativeXYZ() and took 4h total.


Mode 5 - List trivial solutions
-------------------------------
This is mode 2 + 3 + 4 combined.

`./mode 5` returns the following: [trivial_solutions.txt](Solutions/trivial_solutions.txt) (text file) or [trivial_solutions.csv](Results/trivial_solutions.csv) (CSV file) for n = [0..1000] and x,y,z = [0..100000] and line-sorted afterwards (took 4h total).


Mode 6 - List nontrivial solutions for negative y and z
-------------------------------------------------------
This mode lists nontrivial solutions by using a shotgun algorithm in function listSolutionsForNegativeYZ(). The additional argument is an exponent defining a value range for x, e.g. the default value of 6 means: x=[10^6..10^7].

* `./mode 6 3` returns: [solutions_for_10^3_range.txt](Solutions/solutions_for_10^3_range.txt) (took 0.042s @ Core i9).
* `./mode 6 4` returns: [solutions_for_10^4_range.txt](Solutions/solutions_for_10^4_range.txt) (took 3.4s @ Core i9).
* `./mode 6 5` returns: [solutions_for_10^5_range.txt](Solutions/solutions_for_10^5_range.txt) (took 5min 23s @ Core i9).
* `./mode 6 6` returns: [solutions_for_10^6_range.txt](Solutions/solutions_for_10^6_range.txt) (took 2h @ Core i9).
* `./mode 6 7` returns: [solutions_for_10^7_range.txt](Solutions/solutions_for_10^7_range.txt) (took 7h @ Core i9).
* `./mode 6 8` returns: [solutions_for_10^8_range.txt](Solutions/solutions_for_10^8_range.txt).


🏆 Nontrivial Solutions
------------------------
The following nontrivial solutions have been solved already:

* **30** = `3982933876681³ + (-636600549515)³ + (-3977505554546)³` (solved 1999 by Beck, Pine, Tarrant, and Yarbrough Jensen)
* **33** = `88661289752875283³ + (-87784054428622393)³ + (-27361114688070403)³` (solved 2019 by Andrew Booker)
* **42** = `(-80538738812075974)³ + 80435758145817515³ + 1260212329733563³` (solved 2019 by Andrew Booker and Andrew Sutherland)
* **52** = `60702901317³ + 23961292454³ + (-61922712865)³`
* **74** = `(-284650292555885)³ + 66229832190556³ + 283450105697727³` (solved 2016 by Sander G. Huisman)
* **165** = `(-385495523231271884)³ + 383344975542639445³ + 98422560467622814³`
* **795** = `(-14219049725358227)³ + 14197965759741573³ + 2337348783323923³`
* **906** = `(-74924259395610397)³ + 72054089679353378³ + 35961979615356503³`

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

* **3** = `569936821221962380720³ + (-569936821113563493509)³ + (-47271593453327032)³` (solved 2019 by Andrew Booker and Andrew Sutherland)

HINT: Use [WolframAlpha](https://www.wolframalpha.com) with copy&paste to check the results.

📧 Feedback
------------
Send your email feedback to: markus.fleschutz [at] gmail.com


🤝 License & Copyright
-----------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
