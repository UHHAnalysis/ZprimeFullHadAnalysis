#!/bin/sh
#$ -S /bin/sh
#$ -cwd

export MYNUM=$1

export SCRAM_ARCH=slc6_amd64_gcc472
source /cvmfs/cms.cern.ch/cmsset_default.sh
export TMPDIR=$HOME/.proof/tmp
cd /nfs/dust/cms/user/kripav/CMSSW_6_2_8/src/
eval `scramv1 runtime -sh`
cd /nfs/dust/cms/user/kripav/sframe_new/
source /nfs/dust/cms/user/kripav/sframe_new/fullsetup.sh
#source fullsetup.sh

cd /nfs/dust/cms/user/kripav/sframe_new/ZprimeAnalysis/config
cp ZprimePostSelectionCycle_config_Systematics_PDF.xml temp_${MYNUM}.xml

sed -i "s|MYPDFINDEX|${MYNUM}|g" temp_${MYNUM}.xml

#cd /scratch/hh/dust/naf/cms/user/peiffer/Analysis53X/PostSelectionMuon_PDF
sframe_main temp_${MYNUM}.xml
rm temp_${MYNUM}.xml


