#include "Pipeline.h"
#include "Transformations.hpp"
#include "Data.cpp"

#include "Settings.h"

#include <SFML/Graphics.hpp>
#include <math.h>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iterator>
#include <vector>
#include <iostream>

#define BACK_COLOR sf::Color::White
#define EDGE_COLOR sf::Color::Black
#define FILL_COLOR sf::Color::Green

Pipeline::Pipeline(int width, int height){

  camera.position << 0,0,0,1;
  camera.dir.set(Vector(1,0,0,0),Vector(0,1,0,0));
  camera.distance = 1;

  double fov = camera.distance * tan(CAMERA_FOV/2.0 * 3.14 / 180.0);
  float aspect_ratio = AUTO_ASPECT_RATIO ?
                      (float)height/(float)width :
                      ASPECT_RATIO;
  this->wa = -fov + X0;
  this->wb = fov + X0;
  this->wc = -fov * aspect_ratio + Y0;
  this->wd = fov * aspect_ratio + Y0;

  this->va = 0;
  this->vb = width;
  this->vc = height;
  this->vd = 0;

  screenSpace = getViewSpace(wa,wb,wc,wd,va,vb,vc,vd);

  projection = PERSPECTIVE ? getPerspective(camera) : getOrthogonal();

  light = Vector(.5,-1,1,0);
  light.normalize();
}

void Pipeline::normalize(Triangle& tris){
  for(int i = 0; i < 3; i++)
    if(tris.vertex[i](3) != 0)
      tris.vertex[i] /= tris.vertex[i](3);
}

void Pipeline::draw(Object obj){
  //To world space
  Transformation space = getSpaceMatrix(ZERO_VEC, obj.position, obj.dir);
  std::vector<Triangle>::iterator iter;
  for(iter = obj.tris.begin(); iter != obj.tris.end(); iter++){
    Triangle tri = transform(*iter, space);
    tri.color = obj.color;
    buffer.push_back(tri);
  }

}

std::vector<sf::VertexArray> Pipeline::display(){
  out.clear();

  toCamSpace = getSpaceMatrix(camera.position, ZERO_VEC, camera.dir);

  //Sort
  std::sort(buffer.begin(), buffer.end(), std::greater<Triangle>());

  for(std::vector<Triangle>::iterator iter = buffer.begin(); iter != buffer.end(); iter++){

    //To camera space
    *iter = transform(*iter, toCamSpace);

    //Backface checking
    Eigen::Vector3d v1 = PERSPECTIVE ? (*iter).vertex[0].head(3) : Eigen::Vector3d(0,0,1);
    (*iter).computeNormal();
    if(v1.dot((*iter).normal.head(3)) < 0 || !BACK_FACE_CULLING){

      //Light
      (*iter).normal.normalize();
      float intensity = 1;
      float illumination = -1 * (*iter).normal.dot(light) * intensity;
      if(illumination < 0)
        illumination = 0;
      sf::Color color = (*iter).color;
      color.r *= illumination;
      color.g *= illumination;
      color.b *= illumination;

      //Projection
      *iter = transform(*iter, projection);

      //To 2D coordinates
      normalize(*iter);

      //To screenspace
      *iter = transform(*iter, screenSpace);

      //Draw
      if(WIREFRAME){
        sf::VertexArray wire(sf::LineStrip, 4);
        wire[0].position = sf::Vector2f((*iter).vertex[0](0),(*iter).vertex[0](1));
        wire[1].position = sf::Vector2f((*iter).vertex[1](0),(*iter).vertex[1](1));
        wire[2].position = sf::Vector2f((*iter).vertex[2](0),(*iter).vertex[2](1));
        wire[3].position = wire[0].position;

        wire[0].color = color;
        wire[1].color = color;
        wire[2].color = color;
        wire[3].color = color;
        out.push_back(wire);
      }else{
        sf::VertexArray triangle(sf::Triangles, 3);
        triangle[0].position = sf::Vector2f((*iter).vertex[0](0),(*iter).vertex[0](1));
        triangle[1].position = sf::Vector2f((*iter).vertex[1](0),(*iter).vertex[1](1));
        triangle[2].position = sf::Vector2f((*iter).vertex[2](0),(*iter).vertex[2](1));

        triangle[0].color = color;
        triangle[1].color = color;
        triangle[2].color = color;
        out.push_back(triangle);
      }
    }
  }
  buffer.clear();
  return out;

}
