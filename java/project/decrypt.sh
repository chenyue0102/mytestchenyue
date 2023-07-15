#!/bin/bash
#./decrypt.sh -p password -i input -a algorithm

helpFun(){
	echo "./decrypt.sh -p password -i input -a algorithm "
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

java -cp jasypt-1.9.3.jar org.jasypt.intf.cli.JasyptPBEStringDecryptionCLI password=$PASSWORD algorithm=$ALGORITHM input=$INPUT