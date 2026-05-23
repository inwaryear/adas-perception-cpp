#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <pcl/common/common.h>
#include <pcl/impl/point_types.hpp>
#include <pcl/point_cloud.h>
#include <core/lidar_scan.hpp>

namespace adas::utils {
    // NOTE : inline idicates the compilator to inject the method's body, replaceing the method call by the body itself. It erases overload from the function call
    //        increasing performance but it makes the binary bigger.
    inline pcl::PointCloud<pcl::PointXYZI>::Ptr toPointCloud(const core::LidarScan &scan) {
        auto pc = std::make_shared<pcl::PointCloud<pcl::PointXYZI>>();

        // NOTE : LidarScan defines begin() and end() method that gives access to the begin() end end() iterators of the vector of 3D points.
        //        "const auto scanPoint : scan" is equivalent to "auto it = std::begin(scan); it!=std::end(scan); ++it"
        for (const auto scanPoint: scan) { 
            auto point = pcl::PointXYZI(scanPoint.x, scanPoint.y, scanPoint.z, scanPoint.intensity);
            pc->push_back(point);
        };

        return pc;
    };
}
