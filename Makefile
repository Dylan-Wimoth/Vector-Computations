CXX = g++
CXXFLAGS = -Wall -g

main: Vector.o Runner.o main.cpp
	$(CXX) $(CXXFLAGS) Vector.o Runner.o main.cpp -o main

Runner.o: Runner.cpp Vector.cpp
	$(CXX) $(CXXFLAGS) -c Runner.cpp

Vector.o: Vector.cpp
	$(CXX) $(CXXFLAGS) -c Vector.cpp

run1:
	./main data1.txt

run2:
	./main data2.txt

run3:
	./main data3.txt

run4:
	./main data4.txt

val1:
	valgrind ./main data1.txt

val2:
	valgrind ./main data2.txt

val3:
	valgrind ./main data3.txt

val4:
	valgrind ./main data4.txt

clean:
	rm *~
	rm *.o

debug1:
	gdb gdbarg1 --args ./main data1.txt
