CXX = g++
MACHINE= $(shell uname -s)
ifeq ($(MACHINE),Darwin)
    SDL = -framework SDL2 -framework SDL2_image
    CXXFLAGS = -Wall -c -std=c++11
    LDFLAGS = $(SDL)
else
    SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
	SDL_INCLUDE = -I/usr/local/include
	CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
	LDFLAGS = $(SDL_LIB)
endif

EXE = SimpleRPG

all: $(EXE)

$(EXE): main.o Engine.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: src/main.cpp src/Engine.h
	$(CXX) $(CXXFLAGS) $< -o $@
Engine.o: src/Engine.cpp src/Engine.h
	$(CXX) $(CXXFLAGS) $< -o $@


clean:
	rm *.o && rm $(EXE)