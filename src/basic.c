/// \file
///
/// This file contains code that creates and destroys immediate tiny
/// strings. Creation of immediate tiny strings may need to do an
/// allocation (to store the string when it's not tiny). In order to
/// have one bit "free" to encode whether a immediate tiny string
/// contains the actual tiny string or a pointer to the string the
/// allocation must return an (at least) 2 byte aligned address.


#include "its.h"
#include "config.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


/// Check whether a pointer is aligned to 2 bytes.
///
#define IS_ALIGNED_2BYTE(value) (((uintptr_t)(value) & 0x01) == 0)


/// Allocate a memory region of the specified size at an even (2 byte
/// aligned) address.
///
/// \param[in] size Required size of the memory region.
/// \return Pointer to the memory, or NULL on failure.
inline static void * allocate_2byte_aligned(size_t size) {
#ifdef HAVE_ALIGNED_ALLOC
  return aligned_alloc(2, size);
#elif defined(HAVE_POSIX_MEMALIGN)
  void * ptr;
  if (posix_memalign(&ptr, sizeof(void *), size) == 0) {
    assert(IS_ALIGNED_2BYTE(ptr)); // Paranoia due to uncertainty
                                   // about alignment parameter to
                                   // posix_memalign.
    return ptr;
  } else {
    return NULL;
  }
#else
  char * const memory = malloc(size + 2);
  if (! memory) {
    return NULL;
  }
  if (IS_ALIGNED_2BYTE(memory)) {
    // memory is correctly aligned, but to distinguish from originally
    // not aligned addresses when freeing we need to have at least one
    // byte. Thus we return the next correctly aligned address and
    // leave a note in the byte directly preceeding that address.
    memory[1] = '1';
    return &(memory[2]);
  } else {
    // memory is not correctly aligned. Leave a note in the first byte
    // about this for freeing later and return the next (and correctly
    // aligned) address.
    memory[0] = '0';
    return &(memory[1]);
  }
#endif
}


/// Free memory previously allocated with allocate_2byte_aligned.
///
/// \param[in] ptr Pointer to the 2 byte aligned memory region.
inline static void free_2byte_aligned(void * ptr) {
  assert(IS_ALIGNED_2BYTE(ptr));
#if defined(HAVE_ALIGNED_ALLOC) || defined(HAVE_POSIX_MEMALIGN)
  free(ptr);
#else
  char const * const memory = ptr;
  void const * original_address;
  if (memory[-1] == '0') {
    // malloc returned an address that was not aligned when allocating
    // this memory block. Thus we left one byte unused and returned
    // the address of memory[1]. Now we need to undo this addition.
    original_address = &(memory[-1]);
  } else {
    // malloc returned an address that was aligned. We left two bytes
    // unused and need to undo that now.
    assert(memory[-1] == '1');
    original_address = &(memory[-2]);
  }
  free((void *) original_address);
#endif
}


#define PATTERN_IMMEDIATE 0x01
#define PATTERN_INVALID (0x02 | PATTERN_IMMEDIATE)


its its_alloc(size_t size) {
  if (size < sizeof(uintptr_t)) {
    its const immediate_string = {.data = PATTERN_IMMEDIATE};
    return immediate_string;
  } else {
    void * const memory = allocate_2byte_aligned(size);
    assert(IS_ALIGNED_2BYTE(memory));
    its const allocated_string = {
      .data = memory ? (uintptr_t) memory : PATTERN_INVALID};
    return allocated_string;
  }
}


bool its_good(its string) {
  return (string.data != PATTERN_INVALID);
}


void its_free(its string) {
  if (IS_ALIGNED_2BYTE(string.data)) {
    free_2byte_aligned((void *) string.data);
  } // else immediate, thus no action neccessary
}


size_t its_length(its string) {
  return strlen(its_cstring(&string));
}


char * its_cstring(its * string) {
  assert(string != NULL);
  if (IS_ALIGNED_2BYTE(string->data)) {
    return (char *) string->data;
  } else {
#ifdef WORDS_BIGENDIAN
    return (char *) &string->data;
#else
    // On little endian systems, the least significant byte is stored
    // first. We use this byte to distinguish between immediate and
    // non immediate strings, thus skip it.
    return ((char *) &string->data) + 1;
#endif
  }
}


char const * its_const_cstring(its const * string) {
  // Removing the const is OK because we know that its_cstring won't
  // be modifying the its structure. The returned pointer is converted
  // to a pointer to const, thus also not allowing modifications.
  return its_cstring((its *) string);
}


its its_from_cstring(char const * cstring) {
  its string = its_alloc(strlen(cstring) + 1);
  if (its_good(string)) {
    strcpy(its_cstring(&string), cstring);
  }
  return string;
}
