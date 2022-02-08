CXX := clang++
CXXFLAGS := -std=c++17 -Wall

SRC := $(wildcard src/*.cpp)
OUT := -o bin/main

INCLUDES := \
			-Iext/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2 \
			-Iext/SDL2_ttf-2.0.18/x86_64-w64-mingw32/include/SDL2

LIBINCLUDES := \
				-Lext/SDL2-2.0.20/x86_64-w64-mingw32/lib \
				-Lext/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib

LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) $(LIBINCLUDES) $(LIBS) $(OUT)