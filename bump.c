typedef struct bump {
    void *base;
    usize size;
    usize offset;
    usize committed;
} bump;

#define BUMP_DEFAULT_SIZE (512 * MB)

#ifdef _WIN32
#include "bump_win32.c"
#else
#include "bump_linux.c"
#endif

b32 bump_init(bump *b) {
    return bump_init_sized(b, BUMP_DEFAULT_SIZE);
}

void bump_free(bump *b, void *ptr_or_size) {
    (void)b;
    (void)ptr_or_size;
}

void bump_free_all(bump *b) {
    b->offset = 0;
    b->committed = 0;
}

#define allocator_bump_init(bump_ptr) (allocator){bump_ptr, bump_alloc, bump_free, bump_free_all}
