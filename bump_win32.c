b32 bump_init_sized(bump *b, usize size) {
    if (!PAGE_SIZE) {
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        PAGE_SIZE = info.dwPageSize;
    }

    *b = (bump){
        .size = size,
        .base = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE)
    };

    if (!b->base) {
        return 0;
    }

    return 1;
}

void *bump_alloc(bump *b, usize size) {
    if (!size) {
        return 0;
    }

    usize new_offset = b->offset + size;

    if (new_offset > b->size) {
        printf("Bump is full. Tried to allocate %zu bytes, but only %zu available.\n", size, b->size - b->offset);
        return 0;
    }

    usize pages_required = (new_offset / PAGE_SIZE) - (b->committed / PAGE_SIZE);
    if (new_offset % PAGE_SIZE) {
        pages_required += 1;
    }

    if (pages_required > 0) {
        usize additional_size = pages_required * PAGE_SIZE;
        void *try = VirtualAlloc((byte *)b->base + b->committed, additional_size, MEM_COMMIT, PAGE_READWRITE);
        if (!try) {
            printf("VirtualAlloc failed to commit %zu bytes starting at %p.\n", additional_size, (byte *)b->base + b->committed);
            return 0;
        }
        b->committed += additional_size;
    }

    void *ptr = (byte *)b->base + b->offset;
    b->offset = new_offset;

    return ptr;
}
