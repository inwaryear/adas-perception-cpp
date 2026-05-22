#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <thread>
#include <mutex>
#include <optional>

struct Point3D {
    float x, y, z;
    float intensity;

    Point3D(float x, float y, float z, float intensity = 0.0f)
        : x(x), y(y), z(z), intensity(intensity) {}

    float distanceToOrigin() const {
        return std::sqrt(x*x + y*y + z*z);
    }
};

class LidarScan {
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

    // NOTE : (= delete) Throw an error at compilation if used in any part of the code.
    //        It is a more modern approach to make sure that this is not used at anytime, 
    //        in older c++ those method where declared as private.
    LidarScan(const LidarScan& scan) = delete; 
    LidarScan& operator=(const LidarScan& scan) = delete;
private:
    std::vector<Point3D> points_;
};

class LidarBuffer {
public:
    LidarBuffer() : lidar_mutex_(), scan_() {};

    void Push(std::unique_ptr<LidarScan> scan) {
        std::lock_guard<std::mutex> guard(lidar_mutex_);
        scan_ = std::move(scan);
    };

    std::optional<std::unique_ptr<LidarScan>> Take() {
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
    std::unique_ptr<LidarScan> scan_;
};

class PcdFileReader {
public:
    PcdFileReader() : file_stream_() {}

    std::unique_ptr<LidarScan> getPcd(const std::string& path) {
        auto scan =std::make_unique<LidarScan>();

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

int main() {
    auto scan = LidarScan();

    scan.addPoint(1.0f, 0.5f, 0.2f, 0.8f);
    scan.addPoint(3.2f, 1.1f, 0.0f, 0.6f);
    scan.addPoint(0.3f, 4.7f, 0.1f, 0.9f);

    scan.printSummary();

    auto scan2 = std::move(scan);
    scan.printSummary();
    scan2.printSummary();
    std::cout << "Pipeline ADAS initialized. Ready.\n";
    return 0;
}
