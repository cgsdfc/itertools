//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_MAP_H
#define ITERTOOLS_MAP_H
#include <tuple>
#include "detail.h"
#include "zip.h"

namespace itertools {

template <class Callable, class ... Iterables>
class map {
public:
  using value_type = typename std::invoke_result<Callable,
                                                 typename iterable_traits<Iterables>::deref_value_type...>::type;
  using wrapped_iterable = zip<Iterables...>;
  using raw_iterator = typename wrapped_iterable::iterator;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    Callable func_;
    raw_iterator args_;
  public:
    iterator(Callable func, raw_iterator args) : func_(std::move(func)), args_(std::move(args)) {}
    bool operator==(const iterator &that) const {
      return args_ == that.args_;
    }
    value_type operator*() const {
      return std::apply(func_, *args_);
    }
    iterator &operator++() {
      ++args_;
      return *this;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };
  explicit map(Callable func, Iterables &&... iterables)
      : func_(std::move(func)), iterable_(std::forward<Iterables>(iterables)...) {}
  iterator begin() {
    return iterator(func_, iterable_.begin());
  }
  iterator end() {
    return iterator(func_, iterable_.end());
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(map)
private:
  Callable func_;
  wrapped_iterable iterable_;
};

template <class Callable, class Iterable>
class map<Callable, Iterable> {
public:
  using traits = iterable_traits<Iterable>;
  using wrapped_iterable = typename traits::wrapped_iterable;
  using raw_iterator = typename traits::raw_iterator;
  using value_type = typename std::invoke_result<Callable, typename traits::deref_value_type>::type;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    Callable func_;
    raw_iterator arg_;
  public:
    iterator(Callable func, raw_iterator arg) : func_(std::move(func)), arg_(std::move(arg)) {}
    value_type operator*() {
      return func_(*arg_);
    }
    bool operator==(const iterator &that) const {
      return arg_ == that.arg_;
    }
    iterator &operator++() {
      ++arg_;
      return *this;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

  map(Callable func, Iterable &&iterable)
      : func_(std::move(func)), iterable_(std::forward<Iterable>(iterable)) {}

  iterator begin() {
    return iterator(func_, std::begin(iterable_));
  }
  iterator end() {
    return iterator(func_, std::end(iterable_));
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(map)
private:
  Callable func_;
  wrapped_iterable iterable_;
};

template <class Callable, class ... Iterables>
map(Callable, Iterables &&...) -> map<Callable, Iterables && ...>;

}
#endif //ITERTOOLS_MAP_H
