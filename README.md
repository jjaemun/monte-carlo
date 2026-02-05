# monte-carlo!

`monte-carlo` is `in progress...`. 

## Overview 

`monte-carlo` develops an options pricing library in `c++`. The framework follows from 
the general valuation formula under a frictionless security market with continuous trading.


## Objectives

This project is intended as a practical exercise. Its subject is systems design, 
though it is not entirely uninterested in the numerical quality of the results. 
That is, it will try to find a suitable abstraction boundary for a monte-carlo 
simulation system, and it just happens that it will produce some 
results while doing so. Naturally these should confirm implementation correctness, 
but the discussion will drift away from them. 

Its dealing with monte-carlo pricing is then intentional. Because it is an established 
problem in the theory of mathematical finance, it affords directing significant attention
to design. 

For purposes of documentation, we may be formal sometimes, informal some others,
or even ommit mathematical definitions altogether. Typeset supplementary material
will be provided where pertinent, but the expectation from the reader is that of intimate 
familiarity with the topic. 

## Scope
`[redacted]`

## Thoughts & comments

### Random number generation

Random number generation is a non-trivial element of any monte carlo framework, and is
currently among the more dynamic organs in the system. This section addresses the
concerns that consequently arise 
There are a score of methods and 
algorithms to generate random deviates with an equal claim to be called vital in such a 
context. 
 .

#### Sampling strategies

A general form for antithetic sampling cannot be constructed in sample space. 

In order that distribution symmetry need not be assumed, it must be informed of 
the underlying distribution and the inverse cumulative distribution function, whenever
it is well defined. 

This constraint suggests that any architecture where statistical distributions preceed
variance reduction strategies is therefore limited by definition of its own abstractions.
At the very least, not without clumsily deferring computations to accommodate all logic
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



