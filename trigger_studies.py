from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TF1,TGraphAsymmErrors,kWhite
from math import atan,sqrt
from array import array
from sys import argv
from os import system
import sys
#setup
print 'setup'
gROOT.SetBatch()

path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
#sample_list=['ZprimeFullHadCycle.MC.ZP750W7p5','ZprimeFullHadCycle.MC.ZP1000W10','ZprimeFullHadCycle.MC.ZP1250W12p5','ZprimeFullHadCycle.MC.ZP1500W15','ZprimeFullHadCycle.MC.ZP2000W20','ZprimeFullHadCycle.MC.TTbar']#'ZP500W5',
sample_list=['ZprimeFullHadCycle.MC.ZP1000W10','ZprimeFullHadCycle.MC.TTbar']
#sample_list=['ZP2000W20']
colors=[kRed,kBlue,kBlack,kGreen,kOrange,6,9]
#histo_list=['SumOfTopCandidatesPt2','SubLeadingTopCandidatePt2','HT50','pT4']#,'SumOfTopCandidatesPt','LeadingTopCandidatePt','SubLeadingTopCandidatePt','HT50'
#histo_list2=['SumOfTopCandidatesPt2','SubLeadingTopCandidatePt2','HT_{50} [GeV]','pT4']
histo_list=['HT50','pT4']#,'SumOfTopCandidatesPt','LeadingTopCandidatePt','SubLeadingTopCandidatePt','HT50'
histo_list2=['HT_{50} [GeV]','p_{T} fourth AK5 jet']


#cut_list=["Trigger1Histos","Trigger2Histos","Trigger3Histos"]#,"Trigger4Histos","Trigger5Histos"
#trigger_names=["HLT_HT750","HLT_QuadJet50","HLT_HT750||HLT_QuadJet50"]
#base_cut="BaseHistos"

cut_list=["SFHTHistos","SFQuadHistos"]#,"Trigger4Histos","Trigger5Histos"
trigger_names=["HLT_HT750","HLT_QuadJet50"]
base_cut="SFbaseHistos"


def hadd(inputlist,outputname):
  command_list='hadd -f '+path_base+outputname+'.root'#-v 0
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'

hadd(['ZprimeFullHadCycle.DATA.MUDATA_C.root','ZprimeFullHadCycle.DATA.MUDATA_D.root'],'mudata_trigger')#'ZprimeFullHadCycle.DATA.MUDATA_A.root','ZprimeFullHadCycle.DATA.MUDATA_B.root',
sample_list.append('mudata_trigger')

hadd(['ZprimeFullHadCycle.MC.QCD_HT-100To250.root','ZprimeFullHadCycle.MC.QCD_HT-250To500.root','ZprimeFullHadCycle.MC.QCD_HT-500To1000.root','ZprimeFullHadCycle.MC.QCD_HT-1000ToInf.root'],'muqcd_trigger')
sample_list.append('muqcd_trigger')

hadd(['ZprimeFullHadCycle.DATA.DATA_A.root','ZprimeFullHadCycle.DATA.DATA_B.root','ZprimeFullHadCycle.DATA.DATA_C.root','ZprimeFullHadCycle.DATA.DATA_D.root'],'data_trigger')

sample_names=["Z' 1TeV","ttbar","Data","MC QCD"]

#trigger_names=["HLT_SixJet50","HLT_QuadJet50","HLT_QuadJet70","HLT_QuadJet80","HLT_QuadJet90"]
#,"a","a"
  #["HLT_DiJet80_DiJet60_DiJet20","HLT_QuadJet90","HLT_SixJet50","HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05d03","HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v4"]
#cut_list#["HLT_HT750_v3","HLT_BTagMu_Jet300_Mu5_v3","HLT_Jet160Eta2p4_Jet120Eta2p4_DiBTagIP3DFastPVLoose_v4","HLT_DiPFJet80_DiPFJet30_BTagCSVd07d05_v1","HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v4"]

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
  error_bars=TGraphAsymmErrors()
  error_bars.Divide(trigger_hist,base_hist,"cl=0.683 b(1,1) mode")
  eff_histo.Divide(trigger_hist,base_hist,1,1,'B')
  eff_histo.SetStats(kFALSE)
  eff_histo.SetLineWidth(3)
  eff_histo.SetMaximum(1.01)
  eff_histo.SetMinimum(0.)
  eff_histo.GetYaxis().SetTitle("Trigger rate")
  eff_histo.SetTitle(trigger_names[cut_index])
  c=TCanvas(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]+'_Canvas')
  eff_histo.Draw("X0")
  c.SaveAs("pdf/"+sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]+".pdf")
  outfile.cd()
  c.Write()
  #return eff_histo
