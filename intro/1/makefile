CFLAGS = -Wall -g
ALL = daytimetcpcli daytimetcpsrv client server byteorder

all: ${ALL}

daytimetcpcli.o: daytimetcpcli.cpp
	g++ ${CFLAGS} -c -o daytimetcpcli.o daytimetcpcli.cpp -I ../../lib
daytimetcpcli: daytimetcpcli.o
	g++ ${CFLAGS} -o daytimetcpcli daytimetcpcli.o ../../libunp.a -I ../../lib

daytimetcpsrv.o: daytimetcpsrv.cpp
	g++ ${CFLAGS} -c -o daytimetcpsrv.o daytimetcpsrv.cpp -I ../../lib
daytimetcpsrv: daytimetcpsrv.o
	g++ ${CFLAGS} -o daytimetcpsrv daytimetcpsrv.o ../../libunp.a -I ../../lib

client.o: client.cpp
	g++ ${CFLAGS} -c -o client.o client.cpp
client: client.o
	g++ ${CFLAGS} -o client client.o

server.o: server.cpp
	g++ ${CFLAGS} -c -o server.o server.cpp
server: server.o
	g++ ${CFLAGS} -o server server.o

byteorder.o: byteorder.cpp
	g++ ${CFLAGS} -c -o byteorder.o byteorder.cpp  -I ../../lib
byteorder: byteorder.o
	g++ ${CFLAGS} -o byteorder byteorder.o -I ../../lib

clean:
	rm *.o ${ALL}
