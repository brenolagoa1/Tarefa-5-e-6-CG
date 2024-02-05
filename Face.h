
#ifndef FACE_H
#define FACE_H

/**
 * @brief Classe que representa uma face em um modelo 3D.
 */
class Face {
public:
    // Índices dos três vértices da face
    int v1;
    int v2;
    int v3;
    int n1;
    int n2;
    int n3;

    /**
     * @brief Construtor da classe Face.
     * @param v1 Índice do primeiro vértice.
     * @param v2 Índice do segundo vértice.
     * @param v3 Índice do terceiro vértice.
     * @param n1 Índice da primeira normal.
     * @param n2 Índice da segunda normal.
     * @param n3 Índice da terceira normal.
     */
    Face(int v1, int v2, int v3, int n1, int n2, int n3) : v1(v1), v2(v2), v3(v3), n1(n1), n2(n2), n3(n3) {}
};

#endif#pragma once
