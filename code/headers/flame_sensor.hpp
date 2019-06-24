#pragma once

#include <hwlib.hpp>

namespace r2d2::flame_sensor {
    class flame_sensor_c {
    private:
        hwlib::target::pin_adc leds[5];
        unsigned int flame_threshhold;
        unsigned int threshhold_error;
        unsigned int total_detection_angle;

        template <size_t SIZE, class T>
        size_t array_size(T (&leds)[SIZE]);

    public:
        flame_sensor_c(
            hwlib::target::pin_adc &ir_led_1, hwlib::target::pin_adc &ir_led_2,
            hwlib::target::pin_adc &ir_led_3, hwlib::target::pin_adc &ir_led_4,
            hwlib::target::pin_adc &ir_led_5, unsigned int flame_threshhold,
            unsigned int threshhold_error, unsigned int total_detection_angle);

        /**
         * @brief calculate the average infrared level from the IR leds
         *
         * @return the average value from all the sensors with a given offset
         * added to it
         */
        unsigned int get_sensor_average();

        /**
         * @brief Check if sensor detects a flame anywhere near
         *
         *
         * @return true if one or more of the leds detect a flame
         * @return false if no flames are detected
         */
        bool is_flame_detected();

        /**
         * @brief Check if sensor detects a flame near the specified sensor
         *
         *
         * @return true if the specified led detects a flame
         * @return false if the specified led detects no flame
         */
        bool is_single_flame_detected(hwlib::target::pin_adc pin_to_check,
                                      unsigned int sensor_average);

        /**
         * @brief Get the flame direction
         *
         * @return int position of flame in degrees (from sensor)
         */
        int get_flame_direction();
    };
} // namespace r2d2::flame_sensor
