from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TF1,TGraphAsymmErrors,kWhite
from math import atan,sqrt
from array import array
from sys import argv
import sys
#setup
print 'setup'
gROOT.SetBatch()

path_base='/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZprimeFullHadCycle.MC.'
sample_list=['ZP1000W10','ZP1000W100','ZP1250W125','ZP1250W12p5','ZP1500W15','ZP1500W150','ZP2000W20','ZP2000W200','ZP3000W30','ZP3000W300','ZP4000W40','ZP4000W400','ZP500W5','ZP500W50','ZP750W75','ZP750W7p5']
histo_list=['SumOfTopCandidatesPt','LeadingTopCandidatePt']
cut_list=["Trigger1Histos","Trigger2Histos","Trigger3Histos","Trigger4Histos","Trigger5Histos"]
trigger_names=["HLT_HT750_v3","HLT_BTagMu_Jet300_Mu5_v3","HLT_Jet160Eta2p4_Jet120Eta2p4_DiBTagIP3DFastPVLoose_v4","HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05_v1","HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v4"]
base_cut="BaseHistos"
#sample_index=0
#histo_index=0
#cut_index=0
outfile=TFile("triggerout.root","RECREATE")
def getEff(sample_index,histo_index,cut_index):
  sample_file=TFile(path_base+sample_list[sample_index]+'.root')
  #print sample_file
  base_hist=sample_file.Get(base_cut+"/"+histo_list[histo_index])
  trigger_hist=sample_file.Get(cut_list[cut_index]+"/"+histo_list[histo_index])
  eff_histo=trigger_hist.Clone(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index])
  eff_histo.Divide(trigger_hist,base_hist,1,1,'B')
  eff_histo.SetStats(kFALSE)
  eff_histo.SetLineWidth(3)
  eff_histo.SetMaximum(1.01)
  eff_histo.SetMinimum(0.)
  eff_histo.GetYaxis().SetTitle("Trigger rate")
  eff_histo.SetTitle(trigger_names[cut_index])
  c=TCanvas(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]+'_Canvas')
  eff_histo.Draw()
  c.SaveAs("pdf/"+sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]+".pdf")
  outfile.cd()
  c.Write()
  #return eff_histo


for sampleIndex in range(len(sample_list)):
  for cutIndex in range(len(cut_list)):
    for histoIndex in range(len(histo_list)):
      getEff(sampleIndex,histoIndex,cutIndex)
#eff.Write()
outfile.Close()