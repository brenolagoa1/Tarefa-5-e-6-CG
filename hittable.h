#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

// Forward declaration
class material;

/**
 * @brief Classe que representa um registro de colisão.
 */
class hit_record {
public:
    vec3 p;                      // Ponto de colisão
    vec3 normal;                 // Normal à superfície no ponto de colisão
    shared_ptr<material> mat;    // Material atingido
    double t;                    // Parâmetro de tempo de colisão
    bool front_face;             // Indica se a face da superfície está voltada para o raio

    /**
     * @brief Define a normal da face com base na direção do raio e na normal externa.
     * @param r O raio incidente.
     * @param outward_normal A normal externa.
     */
    void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

/**
 * @brief Classe abstrata que define um objeto que pode ser atingido por um raio.
 */
class hittable {
public:
    virtual ~hittable() = default;

    /**
     * @brief Verifica se o raio atinge o objeto e, se sim, registra as informações de colisão.
     * @param r O raio a ser verificado.
     * @param ray_t Intervalo de tempo para o raio.
     * @param rec O registro de colisão a ser preenchido em caso de colisão.
     * @return true se o raio atinge o objeto, false caso contrário.
     */
    virtual bool hit(const Ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
#pragma once

