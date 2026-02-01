# monte-carlo!

`monte-carlo` is `in progress...`. 

## Overview 

`monte-carlo` develops an options pricing library in `c++`. The framework follows from the 
general valuation formula under a frictionless security market with continuous trading.


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

It is hard to scope the project, so we will loosely define the intended coverage. After all,
it is unlikely that I can develop a fully-featured library in a reasonable amount of time.
For now, a first iteration should include the minimal pipeline to price vanilla european options,
but evry phase must be a suitable recipient to extension. Scaffolding rather than features.

The project will develop in phases. Briefly, the current phase is concerned with a 
clarity-and-correctness-first approach. It will serve as a baseline to improve upon.
This is reflected in the usage of the `stl`. From this phase out, the extension to different
backends is natural. There are no clear directions in that regard, but it is unlikely to 
dip into gpu territory. Lastly, software optimizations will come in, once the desired generality,
flexibility are achieved and tested for the system design.  


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



