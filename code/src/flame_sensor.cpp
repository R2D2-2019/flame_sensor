#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {
    flame_sensor_c::flame_sensor_c(hwlib::pin_oc &ir_led_1,
                                   hwlib::pin_oc &ir_led_2 = hwlib::pin_oc_dummy,
                                   hwlib::pin_oc &ir_led_3 = hwlib::pin_oc_dummy,
                                   hwlib::pin_oc &ir_led_4 = hwlib::pin_oc_dummy,
                                   hwlib::pin_oc &ir_led_5 = hwlib::pin_oc_dummy)
        : ir_led_1(ir_led_1),
          ir_led_2(ir_led_2),
          ir_led_3(ir_led_3),
          ir_led_4(ir_led_4),
          ir_led_5(ir_led_5) {
    }

    void flame_sensor_c::read_output() {
       
    }

    bool flame_sensor_c::is_flame_detected() {
        hwlib::pin_oc* leds[5] = {&ir_led_1, &ir_led_2, &ir_led_3, &ir_led_4, &ir_led_5};
        for (int i=0; i<5;++i) {
            if (leds[i]->read() == 1){
                return 1;
            }
        }
        hwlib::wait_ms(100);
        return 0;
    }

    int flame_sensor_c::get_flame_direction() {
        return 0;
    }
} // namespace r2d2::flame_sensor