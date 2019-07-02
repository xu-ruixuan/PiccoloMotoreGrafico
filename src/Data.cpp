#ifndef PERS_DATA_H
#define PERS_DATA_H

#include <eigen3/Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <vector>

#define IDENTITY3X3 Eigen::Matrix3d::Identity()
#define ZERO_VEC Eigen::Vector4d::Zero()

typedef Eigen::Vector4d Vertex;
typedef Eigen::Vector4d Vector;
typedef Eigen::Matrix4d Transformation;
typedef Eigen::Matrix4d Space;

struct Triangle{
  Vertex vertex[3];
  Vector normal;
  sf::Color color;

  void computeNormal(){
    Eigen::Vector3d v1 = vertex[0].head(3);
    Eigen::Vector3d l1 = vertex[1].head(3) - v1;
    Eigen::Vector3d l2 = vertex[2].head(3) - v1;
    normal << l1.cross(l2), 0;
  }

  bool operator > (const Triangle & triangle) const {
    float f1 = (this->vertex[0](2) + this->vertex[1](2) + this->vertex[2](2)) / 3;
    float f2 = (triangle.vertex[0](2) + triangle.vertex[1](2) + triangle.vertex[2](2)) / 3;
    return f1 > f2;
  }
};

struct Orientation{
  Vector forward;
  Vector up;
  Vector left;

  void set(const Vector & f, const Vector & u){
    Eigen::Vector3d f3 = f.head(3);
    Eigen::Vector3d u3 = u.head(3);
    f3.normalize();
    u3.normalize();
    forward << f3(0), f3(1), f3(2), 0;
    up << u3(0), u3(1), u3(2), 0;
    left << f3.cross(u3), 0;
  }
};

struct Object{
  std::vector<Triangle> tris;
  sf::Color color;
  Vector position;
  Orientation dir;
};

struct Camera{
  Vector position;
  Orientation dir;
  double distance;
};

#endif
