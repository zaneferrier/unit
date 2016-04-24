#pragma once

#include "unit/unit_base.hpp"
#include "unit/unit_macro.hpp"

#include <ratio>

namespace units
{

struct frequency_tag {};

MAKE_UNIT_BASE("Hz", hz, frequency_tag, frequency, std::ratio<1>)
MAKE_UNIT_BASE("kHz", khz, frequency_tag, frequency, std::kilo)
MAKE_UNIT_BASE("MHz", mhz, frequency_tag, frequency, std::mega)
MAKE_UNIT_BASE("GHz", ghz, frequency_tag, frequency, std::giga)

} // end namespace units