def getEff2(histo_index,cut_index,rebin=0):
  c=TCanvas(cut_list[cut_index]+'_'+histo_list[histo_index]+'_Canvas')
  legend=TLegend(0.8,0.1,0.999,0.6)
  legend.SetFillColor(kWhite)
  eff_histos=[]
  eff_error_bars=[]
  sample_files=[]
  for sample_index in range(len(sample_list)):
    #print path_base+sample_list[sample_index]+'.root'
    sample_files.append(TFile(path_base+sample_list[sample_index]+'.root'))
    #print sample_file
    base_hist=sample_files[-1].Get(base_cut+"/"+histo_list[histo_index]).Clone('base'+sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index])
    trigger_hist=sample_files[-1].Get(cut_list[cut_index]+"/"+histo_list[histo_index]).Clone(cut_list[cut_index]+'_'+histo_list[histo_index]+'_'+sample_list[sample_index])
    if rebin!=0:
      base_hist.Rebin(rebin)
      trigger_hist.Rebin(rebin)
    #eff_histos.append(eff_histo)
    #print sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]
    error_bars=TGraphAsymmErrors()
    error_bars.Divide(trigger_hist,base_hist,"cl=0.683 b(1,1) mode")
    eff_error_bars.append(error_bars)
    eff_histos.append(trigger_hist)
    eff_histos[-1].Divide(trigger_hist,base_hist,1,1,'B')
    eff_histos[-1].SetStats(kFALSE)
    eff_histos[-1].SetLineWidth(3)
    eff_histos[-1].GetXaxis().SetTitle(histo_list2[histo_index])
    eff_histos[-1].SetLineColor(colors[sample_index])
    eff_histos[-1].SetMaximum(1.01)
    eff_histos[-1].SetMinimum(0.)
    eff_histos[-1].GetYaxis().SetTitle("Trigger rate")
    eff_histos[-1].SetTitle(trigger_names[cut_index])
    
    eff_error_bars[-1].SetLineWidth(3)
    eff_error_bars[-1].GetXaxis().SetTitle(histo_list2[histo_index])
    eff_error_bars[-1].SetLineColor(colors[sample_index])
    eff_error_bars[-1].SetMaximum(1.01)
    eff_error_bars[-1].SetMinimum(0.)
    eff_error_bars[-1].GetYaxis().SetTitle("Trigger rate")
    eff_error_bars[-1].SetTitle(trigger_names[cut_index])
    
    legend.AddEntry(eff_histos[-1],sample_names[sample_index],'l')
    if len(eff_histos)==1:
      c.cd()
      #eff_histos[-1].Draw('AXIS')
      eff_error_bars[-1].Draw('AP')
    else:
      c.cd()
      #eff_histos[-1].Draw('SAME')
      eff_error_bars[-1].Draw('PSAME')
    c2=TCanvas(cut_list[cut_index]+'_'+histo_list[histo_index]+'_'+sample_list[sample_index]+'_Canvas')
    #eff_histos[-1].Draw('AXIS')
    eff_error_bars[-1].Draw()
    legend2=TLegend(0.8,0.2,0.999,0.93)
    legend2.AddEntry(eff_histos[-1],sample_list[sample_index],'l')
    legend2.Draw()
    c2.SaveAs("pdf/"+cut_list[cut_index]+'_'+histo_list[histo_index]+'_'+sample_list[sample_index]+".pdf")
    outfile.cd()
    eff_histos[-1].Write()
    c2.Write()
  
  c.cd()
  legend.Draw()
  c.SaveAs("pdf/"+cut_list[cut_index]+'_'+histo_list[histo_index]+".pdf")
  outfile.cd()
  c.Write()

#for sampleIndex in range(len(sample_list)):
  #for cutIndex in range(len(cut_list)):
    #for histoIndex in range(len(histo_list)):
      #getEff(sampleIndex,histoIndex,cutIndex)

for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHT650Histos"]#,"Trigger4Histos","Trigger5Histos"
trigger_names=["HLT_HT750 on top of HT650"]
base_cut="SFbase650Histos"
sample_list=['ZprimeFullHadCycle.MC.ZP1000W10','ZprimeFullHadCycle.MC.TTbar','data_trigger','muqcd_trigger']
sample_names=["Z' 1TeV","ttbar","Data","MC QCD"]

for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHTBtagHistos","SFQuadBtagHistos"]#,"Trigger4Histos","Trigger5Histos"
trigger_names=["HLT_HT750","HLT_QuadJet50"]
base_cut="SFbaseBtagHistos"
sample_list=['ZprimeFullHadCycle.MC.TTbar','mudata_trigger']
sample_names=["TTbar","Data"]

