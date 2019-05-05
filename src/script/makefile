#serviceName
#interServiceName

desDir=$(shell echo `pwd`"/service_lib/")
srcDir=$(shell echo `pwd`"/thrift_gen/"${serviceName})

INCLUDE= -I thirdparty/thrift/include/ -I ${srcDir} -I thirdparty/simple-log/include/

CFLAGS=-std=c++0x -g -fPIC -shared -Wno-deprecated

LIB=-L./thirdparty/thrift/lib 

VPATH +=. ${srcDir}

Client: ${serviceName}_constants.o ${serviceName}_types.o ${interServiceName}.o ${interServiceName}Client.o
	g++ ${CFLAGS} $^ -o ${desDir}/lib${serviceName}client.so ${LIB}
	rm $^

Server: ${serviceName}_constants.o ${serviceName}_types.o ${interServiceName}.o ${interServiceName}Server.o
	g++ ${CFLAGS} $^ -o ${desDir}/lib${serviceName}server.so ${LIB}
	rm $^

Only_Client: ${interServiceName}Client.o
	g++ ${CFLAGS} $^ -o ${desDir}/lib${serviceName}client.so ${LIB}
	rm $^

Only_Server: ${interServiceName}Server.o
	g++ ${CFLAGS} $^ -o ${desDir}/lib${serviceName}server.so ${LIB}
	rm $^

%.o:%.cpp
	@echo "Compiling $< ..."
	@g++ -c ${INCLUDE} ${CFLAGS} $^ -o ./$@
