CC := gcc
CFLAGS := -Wall -Wextra -ggdb

all: test_hash.elf

test_hash.elf: test_hash.c
	$(CC) $(CFLAGS) -o $@ $^

callgrind.out: test_hash.elf
	valgrind --tool=callgrind --callgrind-out-file=$@ ./$^

out.dot: callgrind.out
	gprof2dot --format=callgrind --output=$@ $^

graph.png: out.dot
	dot -Tpng $^ -o $@

.PHONY: clean all
clean:
	-rm test_hash.elf callgrind.out out.dot graph.png
