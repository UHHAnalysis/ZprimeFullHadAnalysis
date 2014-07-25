#!/bin/zsh

crabid=(
"config/Last2DESY_MultiJet1Parked_Run2012D-part1_10Dec2012-v1_ntuplewriter_ttbsm_53_plusprunedcfg_sge_22"
)

iteracount=0

for listname in ${crabid}; do

numberfiles=$(wc -l ${listname} | awk '{print $1}')

echo "There are ${numberfiles} jobs for the id ${listname}"

outputdir="/nfs/dust/cms/user/usaiem/mj/part1sge2/"

if [ -e ${outputdir} ]; then
echo "Output directory ${outputdir} already exists"
else
mkdir ${outputdir}

if [[ $? != 0 ]]; then
echo "Problem mkdir"
exit 1
fi

fi

i=1

while [ $i -le $numberfiles ]; do

filename=$(cut -d'
' -f$i ${listname})

filename=$(echo ${filename} | awk 'BEGIN{FS="pnfs"} {print $2}'| awk 'BEGIN{FS="\""} {print $1}')

filename=$(echo "/pnfs${filename}")

echo "copying gsidcap://dcache-cms-gsidcap.desy.de:22128/${filename} to ${outputdir}"

dccp gsidcap://dcache-cms-gsidcap.desy.de:22128/${filename} ${outputdir}

if [[ $? != 0 ]]; then
echo "Problem copying"
exit 2
fi

let "iteracount=iteracount +1"

let "i=i + 1"
done

done


echo "Total ${iteracount} files"

