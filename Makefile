main:	funkc.o
	g++ -o main masyva.cpp funkc.o
circle:
	g++ -c -03 funkc.cpp
clean:
	rm *.o main kieciukai.txt nuskriaustukai.txt 10.txt 100.txt 1000.txt 10000.txt 100000.txt
