/// \file
///
/// This is the header file containing the user visible API of the
/// immediate tiny strings library. It contains the structure and type
/// definition of the its type as well as declarations of all
/// available functions that are part of the library.


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
/// Allocation failure can (and must) be checked for by calling
/// its_good on the return value.
///
/// \warning The contents of the string won't be initialised; using
/// them without assigning content first results in undefined
/// behaviour.
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


/// Determine the length of the string.
///
/// \remark This operation takes time linear to the actual length of
/// the string.
///
/// \param[in] string The string whose length is asked for.
/// \return The length of the string.
size_t its_length(its string);


/// Get access to the underlying C string.
///
/// \warning Do not write beyond the strings length, otherwise
/// behavior is undefined!
///
/// \param[in,out] string String whose C string is to be accessed.
/// \return C string backing the immediate tiny string.
char * its_cstring(its * string);


/// Get (read only) access to the underlying C string.
///
/// \see its_cstring(its*)
char const * its_const_cstring(its const * string);


/// Create an immediate tiny string from a C string.
///
/// Creates a new immediate tiny string and copies the given C string
/// to it.
///
/// \param[in] cstring C string which shall be converted to an
/// immediate tiny string.
/// \return Immediate tiny string with the same contents as the given
/// C string.
its its_from_cstring(char const * cstring);


#endif // IMMEDIATE_TINY_STRING_HEADER
