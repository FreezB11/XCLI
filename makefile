CC = g++
OUT_DIR = ./build/

all:
	${CC} -g -std=c++20 -o ${OUT_DIR}client ./src/_env.cc ./src/xcli_client.cc
	${CC} -g -o ${OUT_DIR}server ./src/_env.cc ./src/xcli_server.cc
test:
	${CC} -o test test.cc -lssl -lcrypto
