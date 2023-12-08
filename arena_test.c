void test_arena_initialization() {
    arena test_arena;
    assert(arena_init(&test_arena));
    assert(test_arena.base != 0);
    assert(test_arena.size == ARENA_DEFAULT_SIZE);
    assert(test_arena.offset == 0);
    assert(test_arena.committed == 0);
    printf("Arena initialization test passed.\n");
}

void test_arena_allocation() {
    arena test_arena;
    arena_init(&test_arena);

    void *block1 = arena_alloc(&test_arena, 1024);
    assert(block1 != 0);
    assert(is_aligned(block1, DEFAULT_ALIGNMENT));
    assert(test_arena.offset >= 1024);

    void *block2 = arena_alloc(&test_arena, test_arena.size); // This should fail
    assert(block2 == 0);

    printf("Arena allocation test passed.\n");
}

void test_arena_alignment() {
    arena test_arena;
    arena_init(&test_arena);

    void *block = arena_alloc_aligned(&test_arena, 1024, 64);
    assert(block != 0);
    assert(is_aligned(block, 64));

    printf("Arena alignment test passed.\n");
}

void test_arena_free_all() {
    arena test_arena;
    arena_init(&test_arena);

    arena_alloc(&test_arena, 1024);
    arena_alloc(&test_arena, 2048);

    arena_free_all(&test_arena);
    assert(test_arena.offset == 0);
    assert(test_arena.committed == 0);

    void *block = arena_alloc(&test_arena, 512);
    assert(block != 0); // Should work after free_all

    printf("Arena free all test passed.\n");
}

void test_arena_edge_cases() {
    arena test_arena;
    arena_init(&test_arena);

    // Allocation of zero bytes
    void *block_zero = arena_alloc(&test_arena, 0);
    assert(block_zero == 0);

    // Non-power-of-two alignment
    void *block_non_pow2 = arena_alloc_aligned(&test_arena, 1024, 30);
    assert(block_non_pow2 == 0);

    printf("Arena edge case tests passed.\n");
}

void arena_test_all() {
    test_arena_initialization();
    test_arena_allocation();
    test_arena_alignment();
    test_arena_free_all();
    test_arena_edge_cases();
}
