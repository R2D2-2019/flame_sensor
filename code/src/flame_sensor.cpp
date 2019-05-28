#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {
    flame_sensor_c::flame_sensor_c(hwlib::pin_oc &ir_led_1,
                                   hwlib::pin_oc &ir_led_2,
                                   hwlib::pin_oc &ir_led_3,
                                   hwlib::pin_oc &ir_led_4,
                                   hwlib::pin_oc &ir_led_5)
        : ir_led_1(ir_led_1),
          ir_led_2(ir_led_2),
          ir_led_3(ir_led_3),
          ir_led_4(ir_led_4),
          ir_led_5(ir_led_5) {
    }

    flame_sensor_c::flame_sensor_c(hwlib::pin_oc &ir_led_test)
        : ir_led_1(ir_led_test),
          ir_led_2(hwlib::pin_oc_dummy),
          ir_led_3(hwlib::pin_oc_dummy),
          ir_led_4(hwlib::pin_oc_dummy),
          ir_led_5(hwlib::pin_oc_dummy) {
    }

    flame_sensor_c::flame_sensor_c(hwlib::pin_oc &ir_led_test_a,
                                   hwlib::pin_oc &ir_led_test_d)
        : ir_led_1(ir_led_test_a),
          ir_led_2(ir_led_test_d),
          ir_led_3(hwlib::pin_oc_dummy),
          ir_led_4(hwlib::pin_oc_dummy),
          ir_led_5(hwlib::pin_oc_dummy) {
    }

    // made to test output for the leds
    void flame_sensor_c::test_output() {
        for (;;) {
            hwlib::wait_ms(500);
            // hwlib::cout << "Analog: " << ir_led_0.read()
            //<< hwlib::endl; // led 1 -> analog
            hwlib::cout << "Digital: " << ir_led_1.read()
                        << hwlib::endl; // led 1 -> digital
        }
    }

    bool flame_sensor_c::is_flame_detected() {
        return ir_led_1.read();
    }

    int flame_sensor_c::get_flame_direction() {
        return 0;
    }
} // namespace r2d2::flame_sensor