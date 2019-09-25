LSS
===

Program to list simple solutions for the sum of three cubes: x³ + y³ + z³ = k (for k < 100000 and search band < 1000)

Execute the following steps:

1. git clone https://github.com/fleschutz/LSS.git

2. cd LSS

3. gcc -O3 main.c (for GCC compiler) or: clang -O3 main.c (for CLANG compiler)

4. ./a.out > out.txt

5. sort -g out.txt > list.txt

Now, see list.txt for the resulting solutions.
