infile = main.cpp
outfile = main.out
command = $(CXX) $(infile) $(CXXFLAGS)

CXXFLAGS = -o $(outfile) -Wall -lGL -lglut -lGLU 

all: $(outfile)

debug: CXXFLAGS += -g
debug: all

$(outfile): $(infile)
	$(command)
	
run: all
	./$(outfile)
