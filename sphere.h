#ifndef SPHERE_H
#define SPHERE_H


#include "hittable.h"
#include "utilities.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, double r, shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m) {}; 

	virtual bool hit(
		const ray& r, double tmin, double tmax, hit_record& rec) const override;

public:
	point3 center;
	double radius; 
	shared_ptr<material> mat_ptr;
};

 bool sphere :: hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	//getting the discriminant
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	//checking if the discriminant is positive (if the ray does actually hit the sphere)
	if (discriminant > 0) {
		auto root = sqrt(discriminant);

		//positive side
		auto temp = (-half_b - root) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}


		//negative side
		temp = (-half_b + root) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.at(rec.t);
			rec.normal = (rec.p - center) / radius;
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}

	}
	return false;
}


#endif
