#!/bin/bash

# create source archive

ver=`cat ../src/Revision.h | grep VERSION | tr -d " A-Za-z;="`
rev=`cat ../src/Revision.h | grep REVISION | tr -d " A-Za-z;="`
build=`cat ../src/Revision.h | grep BUILD | tr -d " A-Za-z;="`

rm -f ./AMDOverdriveCtrl_$ver.$rev.$build.src.tar.bz2
rm -rf ./AMDOverdriveCtrl.src
mkdir ./AMDOverdriveCtrl.src
mkdir ./AMDOverdriveCtrl.src/src
mkdir ./AMDOverdriveCtrl.src/create_deb
mkdir ./AMDOverdriveCtrl.src/documentation
mkdir ./AMDOverdriveCtrl.src/screenshots
mkdir ./AMDOverdriveCtrl.src/scripts
mkdir ./AMDOverdriveCtrl.src/ADL_SDK

cp ../makefile ./AMDOverdriveCtrl.src
cp ../configure ./AMDOverdriveCtrl.src
cp ../*.workspace ./AMDOverdriveCtrl.src
cp ../*.project ./AMDOverdriveCtrl.src
cp ../*.txt ./AMDOverdriveCtrl.src
cp ../bin2h ./AMDOverdriveCtrl.src
cp -r ../src/* ./AMDOverdriveCtrl.src/src
cp -r ../create_deb/* ./AMDOverdriveCtrl.src/create_deb
cp -r ../documentation/* ./AMDOverdriveCtrl.src/documentation
cp -r ../screenshots/* ./AMDOverdriveCtrl.src/screenshots
cp -r ../ADL_SDK/* ./AMDOverdriveCtrl.src/ADL_SDK
cp -r ./*.sh ./AMDOverdriveCtrl.src/scripts

tar cfj ./AMDOverdriveCtrl_ADL.$ver.$rev.$build.src.tar.bz2 ./AMDOverdriveCtrl.src/*

rm -rf ./AMDOverdriveCtrl.src

