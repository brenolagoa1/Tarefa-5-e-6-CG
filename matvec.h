#ifndef MATVEC_H
#define MATVEC_H

#include <cmath>

/**
 * @file
 * @brief Cont�m as defini��es de classes para vetores e matrizes 2D, 3D e 4D.
 */

 /**
  * @class vec2
  * @brief Classe que representa um vetor 2D.
  */
class vec2 {
public:
    double x, y;

    /**
     * @brief Construtor padr�o.
     */
    vec2();

    /**
     * @brief Construtor com par�metros.
     * @param x Componente x do vetor.
     * @param y Componente y do vetor.
     */
    vec2(double x, double y);

    /**
     * @brief Sobrecarga do operador de adi��o.
     */
    vec2 operator+(const vec2& other) const;

    /**
     * @brief Sobrecarga do operador de subtra��o.
     */
    vec2 operator-(const vec2& other) const;

    /**
     * @brief Sobrecarga do operador de produto escalar.
     */
    double operator*(const vec2& other) const;

    /**
     * @brief Sobrecarga do operador de multiplica��o por escalar.
     */
    vec2 operator*(double scalar) const;

    /**
     * @brief Sobrecarga do operador de divis�o por escalar.
     */
    vec2 operator/(double scalar) const;

    /**
     * @brief Calcula o comprimento do vetor.
     */
    double length() const;
};

/**
 * @class vec3
 * @brief Classe que representa um vetor 3D.
 */
class vec3 {
public:
    double x, y, z;

    /**
     * @brief Construtor padr�o.
     */
    vec3();

    /**
     * @brief Construtor com par�metros.
     * @param x Componente x do vetor.
     * @param y Componente y do vetor.
     * @param z Componente z do vetor.
     */
    vec3(double x, double y, double z);

    /**
     * @brief Sobrecarga do operador de adi��o.
     */
    vec3 operator+(const vec3& other) const;

    /**
     * @brief Sobrecarga do operador de subtra��o.
     */
    vec3 operator-(const vec3& other) const;

    /**
     * @brief Sobrecarga do operador de divis�o por escalar.
     */
    vec3 operator/(double scalar) const;

    /**
     * @brief Calcula o comprimento do vetor.
     */
    double length() const;

    /**
     * @brief Calcula o comprimento do vetor ao quadrado.
     */
    double length_squared() const;

    /**
     * @brief Verifica se o vetor � aproximadamente zero.
     */
    bool near_zero() const;

    /**
     * @brief Sobrecarga do operador de multiplica��o por escalar.
     */
    vec3 operator*(double scalar) const;
};

/**
 * @class ivec3
 * @brief Classe que representa um vetor de inteiros 3D.
 */
class ivec3 {
public:
    int x, y, z;

    /**
     * @brief Construtor padr�o.
     */
    ivec3();

    /**
     * @brief Construtor com par�metros.
     * @param x Componente x do vetor.
     * @param y Componente y do vetor.
     * @param z Componente z do vetor.
     */
    ivec3(int x, int y, int z);
};

/**
 * @brief Sobrecarga do operador de subtra��o para vetores 3D.
 * @param v Vetor a ser subtra�do.
 * @return Vetor resultante da subtra��o.
 */
vec3 operator-(const vec3& v);

/**
 * @brief Implementa a multiplica��o de vetor 3D por escalar.
 */
vec3 operator*(double scalar, const vec3& v);

/**
 * @brief Implementa a divis�o de escalar por vetor 3D.
 */
vec3 operator/(double scalar, const vec3& v);

/**
 * @brief Implementa a normaliza��o de um vetor 3D.
 */
vec3 unit_vector(const vec3& v);

/**
 * @brief Implementa o produto vetorial de dois vetores 3D.
 */
vec3 cross(const vec3& v1, const vec3& v2);

/**
 * @brief Implementa o produto escalar de dois vetores 3D.
 */
double dot(const vec3& v1, const vec3& v2);

/**
 * @class vec4
 * @brief Classe que representa um vetor 4D.
 */
class vec4 {
public:
    double x, y, z, w;

    /**
     * @brief Construtor padr�o.
     */
    vec4();

    /**
     * @brief Construtor com par�metros.
     * @param x Componente x do vetor.
     * @param y Componente y do vetor.
     * @param z Componente z do vetor.
     * @param w Componente w do vetor.
     */
    vec4(double x, double y, double z, double w);

    /**
     * @brief Sobrecarga do operador de adi��o.
     * @param other O vetor a ser somado.
     * @return O vetor resultante da soma.
     */
    vec4 operator+(const vec4& other) const;

    /**
     * @brief Sobrecarga do operador de subtra��o.
     * @param other O vetor a ser subtra�do.
     * @return O vetor resultante da subtra��o.
     */
    vec4 operator-(const vec4& other) const;

    /**
     * @brief Sobrecarga do operador de produto escalar.
     * @param other O vetor para o produto escalar.
     * @return O produto escalar entre os vetores.
     */
    double operator*(const vec4& other) const;

    /**
     * @brief Sobrecarga do operador de multiplica��o por escalar.
     * @param scalar O escalar para a multiplica��o.
     * @return O vetor resultante da multiplica��o por escalar.
     */
    vec4 operator*(double scalar) const;

    /**
     * @brief Sobrecarga do operador de divis�o por escalar.
     * @param scalar O escalar para a divis�o.
     * @return O vetor resultante da divis�o por escalar.
     */
    vec4 operator/(double scalar) const;

