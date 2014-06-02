CC = g++
CFLAGS 	= -c -Wall -O3  -I ./include/

#include Libs
#include OpenCV
CFLAGS 		+= $(shell pkg-config opencv --cflags)
LDFLAGS 	+= $(shell pkg-config opencv --libs)

SOURCES		= $(wildcard ./newmain.cpp)
#SOURCES		= $(wildcard ./src/pca_test.cpp ./src/ImageData.cpp ./src/PathGenerate.cpp)
OBJECTS		= $(SOURCES:.cpp=.o)

EXECUTABLE = pca

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CURDIR)/$< -o $@

clean:
	rm -rf ./src/*.o $(EXECUTABLE)
