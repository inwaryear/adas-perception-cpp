#pragma once

#include <core/lidar_scan.hpp>
#include <memory>
#include <mutex>

namespace adas::com {

    class LidarBuffer {
    public:
        LidarBuffer() : lidar_mutex_(), scan_() {};

        void Push(std::unique_ptr<adas::core::LidarScan> scan) {
            std::lock_guard<std::mutex> guard(lidar_mutex_);
            scan_ = std::move(scan);
        };

        std::optional<std::unique_ptr<adas::core::LidarScan>> Take() {
            std::lock_guard<std::mutex> guard(lidar_mutex_);

            // NOTE : std::unique_ptr has an implicit conversion in boolean that return true if the pointer handles a resource and
            //        false otherwise.
            if (scan_) {
                return std::move(scan_);
            }

            // NOTE : null indicator for std::optional
            return std::nullopt;
        };
    private:
        std::mutex lidar_mutex_;
        std::unique_ptr<adas::core::LidarScan> scan_;
    };
}