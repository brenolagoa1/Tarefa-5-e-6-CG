#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "Color.h"
#include "CImg.h"
#include <omp.h>
#include "matvec.h"
#include "objeto.h"
#include "Triangulo.h"
#include "Interval.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "hittable.h"
#include "material.h"

#include <iostream>

/**
 * @brief Classe que representa uma câmera para renderização de imagens.
 */
class camera {
public:
	/**
	 * @brief Taxa de aspecto da imagem.
	 */
	double aspect_ratio;  

	/**
	 * @brief Largura da imagem renderizada em contagem de pixels.
	 */
	int    image_width;  

	/**
	 * @brief Contagem de amostras aleatórias para cada pixel.
	 */
	int    samples_per_pixel; 

	/**
	 * @brief Profundidade máxima de rastreamento de raios.
	 */
	int    max_depth;

	/**
	 * @brief Ângulo de visão vertical (campo de visão).
	 */
	double vfov; 

	/**
	 * @brief Ponto de onde a câmera está olhando.
	 */
	vec3 lookfrom; 

	/**
	 * @brief Ponto para onde a câmera está olhando.
	 */
	vec3 lookat; 

	/**
	 * @brief Direção "para cima" em relação à câmera.
	 */
	vec3 vup; 

	/**
	 * @brief Renderiza a cena definida pelo mundo.
	 * @param world O mundo a ser renderizado.
	 * @return A imagem renderizada.
	 */
	cimg_library::CImg<unsigned char> render(const hittable& world) {

		initialize();

		cimg_library::CImg<unsigned char> imagem(image_width, image_height, 1, 3, 255);

		const int tile_size = 16;  // Tamanho do bloco para processamento

		
		for (int j = 0; j < image_height; ++j) {
			for (int i = 0; i < image_width; ++i) {
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; ++sample) {
					Ray r = get_ray(i, j);


					pixel_color = pixel_color + ray_color(r, max_depth, world);
				}
				color color_aux = write_color(pixel_color, samples_per_pixel);
				unsigned char cor[3] = { static_cast<unsigned char>(255.999 * color_aux.x),
										 static_cast<unsigned char>(255.999 * color_aux.y),
										 static_cast<unsigned char>(255.999 * color_aux.z) };

				imagem.draw_point(i, j, 0, cor);
			}
		}
		
		std::clog << "\rDone.                 \n";

		return imagem;
	}

private:
	/**
	 * @brief Altura da imagem renderizada.
	 */
	int    image_height;   

	/**
	 * @brief Centro da câmera.
	 */
	vec3 center;         

	/**
	 * @brief Localização do pixel 0,0.
	 */
	vec3 pixel00_loc;   

	/**
	 * @brief Delta de pixel na direção u.
	 */
	vec3   pixel_delta_u;  

	/**
	 * @brief Delta de pixel na direção v.
	 */
	vec3   pixel_delta_v;  

	/**
	 * @brief Vetores básicos do quadro da câmera.
	 */
	vec3   w, u, v;        

	/**
	 * @brief Inicializa os parâmetros da câmera.
	 */
	void initialize() {

		image_height = static_cast<int>(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		center = lookfrom;

		
		auto focal_length = (lookfrom - lookat).length();
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h * focal_length;
		auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

		
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		
		auto viewport_u = viewport_width * u; 
		auto viewport_v = viewport_height * -v; 

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		
		auto viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}

	/**
	 * @brief Obtém um raio para um pixel específico.
	 * @param i Coordenada x do pixel.
	 * @param j Coordenada y do pixel.
	 * @return O raio para o pixel especificado.
	 */
	Ray get_ray(int i, int j) const {
		

		auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
		auto pixel_sample = pixel_center + pixel_sample_square();

		auto ray_origin = center;
		auto ray_direction = pixel_sample - ray_origin;

		return Ray(ray_origin, ray_direction);
	}

	/**
	 * @brief Amostra um ponto no quadrado do pixel.
	 * @return O ponto amostrado no quadrado do pixel.
	 */
	vec3 pixel_sample_square() const {
		
		auto px = -0.5 + random_double();
		auto py = -0.5 + random_double();
		return (px * pixel_delta_u) + (py * pixel_delta_v);
	}

	/**
	 * @brief Cor de fundo para o raio.
	 * @param r O raio.
	 * @return A cor de fundo para o raio.
	 */
	color background_color(const Ray& r) const {
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
	}

	/**
	 * @brief Cor do raio.
	 * @param r O raio.
	 * @param depth A profundidade máxima.
	 * @param world O mundo.
	 * @return A cor do raio.
	 */
	color ray_color(const Ray& r, int depth, const hittable& world) const {
		hit_record rec;
		if (depth <= 0)
			return color(0, 0, 0);

		if (world.hit(r, interval(0.001, infinity), rec)) {
			Ray scattered;
			color attenuation;

			if (rec.mat->scatter(r, rec, attenuation, scattered)) {

				return color(attenuation.x, attenuation.y, attenuation.z) * ray_color(scattered, depth - 1, world);
			}
			return color(0, 0, 0);
		}

		return background_color(r);
	}

};

#endif
