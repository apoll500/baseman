#!/bin/bash

# param 0:
# param 1: output path
# param 2: package name

cd $1
tar -cavf $2.tar.gz $2/
rm -R $2/
rm $2.tar.gz.sig
gpg --sign -b $2.tar.gz
