#include <thread>
#include <vector>
#include <future>
#include <chrono>

int findMaxPrefix(std::future<std::vector<int>> &f) {
    printf("find max prefix\n");
    auto vec = f.get();
    std::vector<int> sums(vec.size() + 1);
    sums[0] = 0;
    int maxPref = 0;
    for (size_t i = 1; i < sums.size(); i++) {
        sums[i] = sums[i - 1] + vec[i - 1];
        if (sums[i] > maxPref)
            maxPref = sums[i];
    }
    printf("find max prefix finished\n");
    return maxPref;
}

int maxConsecutiveElements(std::future<std::vector<int>> &f) {
    printf("calc max consecutive elements\n");
    int maxConsEls = 0;
    int currMax;
    auto vec = f.get();
    for (size_t i = 0; i < vec.size(); i += currMax) {
        currMax = 1;
        for (size_t j = i + 1; j < vec.size(); j++) {
            if (vec[i] == vec[j])
                currMax++;
            else if (currMax > maxConsEls)
                maxConsEls = currMax;
        }
    }
    printf("calc max consecutive elements finished\n");
    return maxConsEls;
}

[[maybe_unused]] void foo(int seconds) {
    std::printf("%s started\n", __FUNCTION__);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::printf("%s worked for %d seconds\n", __FUNCTION__, seconds);
}

[[maybe_unused]] void bar(int seconds) {
    std::printf("%s started\n", __FUNCTION__);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::printf("%s worked for %d seconds\n", __FUNCTION__, seconds);
}

bool make_vector(std::vector<int> &vec, std::promise<std::vector<int>> &p) {
    for (auto &val: vec) {
        val = static_cast<int>(random());
    }
    printf("randomization is done\n");
    p.set_value(vec);
    return true;
}

using namespace std::chrono_literals;

int main1() {
    const uint32_t n = 100000;
    std::vector<int> vec(n);
    std::promise<std::vector<int>> p;
    std::future<std::vector<int>> inpVecFu(p.get_future());

    std::future fuMaxConsEls = std::async(std::launch::async, maxConsecutiveElements, std::ref(inpVecFu));
    std::thread t(make_vector, std::ref(vec), std::ref(p));

    printf("%d\n", fuMaxConsEls.get());


//    const uint32_t n = 100000;
//    std::vector<int> vec(n);
//    std::promise<std::vector<int>> setValPromise;
//    std::future<std::vector<int>> sharedFuture = setValPromise.get_future();
//    printf("starting threads...\n");
//    std::future fuMaxConsEls = std::async(std::launch::async, maxConsecutiveElements, std::ref(sharedFuture));
//    std::future generate(make_vector, std::ref(vec));
//    printf("getting randomized vector...\n");
//    generate.join();
//    printf("vector's ready and set\n");
//    setValPromise.set_value(vec);
//    while (sharedFuture.wait_for(1ms) != std::future_status::ready) {
//        printf("...");
//    }
//    printf("threads exited\n");
//    char r;
//    std::scanf("%c", &r);
//    printf("bye");
}