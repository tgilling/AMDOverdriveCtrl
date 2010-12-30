#!/bin/bash

ver=`cat ../src/Revision.h | grep VERSION | tr -d " A-Za-z;="`
rev=`cat ../src/Revision.h | grep REVISION | tr -d " A-Za-z;="`
build=`cat ../src/Revision.h | grep BUILD | tr -d " A-Za-z;="`

echo "AMDOverdriveCtrl V"$ver"."$rev"."$build
