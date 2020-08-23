IDIR =../include
CC=g++

all: bellman bfs dfs dijkstra fulkerson mincut prim

%: %.cpp
	$(CC) -o $@ $^ 

clean:
	rm -f *.o *~

#bellman: bellman.cpp
#	g++ bellman.cpp -o bellman
