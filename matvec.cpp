#include "matvec.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

// Implementação da classe vec2

/// Construtor padrão da classe vec2.
vec2::vec2() : x(0.0), y(0.0) {}

/// Construtor da classe vec2 com parâmetros.
vec2::vec2(double x, double y) : x(x), y(y) {}

/// Sobrecarga do operador de adição para vetores 2D.
vec2 vec2::operator+(const vec2& other) const {
	return vec2(x + other.x, y + other.y);
}

/// Sobrecarga do operador de subtração para vetores 2D.
vec2 vec2::operator-(const vec2& other) const {
	return vec2(x - other.x, y - other.y);
}

/// Sobrecarga do operador de multiplicação escalar para vetores 2D.
double vec2::operator*(const vec2& other) const {
	return x * other.x + y * other.y;
}

/// Sobrecarga do operador de multiplicação por escalar para vetores 2D.
vec2 vec2::operator*(double scalar) const {
	return vec2(x * scalar, y * scalar);
}

/// Sobrecarga do operador de divisão por escalar para vetores 2D.
vec2 vec2::operator/(double scalar) const {
	if (scalar == 0) {
		return vec2(0, 0);
	}
	return vec2(x / scalar, y / scalar);
}

/// Calcula o comprimento (magnitude) do vetor 2D.
double vec2::length() const {
	return std::sqrt(x * x + y * y);
}

// Implementação da classe vec3

/// Construtor padrão da classe vec3.
vec3::vec3() : x(0.0), y(0.0), z(0.0) {}

/// Construtor da classe vec3 com parâmetros.
vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

/// Sobrecarga do operador de adição para vetores 3D.
vec3 vec3::operator+(const vec3& other) const {
	return vec3(x + other.x, y + other.y, z + other.z);
}

/// Sobrecarga do operador de subtração para vetores 3D.
vec3 vec3::operator-(const vec3& other) const {
	return vec3(x - other.x, y - other.y, z - other.z);
}

/// Sobrecarga do operador de multiplicação por escalar para vetores 3D.
//vec3 vec3::operator*(double scalar) const {
//    return vec3(x * scalar, y * scalar, z * scalar);
//}

/// Sobrecarga do operador de divisão por escalar para vetores 3D.
vec3 vec3::operator/(double scalar) const {
	if (scalar == 0) {
		return vec3(0, 0, 0);
	}
	return vec3(x / scalar, y / scalar, z / scalar);
}

/// Calcula o comprimento (magnitude) do vetor 3D.
double vec3::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

double vec3::length_squared() const {
	return x * x + y * y + z * z;
}

bool vec3::near_zero() const {
	// Return true if the vector is close to zero in all dimensions.
	auto s = 1e-8;
	return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
}

vec3 vec3::operator*(double scalar) const {
	return vec3(x * scalar, y * scalar, z * scalar);
}



// Outras funções relacionadas a vec3

/// Sobrecarga do operador de multiplicação escalar por vetor 3D.
vec3 operator*(double scalar, const vec3& v) {
	return v * scalar;
}

/// \brief Sobrecarga do operador de negação para vetores 3D.
/// \param v Vetor a ser negado.
/// \return Vetor resultante da negação.
vec3 operator-(const vec3& v)
{
	return vec3(-v.x, -v.y, -v.z);
}

/// Sobrecarga do operador de divisão escalar por vetor 3D.
vec3 operator/(double scalar, const vec3& v) {
	if (scalar == 0) {
		return vec3(0, 0, 0);
	}
	return vec3(v.x / scalar, v.y / scalar, v.z / scalar);
}

/// Calcula o vetor normalizado (unitário) de um vetor 3D.
vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

/// Calcula o produto vetorial de dois vetores 3D.
vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

