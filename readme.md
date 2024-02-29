# Algorithms for Galois Words: Detection, Factorization, and Rotation

This repository provides the following programs:
 - `galois_factorization.x`: computes the Galois factorization of the input
 - `is_galois.x`: checks whether the input is a Galois word (output is '1' for Galois, and '0' otherwise)
 - `galois_rotation.x`: computes the Galois rotation of a **primitive** input

The input is read from standard input (`stdin`). 

Example Usage:
```bash
echo -n 'aba' | ./is_galois.x
echo -n 'baa' | ./is_galois.x
echo -n 'baa' | ./galois_rotation.x
echo -n 'baa' | ./galois_factorization.x
```

Per default, all programs check their output. 
Compile with flag `NDEBUG` to omit these checks.
