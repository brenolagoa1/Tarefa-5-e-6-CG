#ifndef Triangulo_H
#define Triangulo_H

#include "ray.h" // Arquivo de definição da classe Ray
#include "matvec.h" // Arquivo de definição de vetores e matrizes
#include "hittable.h" // Arquivo de definição da classe hittable

/**
 * @brief Classe que representa um triângulo em um espaço tridimensional.
 */
class Triangulo : public hittable {
public:
    vec3 v0, v1, v2; // Vértices do triângulo
    vec3 n0, n1, n2; // Normais em cada vértice
    shared_ptr<material> mat; // Material associado ao triângulo

    /**
     * @brief Construtor da classe Triangulo.
     * @param v0 Primeiro vértice do triângulo.
     * @param v1 Segundo vértice do triângulo.
     * @param v2 Terceiro vértice do triângulo.
     */
    Triangulo(const vec3& v0, const vec3& v1, const vec3& v2) : v0(v0), v1(v1), v2(v2) {}

    /**
     * @brief Função de interseção de raio-triângulo.
     * @param r Raio a ser testado quanto à interseção com o triângulo.
     * @param ray_t Intervalo de tempo do raio.
     * @param rec Registro de informações sobre a interseção (se ocorrer).
     * @return True se houver interseção, False caso contrário.
     */
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
        // Vetor que representa a primeira aresta do triângulo
        vec3 edge1 = v1 - v0;
        // Vetor que representa a segunda aresta do triângulo
        vec3 edge2 = v2 - v0;
        // Vetor perpendicular ao plano do triângulo e ao raio
        vec3 h = cross(r.direction(), edge2);
        // Produto escalar entre a primeira aresta e o vetor h
        double a = dot(edge1, h);

        // Verifica se o raio é paralelo ou quase paralelo ao triângulo
        if (a > -1e-6 && a < 1e-6) {
            return false;
        }

        // Fator de escala para calcular a interseção
        double f = 1.0 / a;
        // Vetor da origem do raio ao primeiro vértice do triângulo
        vec3 s = r.origin() - v0;
        // Coordenada baricêntrica u
        double u = f * dot(s, h);

        // Verifica se o ponto de interseção está fora do triângulo na direção da primeira aresta
        if (u < 0.0 || u > 1.0) {
            return false;
        }

        // Vetor perpendicular ao vetor s e à primeira aresta
        vec3 q = cross(s, edge1);
        // Coordenada baricêntrica v
        double v = f * dot(r.direction(), q);

        // Verifica se o ponto de interseção está fora do triângulo na direção da segunda aresta
        if (v < 0.0 || u + v > 1.0) {
            return false;
        }

        // Calcula a distância do raio ao plano do triângulo
        double t = f * dot(edge2, q);
        // Verifica se a interseção está dentro do intervalo de tempo do raio e t é positivo
        if (ray_t.contains(t) && t > 1e-6) {
            // Preenche o registro de interseção
            rec.t = t;
            rec.p = r.at(t);
            // Calcula as coordenadas baricêntricas
            vec3 barycentric = toBarycentricCoordinates(rec.p);
            // Interpola a normal usando as coordenadas baricêntricas
            vec3 interpolated_normal = unit_vector(barycentric.x * n0 + barycentric.y * n1 + barycentric.z * n2);
            // Define a normal da superfície com base na normal interpolada
            rec.set_face_normal(r, interpolated_normal);
            rec.mat = mat;
            return true;
        }
        return false;
    }

    /**
     * @brief Função para calcular as coordenadas baricêntricas de um ponto dentro do triângulo.
     * @param point Ponto para o qual as coordenadas baricêntricas devem ser calculadas.
     * @return Coordenadas baricêntricas do ponto dentro do triângulo.
     */
    vec3 toBarycentricCoordinates(const vec3& point) const {
        // Vetor da origem do triângulo ao ponto
        vec3 v2 = point - v0;

        // Produtos escalares entre as arestas do triângulo
        double d00 = dot(v1 - v0, v1 - v0);
        double d01 = dot(v1 - v0, v2);
        double d11 = dot(v2, v2);
        double d20 = dot(v2, v1 - v0);
        double d21 = dot(v2, v2 - v0);

        // Calcula as coordenadas baricêntricas u, v e w
        double denominator = d00 * d11 - d01 * d01;
        double v = (d11 * d20 - d01 * d21) / denominator;
        double w = (d00 * d21 - d01 * d20) / denominator;
        double u = 1.0 - v - w;

        return vec3(u, v, w);
    }
};

#endif
