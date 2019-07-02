#include "ObjectGenerator.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Object generatePiramid(){
  Object obj;
  Triangle tris[6];

  tris[0].vertex[0] << 0,0,0,1;
  tris[0].vertex[1] << 1,1,1,1;
  tris[0].vertex[2] << 2,0,0,1;

  tris[1].vertex[0] << 2,0,0,1;
  tris[1].vertex[1] << 1,1,1,1;
  tris[1].vertex[2] << 2,0,2,1;

  tris[2].vertex[0] << 2,0,2,1;
  tris[2].vertex[1] << 1,1,1,1;
  tris[2].vertex[2] << 0,0,2,1;

  tris[3].vertex[0] << 0,0,0,1;
  tris[3].vertex[1] << 0,0,2,1;
  tris[3].vertex[2] << 1,1,1,1;

  tris[4].vertex[0] << 0,0,0,1;
  tris[4].vertex[1] << 2,0,0,1;
  tris[4].vertex[2] << 0,0,2,1;

  tris[5].vertex[0] << 2,0,0,1;
  tris[5].vertex[1] << 2,0,2,1;
  tris[5].vertex[2] << 0,0,2,1;

  for(int i = 0; i < 6 ; i++){
    tris[i].computeNormal();
    obj.tris.push_back(tris[i]);
  }

  obj.position << 0,0.5,5,1;
  obj.dir.set(Vector(1,0,0,0), Vector(0,1,0,0));
  return obj;
    obj.dir.forward <<1,0,0,0;
}

Object readObjFile(std::string path){
    Object obj;
    std::vector<Vertex> vertices;
    std::ifstream file;
    char index;
    double x,y,z;

    file.open(path);

    if(!file.is_open()){
      std::cout << "File not open" << '\n';
      std::cout << "path : " << path<< '\n';
      std::cout << "Error : " <<std::strerror(errno) <<'\n';
      return obj;
    }

    while(!file.eof()){
      file >> index >> x >> y >> z;
      if(index == 'v'){
        vertices.push_back(Vertex(x,y,z,1));
      }
      if(index == 'f'){
        Triangle tris;
        tris.vertex[0] = vertices.at(x - 1);
        tris.vertex[1] = vertices.at(y - 1);
        tris.vertex[2] = vertices.at(z - 1);
        tris.computeNormal();
        obj.tris.push_back(tris);
      }
    }
    obj.position << 0,0,0,1;
    obj.dir.set(Vector(1,0,0,0), Vector(0,1,0,0));
    return obj;
}
