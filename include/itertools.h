//
// Created by cgsdfc on 19-6-3.
//

#ifndef ITERTOOLS_ITERTOOLS_H
#define ITERTOOLS_ITERTOOLS_H

#include "itertools/enumerate.h"
#include "itertools/zip.h"
#include "itertools/range.h"

namespace itertools {

#if 0
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
class map : public IterableAdapter<map_iterator<Callable, iter_from_iterable < Iterables>...>>
{
public:
using Base = IterableAdapter<map_iterator<Callable, iter_from_iterable < Iterables>...>>;
using iterator = typename Base::iterator;
explicit map(Callable func, Iterables &... iterables) : Base(
    iterator(func, std::begin(iterables)...),
    iterator(func, std::end(iterables)...)
) {}
};

template <class Integer>
class count_iterator {
  Integer start_ = 0;
  Integer step_ = 1;
public:
  count_iterator(Integer start, Integer step) : start_(start), step_(step) {}

};
#endif
}

#endif //ITERTOOLS_ITERTOOLS_H
