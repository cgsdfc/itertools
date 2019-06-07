//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_MAP_H
#define ITERTOOLS_MAP_H
#include "detail.h"

namespace itertools {
template <class Callable, class ... Iterators>
using map_value_type = std::invoke_result_t<Callable, typename std::iterator_traits<Iterators>::value_type ...>;

template <class Callable, class ... Iterators>
class map_iterator : public std::iterator<std::forward_iterator_tag, map_value_type<Callable, Iterators...>> {
  Callable func_;
  zip_iterator<Iterators...> args_;
public:
  using value_type = map_value_type<Callable, Iterators...>;
  explicit map_iterator(Callable func, Iterators ... iterators) : func_(func), args_(iterators...) {}
  bool operator==(const map_iterator &rhs) const {
    return args_ == rhs.args_;
  }
  bool operator!=(const map_iterator &rhs) const {
    return !(rhs == *this);
  }
  map_iterator &operator++() {
    ++args_;
    return *this;
  }
  value_type operator*() const {
    auto &&arg_tuple = *args_;
    return std::apply(func_, arg_tuple);
  }
};

template <class Callable, class ... Iterables>
class map {
public:

};
}
#endif //ITERTOOLS_MAP_H
