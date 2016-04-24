#pragma once

#include "unit/unit_base.hpp"
#include "unit/unit_macro.hpp"

#include <ratio>

namespace units
{

struct time_tag {};

MAKE_UNIT_BASE("s", s, time_tag, time, std::ratio<1>)
MAKE_UNIT_BASE("ms", ms, time_tag, time, std::milli)
MAKE_UNIT_BASE("us", us, time_tag, time, std::micro)
MAKE_UNIT_BASE("ns", ns, time_tag, time, std::nano)

} // end namespace units

