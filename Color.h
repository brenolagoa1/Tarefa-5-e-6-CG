// color.h
#ifndef COLOR_H
#define COLOR_H

#include "matvec.h"
#include "interval.h"

#include <iostream>

// Define color as an alias for vec3
using color = vec3;

/**
 * @brief Ajusta e retorna a cor ajustada.
 * @param pixel_color A cor do pixel.
 * @param samples_per_pixel O número de amostras por pixel.
 * @return A cor ajustada.
 */
color write_color(color pixel_color, int samples_per_pixel);

#endif // COLOR_H

