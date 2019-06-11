//
// Created by cgsdfc on 19-6-10.
//

#ifndef ITERTOOLS_COUNT_H
#define ITERTOOLS_COUNT_H
#include <cstddef>
#include <type_traits>

namespace itertools {
template <class Number, std::size_t Args>
class count;

template <class Number>
class count<Number, 0> {

};

template <class ... Numbers>
count(Numbers...) -> count<typename std::common_type<Numbers...>::type, sizeof...(Numbers)>;
}

#endif //ITERTOOLS_COUNT_H
