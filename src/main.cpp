#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

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

private:
    std::vector<Point3D> points_;
};

int main() {
    auto scan = std::make_unique<LidarScan>();

    scan->addPoint(1.0f, 0.5f, 0.2f, 0.8f);
    scan->addPoint(3.2f, 1.1f, 0.0f, 0.6f);
    scan->addPoint(0.3f, 4.7f, 0.1f, 0.9f);

    scan->printSummary();

    std::cout << "Pipeline ADAS initialized. Ready.\n";
    return 0;
}
