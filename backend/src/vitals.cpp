#include "vitals.hpp"

#include <chrono>
#include <unistd.h>  // gethostname — POSIX, works on macOS and the Pi (Linux)

namespace vitals {

namespace {
const auto kStartTime = std::chrono::steady_clock::now();
}

crow::json::wvalue get_vitals() {
    auto now = std::chrono::steady_clock::now();
    auto uptime_sec = std::chrono::duration_cast<std::chrono::seconds>(
        now - kStartTime
    ).count();

    char hostname_buf[256] = {0};
    gethostname(hostname_buf, sizeof(hostname_buf));

    crow::json::wvalue result;
    result["status"] = "OK";
    result["uptime_sec"] = uptime_sec;
    result["hostname"] = std::string(hostname_buf);
    result["source"] = "robot_status_interface (M1 stub)";
    result["robo_temp_c"] = 42.0;  
    result["robo_battery_pct"] = 100.0;
    result["robo_battery_voltage"] = 12.5;
    result["robo_battery_current"] = 1.5;
    result["name"] = "Robi";

    return result;
}

}  // namespace vitals