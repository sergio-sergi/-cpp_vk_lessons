#include <iostream>
#include <unistd.h>

int main() {
    const uint16_t alignment = 8;
    int *pAlligned = (int *) aligned_alloc(alignment, alignment * sizeof(*pAlligned));
    int *pAlligned2 = nullptr;
    int __attribute((aligned(alignment))) a[10] = {1, [5] = 10, 4, [1] = 7};
    auto errFlag = posix_memalign((void**)&pAlligned2, alignment, sizeof(a));
    if(!errFlag){
        printf("p and &p are %p and %p\n", pAlligned2, &pAlligned);
         pAlligned2 = static_cast<int *>(memcpy(pAlligned2, a, sizeof(a)));
         for(size_t i = 0; i < sizeof(a)/ sizeof(a[0]); ++i){
             printf("pAligned2[%zu] = %d\n", i, pAlligned2[i]);
         }
        free(pAlligned2);
    }
    else
        printf("posix_memalign error %d\n", errFlag);
    printf("%d-byte aligned addr: %p\n",alignment, (void*)pAlligned);
    for (auto el: a) {
        std::cout << el << ' ';
    }
    if (pAlligned)
        free(pAlligned);
    return 0;
}