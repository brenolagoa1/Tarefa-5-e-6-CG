// ray.cpp
#include "ray.h"

/**
 * @brief Construtor padrão para Ray.
 */
Ray::Ray() {}

/**
 * @brief Construtor para Ray com origem e direção especificadas.
 * @param origin O ponto de origem do raio.
 * @param direction O vetor de direção do raio.
 */
Ray::Ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {}

/**
 * @brief Função de acesso para obter a origem do raio.
 * @return O ponto de origem do raio.
 */
vec3 Ray::origin() const {
    return orig;
}

/**
 * @brief Função de acesso para obter a direção do raio.
 * @return O vetor de direção do raio.
 */
vec3 Ray::direction() const {
    return dir;
}

/**
 * @brief Retorna um ponto ao longo do raio em um valor de parâmetro especificado.
 * @param t O valor do parâmetro.
 * @return O ponto ao longo do raio no parâmetro t.
 */
vec3 Ray::at(double t) const {
    return orig + t * dir;
}

void Ray::operator*=(double scalar) {
    orig = orig * scalar;
    dir = dir * scalar;
}
