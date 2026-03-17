
#include "testcases.h"
#include "AtlasControl.h"
#include "SystemControl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void _Create_System()
{
    g_system_controller = std::make_unique<AtlasControl>();
    g_system_controller->InitializeSystem();
}

TEST_CASE("Check Set kV", "check if the kv is set correctly") {
    _Create_System();

    g_system_controller->SetkV(10, 0);

    auto kv_return = g_system_controller->GetTargetkV(0);

    REQUIRE(kv_return.has_value());
    CHECK(kv_return.value() == 10);
}
