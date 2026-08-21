#pragma once

#include "crow.h"

// Vitals module: everything about "is the robot OK right now".
//
// M1/M2 scope: uptime + a static status field, hardcoded platform-agnostic.
// M2 will extend get_vitals() to read real system values (CPU temp, etc.)
// on the Pi — main.cpp and the route stay unchanged when that happens.

namespace vitals {

crow::json::wvalue get_vitals();

}  // namespace vitals