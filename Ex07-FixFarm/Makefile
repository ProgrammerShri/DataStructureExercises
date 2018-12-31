source = FixFarm.cpp
outfile = ./a.out

.PHONY: default
default: $(source)
	g++ -O2 $(source) -o $(outfile)

test1:
	@ $(outfile) < test/case_1 > result
	@ diff test/result_1 result
	@ rm result
	@ echo "[1/1] Test case 1 passed"

test: default test1
	@ echo "All cases passed!"