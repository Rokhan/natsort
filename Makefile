CXXFLAGS = -Wall -g -Werror -std=c++11

OBJS = src/strnatcmp.o src/natsort.o

.PHONY: clean test

test/natsort: $(OBJS)
	$(CXX) -o $@ $(OBJS)

test: test/natsort
	@bash -c 'cd ./test/ && ./run-tests.bash'

clean:
	rm -f test/natsort $(OBJS)