    /**
     * @brief Calcula o comprimento do vetor.
     * @return O comprimento do vetor.
     */
    double length() const;
};

/**
 * @class mat2
 * @brief Classe que representa uma matriz 2x2.
 */
class mat2 {
public:
    double data[2][2];

    /**
     * @brief Construtor padr�o.
     */
    mat2();

    /**
     * @brief Construtor com par�metros.
     * @param a Elemento a da matriz.
     * @param b Elemento b da matriz.
     * @param c Elemento c da matriz.
     * @param d Elemento d da matriz.
     */
    mat2(double a, double b, double c, double d);

    /**
     * @brief Sobrecarga do operador de adi��o.
     * @param other A matriz a ser somada.
     * @return A matriz resultante da soma.
     */
    mat2 operator+(const mat2& other) const;
};

/**
 * @class mat3
 * @brief Classe que representa uma matriz 3x3.
 */
class mat3 {
public:
    double data[3][3];

    /**
     * @brief Construtor padr�o.
     */
    mat3();

    /**
     * @brief Construtor com par�metros.
     * @param a Elemento a da matriz.
     * @param b Elemento b da matriz.
     * @param c Elemento c da matriz.
     * @param d Elemento d da matriz.
     * @param e Elemento e da matriz.
     * @param f Elemento f da matriz.
     * @param g Elemento g da matriz.
     * @param h Elemento h da matriz.
     * @param i Elemento i da matriz.
     */
    mat3(double a, double b, double c, double d, double e, double f, double g, double h, double i);

    /**
     * @brief Sobrecarga do operador de adi��o.
     * @param other A matriz a ser somada.
     * @return A matriz resultante da soma.
     */
    mat3 operator+(const mat3& other) const;
};

/**
 * @class mat4
 * @brief Classe que representa uma matriz 4x4.
 */
class mat4 {
public:
    double data[4][4];

    /**
     * @brief Construtor padr�o.
     */
    mat4();

    /**
     * @brief Construtor com par�metros.
     * @param a Elemento a da matriz.
     * @param b Elemento b da matriz.
     * @param c Elemento c da matriz.
     * @param d Elemento d da matriz.
     * @param e Elemento e da matriz.
     * @param f Elemento f da matriz.
     * @param g Elemento g da matriz.
     * @param h Elemento h da matriz.
     * @param i Elemento i da matriz.
     * @param j Elemento j da matriz.
     * @param k Elemento k da matriz.
     * @param l Elemento l da matriz.
     * @param m Elemento m da matriz.
     * @param n Elemento n da matriz.
     * @param o Elemento o da matriz.
     * @param p Elemento p da matriz.
     */
    mat4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p);

    /**
     * @brief Sobrecarga do operador de adi��o.
     * @param other A matriz a ser somada.
     * @return A matriz resultante da soma.
     */
    mat4 operator+(const mat4& other) const;
};

/**
 * @brief Implementa a multiplica��o de matriz 2D por vetor 2D.
 * @param m A matriz 2D.
 * @param v O vetor 2D.
 * @return O vetor resultante da multiplica��o.
 */
vec2 operator*(const mat2& m, const vec2& v);

/**
 * @brief Implementa a multiplica��o de matriz 4D por vetor 4D.
 * @param m A matriz 4D.
 * @param v O vetor 4D.
 * @return O vetor resultante da multiplica��o.
 */
vec4 operator*(const mat4& m, const vec4& v);

/**
 * @brief Gera um n�mero aleat�rio no intervalo [0, 1).
 * @return Um n�mero aleat�rio no intervalo [0, 1).
 */
double random_double();

/**
 * @brief Gera um n�mero aleat�rio no intervalo [min, max).
 * @param min O valor m�nimo do intervalo.
 * @param max O valor m�ximo do intervalo.
 * @return Um n�mero aleat�rio no intervalo [min, max).
 */
double random_double(double min, double max);

/**
 * @brief Sobrecarga do operador de multiplica��o de vetores 3D.
 * @param u O primeiro vetor.
 * @param v O segundo vetor.
 * @return O resultado da multiplica��o de componentes dos vetores.
 */
vec3 operator*(const vec3& u, const vec3& v);

/**
 * @brief Gera um vetor 3D com componentes aleat�rias no intervalo [min, max).
 * @param min O valor m�nimo para as componentes do vetor.
 * @param max O valor m�ximo para as componentes do vetor.
 * @return Um vetor 3D com componentes aleat�rias no intervalo [min, max).
 */
static vec3 random(double min, double max);

/**
 * @brief Gera um vetor 3D aleat�rio dentro de uma esfera unit�ria.
 * @return Um vetor 3D aleat�rio dentro de uma esfera unit�ria.
 */
vec3 random_in_unit_sphere();

/**
 * @brief Gera um vetor 3D aleat�rio com comprimento unit�rio.
 * @return Um vetor 3D aleat�rio com comprimento unit�rio.
 */
vec3 random_unit_vector();

/**
 * @brief Reflete um vetor em rela��o a uma normal.
 * @param v O vetor a ser refletido.
 * @param n A normal com rela��o � qual v ser� refletido.
 * @return O vetor refletido.
 */
vec3 reflect(const vec3& v, const vec3& n);

/**
 * @brief Refrata um vetor atrav�s de uma superf�cie com �ndices de refra��o especificados.
 * @param uv O vetor a ser refratado.
 * @param n A normal da superf�cie.
 * @param etai_over_etat A raz�o dos �ndices de refra��o (eta incidente sobre eta transmitida).
 * @return O vetor refratado.
 */
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);

#endif // MATVEC_H





