CXXFLAGS = -Wall -g -Werror -std=c++11 -I.

OBJS = src/strnatcmp.o src/natsort.o

.PHONY: clean test

test/natsort: $(OBJS)
	$(CXX) -o $@ $(OBJS) -lboost_program_options

test: test/natsort
	@bash -c 'cd ./test/ && ./run-tests.bash ./natsort'

test-vs:
	@bash -c 'cd ./test/ && ./run-tests.bash ../Debug/NatsortExe.exe'

clean:
	rm -f test/natsort $(OBJS)
