if [$1 -eq ""];then
	echo "Input right file name"
	exit 0
fi

if [ -e $1 ];then
	./cgen/commonapi-generator/commonapi-generator-linux-x86 -sk $1
	./cgen/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86 $1
fi
