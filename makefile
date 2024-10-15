CC = g++
OUT_DIR = build/

all:
	${CC} -o ${OUT_DIR}client _env.cc client.cc
	${CC} -o ${OUT_DIR}server _env.cc server.cc
test:
	${CC} -o test test.cc -lssl -lcrypto