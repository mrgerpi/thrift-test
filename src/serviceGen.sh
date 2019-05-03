#!/bin/sh
idl_path=$1
target_path=$2
cur_dir=`pwd`
thrift=${cur_dir}"/thirdparty/thrift/bin/thrift"
#echo ${thrift}
#echo ${target_path}
#echo ${idl_path}

rm -rf ${target_path}
mkdir -p ${target_path}

${thrift}  -r -gen cpp -out ${target_path} ${idl_path}
echo $?
