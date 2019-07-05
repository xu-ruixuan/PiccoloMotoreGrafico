#include "OutWindow.h"
#include "Data.cpp"

#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

OutWindow::OutWindow(){
  OutWindow(800,600);
}
OutWindow::OutWindow(int width, int height){
  set(width, height);
  std::cout<<"Window created"<<std::endl;
}

void OutWindow::set(int width, int height){
  this->width = width;
  this->height = height;
  image.create(width, height, sf::Color::Black);
}

void OutWindow::drawPoint(int x, int y, sf::Color color){
  if(x < 0 || x >= width){
  //  std::cout<<"invalid x : "<<x<<","<<y<<std::endl;
    return;
  }
  if(y < 0 || y >= height){
  //  std::cout<<"invalid y : "<<x<<","<<y<<std::endl;
    return;
  }
  image.setPixel(x,y,color);
}
void OutWindow::drawPoint(Vertex vertex, sf::Color color){
  drawPoint(vertex(0), vertex(1), color);
}

void OutWindow::drawHLine(int x1, int x2,int y, sf::Color color){
  if(x1 > x2)
    std::swap(x1,x2);
  for(int i = x1; i < x2;i++)
    drawPoint(i, y, color);
}
void OutWindow::drawLine(int x1, int y1, int x2, int y2, sf::Color color){
  float rise = y2 - y1;
  float run = x2 - x1;
  float m = rise/run;
  int adjust=0;
  float offset = 0;
  float threshold=0.5;
  int y=0;
  int x=0;

//VERTIVAL LINE
  if(run == 0){
    if(y2<y1)
      std::swap(y1, y2);
    for(int i=y1; i < y2; i++)
      drawPoint(x1,i,color);
  //  std::cout <<"init y "<< y1 << '\n';
//    std::cout << "end y " <<y2<< '\n';
    return;
  }

  if(m >= 0)
    adjust = 1;
  else
    adjust = -1;

  if(-1 <= m && m <= 1){
    y=y1;
    if (x2<x1) {
      std::swap(x1, x2);
      y = y2;
    }
  //  std::cout <<"init x "<< x1 << '\n';
  //  std::cout << "end x " <<x2<< '\n';
    m = fabs(m);
    for(int x = x1; x < x2; x++){
      drawPoint(x,y,color);
      offset+=m;
      if(offset>=threshold){
        y+=adjust;
        threshold++;
      }
    }
  }
  else{
    x=x1;
    if (y2<y1) {
      std::swap(y1,y2);
      x = x2;
    }
    m = fabs(1/m);
    for(int y = y1; y < y2; y++){
      drawPoint(x,y,color);
      offset+=m;
      if(offset>=threshold){
        x+=adjust;
        threshold++;
      }
    }
  }
}
void OutWindow::drawLine(Vertex vert1, Vertex vert2, sf::Color color){
  drawLine(vert1(0),vert1(1),
           vert2(0),vert2(1),
           color);
}

void OutWindow::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, sf::Color color){
  drawLine(x1,y1,x2,y2,color);
  drawLine(x2,y2,x3,y3,color);
  drawLine(x3,y3,x1,y1,color);
}
void OutWindow::drawTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color){
  drawTriangle(vert1(0),vert1(1),
               vert2(0),vert2(1),
               vert3(0),vert3(1),
               color);
}

void OutWindow::fillBottomFlatTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color){
  if((int)vert1(1) == (int)vert2(1))
    return;

  double slope1 = (vert2(0) - vert1(0)) / (vert2(1) - vert1(1));
  double slope2 = (vert3(0) - vert1(0)) / (vert3(1) - vert1(1));

  double curr_x1 = vert1(0);
  double curr_x2 = vert1(0);

  for(int scanY = vert1(1); scanY <= vert2(1); scanY++){
    drawLine((int)curr_x1, scanY, (int)curr_x2, scanY, color);
    curr_x1 += slope1;
    curr_x2 += slope2;
  }
}
void OutWindow::fillTopFlatTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color){
  if((int)vert2(1) == (int)vert3(1))
    return;
  double slope1 = (vert3(0) - vert1(0)) / (vert3(1) - vert1(1));
  double slope2 = (vert3(0) - vert2(0)) / (vert3(1) - vert2(1));

  double curr_x1 = vert3(0);
  double curr_x2 = vert3(0);

  for(int scanY = vert3(1); scanY > vert1(1); scanY--){
    drawLine((int)curr_x1, scanY, (int)curr_x2, scanY, color);
    curr_x1 -= slope1;
    curr_x2 -= slope2;
  }
}

void  OutWindow::fillTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color){
  Vertex aux;
  if(vert1(1) > vert2(1)){
    aux = vert1;
    vert1 = vert2;
    vert2 = aux;
  }
  if(vert1(1) > vert3(1)){
    aux = vert1;
    vert1 = vert3;
    vert3 = aux;
  }
  if(vert2(1) > vert3(1)){
    aux = vert2;
    vert2 = vert3;
    vert3 = aux;
  }

  if(vert2(1) == vert3(1)){
    fillBottomFlatTriangle(vert1, vert2, vert3, color);
  }else if(vert1(1) == vert2(1)){
    fillTopFlatTriangle(vert1, vert2, vert3, color);
  }else{
    Vertex vert4(0,0,0,1);
    vert4(1) = vert2(1);
    vert4(0) = vert1(0) + (((vert4(1) - vert1(1))/(vert3(1) - vert1(1))) * (vert3(0) - vert1(0)));
    if(!((vert1(0) > vert4(0) && vert4(0) > vert3(0))|| (vert1(0) < vert4(0) && vert4(0) < vert3(0)))){
      std::cout << "Vertex error!" << '\n';
      std::cout << "vert_x:" << vert1(0) <<","<<vert4(0) <<","<< vert3(0)<<'\n';
    }
    fillBottomFlatTriangle(vert1,vert2,vert4,color);
    fillTopFlatTriangle(vert2,vert4,vert3, color);
  }
}

void OutWindow::clear(sf::Color color){
  for(int i = 0; i < height; i++)
    for(int j = 0; j < width; j++)
      drawPoint(j,i,color);
}
sf::Sprite OutWindow::getImageAsSprite(){
  texture.loadFromImage(image);
  sprite.setTexture(texture);
  return sprite;
}
