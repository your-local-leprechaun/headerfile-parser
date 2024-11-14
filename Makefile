mainObject:
	g++ -o main headerfile-parser.cpp

main: mainObject
	./main

clean:
	rm main