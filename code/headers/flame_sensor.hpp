#include <hwlib.hpp>

#pragma once

namespace r2d2::flame_sensor {
    class flame_sensor_c {
    private:
//        hwlib::pin_oc &ir_led_1;
//        hwlib::pin_oc &ir_led_2;
//        hwlib::pin_oc &ir_led_3;
//        hwlib::pin_oc &ir_led_4;
//        hwlib::pin_oc &ir_led_5;
        hwlib::target::pin_adc leds[5];
		uint8_t flame_threshhold;

    public:
//        flame_sensor_c(hwlib::pin_oc &ir_led_1, hwlib::pin_oc &ir_led_2,
//                       hwlib::pin_oc &ir_led_3, hwlib::pin_oc &ir_led_4,
//                       hwlib::pin_oc &ir_led_5);

		flame_sensor_c(hwlib::target::pin_adc &ir_led_1, hwlib::target::pin_adc &ir_led_2,
					   hwlib::target::pin_adc &ir_led_3, hwlib::target::pin_adc &ir_led_4,
					   hwlib::target::pin_adc &ir_led_5, int flame_threshhold);

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
