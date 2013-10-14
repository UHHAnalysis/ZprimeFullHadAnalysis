from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TF1,TGraphAsymmErrors,kWhite
from math import atan,sqrt
from array import array
from sys import argv
import sys
#setup
print 'setup'
gROOT.SetBatch()

path_base='/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZprimeFullHadCycle.MC.'
sample_list=['ZP2000W20','QCD']
sample_list2=["QCD_HT-100To250","QCD_HT-250To500","QCD_HT-500To1000","QCD_HT-1000ToInf","TTbar"]
histo_name='Nevts'
cut_list=["Cat_2jet","Cat_2htt","Cat_2htt_2btl","Cat_2htt_2btm","Cat_2htt_2nsb","Cat_2htt_2btl_2nsb","Cat_2btm","Cat_2btl_2nsb","Cat_2nsb","Cat_2htt_1btl","Cat_2htt_1btm"]
name_list=["2jet","2htt","2htt_2btl","2htt_2btm","2htt_2nsb","2htt_2btl_2nsb","2btm","2btl_2nsb","2nsb","2htt_1btl","2htt_1btm"]
base_cut="NoCutsHistos"
outfile=TFile("sbout.root","RECREATE")

def getEff(sample_index,cut_index):
  sample_file=TFile(path_base+sample_list[sample_index]+'.root')
  #print sample_file
  base_hist=sample_file.Get(base_cut+"/"+histo_name)
  cut_hist=sample_file.Get(cut_list[cut_index]+"/"+histo_name)
  eff_histo=cut_hist.Clone(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_name)
  eff_histo.Divide(cut_hist,base_hist,1,1,'B')
  #return [eff_histo.GetBinContent(1),eff_histo.GetBinError(1)]
  return [cut_hist.GetBinContent(1),base_hist.GetBinContent(1)]

def getEff2(cut_index):
  num=0.0
  den=0.0
  for sample_index in range(len(sample_list2)):
    sample_file=TFile(path_base+sample_list2[sample_index]+'.root')
    base_hist=sample_file.Get(base_cut+"/"+histo_name)
    cut_hist=sample_file.Get(cut_list[cut_index]+"/"+histo_name)
    den=den+base_hist.GetBinContent(1)
    num=num+cut_hist.GetBinContent(1)
  #eff_histo=cut_hist.Clone(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_name)
  #eff_histo.Divide(cut_hist,base_hist,1,1,'B')
  return [num,den]
  #eff_histo.SetStats(kFALSE)
  #eff_histo.SetLineWidth(3)
  #eff_histo.SetMaximum(1.01)
  #eff_histo.SetMinimum(0.)
  #eff_histo.GetYaxis().SetTitle("Trigger rate")
  #eff_histo.SetTitle(trigger_names[cut_index])
  #c=TCanvas(sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]+'_Canvas')
  #eff_histo.Draw()
  #c.SaveAs("pdf/"+sample_list[sample_index]+'_'+cut_list[cut_index]+'_'+histo_list[histo_index]+".pdf")
  #outfile.cd()
  #c.Write()
#def getEff3(cut_index):
  
shisto=TH1F("shisto",";Cut;Rate",len(cut_list),0,len(cut_list))
bhisto=TH1F("bhisto",";Cut;Rate",len(cut_list),0,len(cut_list))
sbhisto=TH1F("sbhisto",";Cut;S/B",len(cut_list),0,len(cut_list))
mini=0.000000001
for cut_index in range(len(cut_list)):
  sv=getEff(0,cut_index)
  shisto.SetBinContent(cut_index+1,sv[0]/sv[1])
  #shisto.SetBinError(cut_index+1,sv[1])
  shisto.GetXaxis().SetBinLabel(cut_index+1,name_list[cut_index])
  shisto.SetStats(kFALSE)
  shisto.SetLineWidth(3)
  shisto.SetMaximum(1.01)
  shisto.SetMinimum(mini)
  bv=getEff2(cut_index)
  print bv
  bhisto.SetBinContent(cut_index+1,bv[0]/bv[1])
  #bhisto.SetBinError(cut_index+1,bv[1])
  bhisto.GetXaxis().SetBinLabel(cut_index+1,name_list[cut_index])
  bhisto.SetStats(kFALSE)
  bhisto.SetLineWidth(3)
  bhisto.SetLineColor(kRed)
  bhisto.SetMaximum(1.01)
  bhisto.SetMinimum(mini)
  sbhisto.SetBinContent(cut_index+1,sv[0]/bv[0])
  #sbhisto.SetBinError(cut_index+1,bv[1])
  sbhisto.GetXaxis().SetBinLabel(cut_index+1,name_list[cut_index])
  sbhisto.SetStats(kFALSE)
  sbhisto.SetLineWidth(3)
  sbhisto.SetLineColor(kBlack)
  sbhisto.SetMaximum(0.1)
  sbhisto.SetMinimum(0.000001)
outfile.cd()
c=TCanvas("sbcanvas")
shisto.Draw()
bhisto.Draw("SAME")
c.SetLogy()
c.SaveAs("pdf/sbcanvas_2.pdf")
c.Write()
c2=TCanvas("sbcanvas2")
sbhisto.Draw()
c2.SetLogy()
c2.SaveAs("pdf/sbcanvas2_2.pdf")
c2.Write()
outfile.Close()