Be aware that the compiler may optimize several of these for you, but compiler optimiziation may be lost if you change your code in ways that confuses the compiler.

# mutable data structure

- mutate data in place. this cuts down on allocations and copies which can be expensive

example:

# CharSequence/string_view

- do not copy data unless you have to. allocations are expensive
- stores a pointer and length instead of copying the whole string

example:

# integer instead of float

You can substitute integers for floats when number of decimals is known

- very slightly reduces CPU cost on most modern CPUs
- can be more accurate. IEEE 754 floats are not always accurate
- can use less memory. Int32 instead of using double for example
- in our specific case it can increase the speed of parsing the numbers into a variable

## instead of this

```c
float blab = 11.1;
```

## do this

```c
int blab1 = 111;
```

# shrink datastructure

- can fit more data in cache
  - L1/L2/L3 cache are small
- faster to fetch data in memory
  - one cache line is 64 bytes on intel/amd
  - mention memory alignment?
- less overall memory usage

## instead of this:

```c
struct Data{
  int min;
  int max;
  double sum;
}
```

## do this if the data can fit in smaller types:

```c
struct Data{
  int16_t min;
  int16_t max;
  int32_t sum;
}
```
