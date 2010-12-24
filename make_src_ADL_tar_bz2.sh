#!/bin/bash

# create source archive

rm -f ./AMDOverdriveCtrl_ADL.src.tar.bz2
tar cf ./AMDOverdriveCtrl_ADL.src.tar *.h
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.cpp
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.workspace
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.project
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.mk
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.fbp
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.sh
tar rf ./AMDOverdriveCtrl_ADL.src.tar *.txt
tar rf ./AMDOverdriveCtrl_ADL.src.tar bin2h
tar rf ./AMDOverdriveCtrl_ADL.src.tar Copyright
tar rf ./AMDOverdriveCtrl_ADL.src.tar adl/*
tar rf ./AMDOverdriveCtrl_ADL.src.tar create_deb/*
tar rf ./AMDOverdriveCtrl_ADL.src.tar ADL_SDK/*
bzip2 ./AMDOverdriveCtrl_ADL.src.tar
