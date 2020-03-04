bf:	bf.cpp
	g++ -std=c++11 -Wall -O3 bf.cpp -o bf -fopenmp

clean:
	rm bf
