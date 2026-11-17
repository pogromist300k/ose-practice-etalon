#ifndef INCLUDE_GUARD_ASSERT_H
#define INCLUDE_GUARD_ASSERT_H

#include "panic.h"

#ifdef DEBUG_MODE
  #define assert(cond) \
    if (!(cond)) \
      kernel_panic("Assertion failed: " #cond " at " __FILE__ ":%u", __LINE__);
#else
  #define assert(cond)
#endif

#endif
