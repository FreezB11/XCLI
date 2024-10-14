CC = g++

all:
	rm main
	${CC} -o nigga .*cc
test:
	${CC} -o test test.cc -lssl -lcrypto