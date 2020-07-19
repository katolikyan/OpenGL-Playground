#ifndef __OBJ_VIEWER_INCLUDE_VEC4_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_VEC4_CLASS_HPP__

#include <iostream>

class Vec3 {
  public:
    Vec3(); //init with zeroes;
    Vec3(float value); // init all with one num;
    Vec3(float v0, float v1, float v2); // init with different values;
    Vec3(Vec3 &other);  // copy
    ~Vec3();

    Vec3& operator=(Vec3 const &other);    
    Vec3 operator*(Vec3 const &other);
    Vec3 operator*(float scalar);
    Vec3 operator-(Vec3 const &other);
    Vec3 operator-(float scalar);
    Vec3 operator+(Vec3 const &other);
    Vec3 operator+(float scalar);
    float& operator[](int index);
    friend std::ostream& operator<<(std::ostream& os, Vec3 const& other);

    void  Set(float x, float y, float z);
    void  Rotate(float x, float y, float z);
    void  Scale(float x, float y, float z);
    float Dot(Vec3 const &other);
    Vec3& Cross(Vec3 const &other);
    void  Norimalize();
    float  GetMagnitude() const;

  private:
    float m_vec3[3];
    float m_magnitude;
};

#endif