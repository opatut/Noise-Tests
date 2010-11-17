default: test1.cpp
	g++ -lnoise -lsfml-graphics -otest1 test1.cpp

run:
	./test1
