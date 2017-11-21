SOURCE=tuple_find.cpp
PROG=tuple_find
INCLUDES=../../../googletest/googletest/include
LIBS=-L../../../googletest/googletest/make -lgtest
CXX=g++
CXXFLAGS=-std=c++17 -pthread -g

all: $(PROG)

$(PROG): $(SOURCE)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(SOURCE) -o$(PROG) $(LIBS)

clean:
	rm -f $(PROG)

run:
	./$(PROG)

mc:
	valgrind --leak-check=full ./$(PROG)

memchk:
	$(mc)

