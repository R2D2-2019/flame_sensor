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
        hwlib::pin_oc *leds[5] = {&ir_led_1, &ir_led_2, &ir_led_3, &ir_led_4,
                                  &ir_led_5};

    public:
        flame_sensor_c(hwlib::pin_oc &ir_led_1, hwlib::pin_oc &ir_led_2,
                       hwlib::pin_oc &ir_led_3, hwlib::pin_oc &ir_led_4,
                       hwlib::pin_oc &ir_led_5);
        /**
         * @brief Check if sensor detects a flame anywhere near
         *
         *
         * @return true if one or more of the leds detect a flame
         * @return false if no flames are detected
         */
        bool is_flame_detected();

        /**
         * @brief Get the flame direction
         * Currently no implementation
         *
         * @return int position of flame in degrees (from sensor)
         */
        int get_flame_direction();
    };
} // namespace r2d2::flame_sensor
