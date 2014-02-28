from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TF1,TGraphAsymmErrors,kWhite
from math import atan,sqrt
from array import array
from sys import argv
import sys
#setup
print 'setup'
gROOT.SetBatch()

path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/ZprimeFullHadCycle.MC.'
sample_list=['ZP500W5','ZP750W7p5','ZP1000W10','ZP1250W12p5','ZP1500W15','ZP2000W20']
#sample_list=['ZP2000W20']
colors=[kRed,kBlue,kGreen,kBlack,kOrange,kGray]
histo_list=['SumOfTopCandidatesPt','LeadingTopCandidatePt','SubLeadingTopCandidatePt','HT50']
cut_list=["Trigger1Histos","Trigger2Histos","Trigger3Histos","Trigger4Histos","Trigger5Histos"]
#trigger_names=["HLT_SixJet50","HLT_QuadJet50","HLT_QuadJet70","HLT_QuadJet80","HLT_QuadJet90"]
trigger_names=["HLT_HT750","HLT_QuadJet50","HLT_HT750||HLT_QuadJet50","a","a"]
  #["HLT_DiJet80_DiJet60_DiJet20","HLT_QuadJet90","HLT_SixJet50","HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05d03","HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v4"]
#cut_list#["HLT_HT750_v3","HLT_BTagMu_Jet300_Mu5_v3","HLT_Jet160Eta2p4_Jet120Eta2p4_DiBTagIP3DFastPVLoose_v4","HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05_v1","HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v4"]
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
def getEff2(histo_index,cut_index):
  c=TCanvas(cut_list[cut_index]+'_'+histo_list[histo_index]+'_Canvas')
  legend=TLegend(0.8,0.2,0.999,0.93)
  legend.SetFillColor(kWhite)
  eff_histos=[]
  sample_files=[]
  for sample_index in range(len(sample_list)):
    sample_files.append(TFile(path_base+sample_list[sample_index]+'.root'))
    #print sample_file
    base_hist=sample_files[-1].Get(base_cut+"/"+histo_list[histo_index])
    trigger_hist=sample_files[-1].Get(cut_list[cut_index]+"/"+histo_list[histo_index])
    #eff_histos.append(eff_histo)
    eff_histos.append(trigger_hist.Clone(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]))
    eff_histos[-1].Divide(trigger_hist,base_hist,1,1,'B')
    eff_histos[-1].SetStats(kFALSE)
    eff_histos[-1].SetLineWidth(3)
    eff_histos[-1].SetLineColor(colors[sample_index])
    eff_histos[-1].SetMaximum(1.01)
    eff_histos[-1].SetMinimum(0.)
    eff_histos[-1].GetYaxis().SetTitle("Trigger rate")
    eff_histos[-1].SetTitle(trigger_names[cut_index])
    legend.AddEntry(eff_histos[-1],sample_list[sample_index],'l')
    if len(eff_histos)==1:
      eff_histos[-1].Draw()
    else:
      eff_histos[-1].Draw('SAME')

  legend.Draw()
  c.SaveAs("pdf/"+cut_list[cut_index]+'_'+histo_list[histo_index]+".png")
  outfile.cd()
  c.Write()

#for sampleIndex in range(len(sample_list)):
  #for cutIndex in range(len(cut_list)):
    #for histoIndex in range(len(histo_list)):
      #getEff(sampleIndex,histoIndex,cutIndex)

for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex)     
#eff.Write()
outfile.Close()