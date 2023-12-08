typedef struct allocator {
    void *context;
    void *(*alloc)(void *context, usize size);
    void (*free)(void *context, void *ptr_or_size);
    void (*free_all)(void *context);
} allocator;
