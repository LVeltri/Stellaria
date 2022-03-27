CXXFLAGS = -IC:\Win-builds\include
LXXFLAGS =  -LC:\msys64\mingw64\lib
LIBS = -lmingw32 -llibportaudio

audio:
	g++ -std=c++11 audio.cpp $(CXXFLAGS) $(LXXFLAGS) $(LIBS) -o audio.exe
	audio.exe