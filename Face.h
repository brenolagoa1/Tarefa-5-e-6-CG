
#ifndef FACE_H
#define FACE_H

/**
 * @brief Classe que representa uma face em um modelo 3D.
 */
class Face {
public:
    // �ndices dos tr�s v�rtices da face
    int v1;
    int v2;
    int v3;
    int n1;
    int n2;
    int n3;

    /**
     * @brief Construtor da classe Face.
     * @param v1 �ndice do primeiro v�rtice.
     * @param v2 �ndice do segundo v�rtice.
     * @param v3 �ndice do terceiro v�rtice.
     * @param n1 �ndice da primeira normal.
     * @param n2 �ndice da segunda normal.
     * @param n3 �ndice da terceira normal.
     */
    Face(int v1, int v2, int v3, int n1, int n2, int n3) : v1(v1), v2(v2), v3(v3), n1(n1), n2(n2), n3(n3) {}
};

#endif#pragma once
