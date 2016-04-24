#pragma once

#include "unit/unit_base.hpp"
#include "unit/unit_macro.hpp"

#include <ratio>

namespace units
{

struct weight_tag {};

using g_to_pnd = std::ratio<5000, 12>;

MAKE_UNIT_BASE("g", g, weight_tag, weight, std::ratio<1>)
MAKE_UNIT_BASE("kg", kg, weight_tag, weight, std::kilo)
MAKE_UNIT_BASE("pnd", pnd, weight_tag, weight, g_to_pnd)

} // end namespace units

