#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <stdint.h>

#include <vector>
#include <iterator>

#include <eigen3/Eigen/Dense>

#include "Data.cpp"
#include "Pipeline.h"
#include "Transformations.hpp"
#include "ObjectGenerator.hpp"

#include "Settings.h"

Pipeline * pipe;

void input(Object& obj, sf::Time elapsed){
  Transformation transformation;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    transformation = getTranslation(Vector(-1,0,0,0) * elapsed.asSeconds());
    obj.position = transform(obj.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    transformation = getTranslation(Vector(1,0,0,0)  * elapsed.asSeconds());
    obj.position = transform(obj.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    transformation = getTranslation(Vector(0,1,0,0) * elapsed.asSeconds() );
    obj.position = transform(obj.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    transformation = getTranslation(Vector(0,-1,0,0)  * elapsed.asSeconds() );
    obj.position = transform(obj.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
    transformation = getTranslation(Vector(0,0,1,0)  * elapsed.asSeconds() );
    obj.position = transform(obj.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
    transformation = getTranslation(Vector(0,0,-1,0)  * elapsed.asSeconds() );
    obj.position = transform(obj.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
    transformation = getRotation(Vector(0,0,0,0),Vector(0,1,0,0), 0.1);
    obj.dir.forward = transform(obj.dir.forward, transformation);
    obj.dir.up = transform(obj.dir.up, transformation);
    obj.dir.left = transform(obj.dir.left, transformation);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && PERSPECTIVE){
    pipe->camera.distance += 1 * elapsed.asSeconds();
    pipe->projection = getPerspective(pipe->camera);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && PERSPECTIVE){
    pipe->camera.distance -= 1 * elapsed.asSeconds();
    pipe->projection = getPerspective(pipe->camera);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
    transformation = getNonUniformScale(Vector(0,0,0,0),Vector(1,0,1,0), 1.1);
    obj.dir.forward = transform(obj.dir.forward, transformation);
    obj.dir.up = transform(obj.dir.up, transformation);
    obj.dir.left = transform(obj.dir.left, transformation);
  }


  if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
    transformation = getUniformScale(Vector(0,0,0,0), 1.1);
    obj.dir.forward = transform(obj.dir.forward, transformation);
    obj.dir.up = transform(obj.dir.up, transformation);
    obj.dir.left = transform(obj.dir.left, transformation);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
    transformation = getUniformScale(Vector(0,0,0,0), .9);
    obj.dir.forward = transform(obj.dir.forward, transformation);
    obj.dir.up = transform(obj.dir.up, transformation);
    obj.dir.left = transform(obj.dir.left, transformation);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
    std::cout << "Info:" << '\n';
    std::cout << "Elapsed:" << elapsed.asSeconds() << '\n';
    std::cout << "Pos:" << "\n"<<obj.position << '\n';
    std::cout << "Forward:" << "\n"<<obj.dir.forward<<'\n';
    std::cout << "Up:" <<"\n"<<obj.dir.up<<'\n';
    std::cout << "Left" <<"\n" <<obj.dir.left<< '\n';
  }
}

void camera_mov(sf::Time elapsed){
  Transformation transformation;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
    transformation = getTranslation(Vector(-1,0,0,0) * elapsed.asSeconds());
    pipe->camera.position = transform(pipe->camera.position, transformation);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
    transformation = getTranslation(Vector(1,0,0,0)  * elapsed.asSeconds());
    pipe->camera.position = transform(pipe->camera.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
    transformation = getTranslation(Vector(0,0,1,0) * elapsed.asSeconds());
    pipe->camera.position = transform(pipe->camera.position, transformation);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
    transformation = getTranslation(Vector(0,0,-1,0)  * elapsed.asSeconds());
    pipe->camera.position = transform(pipe->camera.position, transformation);
  }

}

int main(int argc, char const *argv[]) {
  int va = 0;
  int vb = RES_W - 1;
  int vc = RES_H - 1;
  int vd = 0;

  std::vector<sf::VertexArray> shapes;
  std::vector<Object> objects;

  sf::RenderWindow window(sf::VideoMode(abs(vb-va), abs(vd-vc)), "Test");
  window.setActive(true);
  bool running = true;

  pipe = new Pipeline(abs(vb-va), abs(vd-vc));
  if(SHOW_PYRAMID){
    Object obj = generatePiramid();
    obj.color = sf::Color::Blue;
    obj.position << 0,0,4,1;
    objects.push_back(obj);
  }
  if(SHOW_SPHERE){
    Object sphere = readObjFile("obj/sphere.obj");
    sphere.color = sf::Color::Green;
    sphere.position << -2.5,0,7,1;
    objects.push_back(sphere);
  }
  if(SHOW_TEAPOT){
    Object tea = readObjFile("obj/teapot.obj");
    tea.color = sf::Color::Red;
    tea.position << 0,-0.5,10,1;
    objects.push_back(tea);
  }

  sf::Clock clock;
  sf::Time elapsed;
  sf::Time frame_time = sf::seconds(1.0/60.0);
  while(running){
    sf::Event event;

    while(window.pollEvent(event))
      if(event.type == sf::Event::Closed)
        running = false;


    //Wait for next cycle, we were too fast
    elapsed = clock.restart();
    if(frame_time > elapsed){
      sf::sleep(frame_time - elapsed);
      elapsed += clock.getElapsedTime();
    }

    //window.clear(sf::Color(100,100,100));
    window.clear(sf::Color::White);

    //input(obj, elapsed);
    //input(sphere, elapsed);
    input(objects.back(), elapsed);
    camera_mov(elapsed);

    std::vector<Object>::iterator iter1;
    for(iter1 = objects.begin(); iter1 != objects.end(); iter1++)
      pipe->draw(*iter1);

    shapes = pipe->display();
    std::vector<sf::VertexArray>::iterator iter2;
    for(iter2 = shapes.begin(); iter2 != shapes.end(); iter2++)
      window.draw(*iter2);

    window.display();
  }
  return 0;
}
