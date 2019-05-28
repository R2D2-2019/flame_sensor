#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {
    flame_sensor_c::flame_sensor_c(hwlib::pin_oc &ir_led_1,
                                   hwlib::pin_oc &ir_led_2 = hwlib::pin_oc_dummy ,
                                   hwlib::pin_oc &ir_led_3 = hwlib::pin_oc_dummy,
                                   hwlib::pin_oc &ir_led_4 = hwlib::pin_oc_dummy,
                                   hwlib::pin_oc &ir_led_5 = hwlib::pin_oc_dummy)
        : ir_led_1(ir_led_1),
          ir_led_2(ir_led_2),
          ir_led_3(ir_led_3),
          ir_led_4(ir_led_4),
          ir_led_5(ir_led_5) {
    }

    // made to test output for the leds
    void flame_sensor_c::read_output() {
        hwlib::pin_oc* leds[5] = {&ir_led_1, &ir_led_2, &ir_led_3, &ir_led_4, &ir_led_5};
        bool 
        for (;;) {
            for (int i=0; i<5;++i) {
                //hwlib::wait_ms(500);
                hwlib::cout << leds[i]->read();
            }
            hwlib::cout << hwlib::endl;
            hwlib::wait_ms(100);
        }
    }

    bool flame_sensor_c::is_flame_detected() {
        return ir_led_1.read();
    }

    int flame_sensor_c::get_flame_direction() {
        return 0;
    }
} // namespace r2d2::flame_sensor