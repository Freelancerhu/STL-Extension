#ifndef _STL_EXTENSION_TRX_ALGORITHM_H_
#define _STL_EXTENSION_TRX_ALGORITHM_H_

#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <functional>
#include <list>
#include <type_traits>
#include <vector>

#include "type_traits.h"

namespace trx {
//! helper function/class templates for the current header
namespace detail_trx {
//! sort's helper for std::list and std::forward_list
template <class T, class Allo, template <class, class> class Container>
std::enable_if_t<
    std::is_same<Container<T, Allo>, std::list<T, Allo> >::value ||
    std::is_same<Container<T, Allo>, std::forward_list<T, Allo> >::value,
    void> sort_impl(Container<T, Allo> &container) {
  container.sort();
}

//! sort's helper for std::vector and std::deque
template <class T, class Allo, template <class, class> class Container>
std::enable_if_t<
    std::is_same<Container<T, Allo>, std::vector<T, Allo> >::value ||
    std::is_same<Container<T, Allo>, std::deque<T, Allo> >::value,
    void> sort_impl(Container<T, Allo> &container) {
  std::sort(container.begin(), container.end());
}

//! sort's helper for std::array
template <class T, size_t N>
void sort_impl(std::array<T, N> &container) {
  std::sort(container.begin(), container.end());
}

} // namespace detail_trx

//! Searches for the best element among those for which predicate returns true.
/*!
  Searches for the best element among those for which predicate returns true.
  If there are more than one best element, then the first one will be returned.
  
  Parameters
  first, last - the range of elements to examine
  up - unary predicate which returns true for the required sub range
  bp - binary predicate which returns true if the first argument is better
       than the second

  Type requirements
  ForwardIt must meet the requirements of ForwardIterator
  UnaryPredicate must meet the requirements of unary predicate
  BinaryPredicate must meet the requirements of binary predicate

  Return value
  Iterator to the best element in the sub range of [first, last). If several
  elements in the range are equivalent to the best element, returns the
  iterator to the first such element. Returns last if the sub range is empty.

  Time Complexity
  O(n), where n = std::distance(first, last).

  Space Complexity
  O(1)

  Example
  int numbers[] = {1,2,3,4,5,6,7,8,9,10};
  assert(*best_if(numbers, std::end(numbers),
                  [](int x){return x%2==1;}, // subranges of all odd numbers
                  std::greater<int>()) // the biggest
             == 9);
*/
template <class ForwardIt, class UnaryPredicate, class BinaryPredicate>
ForwardIt best_if(ForwardIt first, ForwardIt last, UnaryPredicate up,
                  BinaryPredicate bp) {
  ForwardIt best = last;
  for (; first!=last; ++first)
    if (up(*first) && (first==last || bp(*first, *best)))
      best = first;
  return best;
}

//! Returns the max element among the arguments.
/*!
  Returns the max element among the arguments.
  All arguments must have the same type, while value category can be different.
  
  Parameters
  first - the first element.
  rest... - the rest elements.

  Return value
  The max element, which is returned by value.

  Time Complexity
  O(n)

  Space Complexity
  O(n)
  Note : n std::reference_wrappers is constructed, no data is copied.

  Example
  assert(max_among(1, 2, 5, 4, 3) == 5);
*/
template <class Arg, class... Args>
inline Arg max_among(const Arg &first, const Args&... rest) {
  static_assert(sizeof...(rest)==0 ||
                    tlx_and<std::is_same<Arg, Args>::value...>(),
                "All arguments must have the same type.");
  std::array<std::reference_wrapper<const Arg>, sizeof...(rest)+1> arguments{
    std::ref(first), std::ref(static_cast<const Arg &>(rest))...};
  return *std::max_element(arguments.begin(), arguments.end());
}

//! Returns the max element among the arguments.
/*!
  Returns the max element among the arguments.
  All arguments must can be static_cast to Args, i.e. static_cast<Arg>(rest)
  must be a valide expression.
  
  Parameters
  first - the first element.
  rest... - the rest elements.

  Return value
  The max element, which is returned by value(cast to the type of the first
  element).

  Time Complexity
  O(n)

  Space Complexity
  O(n)
  Note : n std::reference_wrappers is constructed, no data is copied.

  Example
  assert(max_among_trunc(1, 2, 5.0, 4.3, 3) == 5);
*/
template <class Arg, class... Args>
inline Arg max_among_trunc(const Arg &first, const Args&... rest) {
  return max_among(first, static_cast<Arg>(rest)...);
}

//! Sorts the given standard container in ascending order.
/*!
  Sorts the given standard container in ascending order. Uses operator< to
  compare the elements.
  
  Parameters
  container - the container by non-const lvalue reference.

  Return value
  (none)

  Time Complexity
  O(nlogn)

  Space Complexity
  (unspecified)

  Example
  std::vector<int> vtr{9,1,3,4,2};
  sort(vtr);
*/
template <class Container>
void sort(Container &container) {
  detail_trx::sort_impl(container);
}

//! Sorts the given standard container in ascending order.
/*!
  Sorts the given standard container in ascending order. Uses the given
  comparison function comp to compare the elements.
  
  Parameters
  container - the container by non-const lvalue reference.
  comp - comparision function object.

  Return value
  (none)

  Time Complexity
  O(nlogn)

  Space Complexity
  (unspecified)

  Example
  std::vector<int> vtr{9,1,3,4,2};
  sort(vtr, std::greater<>());
*/
template <class Container, class Comp>
void sort(Container &container, Comp comp) {
  detail_trx::sort_impl(container, comp);
}

} // namespace trx

#endif // _STL_EXTENSION_TRX_ALGORITHM_H_
