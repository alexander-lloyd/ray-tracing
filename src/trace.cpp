/**
 * @author      : Alexander Lloyd (axl639@student.bham.ac.uk)
 * @file        : trace
 * @created     : Thursday Jun 27, 2019 11:55:56 BST
 */
#ifndef trace_cpp
#define trace_cpp

#include <vector>
#include "interpolation.cpp"
#include "vector.cpp"
#include "sphere.cpp"

#ifndef MAX_RAY_DEPTH
#define MAX_RAY_DEPTH 1
#endif

#if defined __linux__ || defined __APPLE__
// Compiled for Linux
#else
#define M_PI 3.14159265358973
#define INFINITY 1e8
#endif


Vec3f trace(
		const Vec3f &rayorig,
		const Vec3f &raydir,
		const std::vector<Sphere> &shapes,
		const int &depth) {
	float tNear = INFINITY;
	const Sphere* shape = NULL;

	for (unsigned i = 0; i < shapes.size(); ++i) {
		float t0 = INFINITY, t1 = INFINITY;
		if (shapes[i].intersect(rayorig, raydir, t0, t1)) {
			if (t0 < 0) {
				t0 = t1;
			}
			if (t0 < tNear) {
				tNear = t0;
				shape = &shapes[i];
			}
		}
	}

	if (!shape) {
		return Vec3f(2);
	}
	
	Vec3f surfaceColour = 0; // colour of the ray / surface of the object intersected by the ray
	Vec3f phit = rayorig + raydir * tNear; // point of intersection
	Vec3f nhit = phit - shape->center; // normal at the intersection
	nhit.normalize(); // normalize normal direction



	float bias = 1e-4;
	bool inside = false;

	if (raydir.dot(nhit) > 0) {
		nhit = -nhit;
		inside = true;
	}

	if ((shape->transparency > 0 || shape->reflection > 0) && depth < MAX_RAY_DEPTH) {
		float facingratio = -raydir.dot(nhit);
		float fresneleffect = interpolate(pow(1 - facingratio, 3), 1, -.1);

		Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
		refldir.normalize();
		Vec3f reflection = trace(phit + nhit * bias, refldir, shapes, depth + 1);
		Vec3f refraction = 0;

		if (shape->transparency) {
			float ior = 1.1;
			float eta = (inside) ? ior : 1 / ior; // are we inside or outside surface?
			float cosi = -nhit.dot(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3f refrdir = raydir * eta + nhit * (eta * cosi - sqrt(k));
			refrdir.normalize();
			refraction = trace(phit - nhit * bias, refrdir, shapes, depth + 1);
		}

		surfaceColour = (
				reflection * fresneleffect + 
				refraction * (1 - fresneleffect) * shape->transparency) * shape->surfaceColour;
	}
	else {
	}
}

#endif
