infile = targa.cpp main.cpp
outfile = main.out
command = $(CXX) $(infile) $(CXXFLAGS)

override CXXFLAGS += -o $(outfile) -Wall -Wno-write-strings -lGL -lglut -lGLU

all: $(outfile)

debug: CXXFLAGS += -g
debug: all

$(outfile): $(infile)
	$(command)
	
run: all
	./$(outfile)
