#ifndef OUT_WINDOW_H
#define OUT_WINDOW_H

#include <SFML/Graphics.hpp>
#include "Data.cpp"

class OutWindow{
  int width;
  int height;

  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;


  void fillBottomFlatTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color);
  void fillTopFlatTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color);

public:
  OutWindow();
  OutWindow(int width, int height);

  void set(int width, int height);

  void drawPoint(int x, int y, sf::Color color);
  void drawPoint(Vertex vertex, sf::Color color);

  void drawHLine(int x1, int x2,int y, sf::Color color);
  void drawLine(int x1, int y1, int x2, int y2, sf::Color color);
  void drawLine(Vertex vert1, Vertex vert2, sf::Color color);

  void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, sf::Color color);
  void drawTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color);

  void fillTriangle(Vertex vert1, Vertex vert2, Vertex vert3, sf::Color color);

  void clear(sf::Color color);
  sf::Sprite getImageAsSprite();
};

#endif
