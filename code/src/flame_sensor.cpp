#include <hwlib.hpp>

#pragma once

namespace r2d2::flame_sensor {
    flame_sensor_c::flame_sensor_c(hwlib::pin_oc &ir_led_0,
                                   hwlib::pin_oc &ir_led_1,
                                   hwlib::pin_oc &ir_led_2,
                                   hwlib::pin_oc &ir_led_3,
                                   hwlib::pin_oc &ir_led_4)
        : ir_led_0(ir_led_0),
          ir_led_0(ir_led_1),
          ir_led_0(ir_led_2),
          ir_led_0(ir_led_3),
          ir_led_0(ir_led_4) {
    }

    bool flame_sensor_c::is_flame_detected() {
    }

    int flame_sensor_c::get_flame_direction() {
    }
} // namespace r2d2::flame_sensor