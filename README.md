Sums-of-Three-Cubes Solver
==========================
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

Mode 1 - Calculate a solution for x,y,z
---------------------------------------
This mode calculates the result of: x³ + y³ + z³ for the given values of x, y, z. Note the following examples:

* `./mode 1  1 2 3` returns: 1³ + 2³ + 3³ = 36
* `./mode 1 -80538738812075974 80435758145817515 12602123297335631` returns: -80538738812075974³ + 80435758145817515³ + 12602123297335631³ = 42


Mode 2 - List no solutions
--------------------------
This mode calculates and lists all non-existing solutions. No solution exists for: n equal 4 or 5 modulo 9.

`./mode 2` returns: [no_solutions.txt](Solutions/no_solutions.txt). This mode uses the listNoSolutions() function and took 0.116s on a Core i9.


Mode 3 - List all solutions for positive x,y,z
----------------------------------------------
This mode calculates and lists all solutions for x >= 0, y >= 0, and z >= 0.

`./mode 3` returns: [solutions_for_positive_xyz.txt](Solutions/solutions_for_positive_xyz.txt) (for readability the file has been numerically sorted by executing: `sort -g < infile > outfile`). It uses the listSolutionsForPositiveXYZ() function and took 0.037s on a Core i9. 


Mode 4 - List trivial solutions for negative z
----------------------------------------------
This mode calculates and lists trivial solutions for z < 0.

`./mode 4` returns: [solutions_for_negative_z.txt](Solutions/solutions_for_negative_z.txt). It uses the listSolutionsForNegativeZ() function and took 10s on a Core i9. 


Mode 5 - List trivial solutions for negative y and z
----------------------------------------------------
This mode calculates and lists trivial solutions for y < 0 and z < 0.

`./mode 5` returns: [solutions_for_negative_yz.txt](Solutions/solutions_for_negative_yz.txt). It uses the listSolutionsForNegativeYZ() function and took 4h on a Core i9.


Mode 6 - List trivial solutions
-------------------------------
This mode combines mode 2 + 3 + 4 + 5.

`./mode 6` returns: [trivial_solutions.txt](Solutions/trivial_solutions.txt) and took 4h on a Core i9.


Mode 7 - List nontrivial solutions
----------------------------------
This mode calculates and lists nontrivial solutions for a given value range of x. The value range is defined by an exponent, e.g. exponent 6 means: x=[10^6..10^7].

It uses a 'shotgun' algorithm in the listNontrivialSolutions() function. 

* `./mode 7 3` returns: [solutions_for_x_greater_10^3.txt](Solutions/solutions_for_x_greater_10^3.txt) (took 0.042s on a Core i9).
* `./mode 7 4` returns: [solutions_for_x_greater_10^4.txt](Solutions/solutions_for_x_greater_10^4.txt) (took 3.4s on a Core i9).
* `./mode 7 5` returns: [solutions_for_x_greater_10^5.txt](Solutions/solutions_for_x_greater_10^5.txt) (took 5min 23s on a Core i9).
* `./mode 7 6` returns: [solutions_for_x_greater_10^6.txt](Solutions/solutions_for_x_greater_10^6.txt) (took 2h on a Core i9).
* `./mode 7 7` returns: [solutions_for_x_greater_10^7.txt](Solutions/solutions_for_x_greater_10^7.txt) (took 13h on a Core i9).
* `./mode 7 8` returns: [solutions_for_x_greater_10^8.txt](Solutions/solutions_for_x_greater_10^8.txt) (not finished yet).
* `./mode 7 9` returns: [solutions_for_x_greater_10^9.txt](Solutions/solutions_for_x_greater_10^9.txt) (not finished yet).
* `./mode 7 10` returns: [solutions_for_x_greater_10^10.txt](Solutions/solutions_for_x_greater_10^10.txt) (not finished yet).
* `./mode 7 11` returns: [solutions_for_x_greater_10^11.txt](Solutions/solutions_for_x_greater_10^11.txt) (not finished yet).
* `./mode 7 12` returns: [solutions_for_x_greater_10^12.txt](Solutions/solutions_for_x_greater_10^12.txt) (not finished yet).


🏆 Nontrivial Solutions
------------------------
The following nontrivial solutions have been solved already in the past:

* **30** = *3982933876681³ + (-636600549515)³ + (-3977505554546)³* (solved 1999 by Beck, Pine, Tarrant, and Yarbrough Jensen)
* **33** = *88661289752875283³ + (-87784054428622393)³ + (-27361114688070403)³* (solved 2019 by Andrew Booker)
* **42** = *(-80538738812075974)³ + 80435758145817515³ + 12602123297335631³* (solved 2019 by Andrew Booker and Andrew Sutherland)
* **52** = *60702901317³ + 23961292454³ + (-61922712865)³* (solved by ?)
* **74** = *(-284650292555885)³ + 66229832190556³ + 283450105697727³* (solved 2016 by Sander G. Huisman)
* **165** = *(-385495523231271884)³ + 383344975542639445³ + 98422560467622814³* (solved by ?)
* **795** = *(-14219049725358227)³ + 14197965759741573³ + 2337348783323923³* (solved by Andrew Booker)
* **906** = *(-74924259395610397)³ + 72054089679353378³ + 35961979615356503³* (solved by Andrew Booker)

Use [WolframAlpha](https://www.wolframalpha.com) to verify the solutions or execute: `./mode 1 x y z` (copy&paste recommended). The only remaining unsolved cases up to 1,000 are the following seven numbers:

* **114** = ?
* **390** = ?
* **627** = ?
* **633** = ?
* **732** = ?
* **921** = ?
* **975** = ?

Want to get famous? Just solve one of these numbers. May the force be with you 🖖

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.
* Or just send your feedback to: markus.fleschutz [at] gmail.com

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0 license. All trademarks are the property of their respective owners.
