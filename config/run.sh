#!/bin/sh
#$ -S /bin/sh
#$ -cwd

export MYNUM=$1

# export SCRAM_ARCH=slc6_amd64_gcc472
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# export TMPDIR=$HOME/.proof/tmp
# cd /nfs/dust/cms/user/kripav/CMSSW_6_2_8/src/
# eval `scramv1 runtime -sh`
# cd /nfs/dust/cms/user/kripav/sframe_new/
# source /nfs/dust/cms/user/kripav/sframe_new/fullsetup.sh
# #source fullsetup.sh



export SCRAM_ARCH=slc6_amd64_gcc472
export TMPDIR=$HOME/.proof/tmp
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/desy.de/user/u/usaiem/xxl-af-cms/CMSSW_6_2_5/src
eval `scramv1 runtime -sh`
cd /afs/desy.de/user/u/usaiem/code/
source /afs/desy.de/user/u/usaiem/code/fullsetup.sh

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/nfs/dust/cms/user/marchesi/LHAPDF/install/lib/

# export LHAPATH=/nfs/dust/cms/user/marchesi/LHAPDF/install/share/lhapdf/PDFsets/
export LHAPATH=/nfs/dust/cms/user/mameyer/lhapdf/share/lhapdf/PDFsets/

cd /afs/desy.de/user/u/usaiem/xxl-af-cms/PoD
source /afs/desy.de/user/u/usaiem/xxl-af-cms/PoD/PoD_env.sh 
cd -
cd ZprimeFullHadAnalysis/
cd config
cp sys_pdftop_config.xml temp_${MYNUM}.xml
sed -i "s|PDFINDEX|${MYNUM}|g" temp_${MYNUM}.xml
cat temp_${MYNUM}.xml
sframe_main temp_${MYNUM}.xml
rm temp_${MYNUM}.xml


# cd /nfs/dust/cms/user/kripav/sframe_new/ZprimeAnalysis/config
# cp ZprimePostSelectionCycle_config_Systematics_PDF.xml temp_${MYNUM}.xml
# 
# sed -i "s|MYPDFINDEX|${MYNUM}|g" temp_${MYNUM}.xml
# 
# #cd /scratch/hh/dust/naf/cms/user/peiffer/Analysis53X/PostSelectionMuon_PDF
# sframe_main temp_${MYNUM}.xml
# rm temp_${MYNUM}.xml


