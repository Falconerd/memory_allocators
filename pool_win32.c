b32 pool_init(pool *p, usize capacity, usize item_size) {
    if (item_size < sizeof(void *)) {
        printf("Cannot initialise a pool with item size less than %zu\n.", sizeof(void *));
        return 0;
    }
    usize size = capacity * item_size;

    p->start = VirtualAlloc(0, capacity * item_size, MEM_COMMIT, PAGE_READWRITE);
    if (!p->start) {
        printf("VirtualAlloc failed to allocate space for pool. Tried to get %zu bytes\n", capacity * item_size);
        return 0;
    }

    p->next_free = p->start;
    p->item_size = item_size;
    p->free_items = capacity;
    p->capacity = capacity;

    for (usize i = 0; i < capacity - 1; i += 1) {
        void **next_ptr = (void **)((byte *)p->start + i * item_size);
        *next_ptr = (byte *)p->start + (i + 1) * item_size;
    }

    void **last_ptr = (void **)((byte *)p->start + (capacity - 1) * item_size);
    *last_ptr = 0;

    return 1;
}