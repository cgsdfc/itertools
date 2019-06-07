//
// Created by cgsdfc on 19-6-6.
//
#include "detail.h"
#include "macros.h"

namespace itertools {

using enumerate_index_type = int;

template <class Iterable>
class enumerate {
public:
  using traits = iterable_traits<Iterable>;
  using wrapped_iterable = typename traits::wrapped_iterable;
  using raw_iterator = typename traits::raw_iterator;
  using value_type = std::pair<enumerate_index_type, typename traits::deref_value_type>;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    using Iterator = raw_iterator;
    Iterator iter_;
    enumerate_index_type start_;
  public:
    iterator(Iterator iterator, enumerate_index_type start) : iter_(iterator), start_(start) {}
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

  explicit enumerate(Iterable &&iterable, enumerate_index_type start = 0)
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
  enumerate_index_type start_;
};

template <class Iterable> enumerate(Iterable &&, enumerate_index_type= 0) -> enumerate<Iterable &&>;
}
