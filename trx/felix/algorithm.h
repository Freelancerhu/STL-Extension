#ifndef _STL_EXTENSION_TRX_ALGORITHM_H_
#define _STL_EXTENSION_TRX_ALGORITHM_H_

namespace trx {

// --------------------
//
// Search for the best element among those for which predicate up returns true
//
// Parameters
// first, last - the range of elements to examine
// up - unary predicate which returns true for the required sub range
// bp - binary predicate which returns true if the first argument is better
//      than the second
//
// Type requirements
// ForwardIt must meet the requirements of ForwardIterator
// UnaryPredicate must meet the requirements of unary predicate
// BinaryPredicate must meet the requirements of binary predicate
//
// Return value
// Iterator to the best element in the sub range of [first, last). If several
// elements in the range are equivalent to the best element, returns the
// iterator to the first such element. Returns last if the sub range is empty.
//
// Time Complexity
// O(n), where n = std::distance(first, last).
//
// Space Complexity
// O(1)
//
// Example
// int numbers[] = {1,2,3,4,5,6,7,8,9,10};
// assert(*best_if(numbers, std::end(numbers),
//                 [](int x){return x%2==1;}, // subranges of all odd numbers
//                 std::greater<int>()) // the biggest
//            == 9);
//
// --------------------
template <class ForwardIt, class UnaryPredicate, class BinaryPredicate>
ForwardIt best_if(ForwardIt first, ForwardIt last, UnaryPredicate up,
                  BinaryPredicate bp) {
  ForwardIt best = last;
  for (; first!=last; ++first)
    if (up(*first) && (first==last || bp(*first, *best)))
      best = first;
  return best;
}

} // namespace trx

#endif // _STL_EXTENSION_TRX_ALGORITHM_H_
