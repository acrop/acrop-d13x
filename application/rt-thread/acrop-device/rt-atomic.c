#include "rt-atomic.h"

long long unsigned int __atomic_fetch_add_8(volatile void *mem, long long unsigned int val, int model)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  *(long long unsigned int *)mem += val;
  return val_prev;
}

long long unsigned int __atomic_fetch_and_8(volatile void *mem, long long unsigned int val, int model)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  *(long long unsigned int *)mem &= val;
  return val_prev;
}

long long unsigned int __atomic_fetch_or_8(volatile void *mem, long long unsigned int val, int model)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  *(long long unsigned int *)mem |= val;
  return val_prev;
}

long long unsigned int __atomic_fetch_sub_8(volatile void *mem, long long unsigned int val, int model)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  *(long long unsigned int *)mem -= val;
  return val_prev;
}

long long unsigned int __atomic_fetch_xor_8(volatile void *mem, long long unsigned int val, int model)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  *(long long unsigned int *)mem ^= val;
  return val_prev;
}

void __atomic_store_8(volatile void *mem, long long unsigned int val, int model)
{
  *(long long unsigned int *)mem = val;
}

long long unsigned int __atomic_load_8(volatile void *mem, int model)
{
  return *(long long unsigned int *)mem;
}

long long unsigned int __atomic_exchange_8(volatile void *mem, long long unsigned int val, int model)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  *(long long unsigned int *)mem = val;
  return val_prev;
}

_Bool __atomic_compare_exchange_8(volatile void *mem, void *expected, long long unsigned int desired, bool weak, int success, int failure)
{
  long long unsigned int val_prev = *(long long unsigned int *)mem;
  long long unsigned int val_expected = *(long long unsigned int *)expected;
  if (val_prev == val_expected) {
    *(long long unsigned int *)mem = desired;
    return true;
  } else {
    *(long long unsigned int *)expected = val_prev;
    return false;
  }
}
