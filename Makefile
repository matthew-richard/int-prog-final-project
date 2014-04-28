C++ = g++
CFLAGS = -c -g

all: try_hash try_random map benchmark vsc

test: ML_hash.o Vehicle.o Car.o Motorcycle.o Bus.o Hybrid.o Task.o Record.o VehicleServiceCenter.o test.o
		$(C++) -o test ML_hash.o Vehicle.o Car.o Motorcycle.o Bus.o Hybrid.o Task.o Record.o VehicleServiceCenter.o test.o

try_hash:	try_hash.o ML_hash.o
		$(C++) -o try_hash try_hash.o ML_hash.o

try_random:	try_random.o random_op.o
		$(C++) -o try_random try_random.o random_op.o

map:	map.o ML_hash.o
		$(C++) -o map map.o ML_hash.o

benchmark:	benchmark.o ML_hash.o random_op.o
		$(C++) -o benchmark benchmark.o ML_hash.o random_op.o

clean:
		rm -f *.o *.gch

%.o:	%.cpp
		$(C++) $(CFLAGS) $*.cpp

%.cpp:	%.h
