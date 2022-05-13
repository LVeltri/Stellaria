CXXFLAGS = -IC:\Win-builds\include
LXXFLAGS = -LC:/Win-builds/lib64/SDL2 -LC:\msys64\mingw64\lib
LIBS = -lmingw32 c:\Win-builds\lib64\SDL2\libSDL2main.a -llibsdl2 -llibSDL2_image -llibSDL2_ttf -llibportaudio

compile:
	g++ -std=c++11 src/main.cpp src/Engine.cpp src/Star.cpp src/Constellation.cpp src/Texture.cpp res/stellaria.o -o stellaria.exe $(CXXFLAGS) $(LXXFLAGS) $(LIBS)

project:
	g++ -std=c++11 src/Projection.cpp -o Projection.exe

threading:
	g++ -std=c++11 threadTesting/main.cpp -o thread.exe $(CXXFLAGS) $(LXXFLAGS) $(LIBS)