# monte-carlo!

`monte-carlo` is `in progress...`. 

## Overview 

`monte-carlo` develops an options pricing library in `c++`. The framework follows from 
the general valuation formula under a frictionless security market with continuous trading.


## Objectives

This project is inteded as a practical exercise. Its subject is systems design, 
though it is not entirely uninterested in the numerical quality of the results. 
That is, it will try to find a suitable abstraction boundary for a monte-carlo 
simulation system, and it just happens that it will (hopefully) produce some 
result while doing so. Naturally these should comfirm implementation (in)correctness, 
but the discussion will drift away from them. 

The choice of monte-carlo pricing is intentional. Because it is an established problem,
we may avoid awkwardly stumbling around the theory and direct our attention to design.

## Scope

It is hard to scope the project. After all, it is unlikely that I can develop a 
fully-featured library in a reasonable amount of time. For now, a first iteration 
should include the minimal pipeline to price vanilla european options, but every 
stage must be a suitable recipient for extensions. Scaffolding rather than features.

The project will develop in phases. Briefly, the first and  current phase is concerned 
with a clarity-and-correctness-first approach. It will serve as a baseline to improve upon.
This is reflected in the heavy usage of the `stl`. From this phase out, the extension to 
different backends is natural. There are no clear directions in this regard, but it is 
unlikely to dip into gpu territory. Lastly, software optimizations will come in, once the 
desired generality and flexibility are achieved and tested for the system design.  

## Thoughts & comments

### Random number generation

Random number generation is a non-trivial element of any monte carlo framework, and is
currently among the more dynamic organs of the system. The discussion below explores
its main pain points.

#### Sampling strategies

A general form for antithetic sampling cannot be constructed in sample space. 

In order that distribution symmetry need not be assumed, it must be informed of 
the underlying distribution and the inverse cumulative distribution function, whenever
it is well defined. 

This constraint suggests that any architecture where statistical distributions preceed
variance reduction strategies is therefore limited by definition of its own abstractions.
At the very least, not without clumsily deferring computations to accomodate all logic
at an appropriate level, or by forking functionality according to each distribution.

The same implication holds for quasi-monte-carlo methods or stratified sampling 
strategies, seeing that they also must work in probability space. 

The current outlook holds that the overall simplicity of the system, in terms of
the supported distributions, does not justify immediate design changes, but this is 
duly noted for future iterations.


## TODO!
```
+---------------------------------+-----------------------------------------+
| Task                            | Status                                  |
+---------------------------------+-----------------------------------------+
| noise layer redesign            | owned resources, antithetic, correlated |
| simulator design                | contract? configs?                      |
| driver redesign                 | rethink multi-simulator orchestration   |
| caching (deferred)              | plan random deviate reuse / memory      |
+---------------------------------+-----------------------------------------+
```



