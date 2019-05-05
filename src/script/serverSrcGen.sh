#!/bin/sh
# $1: idl file path, $2: serviceName

#copy handler ifle 
interServiceName=`cat $1 | grep service | awk -F " " '{print $2}' | tr -d '{'`
serviceName=$2
skeleton_file=`pwd`"/thrift_gen/"${serviceName}"/"${interServiceName}"_server.skeleton.cpp"
server_file=`pwd`"/thrift_gen/"${serviceName}"/"${interServiceName}"Server.cpp"
cp ${skeleton_file} ${server_file}

# delete main function
mainBeginLineNum=`cat ${server_file} | grep -n 'int main' | awk -F ':' '{print $1}'`
sed -i "${mainBeginLineNum},$ d" ${server_file}		# -i: edit file directly

#replace snippet/server_response.cpp with real Class, method, response path
#put the code snippet to every method of handler
handler_class_name=${interServiceName}"Handler"
funLineArray=`cat ${server_file} | grep -n void | grep _return | grep const | awk -F ':' '{print $1}'`
lineArray=(${funLineArray})
for ((i=${#lineArray[@]}-1;i>=0;i--))
do
	num=${lineArray[i]}
	methodName=`sed -n ''${num}'p' ${server_file}|awk -F ' ' '{print $2}' | awk -F '(' '{print $1}'`		# -n: print the line that script process
	dataPrefix=`pwd`"/data/"
	dataPath=${dataPrefix}${serviceName}"/"${methodName}"/rsp.json"
	sed -e "s/CLASS/${handler_class_name}/g" -e "s/METHOD/${methodName}/g" -e "s#RESPONSE_PATH#${dataPath}#g" snippet/server_response.cpp > ${num}_response
	sed -i "${num} r ${num}_response" ${server_file}
	rm ${num}_response 
done

#insert server head file
sed -i "3 r snippet/server_header.cpp" ${server_file}

#replace snippet/start_server_entry.cpp with real class servicename , processor
#insert ${service_name}_start_server functiono
processor=${interServiceName}"Processor"
echo ${processor}
sed -e "s/CLASS/${handler_class_name}/g" -e "s/SERVICE_NAME/${serviceName}/g" -e "s/PROCESSOR/${processor}/g" snippet/start_server_entry.cpp > start_server
sed -i "$ r start_server" ${server_file}
rm start_server
echo $?
