Data manipulation in C using lists data structures.

To run the programm, proceed as it follows:

./tema1--command1--command2--command3

Where commandX is the command the programm should execute

e1 - exception elimination using statistics

e2 - "noise" elimination through median filter

Input

[1, 2, 3, 6, 19, 7, 8, 6, 4, 4, 4, 21, 4, 2, −1]

mediana([1, 2, 3, 6, 19]) −→ mediana([1, 2, 3, 6, 19]) −→ 3

mediana([2, 3, 6, 19, 7]) −→ mediana([2, 3, 6, 7, 19]) −→ 6

mediana([3, 6, 19, 7, 8]) −→ mediana([3, 6, 7, 8, 19]) −→ 7

mediana([6, 19, 7, 8, 6]) −→ mediana([6, 6, 7, 8, 19]) −→ 7

mediana([19, 7, 8, 6, 4]) −→ mediana([4, 6, 7, 8, 19]) −→ 7

...

mediana([4, 4, 21, 4, 2]) −→ mediana([2, 4, 4, 4, 21]) −→ 4

mediana([4, 21, 4, 2, −1]) −→ mediana([−1, 2, 4, 4, 21]) −→ 4

Result −→ [3, 6, 7, 7, 7, 6, 4, 4, 4, 4, 4]



e3 - "noise" elimination through based on arithmetic average

Input :[1, 2, 3, 6, 19, 7, 8]

media([1, 2, 3, 6, 19]) −→ 6.2

media([2, 3, 6, 19, 7]) −→ 7.4

media([3, 6, 19, 7, 8]) −→ 8.6

Result −→ [6.2, 7.4, 8.6]

u - frequency uniformization

Input:

3

1000 2.0

2000 3.0

2500 7.0

Output-ul:

3

1000 2.0

1500 2.5

2000 4.75

c - completion of missing data

st<δ> - calculus of the statistics



