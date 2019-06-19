#include <flame_sensor.hpp>
#include <hwlib.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    hwlib::cout << "Starting up...";

    // digital pins
    //    auto test_pin_1 = hwlib::target::pin_oc(hwlib::target::pins::d22);
    //    auto test_pin_2 = hwlib::target::pin_oc(hwlib::target::pins::d24);
    //    auto test_pin_3 = hwlib::target::pin_oc(hwlib::target::pins::d26);
    //    auto test_pin_4 = hwlib::target::pin_oc(hwlib::target::pins::d28);
    //    auto test_pin_5 = hwlib::target::pin_oc(hwlib::target::pins::d30);

    // analog pins
    auto test_pin_1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a4);
    auto test_pin_2 = hwlib::target::pin_adc(hwlib::target::ad_pins::a3);
    auto test_pin_3 = hwlib::target::pin_adc(hwlib::target::ad_pins::a2);
    auto test_pin_4 = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);
    auto test_pin_5 = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);

    r2d2::flame_sensor::flame_sensor_c sensor =
        r2d2::flame_sensor::flame_sensor_c(test_pin_1, test_pin_2, test_pin_3,
                                           test_pin_4, test_pin_5, 2000, 40,
                                           120);
    for (;;) {
        if (sensor.is_flame_detected()) {
            hwlib::cout << sensor.get_flame_direction() << hwlib::endl;
        } else {
            hwlib::cout << "No Fire!" << hwlib::endl;
        }
        hwlib::wait_ms(100);
    }
}