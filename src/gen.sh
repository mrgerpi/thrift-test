function fail() {
	echo "Error: "$1	
	exit 1
}

if test -z $1;then
	fail "no service name"
fi

filename="./idl/"$1".thrift"
if ! test -r $filename; then
	fail "file "$filename" not exists"	
fi

echo "thrift compile $filename ..."
mkdir -p thrift_gen/$1
/home/Shit/thrift-test/src/thirdparty/thrift/bin/thrift -r -gen cpp -out thrift_gen/$1	$filename
