dir_name=`pwd`
LIB_PATH=${dir_name}/thirdparty/simple-log/lib:${dir_name}/thirdparty/libevent/lib

#set LD_LIBARAY_PATH
if [ -z "${LD_LIBRARY_PATH}" ]; then
	export LD_LIBRARY_PATH="${LIB_PATH}"
else
	export LD_LIBRARY_PATH="${LIB_PATH}:${LD_LIBRARY_PATH}"
fi

if [ -z $1 ]; then
	./client 1		#GetServiceList
	./client 2		#AddService
	./client 3		#FillData
	./client 4		#RequestTrigger
else
	./client $1
fi


