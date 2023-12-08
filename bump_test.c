void test_bump_initialization() {
    bump test_bump;
    assert(bump_init(&test_bump));
    assert(test_bump.base != NULL);
    assert(test_bump.size == BUMP_DEFAULT_SIZE);
    assert(test_bump.offset == 0);
    assert(test_bump.committed == 0);
    printf("Bump initialization test passed.\n");
}

void test_bump_allocation() {
    bump test_bump;
    bump_init(&test_bump);

    void *block1 = bump_alloc(&test_bump, 1024);
    assert(block1 != NULL);
    assert(test_bump.offset == 1024);

    void *block2 = bump_alloc(&test_bump, test_bump.size); // This should fail
    assert(block2 == NULL);

    printf("Bump allocation test passed.\n");
}

void test_bump_free_all() {
    bump test_bump;
    bump_init(&test_bump);

    bump_alloc(&test_bump, 1024);
    bump_alloc(&test_bump, 2048);

    bump_free_all(&test_bump);
    assert(test_bump.offset == 0);
    assert(test_bump.committed == 0);

    void *block = bump_alloc(&test_bump, 512);
    assert(block != NULL); // Should work after free_all

    printf("Bump free all test passed.\n");
}

void test_bump_edge_cases() {
    bump test_bump;
    bump_init(&test_bump);

    // Allocation of zero bytes
    void *block_zero = bump_alloc(&test_bump, 0);
    assert(block_zero == NULL);

    printf("Bump edge case tests passed.\n");
}

void bump_test_all() {
    test_bump_initialization();
    test_bump_allocation();
    test_bump_free_all();
    test_bump_edge_cases();
}
