# Itertools
Python's builtin iterators & itertools in modern C++.
Get back all the goodness you miss in Python when typing C++ code!
Just use it and you're be fine.

## Features
- Header-only.
- Lazy sequence with very little overhead.
- Very intuitive syntax and semantic.
- All familiar to Python programmers.
- Simple and straightforward implementation.
- Work with both rvalue and lvalue references.
- Iterables can be composed arbitrarily.

## Examples

Use `enumerate` to loop through a container with a counting index.
You are no longer forced to abandon range-based loop when an index is needed!
Instead of
```cpp
std::vector<int> v;
for (int i = 0; i < v.size(); i++) {
    printf("The #%d item is %d\n", i, v[i]);
}
```
You write
```cpp
std::vector<int> v;
for (auto [i, val] : enumerate(v)) {
    printf("The #%d item is %d\n", i, val);
}
```

Use `zip` to simultaneously loop over several containers, stopping at the shortest one amongst them.
Again, you avoid getting your hand dirty to roll out an index-based for and stay the safe zone of range-based for.
```cpp
std::vector<std::string> first_names, last_names;
std::list<unsigned> phone_numbers;

for (auto [first, last, phone] : zip(first_names, last_names, phone_numbers)) {
    printf("Person %s %s, phone number is %u\n", first, last, phone);
}
```
Just looks great.

When you need to apply some function to a sequence and consume the result iteratively,
`std::transform` sucks you up by forcing you to back the output iterator with some container.
In fact `std::transform` is designed to resemble `std::copy` and its friends to *consume* iterators
but not to become an iterable itself. Suppose you want to turn a list of strings upper case, see this example.
```cpp
std::vector<std::string> strings{"hello", "world"};
std::vector<std::string> upper_strings;

// You have to allocate an output variable and use the ugly back_inserter.
std::transform(std::begin(strings), std::end(strings), std::back_inserter(upper_strings), ::toupper);

// Another use case: write to a stream using the adapter ostream_iterator.
std::ostringstream os;
std::transform(std::begin(strings), std::end(strings), std::ostream_iterator<std::string>(os, ", "), ::toupper);
```
In either case, you have to first save the results in some place and then process them.
It is a waste of time and space if you just want to process the result iteratively.
```cpp
std::vector<std::string> strings{"hello", "world"};
for (auto &&str : map(::upper, strings)) {
    std::cout << str << ' ';
}
```
This just looks much cleaner and indeed more efficient.

~~With map and reduce you can rule the world.~~

Your last resistance to the index-based loop will be the `range` class, which implements the index-based loop but
provide you the range-based interface. Think about saying goodbye to the plain old index loop!
```cpp
std::vector<int> v{1, 2, 3, 4};
for (auto i : range(0, v.size()) {
    printf("%d\n", v[i]);
}

// reverse
for (auto i : range(v.size() - 1, -1, -1)) {
    printf("%d\n", v[i]);
}
```

# Install
```bash
cd itertools && mkdir build && cd build
make && make install
```

# License
MIT License
