#ifndef _STL_EXTENSION_TRX_TYPE_TRAITS_H_
#define _STL_EXTENSION_TRX_TYPE_TRAITS_H_

#include <type_traits>

namespace trx {
//! Helper function/class templates for the current header.
namespace detail_trx {
//! tlx_and's helper for the case of no template argument
template <bool... vals>
constexpr std::enable_if_t<sizeof...(vals)==0, bool> tlx_and_impl() {
  return true;
}

//! tlx_and's helper for the case of one template arguments
template <bool val>
constexpr bool tlx_and_impl() {
  return val;
}

//! tlx_and's helper for the case of multiple template arguments
template <bool val, bool... vals>
constexpr std::enable_if_t<sizeof...(vals)>=1, bool> tlx_and_impl() {
  return val && tlx_and_impl<vals...>();
}

} // namespace detail_trx

//! Returns the result of logical and of all template arguments.
/*!
  Returns the result of logical and of all template arguments.
  If the template arguments is empty, returns true.
*/ 
template <bool... vals>
constexpr bool tlx_and() {
  return detail_trx::tlx_and_impl<vals...>();
}

} // namespace trx

#endif // _STL_EXTENSION_TRX_TYPE_TRAITS_H_
