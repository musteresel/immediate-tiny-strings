#include <assert.h>
#include <its.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool test_conversion_with(char const * cstring) {
  its const string = its_from_cstring(cstring);
  if (! its_good(string)) {
    fprintf(stderr, "Failed to convert \"%s\"\n", cstring);
    return false;
  }
  bool result = true;
  size_t const clen = strlen(cstring);
  size_t const len = its_length(string);
  if (clen != len) {
    fprintf(stderr, "Length wrong (\"%s\"); expected %zu; actual %zu\n",
            cstring, clen, len);
    result = false;
  }
  if (strcmp(cstring, its_const_cstring(&string)) != 0) {
    fprintf(stderr, "Strings don't compare equal (\"%s\")\n",
            cstring);
    result = false;
  }
  its_free(string);
  return result;
}


int main() {
  char const * strings[] = {
    "A", "AB", "ABC", "ABCD", "ABCDE",
    "ABCDEF", "ABCDEFG", "ABCDEFGH", "ABCDEFGHI"};
  assert(sizeof(void *) <= 8); // Otherwise add testcases above!
  bool result = true;
  unsigned i = 0;
  for (; i < sizeof(strings) / sizeof(strings[0]); ++i) {
    bool const test_result = test_conversion_with(strings[i]);
    result = result && test_result;
  }
  return result ? 0 : 1;
}
