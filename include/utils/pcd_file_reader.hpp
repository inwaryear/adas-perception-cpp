#pragma once

#include <core/lidar_scan.hpp>
#include <memory>
#include <fstream>

namespace adas::utils {

    class PcdFileReader {
    public:
        PcdFileReader() : file_stream_() {}

        std::unique_ptr<adas::core::LidarScan> getPcd(const std::string& path) {
            auto scan =std::make_unique<adas::core::LidarScan>();

            file_stream_.open(path);

            if (file_stream_.is_open()) {
                // TODO : Find how to parse pcd content format to Point3D to add in LIdarScan
            }

            // NOTE : here std::ifstream handles the closure automatically. As soon as we leave the method context. Thus, even if there is
            //        an error thrown there will be no leakage.
            return scan;
        };

        ~PcdFileReader() {}
    private:
        // NOTE : RAII convenient file stream
        std::ifstream file_stream_;
    };
}