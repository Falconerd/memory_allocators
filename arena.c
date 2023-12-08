typedef struct arena {
    void *base;
    usize size;
    usize offset;
    usize committed;
} arena;

#define ARENA_DEFAULT_SIZE (512 * MB)

#ifdef _WIN32
#include "arena_win32.c"
#else
#include "arena_linux.c"
#endif

b32 arena_init(arena *a) {
    return arena_init_sized(a, ARENA_DEFAULT_SIZE);
}

void *arena_alloc(void *context, usize size) {
    if (!size) {
        return 0;
    }

    return arena_alloc_aligned((arena *)context, size, DEFAULT_ALIGNMENT);
}

void arena_free(void *a, void *ptr_or_size) {
    (void)a;
    (void)ptr_or_size;
}

void arena_free_all(void *context) {
    arena *a = context;
    a->offset = 0;
    a->committed = 0;
}

#define allocator_arena_init(arena_ptr) (allocator){arena_ptr, arena_alloc, arena_free, arena_free_all}
