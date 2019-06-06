//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_RANGE_H
#define ITERTOOLS_RANGE_H
#include <iterator>

namespace itertools {

template <class Integer>
class range_iterator : public std::iterator<std::forward_iterator_tag, Integer> {
  static_assert(std::is_integral_v<Integer>, "range_iterator must handle integer");
  std::size_t cur_ = 0;
  Integer start_;
  Integer step_;
public:
  using value_type = Integer;
  range_iterator(std::size_t cur, Integer start, Integer step)
      : cur_(cur), start_(start), step_(step) {}
  Integer operator*() const {
    return start_ + cur_ * step_;
  }
  bool operator==(const range_iterator &that) const {
    return cur_ == that.cur_;
  }
  bool operator!=(const range_iterator &that) const {
    return !(that == *this);
  }
  range_iterator &operator++() {
    ++cur_;
  }
};

template <class Integer>
class range {
  using iterator = range_iterator<Integer>;
  Integer start_ = 0;
  Integer stop_;
  Integer step_ = 1;
  std::size_t length_ = 0;

  std::size_t compute_length() const {
    Integer low, high;
    std::size_t pos_step;
    if (step_ > 0) {
      low = start_;
      high = stop_;
      pos_step = step_;
    } else {
      low = stop_;
      high = start_;
      pos_step = -step_;
    }
    if (low > high)
      return 0;
    return ((high - low - 1) / pos_step) + 1;
  }

public:
  explicit range(Integer stop) : range(0, stop, 1) {}
  range(Integer start, Integer stop) : range(start, stop, 1) {}
  range(Integer start, Integer stop, Integer step)
      : start_(start), stop_(stop), step_(step) {
    length_ = compute_length();
  }

  iterator begin() const {
    return {0, start_, step_};
  }

  iterator end() const {
    return {length_, start_, step_};
  }
};
}
#endif //ITERTOOLS_RANGE_H
