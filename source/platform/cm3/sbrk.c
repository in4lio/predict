// Copyright (c) 2014 Liviu Ionescu.
// Copyright (c) 2016 Vitaly Kravtsov.

#include "include.h"
#include <sys/types.h>
#include <errno.h>

char* __max_heap_end__;

// The definitions used here should be kept in sync with the
// stack definitions in the linker script.

caddr_t _sbrk(int incr)
{
  extern char __end__; // Defined by the linker.
  extern char __HeapLimit; // Defined by the linker.

  static char* current_heap_end;
  char* current_block_address;

  if (current_heap_end == 0) {
      current_heap_end = &__end__;
      __max_heap_end__ = current_heap_end;
  }

  current_block_address = current_heap_end;

  // Need to align heap to word boundary, else will get
  // hard faults on Cortex-M0. So we assume that heap starts on
  // word boundary, hence make sure we always add a multiple of
  // 4 to it.
  incr = (incr + 3) & (~3); // align value to 4
  if (current_heap_end + incr > &__HeapLimit) {
      // Heap has overflowed
      errno = ENOMEM;
      ERROR(heap);
      return (caddr_t) - 1;
  }
  current_heap_end += incr;
  if (__max_heap_end__ < current_heap_end) __max_heap_end__ = current_heap_end;

  return (caddr_t) current_block_address;
}
