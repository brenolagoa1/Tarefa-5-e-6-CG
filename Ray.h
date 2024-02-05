// ray.h

#ifndef RAY_H
#define RAY_H

#include "matvec.h"

/**
 * @brief A classe Ray representa um raio no espaço tridimensional.
 */
class Ray {
public:
    /**
     * @brief Construtor padrão para Ray.
     */
    Ray();

    /**
     * @brief Construtor para Ray com origem e direção especificadas.
     * @param origin O ponto de origem do raio.
     * @param direction O vetor de direção do raio.
     */
    Ray(const vec3& origin, const vec3& direction);

    /**
     * @brief Função de acesso para obter a origem do raio.
     * @return O ponto de origem do raio.
     */
    vec3 origin() const;

    /**
     * @brief Função de acesso para obter a direção do raio.
     * @return O vetor de direção do raio.
     */
    vec3 direction() const;

    /**
     * @brief Retorna um ponto ao longo do raio em um valor de parâmetro especificado.
     * @param t O valor do parâmetro.
     * @return O ponto ao longo do raio no parâmetro t.
     */
    vec3 at(double t) const;

    void operator*=(double scalar);

private:
    vec3 orig; ///< O ponto de origem do raio.
    vec3 dir;  ///< O vetor de direção do raio.
};

#endif // RAY_H
