source = Maze.cpp
outfile = ./a.out

.PHONY: default
default: $(source)
	g++ -O2 $(source) -o $(outfile)

test1:
	@ $(outfile) < test/case_1 > result
	@ diff test/result_1 result
	@ rm result
	@ echo "[1/4] Test case 1 passed"

test2:
	@ $(outfile) < test/case_2 > result
	@ diff test/result_2 result
	@ rm result
	@ echo "[2/4] Test case 2 passed"

test3:
	@ $(outfile) < test/case_3 > result
	@ diff test/result_3 result
	@ rm result
	@ echo "[3/4] Test case 3 passed"

test4:
	@ $(outfile) < test/case_4 > result
	@ diff test/result_4 result
	@ rm result
	@ echo "[4/4] Test case 4 passed"

test: test1 test2 test3 test4
	@ echo "All cases passed!"