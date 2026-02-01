# monte-carlo!

## Overview 

`monte-carlo` develops an options pricing library in `c++`. The framework follows from the 
general valuation formula under a frictionless security market with continuous trading.

`monte-carlo` is `in progress...`. 

## Objectives

This project is inteded as a practical exercise. Its subject is systems design, 
though it is not entirely uninterested in the numerical quality of the results. 
That is, it will try to find a suitable abstraction boundary for a monte-carlo 
simulation system, and it just happens that it will (hopefully) produce some result 
while doing so. Naturally these should comfirm implementation (in)correctness, 
but the discussion will drift away from them. 

The choice of monte-carlo pricing is intentional. Because it is an established problem,
we may avoid awkwardly stumbling around the theory and direct our attention to design.

## Thoughts & comments


There is little more to say than the fact
that there is still way too much work ahead. Just recently I changed the project
scope entirely, in favour of a clarity-and-correctness-first, pure `stl` approach. 
This is motivated by at least two desires. To familiarise myself with the 
provided algorithms, mechanisms etc provided in the `stl` (even if some sections
showcase excessive emphasis on `stl` machinery); and, to create a 
solid foundation for later development - a benchmark of sorts. The extension to 
different backends is natural beyond that point, along with the effort it takes
to optimize the existing code. This is reflected in the presence of generics throughout.
For now, naive-but-readable dominates. 


## TODO!
```
+---------------------------------+----------------------------------------+
| Task                            | Status                                 |
+---------------------------------+----------------------------------------+
| blockwise operations            | design iteration / partitioning logic  |
| stats interfaces                | define CRTP-based sample & theoretic   |
| driver redesign                 | rethink multi-simulator orchestration  |
| caching                         | plan random deviate reuse / memory     |
+---------------------------------+----------------------------------------+
```



