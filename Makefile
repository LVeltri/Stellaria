CXXFLAGS = -IC:\Win-builds\include
LXXFLAGS = -LC:/Win-builds/lib64/SDL2
LIBS = -lmingw32 c:\Win-builds\lib64\SDL2\libSDL2main.a -llibsdl2 -llibSDL2_ttf

compile:
	g++ -std=c++11 src/main.cpp src/Engine.cpp src/Star.cpp src/Constellation.cpp src/Texture.cpp res/stellaria.o -o stellaria.exe $(CXXFLAGS) $(LXXFLAGS) $(LIBS)
