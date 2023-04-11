#include <string>
#include <utility>

class Sample {
public:
    explicit Sample(const char *str) : string_(str) {}

    explicit Sample(std::string str) : string_(std::move(str)) {}

    explicit Sample(int i) : intPrm_(i) {}

    explicit Sample(double d) : doublePrm_(d) {}

    explicit operator int() const { return intPrm_; }

    explicit operator double() const { return doublePrm_; }

private:
    std::string string_{};
    int intPrm_{};
    double doublePrm_{};
};

int main() {
    Sample s1(1);
    Sample s2(0.1);
    Sample s3("abc");
    std::string s("hello");
    Sample s4(std::move(s));
    auto b = (double) s2;
    auto c = (int) s1;
    printf("%f %d", b, c);
}