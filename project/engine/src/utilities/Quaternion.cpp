#include "engine/utilities/Quaternion.h"
#include "engine/utilities/Vector3.h"
#include "engine/utilities/Vector2.h"
#include "engine/utilities/Math.h"
#include <cmath>

namespace EisEngine {
    const Quaternion Identity = Quaternion(0, 0, 0, 1);

    float Quaternion::magnitude() const
    { return (float) sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));}

    Quaternion::operator Vector3() const{
        return Math::RadiansToDegrees(Vector3(glm::eulerAngles((glm::quat) *this)));
    }
    Quaternion::operator Vector2() const { return Vector2(x, y);}
    Quaternion::operator glm::quat() const{return {w, x, y, z};}
    Quaternion::operator std::string() const {
        return "({"+
               std::to_string(x)+", "+
               std::to_string(y)+", "+
               std::to_string(z)+"}, "+
               std::to_string(w)+
               ")";
    }

    Quaternion Quaternion::operator+(const EisEngine::Quaternion &q) const {
        return Quaternion(
                x + q.x,
                y + q.y,
                z + q.z,
                w + q.w
                        );
    }
    Quaternion Quaternion::operator-(const EisEngine::Quaternion &q) const {
        return Quaternion(
                x - q.x,
                y - q.y,
                z - q.z,
                w - q.w
                );
    }
    Quaternion Quaternion::operator*(const EisEngine::Quaternion &q) const {
        return Quaternion(
                w * q.x + q.w * x + y * q.z - z * q.y,
                w * q.y - q.w * y + z * q.x - x * q.z,
                w * q.z - q.w * z + x * q.y - y * q.x,
                w * q.w - x * q.x - y * q.y - z * q.z
                );
    }
    Quaternion Quaternion::operator*(const float &c) const {
        return Quaternion(
                x * c,
                y * c,
                z * c,
                w * c
        );
    }
    Quaternion Quaternion::operator*(const int &c) const {
        return Quaternion(
                x * (float) c,
                y * (float) c,
                z * (float) c,
                w * (float) c
        );
    }

    Quaternion &Quaternion::operator+=(const Quaternion &q) {
        x += q.x;
        y += q.y;
        z += q.z;
        w += q.w;
        return *this;
    }
    Quaternion &Quaternion::operator-=(const Quaternion &q) {
        x -= q.x;
        y -= q.y;
        z -= q.z;
        w -= q.w;
        return *this;
    }
    Quaternion &Quaternion::operator*=(const float &c) {
        w *= c;
        x *= c;
        y *= c;
        z *= c;
        return *this;
    }
    Quaternion &Quaternion::operator*=(const int &c) {
        w *= (float) c;
        x *= (float) c;
        y *= (float) c;
        z *= (float) c;
        return *this;
    }
}
