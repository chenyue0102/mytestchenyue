#!/bin/bash
openssl genrsa -out private_key.pem 2048
openssl pkcs8 -topk8 -inform PEM -outform DER -in private_key.pem -out private_key.der -nocrypt
openssl base64 -in private_key.der -out base64.txt
rm private_key.der
rm private_key.pem
