// material.cpp
#include "material.h"
#include "hittable.h"

lambertian::lambertian(const color& a) : albedo(a) {}

bool lambertian::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
const {
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

metal::metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool metal::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(double index_of_refraction) : ir(index_of_refraction) {}

bool dielectric::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
const {
    attenuation = color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.p, direction);
    return true;
}