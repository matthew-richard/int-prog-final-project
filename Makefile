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

tar:	*
		tar -cvf MatthewRichard_ProjectF.tar benchmark.cpp Bus.cpp Bus.h Car.cpp Car.h design.txt driver.cpp Hybrid.cpp Hybrid.h List.cpp List.h Makefile Menu_helpers.h ML_hash.cpp ML_hash.h MLH_Map.cpp MLH_Map.h MLH_Map_Node.cpp Motorcycle.cpp Motorcycle.h random_op.cpp random_op.h Record.cpp Record.h results.txt Task.cpp Task.h Vehicle.cpp Vehicle.h VehicleServiceCenter.cpp VehicleServiceCenter.h

send: tar
		mailx -a MatthewRichard_ProjectF.tar -b mricha56@jhu.edu -s "ProjectF Submission by Matthew Richard" cs120@cs.jhu.edu

clean:
		rm -f *.o *.gch

%.o:	%.cpp
		$(C++) $(CFLAGS) $*.cpp

%.cpp:	%.h
