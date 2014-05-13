#!/bin/sh

for ((II=$1;II<=$2;II+=1))
do
  
  export MYNUM=${II}

  qsub -l h_vmem=4G -l h_rt=02:59:59 -l arch=amd64 -l distro=sld6 -N Run_${MYNUM} run.sh ${MYNUM} 

done

