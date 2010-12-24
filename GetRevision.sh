#!/bin/bash

ver=`cat Revision.h | grep VERSION | tr -d " A-Za-z;="`
rev=`cat Revision.h | grep REVISION | tr -d " A-Za-z;="`
build=`cat Revision.h | grep BUILD | tr -d " A-Za-z;="`

echo "AMDOverdriveCtrl V"$ver"."$rev"."$build
