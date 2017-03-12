#include <its.h>
#include <stdio.h>

int main() {
  unsigned size;
  unsigned failures = 0;
  for (size = 0; size < 100; ++size) {
    its const string = its_alloc(size);
    if (! its_good(string)) {
      ++failures;
      fprintf(stderr, "Failed to allocate size %u\n", size);
    } else {
      its_free(string);
    }
  }
  return (failures > 0);
}
