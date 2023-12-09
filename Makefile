.PHONY: all clean

all: rm

rm: rm.cc
	g++ rm.cc -o rm

clean:
	rm -f rm
