#pragma once

#include "matvec.h"
#include <tuple>

/**
 * @brief Classe para armazenar normais.
 */
class Normais {
public:
    /**
     * @brief Construtor padrão que inicializa a normal com zeros.
     */
    Normais() : n0(0, 0, 0) {}

    /**
     * @brief Construtor que inicializa a normal com os valores especificados.
     * @param n0 O vetor normal.
     */
    Normais(const vec3& n0)
        : n0(n0) {

    }
private:
    vec3 n0; ///< Vértice normal
};

