#!/bin/bash
#cd /afs/desy.de/user/s/stadie/xxl/PoD
#source PoD_env.sh 
pod-server start
pod-submit -n $1 -r ge
watch pod-info -n
