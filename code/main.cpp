#include <flame_sensor.hpp>
#include <hwlib.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    hwlib::cout << "Starting up program...";
    hwlib::wait_ms(500);

    auto test_pin_a = hwlib::target::pin_oc(hwlib::target::pins::a0);
    auto test_pin_d = hwlib::target::pin_oc(hwlib::target::pins::d22);
    r2d2::flame_sensor::flame_sensor_c sensor =
        r2d2::flame_sensor::flame_sensor_c(test_pin_d);

    sensor.test_output();
}