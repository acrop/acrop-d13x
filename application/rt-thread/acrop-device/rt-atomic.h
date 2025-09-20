#include <stdbool.h>
#include <stdint.h>

long long unsigned int __atomic_fetch_add_8(volatile void *mem, long long unsigned int val, int model);
long long unsigned int __atomic_fetch_and_8(volatile void *mem, long long unsigned int val, int model);
long long unsigned int __atomic_fetch_or_8(volatile void *mem, long long unsigned int val, int model);
long long unsigned int __atomic_fetch_sub_8(volatile void *mem, long long unsigned int val, int model);
long long unsigned int __atomic_fetch_xor_8(volatile void *mem, long long unsigned int val, int model);
void __atomic_store_8(volatile void *mem, long long unsigned int val, int model);
long long unsigned int __atomic_load_8(volatile void *mem, int model);
long long unsigned int __atomic_exchange_8(volatile void *mem, long long unsigned int val, int model);
_Bool __atomic_compare_exchange_8(volatile void *mem, void *expected, long long unsigned int desired, bool weak, int success, int failure);