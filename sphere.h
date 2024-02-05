#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "matvec.h"

/**
 * @brief Classe que representa uma esfera em um espaço 3D.
 */
class sphere : public hittable {
public:
    /**
     * @brief Construtor para inicializar a esfera com um centro, raio e material.
     * @param _center O centro da esfera.
     * @param _radius O raio da esfera.
     * @param _material O material da esfera.
     */
    sphere(vec3 _center, double _radius, shared_ptr<material> _material) : center(_center), radius(_radius), mat(_material) {}

    /**
     * @brief Sobrescrita da função da classe base para verificar interseções raio-esfera.
     * @param r O raio.
     * @param ray_t O intervalo do raio.
     * @param rec O registro de acerto.
     * @return Verdadeiro se houver interseção, falso caso contrário.
     */
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;

        // Verifica se o raio intersecta a esfera
        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // Encontra a raiz mais próxima que está dentro do intervalo aceitável.
        auto root = (-half_b - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        // Registra os detalhes da interseção
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    vec3 center; ///< Centro da esfera
    double radius; ///< Raio da esfera
    shared_ptr<material> mat; ///< Material da esfera
};

#endif // SPHERE_H
