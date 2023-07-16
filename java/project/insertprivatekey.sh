#!/bin/bash
#./insertprivatekey.sh -u user -s state -t enable_time -e exptime -f filename

helpFun(){
	echo "./insertprivatekey.sh -u user -s state -t enable_time -e exptime -f filename"
}

USERNAME=""
STATE=""
ENABLE_TIME=""
EXPTIME=""
FILENAME=""

while getopts "u:s:t:e:f:" opt;
do
	case $opt in
		u) USERNAME=$OPTARG ;;
		s) STATE=$OPTARG ;;
		t) ENABLE_TIME=$OPTARG ;;
		e) EXPTIME=$OPTARG ;;
		f) FILENAME=$OPTARG ;;
	esac
done

if [ ! $USERNAME ]; then
	helpFun
	exit
fi

if [ ! $STATE ]; then
	helpFun
	exit
fi

if [ ! $ENABLE_TIME ]; then
	helpFun
	exit
fi

if [ ! $EXPTIME ]; then
	helpFun
	exit
fi

if [ ! $FILENAME ]; then
	FILENAME="base64.txt"
	echo "filename default set to base64.txt"
fi


PRIVATE_KEY_TEXT=`cat $FILENAME`
SQL="insert into observe.private_key(private_key,state,enable_time,expiration) values('$PRIVATE_KEY_TEXT',$STATE,'$ENABLE_TIME','$EXPTIME')"
echo $SQL
CNT=$(mysql -u $USERNAME -p -s -e "${SQL}")
echo "CNT ${CNT}"
#debian-sys-maint
#3CPgaBpsl7HRf7H0
