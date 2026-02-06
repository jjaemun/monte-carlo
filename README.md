# monte-carlo!

`monte-carlo` is `in progress...`. 

## Overview 

`monte-carlo` develops an options pricing library in `c++`. The framework follows from 
the general valuation formula under a frictionless security market with continuous trading.


## Objectives

This project is intended as a practical exercise. Its subject is systems design, 
though without loosing interest in the numerical quality of the results. 
That is, it will try to find a suitable abstraction boundary for a monte-carlo 
simulation system, and it just happens that it will produce some 
results while doing so. Naturally, these should confirm implementation correctness, 
but the discussion will drift away from them. 

Its dealing with monte-carlo pricing is then intentional. As an established 
problem in mathematical and computational finance, it affords directing significant attention
to design. After all, whoever sets to describe in adequate treatment the theory of
monte carlo methods in less than a large volume must be willing to lie about it 
or suggest that it is a deeply irrelevant topic - neither of which I am ready to commit. 

And so, for purposes of documentation, we may be formal sometimes, informal some others,
or even ommit mathematical definitions altogether. Typeset supplementary material
will be provided where pertinent, but the expectation from the reader is that of intimate 
familiarity with the topic. 

## Scope
`[redacted]`

## Thoughts & comments

### Random number generation

Random number generation is a non-trivial element of any monte carlo framework, and is
currently among the more dynamic organs in the system. This section addresses
concerns about both of those qualities. 

There are a score of methods and algorithms to generate random deviates with an 
equal claim to be called vital...

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



