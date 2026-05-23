#pragma once

#include <cmath>

namespace adas::core {

    struct Point3D {
        float x, y, z;
        float intensity;

        Point3D(float x, float y, float z, float intensity = 0.0f)
            : x(x), y(y), z(z), intensity(intensity) {}

        float distanceToOrigin() const {
            return std::sqrt(x*x + y*y + z*z);
        }
};
}