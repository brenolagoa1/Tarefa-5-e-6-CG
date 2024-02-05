#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings

using std::shared_ptr; ///< Uso de ponteiro compartilhado
using std::make_shared; ///< Criação de ponteiro compartilhado
using std::sqrt; ///< Função de raiz quadrada

// Constants

const double infinity = std::numeric_limits<double>::infinity(); ///< Infinito
const double pi = 3.1415926535897932385; ///< Valor de pi

// Utility Functions

/**
 * @brief Converte graus para radianos.
 * @param degrees O valor em graus.
 * @return O valor convertido em radianos.
 */
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "color.h" ///< Cor
#include "interval.h" ///< Intervalo
#include "ray.h" ///< Raio
#include "matvec.h" ///< Vetores e Matrizes

#endif // RTWEEKEND_H
#pragma once
