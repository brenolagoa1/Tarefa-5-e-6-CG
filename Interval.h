#pragma once
#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

/**
 * @brief Classe que representa um intervalo.
 */
class interval {
public:
    double min, max; ///< M�nimo e m�ximo do intervalo

    /**
     * @brief Construtor padr�o.
     */
    interval(); // Default constructor

    /**
     * @brief Construtor que inicializa o intervalo com valores m�nimos e m�ximos.
     * @param _min O valor m�nimo do intervalo.
     * @param _max O valor m�ximo do intervalo.
     */
    interval(double _min, double _max);

    /**
     * @brief Verifica se o valor x est� contido no intervalo.
     * @param x O valor a ser verificado.
     * @return true se x estiver dentro do intervalo, false caso contr�rio.
     */
    bool contains(double x) const;

    /**
     * @brief Verifica se x est� dentro do intervalo.
     * @param x O valor a ser verificado.
     * @return true se x estiver dentro do intervalo, false caso contr�rio.
     */
    bool surrounds(double x) const;

    /**
     * @brief Limita o valor x ao intervalo.
     * @param x O valor a ser limitado.
     * @return O valor de x limitado ao intervalo.
     */
    double clamp(double x) const;

    /**
     * @brief Intervalo vazio.
     */
    static const interval empty;

    /**
     * @brief Universo completo.
     */
    static const interval universe;
};

extern const interval empty; ///< Intervalo vazio
extern const interval universe; ///< Universo completo

#endif
