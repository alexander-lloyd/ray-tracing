/**
 * @author      : Alexander Lloyd (axl639@student.bham.ac.uk)
 * @file        : sphere
 * @created     : Thursday Jun 27, 2019 11:27:26 BST
 */
#ifndef sphere_cpp
#define sphere_cpp

#include <cmath>

#include "vector.cpp"

class Sphere {
	public:
		Vec3f center; // Position of the sphere
		float radius, radius2; // Radius of the circle
		Vec3f surfaceColour, emissionColour; // Surface colour and emission (light)
		float transparency, reflection; // Surface transparency and reflectivity

		Sphere(
				const Vec3f &c,
				const float &r,
				const Vec3f &sc,
				const float &refl = 0,
				const float &transp = 0,
				const Vec3f &ec = 0) :
			center(c),
			radius(r),
			radius2(r * r),
			surfaceColour(sc),
			emissionColour(ec),
			transparency(transp),
			reflection(refl) { }

		bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const {
			Vec3f l = center - rayorig;
			float tca = l.dot(raydir);
			if (tca < 0) {
				return false;
			}

			float d2 = l.dot(l) - tca * tca;

			if (d2 > radius2) {
				return false;
			}

			float thc = sqrt(radius2 - d2);
			t0 = tca - thc;
			t1 = tca + thc;

			return true;
		}
};

#endif
