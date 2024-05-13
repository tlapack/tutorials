include make.inc

all: lu_example.out lu_example_mpreal.out gemm_recursive.out

lu_example.out: lu_example.cpp testutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(TLAPACKDIR)/include

lu_example_mpreal.out: lu_example_mpreal.cpp testutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(TLAPACKDIR)/include -lmpfr -lgmp

gemm_recursive.out: gemm_recursive.cpp testutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(TLAPACKDIR)/include

testutils.o: $(TLAPACKDIR)/test/src/testutils.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ -I$(TLAPACKDIR)/include -I$(TLAPACKDIR)/test/include