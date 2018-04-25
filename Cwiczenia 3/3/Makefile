infile = targa.cpp main.cpp
outfile = main.out
command = g++ $(infile)
flags = -o $(outfile) -Wall -lGL -lglut -lGLU
all:
	$(command) $(flags)
debug:
	$(command) $(flags) -g
run: all
	./$(outfile)
