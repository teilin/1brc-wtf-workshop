Be aware that the compiler may optimize several of these for you, but compiler optimiziation may be lost if you change your code in ways that confuses the compiler.

# mutable data structure

- mutate data in place. this cuts down on allocations and copies which can be expensive

example:

# CharSequence/string_view/c#?

- do not copy data unless you have to. allocations are expensive
- stores a pointer and length instead of copying the whole string

example:

# shrink datastructure

- can fit more data in cache
  - L1/L2/L3 cache are small
- faster to fetch data in memory
  - one cache line is 64 bytes on intel/amd
  - mention memory alignment?
- less overall memory usage

## instead of this:

```
struct Data{
  int min;
  int max;
  double sum;
}
```

## do this if the data can fit in a short:

```
struct Data{
  int16 min;
  int16 max;
  int32 sum;
}
```

# int-for-float

Using integers instead of floats when number of decimals is known:

- very slightly reduces CPU cost
- can be more accurate. especially if number of decimals are known. IEEE 754 floats are not always accurate
- can use less memory. int32 instead of using double for example.
- in our specific case it can increase the speed of parsing the numbers into a variable

# instead of this

```
float blab = 11.1;
```

# do this

```
int blab1 = 111;
```
