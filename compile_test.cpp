#include "generated/frequency_unit.hpp"
#include "generated/time_unit.hpp"

using namespace units;

struct test_units
{
public:

    test_units(frequency_khz f1, time_ms t1)
        : f(f1),
          t(t1)
    { }
    
    frequency_khz freq() const
    { return f; }
    
    time_ms time() const
    { return t; }

private:

    frequency_khz f;
    time_ms       t;
};    
    

int main()
{
    using namespace units::literals;
    
    auto x = 100.0_khz;
    auto y = 100.0_hz;
    
    frequency_khz f = to_khz(y);
    frequency_hz f3 = to_hz(x);
    std::cout << f << '\n';
    std::cout << f3 << '\n';
    
    auto f2 = x + y;
    std::cout << f2 << '\n';
    
    auto t1 = 1.5_ms;
    auto t2 = 9.5_us;
    auto t3 = t1 + t2;
    std::cout << t3 << '\n';
    
    test_units test_u(105.32_khz, 55.6_ms);
    std::cout << test_u.freq() << '\n';
}
    
