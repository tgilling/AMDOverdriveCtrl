#!/bin/bash

# create source archive

rm -f ./AMDOverdriveCtrl.src.tar.bz2
tar cf ./AMDOverdriveCtrl.src.tar *.h
tar rf ./AMDOverdriveCtrl.src.tar *.cpp
tar rf ./AMDOverdriveCtrl.src.tar *.workspace
tar rf ./AMDOverdriveCtrl.src.tar *.project
tar rf ./AMDOverdriveCtrl.src.tar *.mk
tar rf ./AMDOverdriveCtrl.src.tar *.fbp
tar rf ./AMDOverdriveCtrl.src.tar *.sh
tar rf ./AMDOverdriveCtrl.src.tar *.txt
tar rf ./AMDOverdriveCtrl.src.tar bin2h
tar rf ./AMDOverdriveCtrl.src.tar Copyright
tar rf ./AMDOverdriveCtrl.src.tar adl/*
tar rf ./AMDOverdriveCtrl.src.tar create_deb/*
bzip2 ./AMDOverdriveCtrl.src.tar
