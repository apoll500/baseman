#!/bin/bash

# param 0:
# param 1: output path
# param 2: package name

cd $1
wget https://www.andreaspollhammer.com/downloads/packages/$2.tar.gz.sig
wget https://www.andreaspollhammer.com/downloads/packages/$2.tar.gz
