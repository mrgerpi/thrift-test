INCLUDE = -I ./	\
		  -I ./main 	\
		  -I ./util\
		  -I ./thirdparty/simple-log/include/	\
		  -I ./thirdparty/thrift/include/	\
		  -I ./thrift_gen/thrift_test_kernal \

LIB = ./thirdparty/simple-log/lib/libsimplelog.a	\
	  -L./thirdparty/thrift/lib -lthriftnb -lthrift         \
	  -lpthread 

FLAGS = -O2  -g -lrt -std=c++11

OBJ_DIR = ./obj_dir

VPATH = ./	\
		./main	\
		./util \
		./thrift_gen/thrift_test_kernal \
		./thrift_server/thrift_test_kernal \
		${OBJ_DIR}

main_obj = main.o
util_obj = didiutils.o

thrift_test_kernal_gen_obj = thrift_test_kernal_constants.o ThriftTestKernalService.o thrift_test_kernal_types.o #ThriftTestKernalService_server.skeleton.o 

all: thrift-test-client

thrift-test-client: ${main_obj} ${util_obj} ${thrift_test_kernal_gen_obj} 
	g++ ${FLAGS} $(patsubst %.o,$(OBJ_DIR)/%.o,$(^F)) $(LIB) -o ./$@ 

%.o:%.cpp 
	@mkdir -p ${OBJ_DIR}
	@echo "Compiling $< ..."
	@g++ -c ${INCLUDE} ${FLAGS} $< -o ${OBJ_DIR}/$@

clean:
	rm -rf ${OBJ_DIR}
	rm thrift-test
