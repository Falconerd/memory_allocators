b32 arena_init_sized(arena *a, usize size) {
    if (!PAGE_SIZE) {
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        PAGE_SIZE = info.dwPageSize;
    }

    *a = (arena){
        .size = size,
        .base = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE)
    };

    if (!a->base) {
        return 0;
    }

    return 1;
}

void *arena_alloc_aligned(arena *a, usize size, usize alignment) {
    uptr curr_ptr = (uptr)a->base + (uptr)a->offset;
    uptr offset = align_forward(curr_ptr, alignment);
    offset -= (uptr)a->base;

    if (offset + size > a->size) {
        printf("Arena is full. Tried to allocated %zu bytes, but %zu available.\n", size, a->size - a->offset);
        return 0;
    }

    usize s = PAGE_SIZE * (size / PAGE_SIZE + 1);
    void *try = VirtualAlloc((byte *)a->base + a->committed, s, MEM_COMMIT, PAGE_READWRITE);
    if (!try) {
        printf("VirtualAlloc failed to commit %zu bytes starting at %p.\n", s, (byte *)a->base + a->committed);
        return 0;
    }

    a->committed += s;
    void *ptr = (byte *)a->base + offset;
    a->offset = offset + size;

    return ptr;
}

