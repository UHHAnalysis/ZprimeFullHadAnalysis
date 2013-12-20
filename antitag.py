from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TF1,TGraphAsymmErrors,kWhite
from math import atan,sqrt
from array import array
from sys import argv
import sys
#setup
print 'setup'
gROOT.SetBatch()

path_base='/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZAnalysisCycle.'
sample_list=['MC.QCD','MC.TTbarHad','DATA.DATA']
histo_name='Nevts'
den_folder="antitag_den"
num_folder="antitag_num"
histo_name="TopCandidate2Pt"
postfix=''
outfile=TFile("antitag"+postfix+".root","RECREATE")

def getMistag(sample):
  sample_file=TFile(path_base+sample+'.root')
  num_histo=sample_file.Get(num_folder+"/"+histo_name)
  den_histo=sample_file.Get(den_folder+"/"+histo_name)
  mistag_histo=num_histo.Clone('Mistag_'+sample.split('.')[1])
  mistag_histo.Divide(num_histo,den_histo,1,1,'B')
  outfile.cd()
  num_histo.Write('Numerator_'+sample.split('.')[1])
  den_histo.Write('Denominator_'+sample.split('.')[1])
  mistag_histo.Write()
  return mistag_histo

for i in sample_list:
  getMistag(i)

sample_file1=TFile(path_base+sample_list[2]+'.root')
num_histo1=sample_file1.Get(num_folder+"/"+histo_name)
den_histo1=sample_file1.Get(den_folder+"/"+histo_name)

sample_file2=TFile(path_base+sample_list[0]+'.root')
num_histo2=sample_file2.Get(num_folder+"/"+histo_name)
den_histo2=sample_file2.Get(den_folder+"/"+histo_name)

dmc_num=num_histo1.Clone('Numerator_DataOverQCD')
dmc_num.Divide(num_histo2)
dmc_den=den_histo1.Clone('Denominator_DataOverQCD')
dmc_den.Divide(den_histo2)

outfile.cd()
dmc_num.Write()
dmc_den.Write()

outfile.Close()