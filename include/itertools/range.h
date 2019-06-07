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
  static_assert(std::is_integral_v<Integer>, "range must handle integer");
public:
  using value_type = Integer;
  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    std::size_t cur_ = 0;
    value_type start_;
    value_type step_;
  public:
    iterator(std::size_t cur, value_type start, value_type step)
        : cur_(cur), start_(start), step_(step) {}
    value_type operator*() const {
      return start_ + cur_ * step_;
    }
    bool operator==(const iterator &that) const {
      return cur_ == that.cur_;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
    iterator &operator++() {
      ++cur_;
    }
  };

public:
  explicit range(value_type stop) : range(0, stop, 1) {}
  range(value_type start, value_type stop) : range(start, stop, 1) {}
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

template <class ... Integers>
struct range_integer {
  using common_type = typename std::common_type<Integers...>::type;
  using type = typename std::make_signed<common_type>::type;
};

template <class ... Integers>
range(Integers...) -> range<typename range_integer<Integers...>::type>;

}
#endif //ITERTOOLS_RANGE_H
