/**
 * @file flat_vector.h
 * @brief Implementation and header for flat_vector
 * @details templated k-dimensional vectors allocated contigously
 * @see std::vector
 * @author tacoearth
 */

#ifndef _CORE_FLAT_VECTOR
#define _CORE_FLAT_VECTOR

#include "aligned_allocator.h"
#include <algorithm>
#include <cstddef>
#include <mdspan>
#include <memory>
#include <new>

/**
 * @namespace core::container
 * @brief Thread-safe containers, data structures and algorithms to be used by
 * the core.
 */
namespace core::container {

template <typename T, std::size_t dimension,
          class allocator = core::container::aligned_allocator<T>>
struct flat_vector {

private:
  using size_type = size_t;
  std::mdspan<T, std::dextents<size_type, dimension>> view;
  T *begin;
  size_t size;

  [[no_unique_address]] allocator alloc;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  flat_vector() : view(std::allocator_traits<allocator>::allocate(alloc, 20)) {}
};

} // namespace core::container
#endif
