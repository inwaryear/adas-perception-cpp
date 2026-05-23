#include <core/lidar_scan.hpp>

int main() {
    auto scan = adas::core::LidarScan();

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
