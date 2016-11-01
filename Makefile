INC=-I ./include
TESTINC= -isystem ./googletest/include -I./googletest -I./
GCC=g++ -Wall $(INC)

SRCFILES=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,objs/%.o, $(SRCFILES))
MAINSRC=$(wildcard main/*.cpp)
MAINOBJS=$(patsubst main/%.cpp,objs/%.o, $(MAINSRC))
MAINS=$(patsubst main/%.cpp,output/%, $(MAINSRC))
TESTSRC=$(wildcard test/*.cpp)
TESTOBJS=$(patsubst test/%.cpp,objs/%.o, $(TESTSRC))
TESTS=$(patsubst test/%.cpp,test_output/%, $(TESTSRC))
RUN_TESTS=$(wildcard test_output/*)

all: $(MAINS)

output/%: $(OBJS) objs/%.o
	$(GCC) $^ -o $@

objs/%.o: src/%.cpp
	$(GCC) -c $^ -o $@

objs/%.o: main/%.cpp
	$(GCC) -c $^ -o $@

test: $(TESTS)

run_test: $(RUN_TESTS)
	$(foreach test,$^, ./$(test);)

test_output/%: $(OBJS) test/gtest_main.a objs/%.o
	$(GCC) -lpthread $^ -o $@

objs/%.o: test/%.cpp
	$(GCC) $(TESTINC) -c $^ -o $@

test/gtest_main.a: googletest/gtest-all.o googletest/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

googletest/gtest-all.o: ./googletest/src/gtest-all.cc
	$(GCC) $(TESTINC) -c $^ -o $@

googletest/gtest_main.o: ./googletest/src/gtest_main.cc
	$(GCC) $(TESTINC) -c $^ -o $@

clean:
	rm test_output/* output/* 2>/dev/null
