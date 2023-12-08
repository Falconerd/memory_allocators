typedef struct pool {
    void *start;
    void *next_free;
    usize item_size;
    usize free_items;
    usize capacity;
} pool;

#ifdef _WIN32
#include "pool_win32.c"
#else
#include "pool_linux.c"
#endif

void *pool_alloc(void *context, usize unused) {
    pool *p = (pool *)context;
    (void)unused;

    if (p->free_items == 0) {
        return 0;
    }

    void *item = p->next_free;
    p->next_free = *(void **)item;
    p->free_items -= 1;

    return item;
}

void pool_free(void *context, void *item) {
    pool *p = (pool *)context;
    if (!item) {
        return;
    }

    *(void **)item = p->next_free;
    p->next_free = item;
    p->free_items += 1;
}

void pool_free_all(void *context) {
    pool *p = (pool *)context;
    for (usize i = 0; i < p->capacity - 1; i += 1) {
        void **next_ptr = (void **)((byte *)p->start + i * p->item_size);
        *next_ptr = (byte *)p->start + (i + 1) * p->item_size;
    }

    void **last_ptr = (void **)((byte *)p->start + (p->capacity - 1) * p->item_size);
    *last_ptr = 0;
    p->next_free = p->start;
    p->free_items = p->capacity;
}

#define allocator_pool_init(pool_ptr) (allocator){pool_ptr, pool_alloc, pool_free, pool_free_all}
