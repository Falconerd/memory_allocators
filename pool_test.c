void test_pool_initialization() {
    pool test_pool;
    usize capacity = 10;
    usize item_size = sizeof(usize);
    assert(pool_init(&test_pool, capacity, item_size));
    assert(test_pool.start != 0);
    assert(test_pool.next_free == test_pool.start);
    assert(test_pool.item_size == item_size);
    assert(test_pool.free_items == capacity);
    assert(test_pool.capacity == capacity);
    printf("Pool initialization test passed.\n");
}

void test_pool_allocation_and_free() {
    pool test_pool;
    usize capacity = 10;
    usize item_size = sizeof(usize);
    pool_init(&test_pool, capacity, item_size);

    // Test allocation
    for (usize i = 0; i < capacity; i++) {
        void *item = pool_alloc(&test_pool, 0);
        assert(item != 0);
        assert(test_pool.free_items == capacity - i - 1);
    }

    // Allocation should fail now since pool is full
    assert(pool_alloc(&test_pool, 0) == 0);

    // Test free
    for (usize i = 0; i < capacity; i++) {
        void *item = (byte *)test_pool.start + i * item_size;
        pool_free(&test_pool, item);
        assert(test_pool.free_items == i + 1);
    }

    printf("Pool allocation and free test passed.\n");
}

void test_pool_free_all() {
    pool test_pool;
    usize capacity = 10;
    usize item_size = sizeof(usize);
    pool_init(&test_pool, capacity, item_size);

    pool_alloc(&test_pool, 0);
    pool_alloc(&test_pool, 0);

    pool_free_all(&test_pool);
    assert(test_pool.next_free == test_pool.start);
    assert(test_pool.free_items == capacity);

    printf("Pool free all test passed.\n");
}

void pool_test_all() {
    test_pool_initialization();
    test_pool_allocation_and_free();
    test_pool_free_all();
}
