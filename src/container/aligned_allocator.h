/**
 * @file aligned_allocator.h
 * @brief Implementation and header for aligned_allocator
 * @details aligned_allocator allocates memory on heap aligned to cache line
 * boundaries to prevent false-sharing when using concurrent data structures
 * allocated by this allocator.
 * @see std::allocator
 * @author tacoearth
 */

#ifndef _CORE_ALIGNED_ALLOCATOR
#define _CORE_ALIGNED_ALLOCATOR

#include <algorithm>
#include <cstddef>
#include <new>

/**
 * @namespace core::container
 * @brief Thread-safe containers, data structures and algorithms to be used by
 * the core.
 */
namespace core::container {

template <class T> struct aligned_allocator {

  // Required by allocator_traits
  using value_type = T;

  /**
   * @brief Memory alignment
   * @details If type is larger than the cache line, for e.g. some AVX types,
   * alignment is as per the layout of the type.
   * */
  constexpr static std::size_t alignment =
      std::max(alignof(T), std::hardware_constructive_interference_size);

  /**
   * @brief Explicitly default constructor
   * @details Defined to avoid deletion when T has a non-default constructor.
   */
  constexpr aligned_allocator() noexcept = default;

  /**
   * @brief Explicitly default destructor
   * @details Defined to avoid deletion when T has a non-default destructor.
   */
  constexpr ~aligned_allocator() noexcept = default;

  /**
   * @brief Copy constructor
   * @details Copy constructor which allows for rebinding
   */
  template <class U>
  constexpr aligned_allocator(const aligned_allocator<U> &) noexcept {}

  /**
   * @brief Allocate memory
   * @details Allocates memory with cache-line width padding and alignment for
   * performance and avoiding thread contention.
   *
   * @return Pointer to the allocated memory
   * @param [in] n Number of elements
   *
   */
  [[nodiscard]] inline T *allocate(std::size_t n) {
    std::size_t size =
        ((n * sizeof(T) + alignment - 1) / alignment) * alignment;
    return static_cast<T *>(
        ::operator new(size, static_cast<std::align_val_t>(alignment)));
  }

  /**
   * @brief Deallocate memory
   * @details Deallocate memory allocated by aligned_allocater.
   *
   * @par Returns
   *  Nothing.
   * @param [in] pointer Address of previously allocated pointer
   * @param [in] n Number of members in previous allocation
   */
  inline void deallocate(T *pointer, std::size_t n) noexcept {
    std::size_t size =
        ((n * sizeof(T) + alignment - 1) / alignment) * alignment;
    ::operator delete(pointer, size, static_cast<std::align_val_t>(alignment));
  }

  /**
   * @brief Overloaded operator==
   * @details  Declares the allocator to be stateless to allow for optimizations
   * which involve allocator A freeing up an allocation by allocator B.
   * Implicitly defines operator!= as well.
   */
  template <class U, class W>
  friend constexpr bool operator==(const aligned_allocator<U> &,
                                   const aligned_allocator<W> &) noexcept {
    return true;
  }
  using is_always_equal = std::true_type; /**< Trait used by allocator_traits */
};

} // namespace core::container

#endif
