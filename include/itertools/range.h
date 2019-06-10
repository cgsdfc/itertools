//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_RANGE_H
#define ITERTOOLS_RANGE_H
#include "macros.h"
#include <iterator>

namespace itertools {

// TODO: any ctor that has optional arguments can be optimized to have less members
// given the default value coded in. This optimization can make them closer to hand-rolled loop.

template <class Integer, std::size_t Args>
class range;

namespace detail {
template <class Integer>
class single_step_iterator : public std::iterator<std::forward_iterator_tag, Integer> {
  Integer cur_;
public:
  explicit single_step_iterator(Integer value) : cur_(value) {}
  bool operator==(const single_step_iterator &that) const {
    return cur_ == that.cur_;
  }
  Integer operator*() const {
    return cur_;
  }
  single_step_iterator &operator++() {
    ++cur_;
    return *this;
  }
  ITERTOOLS_IMPL_NEQ_POST_INC(single_step_iterator)
};
}

template <class Integer>
class range<Integer, 1> {
public:
  using value_type = Integer;
  using iterator = detail::single_step_iterator<value_type>;
  explicit range(value_type stop) : stop_(stop) {}
  iterator begin() {
    return iterator(0);
  }
  iterator end() {
    return iterator(std::max(0, stop_));
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(range)
private:
  value_type stop_;
};

template <class Integer>
class range<Integer, 2> {
public:
  using value_type = Integer;
  using iterator = detail::single_step_iterator<value_type>;
  range(value_type start, value_type stop) : start_(start), stop_(stop) {}
  iterator begin() {
    return iterator(start_);
  }
  iterator end() {
    return iterator(std::max(stop_, start_));
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(range)
private:
  value_type start_;
  value_type stop_;
};

template <class Integer>
class range<Integer, 3> {
public:
  using size_type = std::size_t;
  using value_type = Integer;
  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    size_type cur_ = 0;
    value_type start_;
    value_type step_;
  public:
    iterator(size_type cur, value_type start, value_type step)
        : cur_(cur), start_(start), step_(step) {}
    value_type operator*() const {
      return start_ + cur_ * step_;
    }
    bool operator==(const iterator &that) const {
      return cur_ == that.cur_;
    }
    iterator &operator++() {
      ++cur_;
      return *this;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

public:
  range(value_type start, value_type stop, value_type step)
      : start_(start), step_(step) {
    length_ = compute_length(stop);
  }

  iterator begin() {
    return iterator(0, start_, step_);
  }
  iterator end() {
    return iterator(length_, start_, step_);
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(range)
private:
  value_type start_ = 0;
  value_type step_ = 1;
  std::size_t length_ = 0;

  std::size_t compute_length(value_type stop) const {
    value_type low, high;
    std::size_t pos_step;
    if (step_ > 0) {
      low = start_;
      high = stop;
      pos_step = step_;
    } else {
      low = stop;
      high = start_;
      pos_step = -step_;
    }
    if (low > high)
      return 0;
    return ((high - low - 1) / pos_step) + 1;
  }
};

namespace detail {
template <class ... Integers>
struct range_integer {
  using common_type = typename std::common_type<Integers...>::type;
  using type = typename std::make_signed<common_type>::type;
};
}

template <class ... Integers>
range(Integers...) -> range<typename detail::range_integer<Integers...>::type, sizeof...(Integers)>;

}
#endif //ITERTOOLS_RANGE_H
