#ifndef Triangulo_H
#define Triangulo_H

#include "ray.h" // Arquivo de defini��o da classe Ray
#include "matvec.h" // Arquivo de defini��o de vetores e matrizes
#include "hittable.h" // Arquivo de defini��o da classe hittable

/**
 * @brief Classe que representa um tri�ngulo em um espa�o tridimensional.
 */
class Triangulo : public hittable {
public:
    vec3 v0, v1, v2; // V�rtices do tri�ngulo
    vec3 n0, n1, n2; // Normais em cada v�rtice
    shared_ptr<material> mat; // Material associado ao tri�ngulo

    /**
     * @brief Construtor da classe Triangulo.
     * @param v0 Primeiro v�rtice do tri�ngulo.
     * @param v1 Segundo v�rtice do tri�ngulo.
     * @param v2 Terceiro v�rtice do tri�ngulo.
     */
    Triangulo(const vec3& v0, const vec3& v1, const vec3& v2) : v0(v0), v1(v1), v2(v2) {}

    /**
     * @brief Fun��o de interse��o de raio-tri�ngulo.
     * @param r Raio a ser testado quanto � interse��o com o tri�ngulo.
     * @param ray_t Intervalo de tempo do raio.
     * @param rec Registro de informa��es sobre a interse��o (se ocorrer).
     * @return True se houver interse��o, False caso contr�rio.
     */
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
        // Vetor que representa a primeira aresta do tri�ngulo
        vec3 edge1 = v1 - v0;
        // Vetor que representa a segunda aresta do tri�ngulo
        vec3 edge2 = v2 - v0;
        // Vetor perpendicular ao plano do tri�ngulo e ao raio
        vec3 h = cross(r.direction(), edge2);
        // Produto escalar entre a primeira aresta e o vetor h
        double a = dot(edge1, h);

        // Verifica se o raio � paralelo ou quase paralelo ao tri�ngulo
        if (a > -1e-6 && a < 1e-6) {
            return false;
        }

        // Fator de escala para calcular a interse��o
        double f = 1.0 / a;
        // Vetor da origem do raio ao primeiro v�rtice do tri�ngulo
        vec3 s = r.origin() - v0;
        // Coordenada baric�ntrica u
        double u = f * dot(s, h);

        // Verifica se o ponto de interse��o est� fora do tri�ngulo na dire��o da primeira aresta
        if (u < 0.0 || u > 1.0) {
            return false;
        }

        // Vetor perpendicular ao vetor s e � primeira aresta
        vec3 q = cross(s, edge1);
        // Coordenada baric�ntrica v
        double v = f * dot(r.direction(), q);

        // Verifica se o ponto de interse��o est� fora do tri�ngulo na dire��o da segunda aresta
        if (v < 0.0 || u + v > 1.0) {
            return false;
        }

        // Calcula a dist�ncia do raio ao plano do tri�ngulo
        double t = f * dot(edge2, q);
        // Verifica se a interse��o est� dentro do intervalo de tempo do raio e t � positivo
        if (ray_t.contains(t) && t > 1e-6) {
            // Preenche o registro de interse��o
            rec.t = t;
            rec.p = r.at(t);
            // Calcula as coordenadas baric�ntricas
            vec3 barycentric = toBarycentricCoordinates(rec.p);
            // Interpola a normal usando as coordenadas baric�ntricas
            vec3 interpolated_normal = unit_vector(barycentric.x * n0 + barycentric.y * n1 + barycentric.z * n2);
            // Define a normal da superf�cie com base na normal interpolada
            rec.set_face_normal(r, interpolated_normal);
            rec.mat = mat;
            return true;
        }
        return false;
    }

    /**
     * @brief Fun��o para calcular as coordenadas baric�ntricas de um ponto dentro do tri�ngulo.
     * @param point Ponto para o qual as coordenadas baric�ntricas devem ser calculadas.
     * @return Coordenadas baric�ntricas do ponto dentro do tri�ngulo.
     */
    vec3 toBarycentricCoordinates(const vec3& point) const {
        // Vetor da origem do tri�ngulo ao ponto
        vec3 v2 = point - v0;

        // Produtos escalares entre as arestas do tri�ngulo
        double d00 = dot(v1 - v0, v1 - v0);
        double d01 = dot(v1 - v0, v2);
        double d11 = dot(v2, v2);
        double d20 = dot(v2, v1 - v0);
        double d21 = dot(v2, v2 - v0);

        // Calcula as coordenadas baric�ntricas u, v e w
        double denominator = d00 * d11 - d01 * d01;
        double v = (d11 * d20 - d01 * d21) / denominator;
        double w = (d00 * d21 - d01 * d20) / denominator;
        double u = 1.0 - v - w;

        return vec3(u, v, w);
    }
};

#endif
