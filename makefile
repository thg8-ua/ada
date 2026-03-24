# Tamer Hawatmeh Goussous, 54795313K

# Flags de compilación (exactamente como los especificaste)
OPTS = -Wall -Wextra -O3 -std=c++0x

# Regla principal: genera 'maze' a partir de maze.cc
maze: maze.cc
	g++ $(OPTS) -o maze maze.cc
