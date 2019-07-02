# -*- MakeFile -*-

path_l = ../obj/
sfml_lib = -lsfml-system -lsfml-window -lsfml-graphics
path_bin = ../bin/
prog = engine
modules = $(path_l)engine.o $(path_l)data.o $(path_l)pipeline.o $(path_l)transformations.o $(path_l)object.o
headers = Settings.h
debug = -g -Wall
$(prog): $(modules)
	g++ $(debug) $(modules) $(sfml_lib) -o $(path_bin)$(prog) $(headers)

$(path_l)engine.o: main.cpp $(headers)
	g++ -c main.cpp -o $(path_l)engine.o

$(path_l)data.o: Data.cpp
	g++ -c Data.cpp -o $(path_l)data.o

$(path_l)pipeline.o: Pipeline.h Pipeline.cpp $(headers)
	g++ -c Pipeline.cpp -o $(path_l)pipeline.o

$(path_l)transformations.o: Transformations.hpp Transformations.cpp
	g++ -c Transformations.cpp -o $(path_l)transformations.o

$(path_l)object.o: ObjectGenerator.hpp ObjectGenerator.cpp
	g++ -c ObjectGenerator.cpp -o $(path_l)object.o
