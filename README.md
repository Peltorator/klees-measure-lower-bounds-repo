# Codes and constructions for "Combinatorial Designs Meet Hypercliques: Higher Lower Bounds for Klee’s Measure Problem and Related Problems in Dimensions $d \ge 4$"

- `covering-design-match-check.cpp` — program that given a covering design with $v/d$ unique elements at the beginning of each block checks that it is indeed a covering design and indeed all $v/d \cdot d$ elements at the beginnings of all blocks are unique. Such a covering design is then suitable to obtain a lower bound for $\gamma_d$ using Theorem 7. Example input is given at the bottom of the file.

- `covering-designs-for-lower-bounds.txt` — best known to us covering designs for each value of $d$ from $3$ to $44$ already given as suitable inputs for `covering-design-match-check.cpp` and corresponding lower bounds obtained by using these covering designs.

- `prefix-covering-design-check.cpp` — given $d$, $K$, $\alpha$ and a sequence of blocks checks whether it is indeed a correct $(d, K, \alpha)$ prefix covering design. Can be used to check Theorem 5 constructions. Needed inputs are given at the bottom of the file.
