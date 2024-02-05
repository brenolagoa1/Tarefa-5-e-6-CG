#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Triangulo.h"
#include "hittable.h"
#include "matvec.h"
#include "Normais.h"
#include "Face.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


/// \class Objeto
/// \brief Classe que representa um objeto tridimensional carregado a partir de um arquivo.
class Objeto {
public:
    

    /**
     * @brief Função para ler um arquivo OBJ e criar uma lista de Triângulos.
     * @param filePath O caminho do arquivo OBJ.
     * @param point O ponto para o qual o objeto será transladado.
     * @param resize O fator de redimensionamento para os vértices.
     * @return Uma lista de Triângulos lidos a partir do arquivo OBJ.
     */
    std::vector<Triangulo> readObj(const std::string& filePath, const vec3 point, float resize) const{

        try {
            std::ifstream fileReader(filePath);
            if (!fileReader.is_open()) {
                throw std::runtime_error("Erro ao abrir o arquivo: " + filePath);
            }

            std::string line;
            std::vector<vec3> vertices;
            std::vector<vec3> normais;
            std::vector<Face> faces;

            while (std::getline(fileReader, line)) {
                if (line.empty() || line[0] == '#') {
                    continue;
                }

                std::istringstream iss(line);
                std::string token;
                iss >> token;

                if (token == "v") {
                    double x, y, z;
                    iss >> x >> y >> z;
                    vertices.emplace_back(x, y, z);
                }
                else if (token == "vn") {
                    double x, y, z;
                    iss >> x >> y >> z;
                    normais.emplace_back(x, y, z);
                }
                else if (token == "f") {
                    std::vector<int> vertexIndices;
                    std::vector<int> normaisindex;
                    int vIndex;
                    char temp;
                    /*while (iss >> vIndex) {*/
                    for (int i = 0; i < 3; i++) {
                        iss >> vIndex;
                        vertexIndices.push_back(vIndex - 1);
                        
                        iss >> temp;
                        iss >> temp;

                        iss >> vIndex;
                        normaisindex.push_back(vIndex - 1);

                        
                    }
                    
                    faces.emplace_back(vertexIndices[0], vertexIndices[1], vertexIndices[2], normaisindex[0], normaisindex[1], normaisindex[2]);
                }
            }

            vec3 centroid;
            double bigDif = calcDimension(vertices, centroid);
            redimensionarVertices(vertices, bigDif);

            vec3 translationDirection = point - centroid;

            //translate the object to a point
            for (auto& vertex : vertices) {
                (vertex = vertex + translationDirection)* resize;
            }


            //translateToCameraCenter(vertices, vec3(0, 0, -1));

            fileReader.close();

            std::vector<Triangulo> triangulos;

            // Convert faces to triangles and store them in the 'triangulos' vector
            for (const auto& face : faces) {
                Triangulo t = criarTriangulo(vertices[face.v1], vertices[face.v2], vertices[face.v3]);
                
                t.n0 = normais[face.n1];
                t.n1 = normais[face.n2];
                t.n2 = normais[face.n3];
                std::clog << "\n" << t.n1.x << "  " << t.n1.y << "  " << t.n1.z;
                triangulos.push_back(t);
            }
            return triangulos;

        }
        catch (const std::exception& e) {
            std::cerr << "Exceção capturada: " << e.what() << std::endl;
        }
        return std::vector<Triangulo>();
    }

    

private:



    /**
     * @brief Cria um Triângulo a partir de três vértices.
     *
     * @param v0 Vértice 0.
     * @param v1 Vértice 1.
     * @param v2 Vértice 2.
     * @return Triangulo Triângulo criado.
     */
    Triangulo criarTriangulo(const vec3& v0, const vec3& v1, const vec3& v2) const {
        // Implemente a criação de um Triangulo usando os vértices v0, v1, v2 e as normais n0, n1, n2
        // Pode ser semelhante ao que você já tinha implementado
        return Triangulo(v0, v1, v2);
    }
    


    /**
     * @brief Redimensiona os vértices do objeto.
     *
     * @param vertices Vetor de vértices a ser redimensionado.
     * @param biggerDif Maior diferença entre as coordenadas.
     */
    void redimensionarVertices(std::vector<vec3>& vertices, double biggerDif) const {
        // Redimensionar os vértices
        for (vec3& vertex : vertices) {
            vertex.x = (vertex.x) / biggerDif;
            vertex.y = (vertex.y) / biggerDif;
            
            vertex.z = (vertex.z) / biggerDif;
        }
    }

    /**
     * @brief Calcula o centroide dos vértices.
     *
     * @param vertices Vetor de vértices.
     * @return vec3 Centroide calculado.
     */
    vec3 calculateCentroid(std::vector<vec3>& vertices) const {
        double sumX = 0, sumY = 0, sumZ = 0;

        for (const vec3& vertex : vertices) {
            sumX += vertex.x;
            sumY += vertex.y;
            sumZ += vertex.z;
        }
        vec3 centroid;
        centroid.x = sumX / vertices.size();
        centroid.y = sumY / vertices.size();
        centroid.z = sumZ / vertices.size();

        return centroid;
    }

    /**
     * @brief Translada os vértices para o centro da câmera.
     *
     * @param vertices Vetor de vértices a ser transladado.
     * @param centroid Vetor de deslocamento para o centro da câmera.
     */
    void translateToCameraCenter(std::vector<vec3>& vertices, const vec3& centroid) const {
        for (vec3& vertex : vertices) {
            vertex.x += centroid.x;
            vertex.y += centroid.y;
            vertex.z += centroid.z;
        }
    }

    /**
    * @brief Calcula a dimensão do objeto e o centroide.
    *
    * @param vertices Vetor de vértices.
    * @param centroid Centroide calculado.
    * @return double Maior diferença entre as coordenadas.
    */
    double calcDimension(std::vector<vec3>& vertices, vec3& centroid) const {
        // Encontrar os limites iniciais
        double minX = std::numeric_limits<double>::max();
        double maxX = std::numeric_limits<double>::min();
        double minY = std::numeric_limits<double>::max();
        double maxY = std::numeric_limits<double>::min();
        double minZ = std::numeric_limits<double>::max();
        double maxZ = std::numeric_limits<double>::min();

        for (const vec3& vertex : vertices) {
            minX = std::min(minX, vertex.x);
            maxX = std::max(maxX, vertex.x);
            minY = std::min(minY, vertex.y);
            maxY = std::max(maxY, vertex.y);
            minZ = std::min(minZ, vertex.z);
            maxZ = std::max(maxZ, vertex.z);
        }

        // Encontrar a maior diferença
        double biggerDif = std::max({ maxX - minX, maxY - minY, maxZ - minZ });

        //centroid
        centroid.x = minX + (maxX - minX) / 2;
        centroid.y = minY + (maxY - minY) / 2;
        centroid.z = minZ + (maxZ - minZ) / 2;

        return biggerDif;
    }
};

#endif
