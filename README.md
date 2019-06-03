# Itertools
Python's builtin iterators & itertools in modern C++.

```cpp
#include <itertools.h>

using namespace itertools;

void foo() {
    for (auto i : range(10)) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}
```
