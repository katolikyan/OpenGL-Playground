#include "Mat4.class.hpp"
#include <cmath>

Mat4::Mat4() {
  for(int i = 0; i < 16; i++)
    m_mat4[i] = 0.0f;
    
}

Mat4::Mat4(float value) {
  for(int i = 0; i < 16; i++)
    m_mat4[i] = (i % 5 == 0 ? value : 0.0f);
}

Mat4::Mat4(float x, float y, float z, float w) {
  for(int i = 0; i < 16; i++)
    m_mat4[i] = 0.0f;
  m_mat4[0] = x;
  m_mat4[5] = y;
  m_mat4[10] = z;
  m_mat4[15] = w;
}

Mat4::Mat4(Mat4 const &other) {
  for(int i = 0; i < 16; i++)
    m_mat4[i] = other.m_mat4[i];
}

Mat4::~Mat4() {}

Mat4& Mat4::operator=(Mat4 const &other) {
  for(int i = 0; i < 16; i++)
    m_mat4[i] = other.m_mat4[i];
  return *this;
}

Mat4 Mat4::operator*(Mat4 const &other) const {
  Mat4 tmp;

  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      for (int i = 0; i < 4; i++)
        tmp.m_mat4[row * 4 + col] += m_mat4[row * 4 + i] * other.m_mat4[i * 4 + col];
  return tmp;
}

Mat4 Mat4::operator*(float scalar) const{
  Mat4 tmp = *this;
  for(int i = 0; i < 16; i++)
    tmp.m_mat4[i] *= scalar;
  return tmp;
}

Mat4 Mat4::operator-(Mat4 const &other) const{
  Mat4 tmp = *this;
  for(int i = 0; i < 16; i++)
    tmp.m_mat4[i] -= other.m_mat4[i];
  return tmp;
}

Mat4 Mat4::operator-(float scalar) const {
  Mat4 tmp = *this;
  for(int i = 0; i < 16; i++) 
    tmp.m_mat4[i] -= scalar;
  return tmp;
}

Mat4 Mat4::operator+(Mat4 const &other) const {
  Mat4 tmp = *this;
  for(int i = 0; i < 16; i++)
    tmp.m_mat4[i] += other.m_mat4[i];
  return tmp;
}

Mat4 Mat4::operator+(float scalar) const {
  Mat4 tmp = *this;
  for(int i = 0; i < 16; i++)
    tmp.m_mat4[i] += scalar;
  return tmp;
}

float& Mat4::operator[](int index) {
  return m_mat4[index];
}

std::ostream& operator<<(std::ostream& os, Mat4 const& other) {
  for(int row = 0; row < 4; row++) {
    if (row == 0)
      os << "[";
    else
      os << " ";
    os << "[";
    os << other.m_mat4[row * 4 + 0] << ", ";
    os << other.m_mat4[row * 4 + 1] << ", ";
    os << other.m_mat4[row * 4 + 2] << ", ";
    os << other.m_mat4[row * 4 + 3] << "]";
    if (row == 3)
      os << "]";
    else
      os << "\n";
  }
  return os;
}

void  Mat4::Rotate(float x, float y, float z) {
  if (x != 0.0f) {
    x *= M_PI / 180;
    Mat4 rot(1.0f);
    rot.m_mat4[5] = cos(x);
    rot.m_mat4[6] = sin(x);
    rot.m_mat4[9] = -sin(x);
    rot.m_mat4[10] = cos(x);
    *this = *this * rot;
  }
  if (y != 0.0f) {
    y *= M_PI / 180;
    Mat4 rot(1.0f);
    rot.m_mat4[0] = cos(y);
    rot.m_mat4[2] = -sin(y);
    rot.m_mat4[8] = sin(y);
    rot.m_mat4[10] = cos(y);
    *this = *this * rot;
  }
  if (z != 0.0f) {
    z *= M_PI / 180;
    Mat4 rot(1.0f);
    rot.m_mat4[0] = cos(z);
    rot.m_mat4[1] = sin(z);
    rot.m_mat4[4] = -sin(z);
    rot.m_mat4[5] = cos(z);
    *this = *this * rot;
  }
}

void  Mat4::SetScale(float x, float y, float z) {

  if(x != 0.0f)
    m_mat4[0] *= x;
  if(y != 0.0f)
    m_mat4[5] *= y;
  if(z != 0.0f)
    m_mat4[10] *= z;
}

void  Mat4::SetTranslate(float x, float y, float z) {
  m_mat4[3] += x;
  m_mat4[7] += y;
  m_mat4[11] += z;
}

void  Mat4::Transpose() {
  Mat4 tmp;

  for(int row = 0; row < 4; row++)
    for(int i = 0; i < 4; i++)
      tmp.m_mat4[i * 4 + row] = m_mat4[row * 4 + i];
  *this = tmp;
}

void  Mat4::Set(float x, float y, float z, float w) {
  m_mat4[0] = x;
  m_mat4[5] = y;
  m_mat4[10] = z;
  m_mat4[15] = w;
}