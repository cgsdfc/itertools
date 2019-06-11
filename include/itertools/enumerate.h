//
// Created by cgsdfc on 19-6-6.
//
#include "detail.h"
#include "macros.h"

namespace itertools {

template <class Iterable>
class enumerate {
public:
  using size_type = typename std::make_signed<std::size_t>::type;
  using traits = iterable_traits<Iterable>;
  using wrapped_iterable = typename traits::wrapped_iterable;
  using raw_iterator = typename traits::raw_iterator;
  using value_type = std::pair<size_type, typename traits::deref_value_type>;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    raw_iterator iter_;
    size_type start_;
  public:
    iterator(raw_iterator iterator, size_type start) : iter_(iterator), start_(start) {}
    bool operator==(const iterator &that) const {
      return iter_ == that.iter_;
    }
    iterator &operator++() {
      ++iter_;
      ++start_;
      return *this;
    }
    value_type operator*() const {
      return {start_, *iter_};
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(iterator)
  };

  explicit enumerate(Iterable &&iterable, size_type start = 0)
      : iterable_(std::forward<Iterable>(iterable)), start_(start) {}

  iterator begin() {
    return iterator(std::begin(iterable_), start_);
  }
  iterator end() {
    return iterator(std::end(iterable_), 0);
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(enumerate)
private:
  wrapped_iterable iterable_;
  size_type start_;
};

template <class Iterable> enumerate(Iterable &&) -> enumerate<Iterable &&>;
template <class Iterable, class Index> enumerate(Iterable &&, Index) -> enumerate<Iterable &&>;
}
