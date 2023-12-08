#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

// TODO: Remove windows.h
#ifdef _WIN32
#include <windows.h>
#endif

/* PRIMITIVES */

typedef int32_t   b32;

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef float     f32;
typedef double    f64;

typedef uintptr_t uptr;
typedef ptrdiff_t size;
typedef size_t    usize;

typedef uint8_t   bit8;
typedef uint16_t  bit16;
typedef uint32_t  bit32;
typedef uint64_t  bit64;

#ifndef byte
typedef uint8_t   byte;
#endif

#define KB (1024ULL)
#define MB (KB * 1024)
#define GB (MB * 1024)
#define DEFAULT_ALIGNMENT (sizeof(void *) * 2)
#define IS_POWER_OF_TWO(x) (x != 0 && (x & (x - 1)) == 0)

usize PAGE_SIZE = 0;

#endif
