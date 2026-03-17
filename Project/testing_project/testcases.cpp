
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

//test cases for XRF Interface
TEST_CASE("Check Set kV", "check if the kv is set correctly") {
    _Create_System();

    CHECK(g_system_controller->SetkV(10, 0) == XRFInterface::Error::no_error);

    auto kv_return = g_system_controller->GetTargetkV(0);

    REQUIRE(kv_return.has_value());
    CHECK(kv_return.value() == 10);
}

TEST_CASE("Check Bad Set Over Max kV", "check if the kv can be set incorrectly") {
    _Create_System();
    auto max_kv = g_system_controller->GetMaxkV(0);

    REQUIRE(max_kv.has_value());
    CHECK(g_system_controller->SetkV(max_kv.value() + 1, 0) != XRFInterface::Error::no_error);
}

TEST_CASE("Check Bad Set Under Min kV", "check if the kv can be set incorrectly") {
    _Create_System();

    auto min_kv = g_system_controller->GetMinkV(0);

    REQUIRE(min_kv.has_value());
    CHECK(g_system_controller->SetkV(min_kv.value() - 1, 0) != XRFInterface::Error::no_error);
}

TEST_CASE("Check Set uA", "check if the uA is set correctly") {
    _Create_System();

    CHECK(g_system_controller->SetuA(10, 0) == XRFInterface::Error::no_error);

    auto kv_return = g_system_controller->GetTargetuA(0);

    REQUIRE(kv_return.has_value());
    CHECK(kv_return.value() == 10);
}

TEST_CASE("Check Bad Set Over Max uA", "check if the uA can be set incorrectly") {
    _Create_System();
    auto max_ua = g_system_controller->GetMaxuA(0);

    REQUIRE(max_ua.has_value());
    CHECK(g_system_controller->SetuA(max_ua.value() + 1, 0) != XRFInterface::Error::no_error);
}

TEST_CASE("Check Bad Set Under Min uA", "check if the uA can be set incorrectly") {
    _Create_System();

    auto min_ua = g_system_controller->GetMinuA(0);

    REQUIRE(min_ua.has_value());
    CHECK(g_system_controller->SetkV(min_ua.value() - 1, 0) != XRFInterface::Error::no_error);
}

TEST_CASE("Check XRF Beam Enable", "check if the beam is set correctly") {
    _Create_System();

   CHECK(g_system_controller->EnableBeam(0) == XRFInterface::Error::no_error);

   auto beam_return = g_system_controller->IsBeamEmittingXrays(0);

   REQUIRE(beam_return.has_value());
   CHECK(beam_return.value() == TRUE);

   CHECK(g_system_controller->DisableBeam(0) == XRFInterface::Error::no_error);

   beam_return = g_system_controller->IsBeamEmittingXrays(0);

   REQUIRE(beam_return.has_value());
   CHECK(beam_return.value() == FALSE);
}

TEST_CASE("Check Set Shutter", "check if the beams shutter is set correctly") {
    _Create_System();

    CHECK(g_system_controller->SetShutter(TRUE, 0) == XRFInterface::Error::no_error);

    auto shutter_return = g_system_controller->IsShutterOpen(0);

    REQUIRE(shutter_return.has_value());
    CHECK(shutter_return.value() == TRUE);

    CHECK(g_system_controller->SetShutter(FALSE, 0) == XRFInterface::Error::no_error);

    shutter_return = g_system_controller->IsShutterOpen(0);

    REQUIRE(shutter_return.has_value());
    CHECK(shutter_return.value() == FALSE);
}