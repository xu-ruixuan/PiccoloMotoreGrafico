#include "Transformations.hpp"
#include "Data.cpp"

#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Dense>

Transformation getTranslation(Vertex t){
  Transformation translation;
  translation << 1,0,0,0,
                 0,1,0,0,
                 0,0,1,0,
                 t(0),t(1),t(2),1;
  return translation;
  }

Transformation getRotation(Vertex o, Vertex axis, float degree){
  Transformation rotation;
  Eigen::Matrix3d rot;
  Eigen::Vector3d u = axis.head(3);
  Eigen::Vector3d q = o.head(3);
  Eigen::Vector3d w(0,0,0);
  Eigen::Matrix3d cross;
  cross << 0,     u(2), -u(1),
          -u(2),  0    , u(0),
           u(1), -u(0),  0;
  rot = (cos(degree) * IDENTITY3X3) + ((1 - cos(degree)) * (u * u.transpose())) + (sin(degree) * cross);
  w = (q.transpose() * (IDENTITY3X3 - rot));
  rot.transposeInPlace();

  rotation << rot(0,0), rot(0,1), rot(0,2), 0,
              rot(1,0), rot(1,1), rot(1,2), 0,
              rot(2,0), rot(2,1), rot(2,2), 0,
              w(0),     w(1),     w(2),     1;
  return rotation;
}

Transformation getUniformScale(Vertex q, float scale){
  Transformation uScaling;
  double t = 1-scale;
  uScaling    << scale,       0,      0, 0,
                 0,       scale,      0, 0,
                 0,           0 , scale, 0,
                 t*q(0), t*q(1), t*q(2), 1;
  return uScaling;
}

Transformation getNonUniformScale(Vertex o, Vertex dir, float scale){
  Transformation nUScaling;
  Eigen::Matrix3d scaling;
  Eigen::Vector3d u = dir.head(3);
  Eigen::Vector3d q = o.head(3);
  Eigen::Vector3d w;

  scaling = IDENTITY3X3 + ((scale - 1) * u * u.transpose());
  scaling.transposeInPlace();
  w = q.transpose() * (IDENTITY3X3 - scaling);
  nUScaling << scaling(0,0), scaling(0,1), scaling(0,2), 0,
               scaling(1,0), scaling(1,1), scaling(1,2), 0,
               scaling(2,0), scaling(2,1), scaling(2,2), 0,
               w(0),         w(1),         w(2),         1;

  return nUScaling;
}

Transformation getViewSpace(float wa, float wb, float wc, float wd,float va, float vb, float vc, float vd){
  Transformation screenSpace;
  screenSpace <<  (vb-va)/(wb-wa), 0, 0, 0,
                  0, (vd-vc)/(wd-wc), 0, 0,
                  0, 0, 1, 0,
                  ((wb*vb)-(wa*va))/(wb-wa), ((wd*vd)-(wc*vc))/(wd-wc),  0, 1;
  return screenSpace;
}

Transformation getPerspective(Camera camera){
  Transformation perspective;
  perspective << 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 1/camera.distance,
                 0, 0, 0, 0;
  return perspective;
}

Transformation getOrthogonal(){
  Transformation orthogonal;
  orthogonal << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 0;
  return orthogonal;
}

Transformation getSpaceMatrix(Vector old_origin, Vector new_origin, Orientation dir){

  Transformation space;
  Vector w = new_origin - old_origin;
  space << dir.forward(0), dir.up(0), dir.left(0),0,
           dir.forward(1), dir.up(1), dir.left(1),0,
           dir.forward(2), dir.up(2), dir.left(2),0,
           w(0), w(1), w(2),1;
  return space;
}

Vertex transform(Vertex v, Transformation trans){
  return v.transpose() * trans;
}

Triangle transform(Triangle tris, Transformation trans){
  tris.vertex[0] = transform(tris.vertex[0], trans);
  tris.vertex[1] = transform(tris.vertex[1], trans);
  tris.vertex[2] = transform(tris.vertex[2], trans);
  tris.normal = transform(tris.normal, trans);
  return tris;
}
