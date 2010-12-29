#!/bin/bash

# create source archive

ver=`cat Revision.h | grep VERSION | tr -d " A-Za-z;="`
rev=`cat Revision.h | grep REVISION | tr -d " A-Za-z;="`
build=`cat Revision.h | grep BUILD | tr -d " A-Za-z;="`

rm -f ./AMDOverdriveCtrl_ADL_$ver.$rev.$build.src.tar.bz2
rm -rf ./AMDOverdriveCtrl.src
mkdir ./AMDOverdriveCtrl.src
mkdir ./AMDOverdriveCtrl.src/adl
mkdir ./AMDOverdriveCtrl.src/create_deb
mkdir ./AMDOverdriveCtrl.src/ADL_SDK

cp makefile ./AMDOverdriveCtrl.src
cp *.h ./AMDOverdriveCtrl.src
cp *.cpp ./AMDOverdriveCtrl.src
cp *.workspace ./AMDOverdriveCtrl.src
cp *.project ./AMDOverdriveCtrl.src
cp *.mk ./AMDOverdriveCtrl.src
cp *.fbp ./AMDOverdriveCtrl.src
cp *.sh ./AMDOverdriveCtrl.src
cp *.txt ./AMDOverdriveCtrl.src
cp bin2h ./AMDOverdriveCtrl.src
cp Copyright ./AMDOverdriveCtrl.src
cp -r adl/* ./AMDOverdriveCtrl.src/adl
cp -r create_deb/* ./AMDOverdriveCtrl.src/create_deb
cp -r ADL_SDK/* ./AMDOverdriveCtrl.src/ADL_SDK

tar cfj ./AMDOverdriveCtrl_ADL.$ver.$rev.$build.src.tar.bz2 ./AMDOverdriveCtrl.src/*

rm -rf ./AMDOverdriveCtrl.src