for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHTBtag2Histos","SFQuadBtag2Histos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbaseBtag2Histos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHTBtaglHistos","SFQuadBtaglHistos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbaseBtaglHistos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHTBtag2lHistos","SFQuadBtag2lHistos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbaseBtag2lHistos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

sample_list=['ZprimeFullHadCycle.MC.TTbar','data_trigger']

cut_list=["SFHT650BtagHistos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbase650BtagHistos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHT650Btag2Histos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbase650Btag2Histos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHT650BtaglHistos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbase650BtaglHistos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

cut_list=["SFHT650Btag2lHistos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbase650Btag2lHistos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)

trigger_names=["HLT_QuadJet50"]
cut_list=["SFQuad300Histos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbase300Histos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)


sample_list=['ZprimeFullHadCycle.MC.TTbar']
trigger_names=["HLT_Mu40"]
cut_list=["SFMu40BtaglHistos"]#,"Trigger4Histos","Trigger5Histos"
base_cut="SFbase40Histos"
for cutIndex in range(len(cut_list)):
  for histoIndex in range(len(histo_list)):
    getEff2(histoIndex,cutIndex,4)



def doSF(num,den,name,title):
  sf=num.Clone('sf_'+name)
  sf.Divide(den)
  sf.SetLineWidth(3)
  sf.GetYaxis().SetTitle(title)
  sf.Write()

doSF(outfile.Get("SFHTBtagHistos_HT50_mudata_trigger"),outfile.Get("SFHTBtagHistos_HT50_ZprimeFullHadCycle.MC.TTbar"),"1xCSVM_ht","1xCSVM")
doSF(outfile.Get("SFHTBtag2Histos_HT50_mudata_trigger"),outfile.Get("SFHTBtag2Histos_HT50_ZprimeFullHadCycle.MC.TTbar"),"2xCSVM_ht","2xCSVM")
doSF(outfile.Get("SFHTBtaglHistos_HT50_mudata_trigger"),outfile.Get("SFHTBtaglHistos_HT50_ZprimeFullHadCycle.MC.TTbar"),"1xCSVL_ht","1xCSVL")
doSF(outfile.Get("SFHTBtag2lHistos_HT50_mudata_trigger"),outfile.Get("SFHTBtag2lHistos_HT50_ZprimeFullHadCycle.MC.TTbar"),"2xCSVL_ht","2xCSVL")

doSF(outfile.Get("SFQuadBtagHistos_pT4_mudata_trigger"),outfile.Get("SFQuadBtagHistos_pT4_ZprimeFullHadCycle.MC.TTbar"),"1xCSVM_quad","1xCSVM")
doSF(outfile.Get("SFQuadBtag2Histos_pT4_mudata_trigger"),outfile.Get("SFQuadBtag2Histos_pT4_ZprimeFullHadCycle.MC.TTbar"),"2xCSVM_quad","2xCSVM")
doSF(outfile.Get("SFQuadBtaglHistos_pT4_mudata_trigger"),outfile.Get("SFQuadBtaglHistos_pT4_ZprimeFullHadCycle.MC.TTbar"),"1xCSVL_quad","1xCSVL")
doSF(outfile.Get("SFQuadBtag2lHistos_pT4_mudata_trigger"),outfile.Get("SFQuadBtag2lHistos_pT4_ZprimeFullHadCycle.MC.TTbar"),"2xCSVL_quad","2xCSVL")

doSF(outfile.Get("SFHT650BtagHistos_HT50_data_trigger"),outfile.Get("SFHT650BtagHistos_HT50_ZprimeFullHadCycle.MC.TTbar"),"1xCSVM_650","1xCSVM")
doSF(outfile.Get("SFHT650Btag2Histos_HT50_data_trigger"),outfile.Get("SFHT650Btag2Histos_HT50_ZprimeFullHadCycle.MC.TTbar"),"2xCSVM_650","2xCSVM")
doSF(outfile.Get("SFHT650BtaglHistos_HT50_data_trigger"),outfile.Get("SFHT650BtaglHistos_HT50_ZprimeFullHadCycle.MC.TTbar"),"1xCSVL_650","1xCSVL")
doSF(outfile.Get("SFHT650Btag2lHistos_HT50_data_trigger"),outfile.Get("SFHT650Btag2lHistos_HT50_ZprimeFullHadCycle.MC.TTbar"),"2xCSVL_650","2xCSVL")

doSF(outfile.Get("SFQuad300Histos_pT4_data_trigger"),outfile.Get("SFQuad300Histos_pT4_ZprimeFullHadCycle.MC.TTbar"),"HT300","HT300")

sf_quad_data_ttbar=outfile.Get("SFQuadHistos_pT4_mudata_trigger").Clone("sf_quad_data_ttbar")
sf_quad_data_zp1000=outfile.Get("SFQuadHistos_pT4_mudata_trigger").Clone("sf_quad_data_zp1000")
sf_quad_data_qcd=outfile.Get("SFQuadHistos_pT4_mudata_trigger").Clone("sf_quad_data_qcd")

sf_quad_data_ttbar.Divide(outfile.Get("SFQuadHistos_pT4_ZprimeFullHadCycle.MC.TTbar"))
sf_quad_data_zp1000.Divide(outfile.Get("SFQuadHistos_pT4_ZprimeFullHadCycle.MC.ZP1000W10"))
sf_quad_data_qcd.Divide(outfile.Get("SFQuadHistos_pT4_muqcd_trigger"))

sf_ht_data_ttbar=outfile.Get("SFHTHistos_HT50_mudata_trigger").Clone("sf_ht_data_ttbar")
sf_ht_data_zp1000=outfile.Get("SFHTHistos_HT50_mudata_trigger").Clone("sf_ht_data_zp1000")
sf_ht_data_qcd=outfile.Get("SFHTHistos_HT50_mudata_trigger").Clone("sf_ht_data_qcd")

sf_ht650_data_ttbar=outfile.Get("SFHT650Histos_HT50_data_trigger").Clone("sf_ht650_data_ttbar")
sf_ht650_data_zp1000=outfile.Get("SFHT650Histos_HT50_data_trigger").Clone("sf_ht650_data_zp1000")
sf_ht650_data_qcd=outfile.Get("SFHT650Histos_HT50_data_trigger").Clone("sf_ht650_data_qcd")

sf_ht_data_ttbar.Divide(outfile.Get("SFHTHistos_HT50_ZprimeFullHadCycle.MC.TTbar"))
sf_ht_data_zp1000.Divide(outfile.Get("SFHTHistos_HT50_ZprimeFullHadCycle.MC.ZP1000W10"))
sf_ht_data_qcd.Divide(outfile.Get("SFHTHistos_HT50_muqcd_trigger"))

sf_ht650_data_ttbar.Divide(outfile.Get("SFHT650Histos_HT50_ZprimeFullHadCycle.MC.TTbar"))
sf_ht650_data_zp1000.Divide(outfile.Get("SFHT650Histos_HT50_ZprimeFullHadCycle.MC.ZP1000W10"))
sf_ht650_data_qcd.Divide(outfile.Get("SFHT650Histos_HT50_muqcd_trigger"))

sf_quad_data_ttbar.SetLineWidth(3)
sf_quad_data_zp1000.SetLineWidth(3)
sf_quad_data_qcd.SetLineWidth(3)

sf_ht_data_ttbar.SetLineWidth(3)
sf_ht_data_zp1000.SetLineWidth(3)
sf_ht_data_qcd.SetLineWidth(3)

sf_ht650_data_ttbar.SetLineWidth(3)
sf_ht650_data_zp1000.SetLineWidth(3)
sf_ht650_data_qcd.SetLineWidth(3)

sf_quad_data_ttbar.GetYaxis().SetTitle('Trigger Data/MC SF (ttbar)')
sf_quad_data_zp1000.GetYaxis().SetTitle("Trigger Data/MC SF (Z' 1TeV)")
sf_quad_data_qcd.GetYaxis().SetTitle("Trigger Data/MC SF (QCD MC)")

sf_ht_data_ttbar.GetYaxis().SetTitle('Trigger Data/MC SF (ttbar)')
sf_ht_data_zp1000.GetYaxis().SetTitle("Trigger Data/MC SF (Z' 1TeV)")
sf_ht_data_qcd.GetYaxis().SetTitle("Trigger Data/MC SF (QCD MC)")

sf_ht650_data_ttbar.GetYaxis().SetTitle('Trigger Data/MC SF (ttbar) wrt HT650')
sf_ht650_data_zp1000.GetYaxis().SetTitle("Trigger Data/MC SF (Z' 1TeV) wrt HT650")
sf_ht650_data_qcd.GetYaxis().SetTitle("Trigger Data/MC SF (QCD MC) wrt HT650")

#sf_quad_data_ttbar.
#sf_quad_data_zp1000.
#sf_ht_data_ttbar.
#sf_ht_data_zp1000.

#sf_quad_data_ttbar.
#sf_quad_data_zp1000.
#sf_ht_data_ttbar.
#sf_ht_data_zp1000.

sf_quad_data_ttbar.Write()
sf_quad_data_zp1000.Write()
sf_quad_data_qcd.Write()
sf_ht_data_ttbar.Write()
sf_ht_data_zp1000.Write()
sf_ht_data_qcd.Write()
sf_ht650_data_ttbar.Write()
sf_ht650_data_zp1000.Write()
sf_ht650_data_qcd.Write()
#eff.Write()
outfile.Close()