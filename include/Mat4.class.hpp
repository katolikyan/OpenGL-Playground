#ifndef __OBJ_VIEWER_INCLUDE_MAT4_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_MAT4_CLASS_HPP__

#include <iostream>

class Mat4 {
  public:
    Mat4(); //init with zeroes;
    Mat4(float value); // init diagonal;
    Mat4(float x, float y, float z, float w); // init diagonal;
    Mat4(Mat4 const &other);
    ~Mat4();

    Mat4& operator=(Mat4 const &other);    
    Mat4 operator*(Mat4 const &other) const;
    Mat4 operator*(float scalar) const;
    Mat4 operator-(Mat4 const &other) const;
    Mat4 operator-(float scalar) const;
    Mat4 operator+(Mat4 const &other) const;
    Mat4 operator+(float scalar) const;
    float& operator[](int index);
    friend std::ostream& operator<<(std::ostream& os, Mat4 const& other);

    void  Rotate(float x, float y, float z);
    void  SetScale(float x, float y, float z);
    void  SetTranslate(float x, float y, float z);
    void  Transpose();
    void  Set(float x, float y, float z, float w);

  private:
    float m_mat4[16];
};

#endif