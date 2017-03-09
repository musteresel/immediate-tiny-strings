#include "its.h"

#include "config.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


/// Allocate a memory region of the specified size at an even (2 byte
/// aligned) address.
///
/// \TODO Check whether posix_memalign accepts 2 as value for
/// alignment. Perhaps increase to sizeof(void *) to be safe.
///
/// \param[in] size Required size of the memory region.
/// \return Pointer to the memory, or NULL on failure.
inline static void * allocate_2byte_aligned(size_t size) {
#ifdef HAVE_ALIGNED_ALLOC
  return aligned_alloc(2, size);
#elif defined(HAVE_POSIX_MEMALIGN)
  void * ptr;
  if (posix_memalign(&ptr, 2, size) == 0) {
    return ptr;
  } else {
    return NULL;
  }
#else
#error Aligned allocation with malloc not yet implemented!
#endif
}


/// Free memory previously allocated with allocate_2byte_aligned.
///
/// \param[in] ptr Pointer to the 2 byte aligned memory region.
inline static void free_2byte_aligned(void * ptr) {
  assert(((uintptr_t)ptr) & 0x01 == 0);
#if defined(HAVE_ALIGNED_ALLOC) || defined(HAVE_POSIX_MEMALIGN)
  free(ptr);
#else
#error Freeing aligned memory allocated with malloc not yet implemented!
#endif
}


#define PATTERN_IMMEDIATE 0x01
#define PATTERN_INVALID (0x02 | PATTERN_IMMEDIATE)
#define RIGHT_SHIFT_IMMEDIATE_LENGTH 2


its its_alloc(size_t size) {
  its const result = {.data = PATTERN_INVALID};
  return result;
}


bool its_good(its string) {
  return !(string.data & PATTERN_INVALID);
}


void its_free(its string) {
#warning Not implemented
}
