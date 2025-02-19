CC = g++
OUT_DIR = ./build/

all:
	${CC} -g -std=c++20 -o ${OUT_DIR}client ./src/_env.cc ./src/xrsa.cc ./src/xcli_client.cc -lssl -lcrypto -Wdeprecated-declarations
	${CC} -g -std=c++20 -o ${OUT_DIR}server ./src/_env.cc ./src/xrsa.cc ./src/xcli_server.cc -lssl -lcrypto -Wdeprecated-declarations

rsa:
	${CC} -o rsa rsa.test.cc -lssl -lcrypto -Wdeprecated-declarations