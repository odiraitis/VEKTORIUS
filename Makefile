main:	funkc.o
	g++ -o main std_vektorius.cpp funkc.o
circle:
	g++ -c -03 funkc.cpp
clean:
	rm *.o main kieciukai.txt nuskriaustukai.txt
