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
  using value_type = T;

  using reference = T &;
  using const_reference = const T &;

  using pointer = T *;
  using const_pointer = const T *;

  using iterator = pointer;
  using const_iterator = const_pointer;

  using allocator_type = allocator;
  using size_type = typename std::allocator_traits<allocator>::size_type;
  using difference_type =
      typename std::allocator_traits<allocator>::difference_type;

  // reverse iterator

  std::mdspan<T, std::dextents<size_type, dimension>> view;
  pointer begin_ptr;
  pointer end_ptr;
  pointer capacity_ptr;

  [[no_unique_address]] allocator alloc;

  flat_vector()
      : view(std::allocator_traits<allocator>::allocate(alloc, alignof(T))),
        begin_ptr(view.at()) {}

  template <std::convertible_to<size_type>... idx_list>
    requires(sizeof...(idx_list) == dimension)
  reference operator[](idx_list... indices) noexcept {
    return view[indices...];
  }

  template <std::convertible_to<size_type>... idx_list>
    requires(sizeof...(idx_list) == dimension)
  const_reference operator[](idx_list... indices) const noexcept {
    return view[indices...];
  }

  template <std::convertible_to<size_type>... idx_list>
    requires(sizeof...(idx_list) == dimension)
  reference at(idx_list... indices) {
    return view.at(indices...);
  }

  template <std::convertible_to<size_type>... idx_list>
    requires(sizeof...(idx_list) == dimension)
  const_reference at(idx_list... indices) const {
    return view.at(indices...);
  }

  reference front() noexcept { return *begin_ptr; }
  const_reference front() const noexcept { return *begin_ptr; }

  reference back() noexcept { return *(end_ptr - 1); }
  const_reference back() const noexcept { return *(end_ptr - 1); }

  pointer data() noexcept { return begin_ptr; }
  const_pointer data() const noexcept { return begin_ptr; }

  iterator begin() noexcept { return begin_ptr; }
  const_iterator begin() const noexcept { return begin_ptr; }
  iterator end() noexcept { return end_ptr; }
  const_iterator end() const noexcept { return end_ptr; }
  const_iterator cbegin() const noexcept { return begin_ptr; }
  const_iterator cend() const noexcept { return end_ptr; }

  bool empty() const noexcept { return begin_ptr == end_ptr; }
  size_type size() const noexcept {
    return static_cast<size_type>(end_ptr - begin_ptr);
  }
  size_type capacity() const noexcept {
    return static_cast<size_type>(capacity_ptr - begin_ptr);
  }
  size_type max_size() const noexcept {
    return std::allocator_traits<allocator>::max_size(alloc);
  }

  private:
  void reallocate(size_type new_capacity) {
    // buffer logic seperate
    // copying logic using mdspan with new dextents
    // reuse move constructor
  }


};

} // namespace core::container
#endif
