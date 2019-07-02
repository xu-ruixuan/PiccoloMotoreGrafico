#ifndef PIPELINE_H
#define PIPELINE_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Data.cpp"

class Pipeline{

  std::vector<Triangle> buffer;
  std::vector<sf::VertexArray> out;
  void normalize(Triangle& tris);

public:
  float va, vb, vc, vd;
  float wa, wb, wc, wd;

  Camera camera;
  Vector light;

  Transformation projection;
  Transformation screenSpace;
  Transformation toCamSpace;

  Pipeline(int width, int height);
  void draw(Object obj);
  std::vector<sf::VertexArray> display();
};

#endif
