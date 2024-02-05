#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

// Forward declaration
class material;

/**
 * @brief Classe que representa um registro de colis�o.
 */
class hit_record {
public:
    vec3 p;                      // Ponto de colis�o
    vec3 normal;                 // Normal � superf�cie no ponto de colis�o
    shared_ptr<material> mat;    // Material atingido
    double t;                    // Par�metro de tempo de colis�o
    bool front_face;             // Indica se a face da superf�cie est� voltada para o raio

    /**
     * @brief Define a normal da face com base na dire��o do raio e na normal externa.
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
     * @brief Verifica se o raio atinge o objeto e, se sim, registra as informa��es de colis�o.
     * @param r O raio a ser verificado.
     * @param ray_t Intervalo de tempo para o raio.
     * @param rec O registro de colis�o a ser preenchido em caso de colis�o.
     * @return true se o raio atinge o objeto, false caso contr�rio.
     */
    virtual bool hit(const Ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
#pragma once

