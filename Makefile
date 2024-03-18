CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lcpprest -lboost_system -lssl -lcrypto
SRCDIR = src
BUILDDIR = build

all: productsapp runUnitTest

productsapp: $(SRCDIR)/main.cpp $(SRCDIR)/functions.cpp
    $(CXX) $(CXXFLAGS) -o $(BUILDDIR)/productsapp $(SRCDIR)/main.cpp $(SRCDIR)/functions.cpp $(LIBS)

runUnitTest: $(SRCDIR)/unitTest.cpp $(SRCDIR)/functions.cpp
    $(CXX) $(CXXFLAGS) -o $(BUILDDIR)/runUnitTest $(SRCDIR)/unitTest.cpp $(SRCDIR)/functions.cpp -lgtest -lgtest_main -lpthread $(LIBS)

clean:
    rm -f $(BUILDDIR)/productsapp $(BUILDDIR)/runUnitTest
