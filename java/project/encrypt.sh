#!/bin/bash
#./encrypt.sh -p password -i input -a algorithm

PASSWORD=""
ALGORITHM=""
INPUT=""

helpFun(){
	echo "./encrypt.sh -p password -i input -a algorithm "
}

while getopts "p:i:a:" opt;
do
	case $opt in
		p) PASSWORD=$OPTARG ;;
		i) INPUT=$OPTARG ;;
		a) ALGORITHM=$OPTARG ;;
	esac
done

if [ ! $PASSWORD ]; then
	helpFun
	exit
fi

if [ ! $INPUT ]; then
	helpFun
	exit
fi

if [ ! $ALGORITHM ]; then
	ALGORITHM="PBEWithMD5AndDES"
	echo "algorithm default set to PBEWithMD5AndDES"
fi

#echo $PASSWORD " " $INPUT " " $ALGORITHM

java -cp jasypt-1.9.3.jar org.jasypt.intf.cli.JasyptPBEStringEncryptionCLI  password=$PASSWORD algorithm=$ALGORITHM input=$INPUT

#java -cp lib/jasypt-1.9.2.jar org.jasypt.intf.cli.JasyptPBEStringEncryptionCLI  password=fdfdfd  algorithm=PBEWithMD5AndDES input=fund