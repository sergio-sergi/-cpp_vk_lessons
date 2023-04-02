#include <iostream>

int main() {
    int *pAlligned = (int *) aligned_alloc(256, 256 * sizeof(*pAlligned));
    int __attribute((aligned(64))) a[10] = {1, [5] = 10, 4, [1] = 7};
    printf("64-byte aligned addr: %p\n", (void*)pAlligned);
    for (auto el: a) {
        std::cout << el << ' ';
    }
    if (pAlligned)
        free(pAlligned);
    return 0;
}