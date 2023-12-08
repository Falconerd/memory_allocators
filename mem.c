uptr align_forward(uptr ptr, usize alignment) {
    uptr p, a, modulo;
    if (!IS_POWER_OF_TWO(alignment)) {
        return 0;
    }

    p = ptr;
    a = (uptr)alignment;

    modulo = p & (a - 1);

    if (modulo) {
        p += a - modulo;
    }

    return p;
}

b32 is_aligned(void *ptr, usize alignment) {
    return ((uptr)ptr % alignment) == 0;
}

