CFLAGS = -Wall -g -Werror

OBJS = src/strnatcmp.o src/natsort.o

.PHONY: clean test

test/natsort: $(OBJS)
	$(CC) -o $@ $(OBJS)

test: test/natsort
	@bash -c 'cd ./test/ && ./run-tests.bash'

clean:
	rm test/natsort $(OBJS)
