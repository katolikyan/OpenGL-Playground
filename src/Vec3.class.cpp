#include "Vec3.class.hpp"
#include <cmath>

Vec3::Vec3() {
  for (int i = 0; i < 3; i++)
    m_vec3[i] = 0.0;
}

Vec3::Vec3(float value) {
  for (int i = 0; i < 3; i++)
    m_vec3[i] = value;
}

Vec3::Vec3(float v0, float v1, float v2) {
  m_vec3[0] = v0;
  m_vec3[1] = v1;
  m_vec3[2] = v2;
}

Vec3::Vec3(Vec3 &other) {
  for (int i = 0; i < 3; i++)
    m_vec3[i] = other.m_vec3[i];
}

Vec3::~Vec3() {}

Vec3& Vec3::operator=(Vec3 const &other) {
  for (int i = 0; i < 3; i++)
    m_vec3[i] = other.m_vec3[i];
  return *this;
}

Vec3 Vec3::operator*(Vec3 const &other) {
  Vec3 tmp;
  for (int i = 0; i < 3; i++)
    tmp.m_vec3[i] = m_vec3[i] * other.m_vec3[i];
  return tmp;
}

Vec3 Vec3::operator*(float scalar) {
  Vec3 tmp;
  for (int i = 0; i < 3; i++)
    tmp.m_vec3[i] = m_vec3[i] * scalar;
  return tmp;
}

Vec3 Vec3::operator-(Vec3 const &other) {
  Vec3 tmp;
  for (int i = 0; i < 3; i++)
    tmp.m_vec3[i] = m_vec3[i] - other.m_vec3[i];
  return tmp;
}

Vec3 Vec3::operator-(float scalar) {
  Vec3 tmp;
  for (int i = 0; i < 3; i++)
    tmp.m_vec3[i] = m_vec3[i] - scalar;
  return *this;
}

Vec3 Vec3::operator+(Vec3 const &other) {
  Vec3 tmp;
  for (int i = 0; i < 3; i++)
    tmp.m_vec3[i] = m_vec3[i] + other.m_vec3[i];
  return tmp;
}
Vec3 Vec3::operator+(float scalar) {
  Vec3 tmp;
  for (int i = 0; i < 3; i++)
    tmp.m_vec3[i] = m_vec3[i] + scalar;
  return tmp;
}

float& Vec3::operator[](int index) {
  return m_vec3[index];
}

std::ostream& operator<<(std::ostream& os, Vec3 const& other){
  os << "(" << other.m_vec3[0] << ", " << other.m_vec3[1] << ", " << other.m_vec3[2] << ")";
  return os;
}

void  Vec3::Set(float x, float y, float z) {
    m_vec3[0] = x;
    m_vec3[1] = y;
    m_vec3[2] = z;
}

void  Vec3::Rotate(float x, float y, float z) {
  Vec3 tmp(*this);

  if (z != 0.0) {
    z *= (M_PI / 180);
    tmp.m_vec3[0] = m_vec3[0] * cos(z) - m_vec3[1] * sin(z);
    tmp.m_vec3[1] = m_vec3[0] * sin(z) + m_vec3[1] * cos(z);
    *this = tmp;
  }
  if (y != 0.0) {
    y *= (M_PI / 180);
    tmp.m_vec3[0] = m_vec3[0] * cos(y) - m_vec3[2] * sin(y);
    tmp.m_vec3[2] = m_vec3[0] * sin(y) + m_vec3[2] * cos(y);
    *this = tmp;
  }
  if (x != 0.0) {
    x *= (M_PI / 180);
    tmp.m_vec3[0] = m_vec3[1] * cos(x) - m_vec3[2] * sin(x);
    tmp.m_vec3[2] = m_vec3[1] * sin(x) + m_vec3[2] * cos(x);
    *this = tmp;
  }
}

void  Vec3::Scale(float x, float y, float z) {
    m_vec3[0] *= x;
    m_vec3[1] *= y;
    m_vec3[2] *= z;
}

float Vec3::Dot(Vec3 const &other) {
  float res = 0;
  for (int i = 0; i < 3; i++)
    res += m_vec3[i] * other.m_vec3[i];
  return res;
}

Vec3& Vec3::Cross(Vec3 const &other){
  Vec3 tmp(*this);  

  tmp.m_vec3[0] = m_vec3[1] * other.m_vec3[2] - m_vec3[2] * other.m_vec3[1];
  tmp.m_vec3[1] = m_vec3[2] * other.m_vec3[0] - m_vec3[0] * other.m_vec3[2];
  tmp.m_vec3[2] = m_vec3[0] * other.m_vec3[1] - m_vec3[1] * other.m_vec3[0];
  *this = tmp;
  return *this;
}

float  Vec3::GetMagnitude() const {
  double sum;
  for (int i = 0; i < 3; i++)
    sum += m_vec3[i] * m_vec3[i];
  return (sqrt(sum));
}

void  Vec3::Norimalize() {
  float magnitude = GetMagnitude();
  for (int i = 0; i < 3; i++)
    m_vec3[i] /= magnitude;
}