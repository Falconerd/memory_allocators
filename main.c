#include "common.h"
#include "allocator.c"
#include "mem.c"
#include "arena.c"
#include "bump.c"
#include "pool.c"

#include "arena_test.c"
#include "bump_test.c"
#include "pool_test.c"
#include "allocator_test.c"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    arena_test_all();
    bump_test_all();
    pool_test_all();

    test_arena_allocator_interface();
    test_bump_allocator_interface();
    test_pool_allocator_interface();    

    printf("All tests passed.\n");
    return 0;
}

