IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

all: bellman bfs dfs dijkstra fulkerson mincut prim

%: %.cpp
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~
