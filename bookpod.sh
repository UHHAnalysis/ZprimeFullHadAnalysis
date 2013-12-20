#!/bin/bash
source /afs/naf.desy.de/group/cms/proof/PoD/PoD_env.sh
pod-server start
pod-submit -q proof.q -n $1 -r ge
watch pod-info -n