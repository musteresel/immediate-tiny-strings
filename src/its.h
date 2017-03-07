#ifndef IMMEDIATE_TINY_STRING_HEADER
#define IMMEDIATE_TINY_STRING_HEADER 1
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/// Structure holding an immediate tiny string.
///
/// This structure either directly contains the tiny string, or if the
/// string is not "tiny" then the pointer to where to string is stored
/// (as a C string) in memory.
typedef struct its_structure {
  uintptr_t data; ///< Either a pointer to the C string, or the actual
                  ///< string, together with a bit to indicate which
                  ///< of those it is.
} its;


/// Allocate space for a string of the given size.
///
/// If the size is too large to make an immediate string, then this
/// function will allocate dynamic memory. Otherwise it just returns
/// an appropriately initialised its structure.
///
/// Allocation failure can (and must) be performed by calling its_good
/// on the return value.
///
/// \param[in] size Desired size of the new string.
/// \return The new string.
its its_alloc(size_t size);


/// Free a previously allocated string.
///
/// Frees any memory that might have been dynamically allocated for
/// the given string. Assumes that the given string is "good", that is
/// calling its_good on it would return true.
///
/// \remark Because the string is passed by value the string object of
/// the caller won't actually be changed in any way. So even after
/// freeing the string, calling its_good would still return true even
/// though the (possibly) allocated memory has been freed!
///
/// \param[in] string A "good" its string to be freed.
void its_free(its string);


/// Check whether a string is "good", i.e. allocation succeeded.
///
/// \remark A string which is short enough to be immediate will always
/// be "good" as there wasn't an allocation that could have failed.
///
/// \param[in] string String to check.
/// \return True if string is good, false otherwise.
bool its_good(its string);


#endif // IMMEDIATE_TINY_STRING_HEADER
