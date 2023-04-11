// T a[N][M] - N последовательно расположенных в памяти строк по M элементов типа T в каждой.
// для a[N][M] верно:
// a == &a[0], a + i == &a[i]
// *a == a[0] == &a[0][0]
// **a == *&a[0][0] == a[0][0]
// a[i][j] == *(*(a+i)+j)

// int (*pd)[2]; - указатель на массив из 2 эл-тов типа int
// int *pda[5]; - массив из 5 указателей на int

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>


const size_t N = 1001;
const size_t M = 1001;

uint64_t sum(std::vector<std::vector<uint32_t>> &inp, bool horiz = true) {
    uint64_t res{};
    if (horiz) {
        for (size_t j = 0; j < inp[0].size(); ++j) {
            for (auto &i: inp) {
                res += i[j];
            }
        }
    } else {
        for (size_t i = 0; i < inp.size(); ++i) {
            for (size_t j = 0; j < inp[0].size(); ++j) {
                res += inp[i][j];
            }
        }
    }
    return res;
}

uint64_t sum(size_t n, uint64_t (*a)[M], bool horizontal = true) {
    uint64_t res{};
    if (horizontal) {
        for (size_t j = 0; j < M; ++j) {
            for (size_t i = 0; i < n; ++i) {
                res += a[i][j];
            }
        }
    } else {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < M; ++j) {
                res += a[i][j];
            }
        }
    }
    return res;
}

TEST_CASE("Array access") {
    uint64_t a[N][M];
    uint32_t first = 0;
    for (auto &row: a) {
        for (auto &el: row) {
            el = first++;
        }
    }
    first = 0;
    std::vector<std::vector<uint32_t >> vec(N);
    for (auto &row: vec) {
        row.resize(M);
        std::iota(row.begin(), row.end(), first);
        first += row.size();
    }
    auto s = sum(vec);
    printf("%llu", s);
    REQUIRE(s == sum(vec, false));
    BENCHMARK("Sum vec horizontal") {
                                        return sum(vec);
                                    };
    BENCHMARK("Sum vec vertical") {
                                      return sum(vec, false);
                                  };
}