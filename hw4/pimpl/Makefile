SOURCE=pimpl.cpp
PROG=pimpl
INCLUDES=../../googletest/googletest/include
LIBS=-L../../googletest/googletest/make -lgtest
CXX=g++
CXXFLAGS=-std=c++11 -pthread

all: $(PROG)

$(PROG): $(SOURCE)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(SOURCE) -o$(PROG) $(LIBS)

clean:
	rm -f $(PROG)

