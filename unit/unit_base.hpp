#pragma once

#include <functional>
#include <iostream>
#include <ratio>
#include <string>

namespace units
{
namespace detail
{

template <typename Tag, typename Value, typename Ratio>
struct unit_string
{ };

template <typename Tag, typename Value, typename Ratio = std::ratio<1>>
class unit
    : public unit_string<Tag, Value, Ratio>
{
public:

    using tag_type   = Tag;
    using value_type = Value;
    using ratio_type = typename Ratio::type;

    explicit unit(Value v)
        : value_(v)
    { }
    
    constexpr Value value() const
    {
        return value_;
    }

private:

    Value value_;
};

struct converter
{
    template <typename Ratio2, typename Tag, typename Value, typename Ratio>
    constexpr static
    unit<Tag, Value, Ratio2> to_other(unit<Tag, Value, Ratio> freq)
    {
        using new_ratio = std::ratio_divide<Ratio2, Ratio>;
        return unit<Tag, Value, Ratio2>(
            (freq.value() * new_ratio::den ) / new_ratio::num
        );
    }
};

template <typename Tag, typename Value, typename Ratio1, 
          typename Ratio2, typename Operator>
detail::unit<Tag, Value, Ratio1> operator_base
(detail::unit<Tag, Value, Ratio1> v1, 
 detail::unit<Tag, Value, Ratio2> v2, 
 Operator op
)
{
    auto as_r1 = detail::converter::to_other<Ratio1>(v2);
    return unit<Tag, Value, Ratio1>(op(v1.value(), as_r1.value()));
}

} // end namespace detail

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator+
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::plus<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator-
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::minus<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator<
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::less<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator<=
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::less_equal<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator>
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::greater<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator>=
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::greater_equal<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator==
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::equal<Value>());
}

template <typename Tag, typename Value, typename Ratio1, typename Ratio2>
detail::unit<Tag, Value, Ratio1> operator!=
(detail::unit<Tag, Value, Ratio1> v1, detail::unit<Tag, Value, Ratio2> v2)
{
    return detail::operator_base(v1, v2, std::not_equal_to<Value>());
}

template <typename Tag, typename Value, typename Ratio>
std::ostream& operator<<(std::ostream& os, detail::unit<Tag, Value, Ratio> u)
{
    os << u.value() << detail::unit<Tag, Value, Ratio>::to_string();
    return os;
}

} // end namespace units

