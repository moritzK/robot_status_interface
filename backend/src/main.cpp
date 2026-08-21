#include "crow.h"
#include <chrono>

// M1 scope: prove the toolchain + deploy loop works end to end.
// Values are hardcoded here on purpose — M2 replaces this with real
// system reads (uptime, CPU temp, etc). Don't add sensor code yet.

int main() {
    crow::SimpleApp app;

    const auto start_time = std::chrono::steady_clock::now();

    CROW_ROUTE(app, "/api/vitals")
    ([&start_time]() {
        auto now = std::chrono::steady_clock::now();
        auto uptime_sec = std::chrono::duration_cast<std::chrono::seconds>(
            now - start_time
        ).count();

        crow::json::wvalue vitals;
        vitals["status"] = "OK";
        vitals["uptime_sec"] = uptime_sec;
        vitals["source"] = "robot_status_interface (M1 stub)";

        return vitals;
    });

    // 8080 avoids clashing with anything else running on the Pi during dev
    app.port(8080).multithreaded().run();
}