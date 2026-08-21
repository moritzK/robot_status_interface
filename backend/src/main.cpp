#include "crow.h"
#include "crow/middlewares/cors.h"
#include "vitals.hpp"

// M1 scope: prove the toolchain + deploy loop works end to end.
// CORS is enabled now (even with no frontend yet) so M4's React app
// can call this API without a same-origin surprise later.

int main() {
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .origin("*")            // fine for local dev; tighten before any real deployment
        .methods("GET"_method);

    CROW_ROUTE(app, "/api/vitals")
    ([]() {
        return vitals::get_vitals();
    });

    // 8080 avoids clashing with anything else running on the Pi during dev
    app.port(8080).multithreaded().run();
}