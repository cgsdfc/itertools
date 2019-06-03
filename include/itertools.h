//
// Created by cgsdfc on 19-6-3.
//

#ifndef ITERTOOLS_ITERTOOLS_H
#define ITERTOOLS_ITERTOOLS_H
#include <iterator>

namespace itertools {

// Adapt an Iterator class to an Iterable class.
template <class Iterator>
class IterableAdapter {
  Iterator begin_;
  Iterator end_;
public:
  using iterator = Iterator;
  IterableAdapter(Iterator begin, Iterator end) : begin_(begin), end_(end) {}
  Iterator begin() { return begin_; }
  Iterator end() { return end_; }
};

template <class Iterable>
using iterator_maybe_const = std::conditional_t<std::is_const_v<Iterable>,
                                                typename Iterable::const_iterator,
                                                typename Iterable::iterator>;

template <template <class> class FunctionIterator, class Iterable>
using IterableWrapper = IterableAdapter<FunctionIterator<iterator_maybe_const<Iterable>>>;

using enum_index_type = int;

template <class Iterator>
using enum_value_type = std::pair<int, typename std::iterator_traits<Iterator>::reference>;

template <class Iterator>
class enum_iterator : public std::iterator<std::forward_iterator_tag, enum_value_type<Iterator>> {
  Iterator iter_;
  enum_index_type start_;
public:
  using value_type = enum_value_type<Iterator>;
  explicit enum_iterator(Iterator iterator, enum_index_type start = 0) : iter_(iterator), start_(start) {}
  bool operator==(const enum_iterator &that) const {
    return iter_ == that.iter_;
  }
  bool operator!=(const enum_iterator &that) const {
    return !operator==(that);
  }
  enum_iterator &operator++() {
    ++iter_;
    ++start_;
    return *this;
  }
  value_type operator*() {
    return {start_, *iter_};
  }
};

template <class Iterable>
class enumerate : public IterableWrapper<enum_iterator, Iterable> {
public:
  using Base =  IterableWrapper<enum_iterator, Iterable>;
  using iterator = typename Base::iterator;

  explicit enumerate(Iterable &iterable, enum_index_type start = 0) : Base(
      iterator(std::begin(iterable), start),
      iterator(std::end(iterable))
  ) {}
};

}

namespace std {

}
#endif //ITERTOOLS_ITERTOOLS_H
