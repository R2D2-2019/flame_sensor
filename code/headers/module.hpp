#pragma once

#include <base_module.hpp>
#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {

    /**
     * This class is the interface for the flame_sensor module.
     * It handles incoming frames and commands the end flame_sensor to
     * do stuff. It has a pointer to the base flame_sensor class.
     */
    class module_c : public base_module_c {
    private:
        flame_sensor_c *flame_sensor;

    public:
        /**
         * The constructor initializes:
         * base_module_c
         * the pointer to the flame_sensor
         *
         * @param comm
         * @param flame_sensor
         */
        module_c(base_comm_c &comm, flame_sensor_c *flame_sensor);

        /**
         * Let the module process data.
         */
        void process() override;
    };
} // namespace r2d2::flame_sensor