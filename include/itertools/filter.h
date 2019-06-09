//
// Created by cgsdfc on 19-6-9.
//

#ifndef ITERTOOLS_FILTER_H
#define ITERTOOLS_FILTER_H
#include "detail.h"
#include "macros.h"

namespace itertools {
template <class Callable, class Iterable, bool FilterFalse>
class basic_filter {
public:
  using traits = iterable_traits<Iterable>;
  using raw_iterator = typename traits::raw_iterator;
  using wrapped_iterable = typename traits::wrapped_iterable;
  using deref_value_type = typename traits::deref_value_type;
  using value_type = typename std::iterator_traits<raw_iterator>::value_type;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    Callable func_;
    mutable raw_iterator iter_;
  public:
    iterator(Callable func, raw_iterator iter) : func_(std::move(func)), iter_(std::move(iter)) {}
    deref_value_type operator*() const {
      // We have to skip since a value is needed right now.
      // And in most cases this is guarded by operator==.
      while (FilterFalse == func_(*iter_)) {
        ++iter_;
      }
      return *iter_;
    }
    bool operator==(const iterator &that) const {
      // We have to skip since the end (that) is passed in and it's time to consume the iter safely (without going out of range)
      while (iter_ != that.iter_ && FilterFalse == func_(*iter_)) {
        ++iter_;
      }
      return iter_ == that.iter_;
    }
    iterator &operator++() {
      // We don't skip here since it is unsafe (without end known) and the result is not needed.
      ++iter_;
      return *this;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

  basic_filter(Callable func, Iterable &&iterable)
      : func_(std::move(func)), iterable_(std::forward<Iterable>(iterable)) {}

  iterator begin() {
    return iterator(func_, std::begin(iterable_));
  }
  iterator end() {
    return iterator(func_, std::end(iterable_));
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(basic_filter);

private:
  Callable func_;
  wrapped_iterable iterable_;
};

#define INSTANTIATE_FILTER(NAME, FILTER_FALSE) \
template <class Callable, class Iterable> \
struct NAME : basic_filter<Callable, Iterable, FILTER_FALSE> { \
  NAME(Callable func, Iterable &&iterable) \
      : basic_filter<Callable, Iterable, FILTER_FALSE>(std::move(func), std::forward<Iterable>(iterable)) {} \
}; \
template <class Callable, class Iterable> \
NAME(Callable func, Iterable &&iterable) ->NAME<Callable, Iterable &&>;

INSTANTIATE_FILTER(filter, false)
INSTANTIATE_FILTER(filter_false, true)

}

#endif //ITERTOOLS_FILTER_H
