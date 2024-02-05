#define cimg_display 0
#include "CImg.h"
#include <omp.h>
#include "matvec.h"
#include "Ray.h"
#include "objeto.h"
#include "Triangulo.h"
#include "Interval.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "hittable_list.h"

#include "camera.h"
#include "color.h"
#include "material.h"
#include "sphere.h"


#include <iostream>
#include "Tarefa5.h"

using namespace cimg_library;

/**
 * @brief Salva uma imagem usando a biblioteca CImg.
 * @param imagem A imagem a ser salva.
 * @param nomeArquivo O nome do arquivo de destino.
 */
void salvarImagem(const CImg<unsigned char>& imagem, const std::string& nomeArquivo) {
	imagem.save_png(nomeArquivo.c_str());
}

/**
 * @brief Função principal do programa.
 * @return 0 em caso de sucesso e tem as duas imagens sendo geradas
 */
int main() {




	hittable_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_seahorse = make_shared<dielectric>(1.1);
	auto material_cube = make_shared<metal>(color(0.512161, 0.014327, 0.2), 0.08);
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));

	world.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(vec3(0.2, 0.0, -1.0), 0.5, material_center));


	

	Objeto obj;

	std::vector<Triangulo> cubo = obj.readObj("C:\\Users\\lagoa\\source\\repos\\tarefa4\\cube.obj", vec3(-0.9, 0.5, -0.8), 0.8);
	std::vector<Triangulo> cavalomarinho = obj.readObj("C:\\Users\\lagoa\\source\\repos\\tarefa4\\cube.obj", vec3(1.7, 0.5, -1.0), 0.8);

	for (Triangulo& t : cavalomarinho) {
		t.mat = material_seahorse;
		world.add(make_shared<Triangulo>(t));
	}

	for (auto& t : cubo) {
		t.mat = material_cube;
		world.add(make_shared<Triangulo>(t));
	}




	camera cam;
	//camera cam2;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 720;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	cam.vfov = 90;
	cam.lookfrom = vec3(0, 0, 1);
	cam.lookat = vec3(0, 0, -1);
	cam.vup = vec3(0, 1, 0);


	CImg<unsigned char> imagem = cam.render(world);

	
	cam.lookfrom = vec3(3, 2, 2);

	CImg<unsigned char> imagem_camera2 = cam.render(world);


	salvarImagem(imagem, "mundo.png");
	salvarImagem(imagem_camera2, "mundocamera2.png");




	return 0;
}

