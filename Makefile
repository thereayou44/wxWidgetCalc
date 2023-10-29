 all:
		g++ -c calc.cpp `wx-config --cflags` -O2
		g++ -c memory.cpp `wx-config --cflags` -O2
		g++ calc.o memory.o `wx-config --libs` -o calc 