/// Calcula o produto escalar de dois vetores 3D.
double dot(const vec3& v1, const vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


// Implementação da classe ivec3
ivec3::ivec3() : x(0), y(0), z(0) {}

ivec3::ivec3(int x, int y, int z) : x(x), y(y), z(z) {}

// Implementação da função para multiplicação de um inteiro por um vetor de inteiros 3D
ivec3 operator*(int scalar, const ivec3& v) {
	return ivec3(scalar * v.x, scalar * v.y, scalar * v.z);
}

// Implementação da função para divisão de um vetor de inteiros 3D por um inteiro
ivec3 operator/(const ivec3& v, int scalar) {
	return ivec3(v.x / scalar, v.y / scalar, v.z / scalar);
}

// Implementação da função para imprimir um vetor de inteiros 3D no cerr
std::ostream& operator<<(std::ostream& os, const ivec3& v) {
	os << "ivec3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}


// Implementação da classe vec4

/// Construtor padrão da classe vec4.
vec4::vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

/// Construtor da classe vec4 com parâmetros.
vec4::vec4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

/// Sobrecarga do operador de adição para vetores 4D.
vec4 vec4::operator+(const vec4& other) const {
	return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

/// Sobrecarga do operador de subtração para vetores 4D.
vec4 vec4::operator-(const vec4& other) const {
	return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

/// Sobrecarga do operador de multiplicação escalar para vetores 4D.
double vec4::operator*(const vec4& other) const {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

/// Sobrecarga do operador de multiplicação por escalar para vetores 4D.
vec4 vec4::operator*(double scalar) const {
	return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

/// Sobrecarga do operador de divisão por escalar para vetores 4D.
vec4 vec4::operator/(double scalar) const {
	if (scalar == 0) {
		return vec4(0, 0, 0, 0);
	}
	return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

/// Calcula o comprimento (magnitude) do vetor 4D.
double vec4::length() const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

// Implementação das classes mat2, mat
/// Construtor padrão de mat2.
mat2::mat2() {
	data[0][0] = 0.0;
	data[0][1] = 0.0;
	data[1][0] = 0.0;
	data[1][1] = 0.0;
}

/// Construtor de mat2 com parâmetros.
mat2::mat2(double a, double b, double c, double d) {
	data[0][0] = a;
	data[0][1] = b;
	data[1][0] = c;
	data[1][1] = d;
}

/// Sobrecarga do operador de adição para mat2.
mat2 mat2::operator+(const mat2& other) const {
	return mat2(data[0][0] + other.data[0][0], data[0][1] + other.data[0][1], data[1][0] + other.data[1][0], data[1][1] + other.data[1][1]);
}

/// Construtor padrão de mat3.
mat3::mat3() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			data[i][j] = 0.0;
		}
	}
}

/// Construtor de mat3 com parâmetros.
mat3::mat3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
	data[0][0] = a;
	data[0][1] = b;
	data[0][2] = c;
	data[1][0] = d;
	data[1][1] = e;
	data[1][2] = f;
	data[2][0] = g;
	data[2][1] = h;
	data[2][2] = i;
}

/// Sobrecarga do operador de adição para mat3.
mat3 mat3::operator+(const mat3& other) const {
	mat3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.data[i][j] = data[i][j] + other.data[i][j];
		}
	}
	return result;
}

/// Construtor padrão de mat4.
mat4::mat4() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = 0.0;
		}
	}
}

/// Construtor de mat4 com parâmetros.
mat4::mat4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p) {
	data[0][0] = a;
	data[0][1] = b;
	data[0][2] = c;
	data[0][3] = d;
	data[1][0] = e;
	data[1][1] = f;
	data[1][2] = g;
	data[1][3] = h;
	data[2][0] = i;
	data[2][1] = j;
	data[2][2] = k;
	data[2][3] = l;
	data[3][0] = m;
	data[3][1] = n;
	data[3][2] = o;
	data[3][3] = p;
}

/// Sobrecarga do operador de adição para mat4.
mat4 mat4::operator+(const mat4& other) const {
	mat4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.data[i][j] = data[i][j] + other.data[i][j];
		}
	}
	return result;
}

// Implementação das operações de multiplicação de matriz por vetor (fora das classes)

/// Multiplica uma matriz 2x2 por um vetor 2D.
vec2 operator*(const mat2& m, const vec2& v) {
	return vec2(m.data[0][0] * v.x + m.data[0][1] * v.y, m.data[1][0] * v.x + m.data[1][1] * v.y);
}




double random_double() {
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0);
}


/// Multiplica uma matriz 4x4 por um vetor 4D.
vec4 operator*(const mat4& m, const vec4& v) {
	return vec4(
		m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z + m.data[0][3] * v.w,
		m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z + m.data[1][3] * v.w,
		m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z + m.data[2][3] * v.w,
		m.data[3][0] * v.x + m.data[3][1] * v.y + m.data[3][2] * v.z + m.data[3][3] * v.w
	);
}



double random_double(double min, double max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random_double();
}


vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}


static vec3 random(double min, double max) {
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 random_in_unit_sphere() {
	while (true) {
		auto p = random(-1, 1);
		if (p.length_squared() < 1)
			return p;
	}
}

vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

