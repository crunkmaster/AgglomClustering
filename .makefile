CC = clang++

full: test cluster
	$(CC) -g -std=c++11 test.o cluster.o -o test

test: cluster.h test.cpp
	$(CC) -g -c -std=c++11 test.cpp

cluster: cluster.cpp cluster.h
	$(CC) -g -c -std=c++11 cluster.cpp

clean:
	rm -f *.o
	rm -f test
