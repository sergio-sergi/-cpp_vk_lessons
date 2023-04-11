#include <cstdio>
#include <cstdlib>
#include <cstring>

int main3() {
    const uint16_t alignment = 64;
    int *pAligned = (int *) aligned_alloc(alignment, alignment * sizeof(*pAligned));
    int *pAligned2{};
    int __attribute__((aligned(alignment))) a[10] = {1, [5] = 10, 4, [1] = 7};
    auto errFlag = posix_memalign((void **) &pAligned2, alignment, sizeof(a));
    if (!errFlag) {
        printf("p and &p are %p and %p\n", pAligned2, &pAligned);
        pAligned2 = static_cast<int *>(memcpy(pAligned2, a, sizeof(a)));
        for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
            printf("pAligned2[%zu] = %d\n", i, pAligned2[i]);
        }
        free(pAligned2);
    } else
        printf("posix_memalign error %d\n", errFlag);
    printf("%d-byte aligned addr: %p\n", alignment, (void *) pAligned);
    for (auto el: a) {
        printf("a = %d\n", el);
    }
    if (pAligned)
        free(pAligned);
    return 0;
}