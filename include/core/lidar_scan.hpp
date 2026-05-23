#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <thread>
#include <mutex>
#include <optional>
#include <core/point_3D.hpp>

namespace adas::core {

    // NOTE : pcl::PointCloud is not used in the architecture directly to have more safety if the PCL library disapear at some point.
    
    class LidarScan {
        using iterator = std::vector<Point3D>::iterator;
        using const_iterator = std::vector<Point3D>::const_iterator;
    public:
        LidarScan() {}

        // NOTE : Constructor that takes a rvalue as parameter. 
        //        Example : 
        //          BEFORE -> this.point_ -> nullptr
        //                 -> other.point_ -> [p1][p2][p..]
        //          AFTER  -> this.point_ -> [p1][p2][p...]
        //                 -> other.points_ -> nullptr
        //
        //        There is no copy and noexcept indicate that this method never throws which allows the 
        //        compiler to optimize better.
        LidarScan(LidarScan&& other) noexcept : points_(std::move(other.points_)) {}

        void addPoint(float x, float y, float z, float intensity = 0.0f) {
            points_.emplace_back(x, y, z, intensity);
        }

        size_t size() const { return points_.size(); }

        void printSummary() const {
            std::cout << "LidarScan: " << points_.size() << " points\n";
            for (const auto& p : points_) {
                std::cout << "  ("
                      << p.x << ", "
                      << p.y << ", "
                      << p.z << ") dist="
                      << p.distanceToOrigin() << "\n";
            }
        }

        // iterators
        iterator begin() noexcept { return points_.begin(); }
        iterator end() noexcept { return points_.end();}

        const_iterator begin() const noexcept { return points_.begin(); }
        const_iterator end() const noexcept { return points_.end(); }

        // NOTE : (= delete) Throw an error at compilation if used in any part of the code.
        //        It is a more modern approach to make sure that this is not used at anytime, 
        //        in older c++ those method where declared as private.
        LidarScan(const LidarScan& scan) = delete; 
        LidarScan& operator=(const LidarScan& scan) = delete;
    private:
        std::vector<Point3D> points_;
    };
}
