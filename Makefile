include make.inc

all: lu_example.out

lu_example.out: lu_example.cpp testutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(TLAPACKDIR)/include

lu_example_mpreal.out: lu_example_mpreal.cpp testutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(TLAPACKDIR)/include -lmpfr -lgmp

testutils.o: $(TLAPACKDIR)/test/src/testutils.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ -I$(TLAPACKDIR)/include -I$(TLAPACKDIR)/test/include