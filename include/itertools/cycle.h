//
// Created by cgsdfc on 19-6-12.
//

#ifndef ITERTOOLS_CYCLE_H
#define ITERTOOLS_CYCLE_H
#include "detail.h"
#include "macros.h"

namespace itertools {

template <class Iterable>
class cycle {
public:
  using traits = iterable_traits<Iterable>;
  using wrapped_iterable = typename traits::wrapped_iterable;
  using raw_iterator = typename traits::raw_iterator;
  using deref_value_type = typename traits::deref_value_type;

  class iterator {
    // The initial value of iter_.
    const raw_iterator initial_iter_;
    // The value changing through iterating.
    mutable raw_iterator iter_;
  public:
    explicit iterator(raw_iterator iter) : initial_iter_(iter), iter_(iter) {}
    deref_value_type operator*() const {
      return *iter_;
    }
    iterator &operator++() {
      ++iter_;
      return *this;
    }
    bool operator==(const iterator &that) const {
      // At the beginning this range is empty.
      if (initial_iter_ == that.initial_iter_) {
        return true;
      }
      // Non-empty range. Loop over and over.
      if (iter_ == that.iter_) {
        iter_ = initial_iter_;
      }
      return false;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

  explicit cycle(Iterable &&iterable) : iterable_(std::forward<Iterable>(iterable)) {}

  iterator begin() {
    return iterator(std::begin(iterable_));
  }
  iterator end() {
    return iterator(std::end(iterable_));
  }
private:
  wrapped_iterable iterable_;
};

template <class Iterable> cycle(Iterable &&) -> cycle<Iterable &&>;

}
#endif //ITERTOOLS_CYCLE_H
