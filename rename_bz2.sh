#!/bin/bash

# create source archive

ver=`cat ./src/Revision.h | grep VERSION | tr -d " A-Za-z;="`
rev=`cat ./src/Revision.h | grep REVISION | tr -d " A-Za-z;="`
build=`cat ./src/Revision.h | grep BUILD | tr -d " A-Za-z;="`

mv $1.tar.bz2 $2.$ver.$rev.$build.tar.bz2 
echo ...
echo $2.$ver.$rev.$build.tar.bz2  created.
echo ...


