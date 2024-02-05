#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

/**
 * @brief Classe que representa uma lista de objetos hittable.
 * Herda da classe hittable, indicando sua capacidade de ser usada em cenários de traçado de raios.
 */
class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects; // Vetor para armazenar ponteiros compartilhados para objetos hittable

    /**
     * @brief Construtor padrão.
     */
    hittable_list() {}

    /**
     * @brief Construtor que inicializa a lista com um objeto hittable.
     * @param object O objeto a ser adicionado à lista.
     */
    hittable_list(shared_ptr<hittable> object) { add(object); }

    /**
     * @brief Limpa a lista, removendo todos os objetos hittable.
     */
    void clear() { objects.clear(); }

    /**
     * @brief Adiciona um objeto hittable à lista.
     * @param object O objeto a ser adicionado.
     */
    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    /**
     * @brief Sobrescreve a função da classe base para verificar interseções entre raios e objetos na lista.
     * @param r O raio a ser verificado.
     * @param ray_t O intervalo de tempo para o raio.
     * @param rec O registro de colisão a ser preenchido em caso de colisão.
     * @return true se o raio atingir algum objeto, false caso contrário.
     */
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        // Itera sobre a lista de objetos hittable
        for (const auto& object : objects) {
            // Verifica a interseção com o objeto atual
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec; // Atualiza o registro de colisão com a interseção mais próxima
            }
        }

        return hit_anything;
    }
};

#endif
