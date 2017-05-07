SOURCE=testDriverFactory.cpp
PROG=testDriverFactory
INCLUDES=../../googletest/googletest/include
LIBS=-L../../googletest/googletest/make -lgtest
CXX=g++
CXXFLAGS=-std=c++14 -pthread -g

all: $(PROG)

$(PROG): $(SOURCE)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(SOURCE) -o$(PROG) $(LIBS)

clean:
	rm -f $(PROG)

