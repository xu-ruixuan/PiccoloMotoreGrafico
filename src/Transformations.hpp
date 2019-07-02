#ifndef TRANS_H
#define TRANS_H

#include "Data.cpp"

Transformation getTranslation(Vertex t);

Transformation getRotation(Vertex o, Vertex axis, float degree);

Transformation getUniformScale(Vertex q, float scale);

Transformation getNonUniformScale(Vertex o, Vertex dir, float scale);

Transformation getPerspective(Camera camera);

Transformation getOrthogonal();

Transformation getViewSpace(float wa, float wb, float wc, float wd,float va, float vb, float vc, float vd);

Transformation getSpaceMatrix(Vector old_origin, Vector new_origin, Orientation dir);

Vertex transform(Vertex v, Transformation trans);

Triangle transform(Triangle tris, Transformation trans);

#endif
