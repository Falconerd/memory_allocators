void test_arena_allocator_interface() {
    arena test_arena;
    assert(arena_init(&test_arena));
    allocator arena_allocator = allocator_arena_init(&test_arena);

    void *block1 = arena_allocator.alloc(arena_allocator.context, 1024);
    assert(block1 != 0);

    // 'free' function doesn't do anything for arena, but we call it for interface compliance
    arena_allocator.free(arena_allocator.context, block1);

    arena_allocator.free_all(arena_allocator.context);
    assert(test_arena.offset == 0);

    printf("Arena allocator interface test passed.\n");
}

void test_bump_allocator_interface() {
    bump test_bump;
    assert(bump_init(&test_bump));
    allocator bump_allocator = allocator_bump_init(&test_bump);

    void *block1 = bump_allocator.alloc(bump_allocator.context, 1024);
    assert(block1 != NULL);

    // 'free' function doesn't do anything for bump, but we call it for interface compliance
    bump_allocator.free(bump_allocator.context, block1);

    bump_allocator.free_all(bump_allocator.context);
    assert(test_bump.offset == 0);

    printf("Bump allocator interface test passed.\n");
}

void test_pool_allocator_interface() {
    pool test_pool;
    usize capacity = 10;
    usize item_size = sizeof(usize);
    assert(pool_init(&test_pool, capacity, item_size));
    allocator pool_allocator = allocator_pool_init(&test_pool);

    void *item = pool_allocator.alloc(pool_allocator.context, 0); // size parameter is unused in pool_alloc
    assert(item != NULL);

    pool_allocator.free(pool_allocator.context, item);

    pool_allocator.free_all(pool_allocator.context);
    assert(test_pool.free_items == capacity);

    printf("Pool allocator interface test passed.\n");
}
