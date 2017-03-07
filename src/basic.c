#include "its.h"

#include "config.h"
#include <stdbool.h>
#include <stddef.h>


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
