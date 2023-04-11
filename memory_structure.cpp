#if defined(__GNUC__) || defined(__GNUC__)
#define always_inline gnu::always_inline
#elif defined(__clang__)
#define always_inline clang::always_inline
#elif defined(_MSC_VER)
#define always_inline msvc::forceinline
#endif

#include <type_traits>
// КАРТА ПАМЯТИ процесса состоит из СЕГМЕНТА ДАННЫХ и ПРОГРАММНОГО СТЕКА
// в СЕГМЕНТ ДАННЫХ входят ОБЛАСТЬ ДАННЫХ, СЕГМЕНТ BSS И КУЧА

// ОБЛАСТЬ ДАННЫХ (data area) - используется для переменных со статической продолжительностью
// хранения, явно получивших значение при инициализации
// - делится на область констант (read-only area) и область чтения/записи (read-write area)
// - инициализируется при загрузке программы, но до входа в main на основании образа
// соответсвующих переменных в объектном файле

// BSS SEGMENT, .bss - предназначен для статических переменных, не получивших
// значение при инициализации (инициализир. 0 битами)
// - располагается выше ОБЛАСТИ ДАННЫХ (по более старшим адресам)
// - может эффективно заполняться нулями до входа в main (zero fill on demand)

// КУЧА (heap) - контроллируется программистом посредством вызова напр. malloc/free
// - располагается выше сегмента BSS
// - является общей для всех разделяемых библиотек и динамически загружаемых объектов
// (DLO, dynamically loaded objects) процесса

// ПРОГРАММНЫЙ СТЕК (stack) - содержит значения передаваемые функции при ее вызове
// (stack frame) и автоматические переменные
// - следует дисциплине LIFO
// - растет вниз, противоположно КУЧЕ
// - обычно занимает самые верхние (максимальные) адреса виртуального адресного пространства процесса


#include <cstdio>
#include <any>
#include <variant>

class Test {
public:
    [[nodiscard]] [[always_inline]] static int foo() {
        return 42;
    }


    static bool isZero(std::variant<uint32_t, uint64_t> &t)  // return type depends on template parameters
    {
        return std::holds_alternative<uint32_t>(t) ? (std::get<uint32_t>(t) == 0 || std::get<uint32_t>(t) == UINT32_MAX)
                                                   : (std::get<uint64_t>(t) == 0 ||
                                                      std::get<uint64_t>(t) == UINT64_MAX);
    }

    static bool isZero(std::any &t)  // return type depends on template parameters
    {
        try {
            auto tmp = std::any_cast<uint32_t>(t);
            return tmp == 0 || tmp == UINT32_MAX;
        }
        catch (std::bad_any_cast &) {
            try {
                auto tmp = std::any_cast<uint64_t>(t);
                return tmp == 0 || tmp == UINT64_MAX;
            }
            catch (std::bad_any_cast &) {
                return false;
            }
        }
    }
};

int main2() {
    auto a = Test::foo();
    printf("%d", a);
    return 0;
}
