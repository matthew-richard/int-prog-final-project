C++ = g++
CFLAGS = -c -g

all: benchmark vehicle

vehicle: ML_hash.o Vehicle.o Car.o Motorcycle.o Bus.o Hybrid.o Task.o Record.o VehicleServiceCenter.o driver.o
		$(C++) -o vehicle ML_hash.o Vehicle.o Car.o Motorcycle.o Bus.o Hybrid.o Task.o Record.o VehicleServiceCenter.o driver.o

benchmark:	benchmark.o ML_hash.o random_op.o
		$(C++) -o benchmark benchmark.o ML_hash.o random_op.o

try_hash:	try_hash.o ML_hash.o
		$(C++) -o try_hash try_hash.o ML_hash.o

try_random:	try_random.o random_op.o
		$(C++) -o try_random try_random.o random_op.o

map:	map.o ML_hash.o
		$(C++) -o map map.o ML_hash.o

clean:
		rm -f *.o *.gch

%.o:	%.cpp
		$(C++) $(CFLAGS) $*.cpp

%.cpp:	%.h
