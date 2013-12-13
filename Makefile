CXXFLAGS = -std=c++0x -g -save-temps
CC = g++
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
HEADERS = $(wildcard *.hpp)

main: $(OBJS)

-include .depend

.depend: $(SRCS) $(HEADERS)
	$(CC) $(CXXFLAGS) -MM $(SRCS) > .depend

test:
	./main < numbers 2

docs:
	doxygen

clean:
	-rm -f *.ii
	-rm -f *.i
	-rm -f *.s
	-rm -f *.o
	-rm -f *.h.gch
	-rm -f *#
	-rm -f *~
	-rm -rf docs
