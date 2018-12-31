source = SortComparison.cpp
outfile = ./a.out

.PHONY: default
default: vector

.PHONY: debug
debug: vector_debug

vector: $(source)
	g++ -O2 $(source) -o $(outfile)

deque: $(source)
	g++ -DSORT_DEQUE -O2 $(source) -o $(outfile)

vector_debug: $(source)
	g++ -Og -DDEBUG $(source) -o $(outfile)

deque_debug: $(source)
	g++ -Og -DSORT_DEQUE -DDEBUG $(source) -o $(outfile)