include make.inc

all: lu_example.out

lu_example.out: lu_example.cpp testutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(TLAPACKDIR)/include

testutils.o: $(TLAPACKDIR)/test/src/testutils.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ -I$(TLAPACKDIR)/include -I$(TLAPACKDIR)/test/include