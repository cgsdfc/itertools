//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_RANGE_H
#define ITERTOOLS_RANGE_H
#include "macros.h"
#include <iterator>

namespace itertools {

template <class Integer>
class range {
  static_assert(std::is_integral_v<Integer>, "range_iterator must handle integer");
public:
  using value_type = Integer;
  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    std::size_t cur_ = 0;
    Integer start_;
    Integer step_;
  public:
    iterator(std::size_t cur, Integer start, Integer step)
        : cur_(cur), start_(start), step_(step) {}
    value_type operator*() const {
      return start_ + cur_ * step_;
    }
    bool operator==(const iterator &that) const {
      return cur_ == that.cur_;
    }
    ITERTOOLS_IMPL_NEQ(iterator)
    iterator &operator++() {
      ++cur_;
    }
  };

public:
  explicit range(Integer stop) : range(0, stop, 1) {}
  range(Integer start, Integer stop) : range(start, stop, 1) {}
  range(Integer start, Integer stop, Integer step)
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
  Integer start_ = 0;
  Integer step_ = 1;
  std::size_t length_ = 0;

  std::size_t compute_length(Integer stop) const {
    Integer low, high;
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
}
#endif //ITERTOOLS_RANGE_H
