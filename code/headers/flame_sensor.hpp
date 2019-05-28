#include <hwlib.hpp>

#pragma once

namespace r2d2::flame_sensor {
    class flame_sensor_c {
    private:
        hwlib::pin_oc &ir_led_1;
        hwlib::pin_oc &ir_led_2;
        hwlib::pin_oc &ir_led_3;
        hwlib::pin_oc &ir_led_4;
        hwlib::pin_oc &ir_led_5;
    public:
        flame_sensor_c(hwlib::pin_oc &ir_led_1, hwlib::pin_oc &ir_led_2,
                       hwlib::pin_oc &ir_led_3, hwlib::pin_oc &ir_led_4,
                       hwlib::pin_oc &ir_led_5);


        void read_output();

        bool is_flame_detected();

        int get_flame_direction();
    };
} // namespace r2d2::flame_sensor
