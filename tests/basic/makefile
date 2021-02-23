ICONF := -I. -I../../include
LCONF = -L../../lib -lhw2
run: main
	./program

test: main
	./program

main: setup
	mpicxx ${ICONF} main.cc -o program ${LCONF}

setup:
	mkdir -p output

clean:
	rm -f ./program
	rm -rf ./output