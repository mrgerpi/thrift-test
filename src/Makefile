INCLUDE = -I ./	\
		  -I ./util	\
		  -I ./main 	\
		  -I ./thirdparty/simple-log/include/	\
		  -I ./thirdparty/thrift/include/	\
		  -I ./thirdparty/config/include/	\
		  -I ./thirdparty/libevent/include/	\
		  -I ./thrift_gen/thrift_test_kernal \
		  -I ./thrift_server/thrift_test_kernal 

LIB = ./thirdparty/simple-log/lib/libsimplelog.a	\
	  -L./thirdparty/config/lib -lconfig++		\
	  -L./thirdparty/thrift/lib -lthriftnb -lthrift         \
	  -L./thirdparty/libevent/lib -levent		\
	  -lpthread 

FLAGS = -O2  -g -lrt -std=c++11

OBJ_DIR = ./obj_dir

VPATH = ./	\
		./main	\
		./util	\
		./thrift_gen/thrift_test_kernal \
		./thrift_server/thrift_test_kernal \
		${OBJ_DIR}

cpu_num = $(shell echo $$(nproc))

main_obj = main.o instance_mgr_terminal.o
util_obj = didiutils.o

thrift_test_kernal_gen_obj = thrift_test_kernal_constants.o ThriftTestKernalService.o thrift_test_kernal_types.o #ThriftTestKernalService_server.skeleton.o 
thrift_test_kernal_server_obj = ThriftTestKernalServiceServer.o ThriftTestKernalServiceHandler.o

all: thrift-test

thrift-test: ${main_obj} ${util_obj} ${thrift_test_kernal_gen_obj} ${thrift_test_kernal_server_obj}
	g++ ${FLAGS} $(patsubst %.o,$(OBJ_DIR)/%.o,$(^F)) $(LIB) -o ./$@ 

%.o:%.cpp 
	@mkdir -p ${OBJ_DIR}
	@echo "Compiling $< ..."
	@g++ -c ${INCLUDE} ${FLAGS} $< -o ${OBJ_DIR}/$@

clean:
	rm -rf ${OBJ_DIR}
	rm thrift-test
