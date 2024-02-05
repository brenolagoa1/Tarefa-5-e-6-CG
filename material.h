#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

// Forward declaration
class hit_record;

/**
 * @brief Classe abstrata que define um material que pode ser usado em objetos.
 */
class material {
public:
    virtual ~material() = default;

    /**
     * @brief Calcula o espalhamento de um raio ao atingir o material.
     * @param r_in O raio incidente.
     * @param rec O registro de colisão.
     * @param attenuation A atenuação do raio.
     * @param scattered O raio espalhado.
     * @return true se houve espalhamento, false caso contrário.
     */
    virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const = 0;
};

/**
 * @brief Material lambertiano que difunde a luz em todas as direções.
 */
class lambertian : public material {
public:
    /**
     * @brief Construtor que define a cor do material lambertiano.
     * @param a A albedo (reflexão difusa) do material.
     */
    lambertian(const color& a) : albedo(a) {}

    bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Captura direção de dispersão degenerada
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo; // Albedo (reflexão difusa) do material lambertiano
};

/**
 * @brief Material metálico que reflete a luz de forma especular.
 */
class metal : public material {
public:
    /**
     * @brief Construtor que define a cor e a rugosidade do material metálico.
     * @param a A albedo (reflexão especular) do material.
     * @param f A rugosidade do material (fuzz).
     */
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_unit_vector());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo; // Albedo (reflexão especular) do material metálico
    double fuzz;  // Rugosidade do material (fuzz)
};

/**
 * @brief Material dielétrico que refrata e reflete a luz.
 */
class dielectric : public material {
public:
    /**
     * @brief Construtor que define o índice de refração do material dielétrico.
     * @param index_of_refraction O índice de refração do material.
     */
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
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

private:
    double ir; // Índice de Refração

    /**
     * @brief Calcula a reflectância usando a aproximação de Schlick.
     * @param cosine Cosseno do ângulo de incidência.
     * @param ref_idx Índice de refração.
     * @return A reflectância calculada.
     */
    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif
