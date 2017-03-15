#include <its.h>
#include <stdio.h>
#include <string.h>


int main() {
  its small = its_alloc(3);
  its large = its_alloc(30);
  if (! its_good(small) || ! its_good(large)) {
    fprintf(stderr, "Allocating strings failed!\n");
    return 1;
  }
  char * const cstr_small = its_cstring(&small);
  char * const cstr_large = its_cstring(&large);
  memset(cstr_small, 'a', 2);
  memset(cstr_large, 'b', 29);
  cstr_small[2] = '\0';
  cstr_large[29] = '\0';
  size_t const len_small = its_length(small);
  size_t const len_large = its_length(large);
  bool success = true;
  if (len_small != 2) {
    fprintf(stderr, "String should have length 2, has: %zu\n",
            len_small);
    success = false;
  }
  if (len_large != 29) {
    fprintf(stderr, "String should have length 29, has: %zu\n",
            len_large);
    success = false;
  }
  its_free(small);
  its_free(large);
  return success ? 0 : 1;
}
