#ifndef vector_cpp
#define vector_cpp

#include <cmath>
#include <iostream>

template<typename T>
class Vec3 {
	public:
		T x, y, z;
		Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
		Vec3(T xx) : x(xx), y(xx), z(xx) {}
		Vec3(T xx, T yy, T zz): x(xx), y(yy), z(zz) {}

		T length2() const {
			return  x * x + y * y + z * z;
		}

		T length() const {
			return sqrt(this->length2());
		}

		Vec3& normalize() {
			T nor2 = length2();
			if (nor2 > 0) {
				T invNor = 1 / sqrt(nor2);
				x *= invNor;
				y *= invNor;
				z *= invNor;
			}

			return *this;
		}

		T dot(const Vec3<T> &v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		Vec3<T> operator * (const T &f) const {
			return Vec3<T>(x * f, y * f, z * f);
		}

		Vec3<T> operator * (const Vec3<T> &v) const {
			return Vec3<T>(x * v.x, y * v.y, z * v.z);
		}

		Vec3<T> operator *= (const Vec3<T> &v) const {
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		Vec3<T> operator + (const Vec3<T> &v) const {
			return Vec3<T>(x + v.x, y + v.y, z + v.z);
		}

		Vec3<T> operator += (const Vec3<T> &v) const {
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		Vec3<T> operator - () const {
			return Vec3<T>(-x, -y, -z);
		}

		Vec3<T> operator - (const Vec3<T> &v) const {
			return Vec3<T>(x - v.x, y - v.y, z - v.z);
		}

		friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v) {
			os << "[" << v.x << " " << v.y << " " << v.z  << "]";
			return os;
		}
};

typedef Vec3<float> Vec3f;

#endif
