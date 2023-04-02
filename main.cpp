#include <iostream>
#include <unistd.h>

int main() {
    int *pAlligned = (int *) aligned_alloc(256, 256 * sizeof(*pAlligned));
    int *pAlligned2 = nullptr, errFlag{};
    int __attribute((aligned(64))) a[10] = {1, [5] = 10, 4, [1] = 7};
    errFlag = posix_memalign((void**)&pAlligned2, 64, sizeof(a));
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
    printf("64-byte aligned addr: %p\n", (void*)pAlligned);
    for (auto el: a) {
        std::cout << el << ' ';
    }
    if (pAlligned)
        free(pAlligned);
    return 0;
}