//
// Created by cgsdfc on 19-6-10.
//

#ifndef ITERTOOLS_REPEAT_H
#define ITERTOOLS_REPEAT_H
#include <iterator>
#include "detail.h"
#include "macros.h"

namespace itertools {
template <class T, bool Infinite>
class repeat;

template <class T>
class repeat<T, true> {
public:
  using value_type = T;
  class iterator {
    value_type value_;
  public:
    using iterator_category = std::forward_iterator_tag;
    explicit iterator(value_type value) : value_(std::move(value)) {}
    bool operator==(const iterator &) const {
      return false; // for operator!= to be always true.
    }
    value_type operator*() const {
      return value_;
    }
    iterator &operator++() {
      return *this;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

  explicit repeat(value_type value) : value_(std::move(value)) {}
  iterator begin() {
    return iterator(value_);
  }
  iterator end() {
    return iterator(value_);
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(repeat)
private:
  value_type value_;
};

template <class T>
repeat(T) -> repeat<T, true>;

template <class T>
class repeat<T, false> {
public:
  using size_type = std::size_t;
  using value_type = T;

  class iterator {
    value_type value_;
    size_type times_;
  public:
    using iterator_category = std::forward_iterator_tag;
    iterator(value_type value, size_type times)
        : value_(std::move(value)), times_(times) {}
    bool operator==(const iterator &that) const {
      return times_ == that.times_;
    }
    iterator &operator++() {
      ++times_;
      return *this;
    }
    value_type operator*() const {
      return value_;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

  repeat(value_type value, size_type times)
      : value_(std::move(value)), times_(times) {}

  iterator begin() {
    return iterator(value_, 0);
  }
  iterator end() {
    return iterator(value_, times_);
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(repeat)
private:
  value_type value_;
  size_type times_;
};

template <class T, class I>
repeat(T, I) -> repeat<T, false>;
}

#endif //ITERTOOLS_REPEAT_H
