#include <module.hpp>

namespace r2d2::flame_sensor {
    module_c::module_c(base_comm_c &comm, flame_sensor_c *flame_sensor)
        : base_module_c(comm), flame_sensor(flame_sensor) {
        comm.listen_for_frames({r2d2::frame_type::FLAME_DETECTION});
    }

    void module_c::module_c::process() {

        while (comm.has_data()) {
            auto frame = comm.get_data();
            // process the frame

            // Is this frame a request?
            if (frame.request) {
                // Process request, e.g. read a sensor and send value

                frame_flame_detection_s flame_frame;
                flame_frame.flame_detected = flame_sensor->is_flame_detected();
                if (flame_frame.flame_detected) {
                    flame_frame.big_fire =
                        (flame_sensor->get_sensor_average() >
                         flame_sensor->get_flame_threshhold());
                    flame_frame.flame_angle =
                        flame_sensor->get_flame_direction();
                    //					hwlib::cout <<
                    //flame_sensor->get_flame_direction() << hwlib::endl;
                } else {
                    flame_frame.flame_angle = 0;
                    //					hwlib::cout << "No Fire!" <<
                    //hwlib::endl;
                }

                hwlib::wait_ms(10);
                comm.send(flame_frame);
            }
        }
    }
} // namespace r2d2::flame_sensor