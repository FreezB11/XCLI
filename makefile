CC = g++
OUT_DIR = build/

all:
	${CC} -o ${OUT_DIR}client _env.cc xcli_client.cc
	${CC} -o ${OUT_DIR}server _env.cc xcli_server.cc
test:
	${CC} -o test test.cc -lssl -lcrypto