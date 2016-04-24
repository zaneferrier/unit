#pragma once

#define MAKE_UNIT_STRING_BASE(STR, TAG, RATIO) \
    template <typename Value> \
    struct unit_string<TAG, Value, RATIO> { \
        static std::string to_string() { \
            return {STR}; \
        } \
    }; 
    
#define PASTE_NAMES(TAG, STR) \
    TAG ##_## STR
    
#define MAKE_UNIT_USING_BASE(STR, TAG, TAG_NAME, RATIO) \
    using PASTE_NAMES(TAG_NAME, STR) = detail::unit<TAG, double, RATIO>;
    
#define MAKE_UNIT_CONVERSION_BASE(NAME, TAG, RATIO) \
    template <typename Value, typename Ratio> \
    constexpr detail::unit<TAG, Value, RATIO> \
    to_##NAME(detail::unit<TAG, Value, Ratio> freq) { \
        return detail::converter::to_other<RATIO>(freq); \
    }
    
#define MAKE_UNIT_LITERAL_BASE(STR, TAG) \
    PASTE_NAMES(TAG, STR) operator"" _##STR(long double d) { \
        return PASTE_NAMES(TAG, STR)(static_cast<double>(d)); \
    } \
    PASTE_NAMES(TAG, STR) operator"" _##STR(unsigned long long d) { \
        return PASTE_NAMES(TAG, STR)(static_cast<double>(d)); \
    }

#define MAKE_UNIT_BASE(STR, NAME, TAG, TAG_NAME, RATIO) \
    namespace detail { \
    MAKE_UNIT_STRING_BASE(STR, TAG, RATIO) \
    }\
    MAKE_UNIT_USING_BASE(NAME, TAG, TAG_NAME, RATIO) \
    MAKE_UNIT_CONVERSION_BASE(NAME, TAG, RATIO) \
    \
    inline namespace literals { \
    MAKE_UNIT_LITERAL_BASE(NAME, TAG_NAME) \
    }

