#include <module.hpp>

namespace r2d2::flame_sensor {
    module_c::module_c(base_comm_c &comm, flame_sensor_c *flame_sensor)
        : base_module_c(comm), flame_sensor(flame_sensor) {
        comm.listen_for_frames({frame_type::ALL});
    }

    void module_c::module_c::process() {
        while (comm.has_data()) {
            auto frame = comm.get_data();
            // process the frame
        }
		// Is this frame a request?
//		if (frame.request) {
//			// Process request, e.g. read a sensor and send value
//		}

        if (flame_sensor->is_flame_detected()) {
            hwlib::cout << flame_sensor->get_flame_direction() << hwlib::endl;
        } else {
            hwlib::cout << "No Fire!" << hwlib::endl;
        }
    }
} // namespace r2d2::flame_sensor