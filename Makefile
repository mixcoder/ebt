CXXFLAGS += -std=c++11 -Wall
AR = gcc-ar

.PHONY: all clean check

all: libebt.a

string.o: string.h
json.o: json.h
unit_test.o: unit_test.h
args.o: args.h
sparse_vector.o: sparse_vector.h
math_util.o: math_util.h
hash.cc: hash.h
exception.o: exception.h
timer.o: timer.h

libebt.a: json.o unit_test.o string.o args.o sparse_vector.o math_util.o hash.o exception.o timer.o
	$(AR) rcs $@ $^

clean:
	-rm libebt.a
	-rm *.o
	-$(MAKE) -C test clean

check: libebt.a
	$(MAKE) -C test
