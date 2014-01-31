from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TF1,TGraphAsymmErrors,kWhite,kMagenta,kAzure,TPaveText
from math import atan,sqrt
from copy import deepcopy
from array import array
from sys import argv
import sys
#setup
print 'setup'
gROOT.SetBatch()
gStyle.SetOptStat('ioue')
gStyle.SetNumberContours(255)
gStyle.SetPalette(55)

print len(argv[1:])
appendix=''
if len(argv[1:])>0:
  appendix='_'+argv[1]


files_path = "/nfs/dust/cms/user/usaiem/ZprimeFullHad/"
#if len(argv[1:])==2:
  #files_path = "/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad"+appendix+"/"
  
#files_path = "/scratch/hh/dust/naf/cms/user/usai/heptoptagval/"
#if len(argv[1:])==2:
  #files_path = "/scratch/hh/dust/naf/cms/user/usai/heptoptagval"+appendix+"/"

file_out_name = "heptoptagvalhistos"+appendix+".root"
files_name_base = "SemileptonicHepTopTagValSelCycle"

process_names_mc = []
subprocess_names_mc = []
#QCD
#process_names_mc.append('QCD')
#subprocess_names_mc.append(["MC.QCD1000","MC.QCD120to170","MC.QCD170to300","MC.QCD300to470","MC.QCD470to600","MC.QCD50to80","MC.QCD600to800","MC.QCD800to1000","MC.QCD80to120"])
#WW,WZ,ZZ
#process_names_mc.append('WW,WZ,ZZ')
#subprocess_names_mc.append(["MC.doubleWW","MC.doubleWZ","MC.doubleZZ"])
#single-Top
process_names_mc.append('Singletop')
subprocess_names_mc.append(["MC.singleTbars","MC.singleTbart","MC.singleTbartW","MC.singleTs","MC.singleTt","MC.singleTtW"])
#Z+Jets
process_names_mc.append('Z+Jets')
subprocess_names_mc.append(["MC.ZJets1","MC.ZJets2","MC.ZJets3","MC.ZJets4"])
#W+Jets
process_names_mc.append('W+Jets')
subprocess_names_mc.append(["MC.WJets1","MC.WJets2","MC.WJets3","MC.WJets4"])

#if len(argv[1:])==1:
  ##TTbarNotSemi
  #process_names_mc.append('TTbarNotSemi')
  #subprocess_names_mc.append(["MC.TTbarNotSemi"+appendix])
  ##TTbarsemi
  #process_names_mc.append('TTbarsemi')
  #subprocess_names_mc.append(['MC.TTbarSemi'+appendix])#"MC.TTbarsemi"])
#else:
  #TTbarlept
process_names_mc.append('Fully-Leptonic t#bar{t}')
subprocess_names_mc.append(["MC.TTbarlept"+appendix])
  #TTbarhad
  #process_names_mc.append('TTbarhad')
  #subprocess_names_mc.append(["MC.TTbarhad"])
  #TTbarsemi
process_names_mc.append('Semi-Leptonic t#bar{t}')
subprocess_names_mc.append(["MC.TTbarsemi"+appendix])

total_subprocess_names_mc=[]
for i in range(len(process_names_mc)):
  for j in range(len(subprocess_names_mc[i])):
    total_subprocess_names_mc.append(subprocess_names_mc[i][j])

#if len(argv[1:])==1:
  #process_names_signal='Semi-Leptonic t#bar{t}'
  #process_names_background=['WW,WZ,ZZ','Singletop','Z+Jets','W+Jets','TTbarNotSemi']#,'TTbarlept','TTbarhad']#'QCD',
  #process_names_ttbar=['Semi-Leptonic t#bar{t}','TTbarNotSemi']#,'TTbarlept','TTbarhad']
  #process_names_ttbarbkg=['TTbarNotSemi']#'TTbarlept','TTbarhad']
  #process_names_bkgnottbar=['WW,WZ,ZZ','Singletop','Z+Jets','W+Jets']#'QCD',
#else:
process_names_signal='Semi-Leptonic t#bar{t}'
process_names_background=['Singletop','Z+Jets','W+Jets','Fully-Leptonic t#bar{t}']#'QCD','WW,WZ,ZZ',,'TTbarhad'
process_names_ttbar=['Semi-Leptonic t#bar{t}','Fully-Leptonic t#bar{t}']#,'TTbarhad']
process_names_ttbarbkg=['Fully-Leptonic t#bar{t}']#,'TTbarhad']
process_names_bkgnottbar=['Singletop','Z+Jets','W+Jets']#'QCD','WW,WZ,ZZ',
    
process_name_data = 'data'
subprocess_name_data = "DATA.DATA"

#process_colors = [2,3,4,5,6,7,8,9]
#process_colors = [3,4,5,6,7,8,9]
process_colors = [kMagenta,kAzure-2,kGreen-3,kRed-7,kRed+1]
#if len(argv[1:])==1:
  #process_colors = [3,4,5,6,7,9]
histogram_names = []
histogram_descriptions = []
histogram_yaxes = []
histogram_xaxes = []

#N_topjets
histogram_names.append('N_topjets')
histogram_descriptions.append('N^{jets}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{jets}')
#N_mu
histogram_names.append('N_mu')
histogram_descriptions.append('N^{muons}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{muons}')
#N_pv
histogram_names.append('N_pv')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#N_pv
histogram_names.append('N_pv200')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#N_pv
histogram_names.append('N_pv300')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#N_pv
histogram_names.append('N_pv400')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#N_pv
histogram_names.append('N_pv500')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#N_pv
histogram_names.append('N_pv600')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#N_events_perLumiBin
histogram_names.append('N_events_perLumiBin')
histogram_descriptions.append('N^{evt}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{evt}')
#N_pv_perLumiBin
histogram_names.append('N_pv_perLumiBin')
histogram_descriptions.append('N^{PV}')
histogram_yaxes.append('Events')
histogram_xaxes.append('N^{PV}')
#DR_Mub
histogram_names.append('DR_Mub')
histogram_descriptions.append('DR muon-b')
histogram_yaxes.append('Events')
histogram_xaxes.append('DR muon-b')
#DPhi_Mub
histogram_names.append('DPhi_Mub')
histogram_descriptions.append('DPhi muon-b')
histogram_yaxes.append('Events')
histogram_xaxes.append('DPhi muon-b')
#DR_Mutop
histogram_names.append('DR_Mutop')
histogram_descriptions.append('DR muon-top')
histogram_yaxes.append('Events')
histogram_xaxes.append('DR muon-top')
#DPhi_Mutop
histogram_names.append('DPhi_Mutop')
histogram_descriptions.append('DPhi muon-top')
histogram_yaxes.append('Events')
histogram_xaxes.append('DPhi muon-top')
#DR_btop
histogram_names.append('DR_btop')
histogram_descriptions.append('DR b-top')
histogram_yaxes.append('Events')
histogram_xaxes.append('DR b-top')
#DPhi_btop
histogram_names.append('DPhi_btop')
histogram_descriptions.append('DPhi b-top')
histogram_yaxes.append('Events')
histogram_xaxes.append('DPhi b-top')
#MassTop
histogram_names.append('MassTop')
histogram_descriptions.append('Top jet mass (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Top jet mass (GeV)')
#Pt_b_sub
histogram_names.append('Pt_b_sub')
histogram_descriptions.append('Pt b-subjet (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt b-subjet (GeV)')
#Pt_nonb_sub
histogram_names.append('Pt_nonb_sub')
histogram_descriptions.append('Pt non-b-subjet (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt non-b-subjet (GeV)')
#Pt_tagged_sub
histogram_names.append('Pt_tagged_sub')
histogram_descriptions.append('Pt non-b-subjet (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt non-b-subjet (GeV)')
#Pt_all_sub
histogram_names.append('Pt_all_sub')
histogram_descriptions.append('Pt all subjets (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt all subjets (GeV)')
#Pt_all_sub_nobin
histogram_names.append('Pt_all_sub_nobin')
histogram_descriptions.append('Pt all subjets (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt all subjets (GeV)')
#Toppt
histogram_names.append('Toppt')
histogram_descriptions.append('Pt top-jet (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt top-jet (GeV)')
#Toppt_2
histogram_names.append('Toppt_2')
histogram_descriptions.append('Pt top-jet (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Pt top-jet (GeV)')
#m01
histogram_names.append('m01')
histogram_descriptions.append('Inv mass of subjets 0+1 (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('m_{12} (GeV)')
#m02
histogram_names.append('m02')
histogram_descriptions.append('Inv mass of subjets 0+2 (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('m_{13} (GeV)')
#m12
histogram_names.append('m12')
histogram_descriptions.append('Inv mass of subjets 1+2 (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('m_{23} (GeV)')
#mW
histogram_names.append('mW')
histogram_descriptions.append('Inv mass of W (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Inv mass of W (GeV)')
#m012
histogram_names.append('m012')
histogram_descriptions.append('Inv mass of subjets 0+1+2 (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Inv mass of subjets 0+1+2 (GeV)')
#mMuB
histogram_names.append('mMuB')
histogram_descriptions.append('Inv mass Mu + Btagged jet (GeV)')
histogram_yaxes.append('Events')
histogram_xaxes.append('Inv mass Mu + Btagged jet (GeV)')
#dRMuB
histogram_names.append('dRMuB')
histogram_descriptions.append('DeltaR Mu Btagged jet')
histogram_yaxes.append('Events')
histogram_xaxes.append('DeltaR Mu Btagged jet')
#Nevts
histogram_names.append('Nevts')
histogram_descriptions.append('Number of events passed')
histogram_yaxes.append('Events')
histogram_xaxes.append('Passed')
#EventCount
histogram_names.append('EventCount')
histogram_descriptions.append('EventCount')
histogram_yaxes.append('Events')
histogram_xaxes.append('')
#ptSFcount
histogram_names.append('ptSFcount')
histogram_descriptions.append('ptSFcount')
histogram_yaxes.append('Events')
histogram_xaxes.append('pT [GeV]')

#var1_HTT
histogram_names.append('var1_HTT')
histogram_descriptions.append('')
histogram_xaxes.append('atan(m_{13}/m_{12})')
histogram_yaxes.append('Events')
#var2_HTT
histogram_names.append('var2_HTT')
histogram_descriptions.append('')
histogram_xaxes.append('m_{23}/m_{123}')
histogram_yaxes.append('Events')
#var3_HTT
histogram_names.append('var3_HTT')
histogram_descriptions.append('')
histogram_xaxes.append('m_{W} [GeV]')
histogram_yaxes.append('Events')
#HTT2D
histogram_names.append('HTT2D')
histogram_descriptions.append('HTT2D')
histogram_yaxes.append('atan( m_{13} / m_{12} )')
histogram_xaxes.append('m_{23}/m_{123}')
#dRsubjet
histogram_names.append('dRsubjet')
histogram_descriptions.append('dRsubjet')
histogram_yaxes.append('DeltaR(subjets)')
histogram_xaxes.append('Events')
#dRsubjet
histogram_names.append('LeptToppt')
histogram_descriptions.append('LeptToppt')
histogram_yaxes.append('Pt leptonic top (GeV)')
histogram_xaxes.append('Events')

cut_names = ["nocutshists","nleptbtagshists","probeselehists","htcuthists","etmisshists","njetshists","masswindowhists","heptoptag_masscut_hists","heptoptag_masscut_nsub_hists","NOheptoptag_NOmasscut_hists","NOheptoptag_masscut_hists","heptoptag_NOmasscut_hists","heptoptag_NOmasscut__NOheptoptag_masscut_hists","pt200hists","pt250hists","pt300hists","pt350hists","pt400hists","ptlowhists","before_tpr_hists","after_tpr_hists","heptoptag_masscut_hists_notpr","NOheptoptag_NOmasscut_hists_notpr","eta0p5","eta1p0","eta2p4","eta0p5to1p0","eta1p0to2p4","eta0p5_HTT","eta1p0_HTT","eta1p0_HTT_nsub","eta2p4_HTT","eta0p5to1p0_HTT","eta1p0to2p4_HTT","eta1p0to2p4_HTT_nsub","eta1p0_400","eta1p0to2p4_400","pt300histshtt","pt400histshtt","cutflow_mass_eta1p0","cutflow_mass_eta1p0to2p4","cutflow_mass_htt_eta1p0","cutflow_mass_htt_eta1p0to2p4","cutflow_mass_htt_nsub_eta1p0","cutflow_mass_htt_nsub_eta1p0to2p4"]
#,"eta1p0","eta1p0_HTT"]"mcmatch_NOhtt","NOmcmatch_NOhtt","mcmatch_htt","NOmcmatch_htt","mcmatch_NOhtt_pt","NOmcmatch_NOhtt_pt","mcmatch_htt_pt","NOmcmatch_htt_pt","pt300histshtt","pt400histshtt",




nevts_index=histogram_names.index('Nevts')
ptSFcount_index=histogram_names.index('ptSFcount')
pt_index=histogram_names.index('Toppt')
pt2_index=histogram_names.index('Toppt_2')
htt2d_index=histogram_names.index('HTT2D')
toppt_index=histogram_names.index('Toppt')
topmass_index=histogram_names.index('MassTop')
index_nn=cut_names.index("NOheptoptag_NOmasscut_hists")
index_yy=cut_names.index("heptoptag_masscut_hists")
index_nn_notpr=cut_names.index("NOheptoptag_NOmasscut_hists_notpr")
index_yy_notpr=cut_names.index("heptoptag_masscut_hists_notpr")
index_ny=cut_names.index("NOheptoptag_masscut_hists")
index_yn=cut_names.index("heptoptag_NOmasscut_hists")
index_yn_ny=cut_names.index("heptoptag_NOmasscut__NOheptoptag_masscut_hists")
#index_matched=cut_names.index("mcmatch_NOhtt")
#index_unmatched=cut_names.index("NOmcmatch_NOhtt")
#index_matched_htt=cut_names.index("mcmatch_htt")
#index_unmatched_htt=cut_names.index("NOmcmatch_htt")
#index_matched_pt=cut_names.index("mcmatch_NOhtt_pt")
#index_unmatched_pt=cut_names.index("NOmcmatch_NOhtt_pt")
#index_matched_htt_pt=cut_names.index("mcmatch_htt_pt")
#index_unmatched_htt_pt=cut_names.index("NOmcmatch_htt_pt")


def scalefactor(data,mc,signal,dmb,title):
  SFbin_DoverD=data[ptSFcount_index][index_yy].Clone('SFbin_DoverD'+title)
  SFbin_DoverD.Divide(data[ptSFcount_index][index_yy],data[ptSFcount_index][index_nn],1,1,'B')
  SFbin_MCoverMC=mc[ptSFcount_index][index_yy].Clone('SFbin_MCoverMC'+title)
  SFbin_MCoverMC.Divide(mc[ptSFcount_index][index_yy],mc[ptSFcount_index][index_nn],1,1,'B')
  SFbin_DmBoverDmB=dmb[ptSFcount_index][index_yy].Clone('SFbin_DmBoverDmB'+title)
  SFbin_DmBoverDmB.Divide(dmb[ptSFcount_index][index_yy],dmb[ptSFcount_index][index_nn],1,1,'B')
  SFbin_SoverS=signal[ptSFcount_index][index_yy].Clone('SFbin_SoverS'+title)
  SFbin_SoverS.Divide(signal[ptSFcount_index][index_yy],signal[ptSFcount_index][index_nn],1,1,'B')
  SFbin=SFbin_DoverD.Clone('SFbin'+title)
  SFbin.Divide(SFbin_MCoverMC)
  SFbin_NoBkg=SFbin_DmBoverDmB.Clone('SFbin_NoBkg'+title)
  SFbin_NoBkg.Divide(SFbin_SoverS)
  return [SFbin_DoverD,SFbin_MCoverMC,SFbin_DmBoverDmB,SFbin_SoverS,SFbin,SFbin_NoBkg]
  
def scalefactor2(data,mc,signal,dmb,title):
  SFbin_DoverD=data[0].Clone('SFbin_DoverD'+title)
  SFbin_DoverD.Divide(data[0],data[1],1,1,'B')
  SFbin_MCoverMC=mc[0].Clone('SFbin_MCoverMC'+title)
  SFbin_MCoverMC.Divide(mc[0],mc[1],1,1,'B')
  SFbin_DmBoverDmB=dmb[0].Clone('SFbin_DmBoverDmB'+title)
  SFbin_DmBoverDmB.Divide(dmb[0],dmb[1],1,1,'B')
  SFbin_SoverS=signal[0].Clone('SFbin_SoverS'+title)
  SFbin_SoverS.Divide(signal[0],signal[1],1,1,'B')
  SFbin=SFbin_DoverD.Clone('SFbin'+title)
  SFbin.Divide(SFbin_MCoverMC)
  SFbin_NoBkg=SFbin_DmBoverDmB.Clone('SFbin_NoBkg'+title)
  SFbin_NoBkg.Divide(SFbin_SoverS)
  return [SFbin_DoverD,SFbin_MCoverMC,SFbin_DmBoverDmB,SFbin_SoverS,SFbin,SFbin_NoBkg]

def getadded(mc_sf_list,data_sf_list,title):
  #add mc
  allmc=[mc_sf_list[0][0].Clone('all_mc_yy_'+title),mc_sf_list[0][1].Clone('all_mc_nn_'+title)]
  for process_name_index in range(1,len(process_names_mc)):
    allmc[0].Add(mc_sf_list[process_name_index][0])
    allmc[1].Add(mc_sf_list[process_name_index][1])
  #add background
  allbkg=[mc_sf_list[process_names_mc.index(process_names_background[0])][0].Clone('all_bkg_yy_'+title),mc_sf_list[process_names_mc.index(process_names_background[0])][1].Clone('all_bkg_nn_'+title)]
  for process_background_index in range(1,len(process_names_background)):
    allbkg[0].Add(mc_sf_list[process_names_mc.index(process_names_background[process_background_index])][0])
    allbkg[1].Add(mc_sf_list[process_names_mc.index(process_names_background[process_background_index])][1])
  #add signal
  allsignal=[mc_sf_list[process_names_mc.index(process_names_signal)][0],mc_sf_list[process_names_mc.index(process_names_signal)][1]]
  #add data - bkg
  alldatambkg=[data_sf_list[0].Clone('all_datambkg_yy_'+title),data_sf_list[1].Clone('all_datambkg_nn_'+title)]
  alldatambkg[0].Add(allbkg[0],-1.0)
  alldatambkg[1].Add(allbkg[1],-1.0)
  #return values
  return [allmc,allbkg,allsignal,alldatambkg]

def copy_sf_lists(mc_sf_list,title):
  mc_sf_new=[]
  for process_name_index in range(0,len(process_names_mc)):
    mc_sf_tmp=[mc_sf_list[process_name_index][0].Clone(mc_sf_list[process_name_index][0].GetName()+title),mc_sf_list[process_name_index][1].Clone(mc_sf_list[process_name_index][1].GetName()+title)]
    mc_sf_new.append(mc_sf_tmp)
  return mc_sf_new
  
#make sf notpr
#index_nn=cut_names.index("NOheptoptag_NOmasscut_hists_notpr")
#index_yy=cut_names.index("heptoptag_masscut_hists_notpr")

SF_bins = [150,200,250,400,10000]
SF_bins_trim = SF_bins[1:-1]
ScaleFactorsNames=[]
for i in range(len(SF_bins)-1):
  if i<len(SF_bins)-2:
    ScaleFactorsNames.append(str(SF_bins[i])+'-'+str(SF_bins[i+1]))
  else:
    ScaleFactorsNames.append('>'+str(SF_bins[i]))

#SF_etabins = [150,200,250,400,10000]
SF_etabins=ScaleFactorsEtaNames=['#eta<0.5','0.5<#eta<1.0','1.0<#eta<2.4','#eta<2.4']

#get the files
print 'get the files'
files_list_mc=[]
for process_name_index in range(len(process_names_mc)):
  process_name=process_names_mc[process_name_index]
  subprocess_sublist=[]
  for subprocess_name_index in range(len(subprocess_names_mc[process_name_index])):
    subprocess_name=subprocess_names_mc[process_name_index][subprocess_name_index]
    subprocess_sublist.append(TFile(files_path+"/"+files_name_base+"."+subprocess_name+".root"))
  files_list_mc.append(subprocess_sublist)
file_data=TFile(files_path+"/"+files_name_base+"."+subprocess_name_data+".root")
#structure: files_list_mc[process_name_index][subprocess_name_index]

#open output file
outfile=TFile(file_out_name, "RECREATE")

#get mc histos
input_histos_mc=[]
for process_name_index in range(len(process_names_mc)):
  process_name=process_names_mc[process_name_index]
  subprocess_sublist=[]
  for subprocess_name_index in range(len(subprocess_names_mc[process_name_index])):
    subprocess_name=subprocess_names_mc[process_name_index][subprocess_name_index]
    histo_sublist=[]
    for histogram_name_index in range(len(histogram_names)):
      histogram_name=histogram_names[histogram_name_index]
      cut_sublist=[]
      for cut_name_index in range(len(cut_names)):
	cut_name=cut_names[cut_name_index]
	cut_sublist.append(files_list_mc[process_name_index][subprocess_name_index].Get(cut_name+"/"+histogram_name))
	cut_sublist[-1].SetTitle('')
	if (cut_name in ['eta1p0_400','eta1p0to2p4_400']) and (histogram_name in ['m01','m02','m12']):
	  cut_sublist[-1].Rebin(4)
      histo_sublist.append(cut_sublist)
    subprocess_sublist.append(histo_sublist)
  input_histos_mc.append(subprocess_sublist)
#structure: input_histos_mc[process_name_index][subprocess_name_index][histogram_name_index][cut_name_index]

#get data histos
print 'get data histos'
input_histos_data=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  tmp_histogram_sublist=[]
  for cut_name_index in range(len(cut_names)):
    cut_name=cut_names[cut_name_index]
    tmp_histogram_sublist.append(file_data.Get(cut_name+"/"+histogram_name))#.Clone())
    #tmp_histogram_sublist[-1].SetLineColor(kBlack)
    #tmp_histogram_sublist[-1].SetLineWidth(2)
    #tmp_histogram_sublist[-1].SetMarkerColor(kBlack)
    tmp_histogram_sublist[-1].SetLineColor(1)
    tmp_histogram_sublist[-1].SetLineStyle(1)
    tmp_histogram_sublist[-1].SetLineWidth(1)
    tmp_histogram_sublist[-1].SetMarkerColor(1)
    tmp_histogram_sublist[-1].SetMarkerStyle(8)
    tmp_histogram_sublist[-1].SetMarkerSize(1)
    tmp_histogram_sublist[-1].SetName(histogram_name+'_'+cut_name)
    tmp_histogram_sublist[-1].SetTitle('')
    if (cut_name in ['eta1p0_400','eta1p0to2p4_400']) and (histogram_name in ['m01','m02','m12']):
      tmp_histogram_sublist[-1].Rebin(4)
    if cut_name=='NOheptoptag_NOmasscut_hists' and histogram_name=='MassTop':
      tmp_histogram_sublist[-1].Write()
    if cut_name in ['NOheptoptag_NOmasscut_hists','heptoptag_masscut_hists'] and histogram_name=='HTT2D':
      tmp_histogram_sublist[-1].Write()
    #tmp_histogram_sublist[-1].Sumw2()
    #tmp_histogram_sublist[-1].Write()
  input_histos_data.append(tmp_histogram_sublist)
#structure: input_histos_data[histogram_name_index][cut_name_index]

input_histos_data[topmass_index][index_nn].Write()
input_histos_data[topmass_index][index_yy].Write()
input_histos_data[toppt_index][index_nn].Write()
input_histos_data[toppt_index][index_yy].Write()

#merge mc histos
print 'merge mc histos'
input_merged_mc=[]
for process_name_index in range(len(process_names_mc)):
  process_name=process_names_mc[process_name_index]
  histo_sublist=[]
  for histogram_name_index in range(len(histogram_names)):
    histogram_name=histogram_names[histogram_name_index]
    cut_sublist=[]
    for cut_name_index in range(len(cut_names)):
      cut_name=cut_names[cut_name_index]
      merged_histo=input_histos_mc[process_name_index][0][histogram_name_index][cut_name_index].Clone(process_name+'_'+histogram_name+'_'+cut_name+'_Merge')
      if len(subprocess_names_mc[process_name_index])>1:
	for subprocess_name_index in range(1,len(subprocess_names_mc[process_name_index])):
	    merged_histo.Add(input_histos_mc[process_name_index][subprocess_name_index][histogram_name_index][cut_name_index])
      process_color=process_colors[process_name_index]
      merged_histo.SetFillColor(process_color)
      merged_histo.SetLineColor(kBlack)
      merged_histo.SetMarkerColor(process_color)
      cut_sublist.append(merged_histo)
    histo_sublist.append(cut_sublist)
  input_merged_mc.append(histo_sublist)
#structure: input_merged_mc[process_name_index][histogram_name_index][cut_name_index]

#top pt reweight normalization
#Int_nn_notpr=0.0
#Int_yy_notpr=0.0
#Int_nn=0.0
#Int_yy=0.0
#for i in ['TTbarlept','TTbarhad','TTbarsemi']: #process_names_mc:
  #Int_nn_notpr+=input_merged_mc[process_names_mc.index(i)][nevts_index][index_nn_notpr].Integral()
  #Int_yy_notpr+=input_merged_mc[process_names_mc.index(i)][nevts_index][index_yy_notpr].Integral()
  #Int_nn+=input_merged_mc[process_names_mc.index(i)][nevts_index][index_nn].Integral()
  #Int_yy+=input_merged_mc[process_names_mc.index(i)][nevts_index][index_yy].Integral()
#weight_nn=Int_nn_notpr/Int_nn
#weight_yy=Int_yy_notpr/Int_yy
#print weight_nn,weight_yy
#for i in ['TTbarlept','TTbarhad','TTbarsemi']:#process_names_mc:
  #process_name_index=process_names_mc.index(i)
  #for histogram_name_index in range(len(histogram_names)):
    #input_merged_mc[process_name_index][histogram_name_index][index_nn].Scale(weight_nn)
    #input_merged_mc[process_name_index][histogram_name_index][index_yy].Scale(weight_yy)#.Scale(weight_nn)

#stack mc histos
print 'stack mc histos'
stacked_mc=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  cut_sublist=[]
  for cut_name_index in range(len(cut_names)):
    cut_name=cut_names[cut_name_index]
    stack_histo=THStack(histogram_name+'_'+cut_name+'_Stack','')
    for process_name_index in range(len(process_names_mc)):
      stack_histo.Add(input_merged_mc[process_name_index][histogram_name_index][cut_name_index])
    cut_sublist.append(stack_histo)
  stacked_mc.append(cut_sublist)
#structure: stacked_mc[histogram_name_index][cut_name_index]

#add mc histos for pull
print 'add mc histos for pull'
added_mc=[]
added_mc_signal=[]
added_mc_background=[]
added_mc_SoverB=[]
added_mc_DoverMC=[]
added_mc_DmBoverS=[]
added_mc_DmB=[]
signal_name= process_names_signal#'TTbarsemi'
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  cut_sublist=[]
  cut_sublist_signal=[]
  cut_sublist_background=[]
  cut_sublist_SoverB=[]
  cut_sublist_DoverMC=[]
  cut_sublist_DmBoverS=[]
  cut_sublist_DmB=[]
  for cut_name_index in range(len(cut_names)):
    cut_name=cut_names[cut_name_index]
    added_histo=input_merged_mc[0][histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_Add')
    added_histo_background=input_merged_mc[0][histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_Background_Add')
    if len(process_names_mc)>1:
      for process_name_index in range(1,len(process_names_mc)):
	added_histo.Add(input_merged_mc[process_name_index][histogram_name_index][cut_name_index])
	if process_names_mc[process_name_index]==signal_name:
	  added_histo_signal=input_merged_mc[process_name_index][histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_Signal_Add')
	else:
	  added_histo_background.Add(input_merged_mc[process_name_index][histogram_name_index][cut_name_index])
    added_histo_SoverB=added_histo_signal.Clone(histogram_name+'_'+cut_name+'_SoverB_Add')
    added_histo_SoverB.Divide(added_histo_background)
    added_histo_DoverMC=input_histos_data[histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_DoverMC_Add')
    added_histo_DoverMC.Divide(added_histo)
    added_histo_DmB=input_histos_data[histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_DmB_Add')
    added_histo_DmB.Add(added_histo_background,-1.0)
    added_histo_DmBoverS=input_histos_data[histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_DmBoverS_Add')
    added_histo_DmBoverS.Add(added_histo_background,-1.0)
    added_histo_DmBoverS.Divide(added_histo_signal)
    #if histogram_name=='ptSFcount' and cut_name=="NOheptoptag_NOmasscut_hists":
    #  added_histo_SoverB.Write()
    cut_sublist.append(added_histo)
    cut_sublist_signal.append(added_histo_signal)
    cut_sublist_background.append(added_histo_background)
    cut_sublist_SoverB.append(added_histo_SoverB)
    cut_sublist_DoverMC.append(added_histo_DoverMC)
    cut_sublist_DmBoverS.append(added_histo_DmBoverS)
    cut_sublist_DmB.append(added_histo_DmB)
    if histogram_name=='Nevts' and cut_name=="NOheptoptag_NOmasscut_hists":
      ndata=input_histos_data[histogram_name_index][cut_name_index].GetBinContent(1)
      ndataerr=input_histos_data[histogram_name_index][cut_name_index].GetBinError(1)
      nmc=added_histo.GetBinContent(1)
      nmcerr=added_histo.GetBinError(1)
      canvas=TCanvas('conto')
      latex=TLatex()
      latex.DrawLatex(0.1,0.8,"N_{DATA}="+str(ndata)+'#pm'+str(ndataerr))
      latex.DrawLatex(0.1,0.6,"N_{MC}="+str(nmc)+'#pm'+str(nmcerr))
      latex.Draw()
      canvas.Write()
    if histogram_name in ['ptSFcount'] and cut_name in ["heptoptag_masscut_hists","NOheptoptag_NOmasscut_hists","NOheptoptag_masscut_hists","heptoptag_NOmasscut_hists","heptoptag_NOmasscut__NOheptoptag_masscut_hists"]:
      SBbin=TH1F(histogram_name+'_'+cut_name+'_SBbin','Signal/Background;p_{T} range [GeV];S/B',len(SF_bins)-1,0,len(SF_bins)-1)
      SBbin.SetStats(kFALSE)
      for i in range(1,len(SF_bins)):
	SBbin.SetBinContent(i,added_histo_SoverB.GetBinContent(i))
	SBbin.SetBinError(i,added_histo_SoverB.GetBinError(i))
	SBbin.GetXaxis().SetBinLabel(i,ScaleFactorsNames[i-1])
      SBbin.GetXaxis().SetLabelSize(0.07)
      SBbin.SetLineWidth(2)
      SBbin.Write()
    if histogram_name in ['Nevts','ptSFcount'] and cut_name in ["heptoptag_masscut_hists","NOheptoptag_NOmasscut_hists"]:#,"NOheptoptag_masscut_hists","heptoptag_NOmasscut_hists","heptoptag_NOmasscut__NOheptoptag_masscut_hists"]:
      added_histo_SoverB.SetStats(kFALSE)
      added_histo_SoverB.SetTitle('Signal/Background')
      added_histo_SoverB.Write()
      added_histo_DoverMC.Write()
      canvas=TCanvas(histogram_name+'_'+cut_name+'_Info')
      SoverBvalue=added_histo_SoverB.GetBinContent(1)
      SoverBerror=added_histo_SoverB.GetBinError(1)
      DoverMCvalue=added_histo_DoverMC.GetBinContent(1)
      DoverMCerror=added_histo_DoverMC.GetBinError(1)
      latex=TLatex()
      #latex.DrawLatex(0.1,0.8,"#frac{S}{B}="+('%.3f' % SoverBvalue)+'#pm'+('%.3f' % SoverBerror))
      #latex.DrawLatex(0.1,0.6,"#frac{DATA}{MC}="+('%.3f' % DoverMCvalue)+'#pm'+('%.3f' % DoverMCerror))
      latex.DrawLatex(0.1,0.8,"#frac{S}{B}="+str(SoverBvalue)+'#pm'+str(SoverBerror))
      latex.DrawLatex(0.1,0.6,"#frac{DATA}{MC}="+str(DoverMCvalue)+'#pm'+str(DoverMCerror))
      latex.Draw()
      canvas.Write()
    if histogram_name in ['HTT2D'] and cut_name in ["heptoptag_masscut_hists","NOheptoptag_NOmasscut_hists"]:
      added_histo.SetStats(kFALSE)
      added_histo_signal.SetStats(kFALSE)
      added_histo_background.SetStats(kFALSE)
      added_histo_SoverB.SetStats(kFALSE)
      added_histo_DoverMC.SetStats(kFALSE)
      added_histo_DmBoverS.SetStats(kFALSE)
      added_histo_DmB.SetStats(kFALSE)
      added_histo.Write()
      added_histo_signal.Write()
      added_histo_background.Write()
      added_histo_SoverB.Write()
      added_histo_DoverMC.Write()
      added_histo_DmBoverS.Write()
      added_histo_DmB.Write()
  added_mc.append(cut_sublist)
  added_mc_signal.append(cut_sublist_signal)
  added_mc_background.append(cut_sublist_background)
  added_mc_SoverB.append(cut_sublist_SoverB)
  added_mc_DoverMC.append(cut_sublist_DoverMC)
  added_mc_DmBoverS.append(cut_sublist_DmBoverS)
  added_mc_DmB.append(cut_sublist_DmB)
#structure: added_mc[histogram_name_index][cut_name_index]

added_mc[topmass_index][index_nn].Write()
added_mc[topmass_index][index_yy].Write()
added_mc[toppt_index][index_nn].Write()
added_mc[toppt_index][index_yy].Write()
#print added_mc[nevts_index][index_nn].Integral(),added_mc[nevts_index][index_nn_notpr].Integral()

#weight_nn=added_mc[nevts_index][index_nn_notpr].Integral()/added_mc[nevts_index][index_nn].Integral()
#weight_yy=added_mc[nevts_index][index_yy_notpr].Integral()/added_mc[nevts_index][index_yy].Integral()
#print weight_nn,weight_yy
#for histogram_name_index in range(len(histogram_names)):
  #added_mc[histogram_name_index][index_nn].Scale(weight_nn)
  #added_mc[histogram_name_index][index_yy].Scale(weight_nn)#.Scale(weight_yy)
#  added_mc[histogram_name_index][index_nn]=added_mc[histogram_name_index][index_nn_notpr]
#  added_mc[histogram_name_index][index_yy]=added_mc[histogram_name_index][index_yy_notpr]
  

#print 'NN data',input_histos_data[nevts_index][index_nn].GetBinContent(1),input_histos_data[nevts_index][index_nn].GetBinError(1)
#print 'NN mc',added_mc[nevts_index][index_nn].GetBinContent(1),added_mc[nevts_index][index_nn].GetBinError(1)
#print 'YY data',input_histos_data[nevts_index][index_yy].GetBinContent(1),input_histos_data[nevts_index][index_yy].GetBinError(1)
#print 'YY mc',added_mc[nevts_index][index_yy].GetBinContent(1),added_mc[nevts_index][index_yy].GetBinError(1)

#calculate efficiencies
print 'calculate efficiencies'
for histogram_name_index in [nevts_index,ptSFcount_index,pt2_index,histogram_names.index('N_pv'),histogram_names.index('N_pv200'),histogram_names.index('N_pv300'),histogram_names.index('N_pv400'),histogram_names.index('N_pv500'),histogram_names.index('N_pv600')]:
  histogram_name=histogram_names[histogram_name_index]
  DoverD=input_histos_data[histogram_name_index][index_yy].Clone(histogram_name+'_DoverD')
  DoverD.Divide(input_histos_data[histogram_name_index][index_yy],input_histos_data[histogram_name_index][index_nn],1,1,'B')
#  DoverD_2=input_histos_data[histogram_name_index][index_yy].Clone(histogram_name+'_DoverD')
#  DoverD_2.Divide(input_histos_data[histogram_name_index][index_yy],input_histos_data[histogram_name_index][index_nn],1,1,'B')
  MCoverMC=added_mc[histogram_name_index][index_yy].Clone(histogram_name+'_MCoverMC')
  MCoverMC.Divide(added_mc[histogram_name_index][index_yy],added_mc[histogram_name_index][index_nn],1,1,'B')
  SoverS=added_mc_signal[histogram_name_index][index_yy].Clone(histogram_name+'_SoverS')
  SoverS.Divide(added_mc_signal[histogram_name_index][index_yy],added_mc_signal[histogram_name_index][index_nn],1,1,'B') 
  BoverB=added_mc_background[histogram_name_index][index_yy].Clone(histogram_name+'_BoverB')
  BoverB.Divide(added_mc_background[histogram_name_index][index_yy],added_mc_background[histogram_name_index][index_nn],1,1,'B')
  DmBoverDmB=input_histos_data[histogram_name_index][index_yy].Clone(histogram_name+'_DmBoverDmB')
  DmBoverDmB.Add(added_mc_background[histogram_name_index][index_yy],-1.0)
  DmBnn=input_histos_data[histogram_name_index][index_nn].Clone(histogram_name+'_DmBnn')
  DmBnn.Add(added_mc_background[histogram_name_index][index_nn],-1.0)
  DmBoverDmB.Divide(DmBoverDmB,DmBnn,1,1,'B')
  
  DoverD.SetLineWidth(2)
  MCoverMC.SetLineWidth(2)
  SoverS.SetLineWidth(2)
  BoverB.SetLineWidth(2)
  DmBoverDmB.SetLineWidth(2)
  DoverD.SetStats(kFALSE)
  MCoverMC.SetStats(kFALSE)
  SoverS.SetStats(kFALSE)
  BoverB.SetStats(kFALSE)
  DmBoverDmB.SetStats(kFALSE)
  DoverD.GetYaxis().SetTitle('HepTopTagger rate')
  MCoverMC.GetYaxis().SetTitle('HepTopTagger rate')
  SoverS.GetYaxis().SetTitle('HepTopTagger rate')
  BoverB.GetYaxis().SetTitle('HepTopTagger rate')
  DmBoverDmB.SetTitle('HepTopTagger rate')
  DoverD.GetYaxis().SetRangeUser(0,1)
  MCoverMC.GetYaxis().SetRangeUser(0,1)
  SoverS.GetYaxis().SetRangeUser(0,1)
  BoverB.GetYaxis().SetRangeUser(0,1)
  DmBoverDmB.GetYaxis().SetRangeUser(0,1)
  DoverD.Write()
  MCoverMC.Write()
  SoverS.Write()
  BoverB.Write()
  DmBoverDmB.Write()

#calculate SF
print 'calculate SF'
#SFbin_DoverD=input_histos_data[ptSFcount_index][index_yy].Clone('SFbin_DoverD')
#SFbin_DoverD.Divide(input_histos_data[ptSFcount_index][index_yy],input_histos_data[ptSFcount_index][index_nn],1,1,'B')
#SFbin_MCoverMC=added_mc[ptSFcount_index][index_yy].Clone('SFbin_MCoverMC')
#SFbin_MCoverMC.Divide(added_mc[ptSFcount_index][index_yy],added_mc[ptSFcount_index][index_nn],1,1,'B')
#SFbin_DmBoverDmB=added_mc_DmB[ptSFcount_index][index_yy].Clone('SFbin_DmBoverDmB')
#SFbin_DmBoverDmB.Divide(added_mc_DmB[ptSFcount_index][index_yy],added_mc_DmB[ptSFcount_index][index_nn],1,1,'B')
#SFbin_SoverS=added_mc_signal[ptSFcount_index][index_yy].Clone('SFbin_SoverS')
#SFbin_SoverS.Divide(added_mc_signal[ptSFcount_index][index_yy],added_mc_signal[ptSFcount_index][index_nn],1,1,'B')
#SFbin=SFbin_DoverD.Clone('SFbin')
#SFbin.Divide(SFbin_MCoverMC)
#SFbin_NoBkg=SFbin_DmBoverDmB.Clone('SFbin_NoBkg')
#SFbin_NoBkg.Divide(SFbin_SoverS)


[SFbin_DoverD,SFbin_MCoverMC,SFbin_DmBoverDmB,SFbin_SoverS,SFbin,SFbin_NoBkg]=scalefactor(input_histos_data,added_mc,added_mc_signal,added_mc_DmB,'')
data_sf=[input_histos_data[ptSFcount_index][index_yy].Clone(input_histos_data[ptSFcount_index][index_yy].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn].Clone(input_histos_data[ptSFcount_index][index_nn].GetName()+'_sf')]

#"eta0p5","eta2p4","eta0p5to1p0","eta1p0to2p4","eta0p5_HTT","eta2p4_HTT","eta0p5to1p0_HTT","eta1p0to2p4_HTT"

index_nn_eta0p5=cut_names.index("eta0p5")
index_yy_eta0p5=cut_names.index("eta0p5_HTT")
index_nn_eta2p4=cut_names.index("eta2p4")
index_yy_eta2p4=cut_names.index("eta2p4_HTT")
index_nn_eta0p5to1p0=cut_names.index("eta0p5to1p0")
index_yy_eta0p5to1p0=cut_names.index("eta0p5to1p0_HTT")
index_nn_eta1p0to2p4=cut_names.index("eta1p0to2p4")
index_yy_eta1p0to2p4=cut_names.index("eta1p0to2p4_HTT")
index_nn_eta1p0=cut_names.index("eta1p0")
index_yy_eta1p0=cut_names.index("eta1p0_HTT")

index_nn_eta1p0_nsub=cut_names.index("eta1p0")
index_yy_eta1p0_nsub=cut_names.index("eta1p0_HTT_nsub")
index_nn_eta1p0to2p4_nsub=cut_names.index("eta1p0to2p4")
index_yy_eta1p0to2p4_nsub=cut_names.index("eta1p0to2p4_HTT_nsub")

index_cutflow1_eta1p0=cut_names.index("cutflow_mass_eta1p0")
index_cutflow1_eta1p0to2p4=cut_names.index("cutflow_mass_eta1p0to2p4")
index_cutflow2_eta1p0=cut_names.index("cutflow_mass_htt_eta1p0")
index_cutflow2_eta1p0to2p4=cut_names.index("cutflow_mass_htt_eta1p0to2p4")
index_cutflow3_eta1p0=cut_names.index("cutflow_mass_htt_nsub_eta1p0")
index_cutflow3_eta1p0to2p4=cut_names.index("cutflow_mass_htt_nsub_eta1p0to2p4")

sf_eta=[]

sf_eta.append(scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta0p5].Clone(input_histos_data[ptSFcount_index][index_yy_eta0p5].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta0p5].Clone(input_histos_data[ptSFcount_index][index_nn_eta0p5].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta0p5].Clone(added_mc[ptSFcount_index][index_yy_eta0p5].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta0p5].Clone(added_mc[ptSFcount_index][index_nn_eta0p5].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta0p5].Clone(added_mc_signal[ptSFcount_index][index_yy_eta0p5].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta0p5].Clone(added_mc_signal[ptSFcount_index][index_nn_eta0p5].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta0p5].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta0p5].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta0p5].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta0p5].GetName()+'_sf')],
'_sf_eta0p5'
)[5])

sf_eta.append(scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta0p5to1p0].Clone(input_histos_data[ptSFcount_index][index_yy_eta0p5to1p0].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta0p5to1p0].Clone(input_histos_data[ptSFcount_index][index_nn_eta0p5to1p0].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta0p5to1p0].Clone(added_mc[ptSFcount_index][index_yy_eta0p5to1p0].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta0p5to1p0].Clone(added_mc[ptSFcount_index][index_nn_eta0p5to1p0].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta0p5to1p0].Clone(added_mc_signal[ptSFcount_index][index_yy_eta0p5to1p0].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta0p5to1p0].Clone(added_mc_signal[ptSFcount_index][index_nn_eta0p5to1p0].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta0p5to1p0].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta0p5to1p0].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta0p5to1p0].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta0p5to1p0].GetName()+'_sf')],
'_sf_eta0p5to1p0'
)[5])

sf_eta.append(scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta1p0to2p4].Clone(input_histos_data[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4].Clone(input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta1p0to2p4].Clone(added_mc[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta1p0to2p4].Clone(added_mc[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta1p0to2p4].Clone(added_mc_signal[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta1p0to2p4].Clone(added_mc_signal[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta1p0to2p4].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta1p0to2p4].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
'_sf_eta1p0to2p41'
)[5])

sf_eta.append(scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta2p4].Clone(input_histos_data[ptSFcount_index][index_yy_eta2p4].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta2p4].Clone(input_histos_data[ptSFcount_index][index_nn_eta2p4].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta2p4].Clone(added_mc[ptSFcount_index][index_yy_eta2p4].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta2p4].Clone(added_mc[ptSFcount_index][index_nn_eta2p4].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta2p4].Clone(added_mc_signal[ptSFcount_index][index_yy_eta2p4].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta2p4].Clone(added_mc_signal[ptSFcount_index][index_nn_eta2p4].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta2p4].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta2p4].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta2p4].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta2p4].GetName()+'_sf')],
'_sf_eta2p4'
)[5])





sf_eta1p0to2p4=scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta1p0to2p4].Clone(input_histos_data[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4].Clone(input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta1p0to2p4].Clone(added_mc[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta1p0to2p4].Clone(added_mc[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta1p0to2p4].Clone(added_mc_signal[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta1p0to2p4].Clone(added_mc_signal[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta1p0to2p4].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta1p0to2p4].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta1p0to2p4].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta1p0to2p4].GetName()+'_sf')],
'_sf_eta1p0to2p4'
)[5]

sf_eta1p0=scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta1p0].Clone(input_histos_data[ptSFcount_index][index_yy_eta1p0].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta1p0].Clone(input_histos_data[ptSFcount_index][index_nn_eta1p0].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta1p0].Clone(added_mc[ptSFcount_index][index_yy_eta1p0].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta1p0].Clone(added_mc[ptSFcount_index][index_nn_eta1p0].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta1p0].Clone(added_mc_signal[ptSFcount_index][index_yy_eta1p0].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta1p0].Clone(added_mc_signal[ptSFcount_index][index_nn_eta1p0].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta1p0].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta1p0].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta1p0].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta1p0].GetName()+'_sf')],
'_sf_eta1p0'
)[5]

sf_eta1p0_nsub=scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta1p0_nsub].Clone(input_histos_data[ptSFcount_index][index_yy_eta1p0_nsub].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta1p0_nsub].Clone(input_histos_data[ptSFcount_index][index_nn_eta1p0_nsub].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta1p0_nsub].Clone(added_mc[ptSFcount_index][index_yy_eta1p0_nsub].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta1p0_nsub].Clone(added_mc[ptSFcount_index][index_nn_eta1p0_nsub].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta1p0_nsub].Clone(added_mc_signal[ptSFcount_index][index_yy_eta1p0_nsub].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta1p0_nsub].Clone(added_mc_signal[ptSFcount_index][index_nn_eta1p0_nsub].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta1p0_nsub].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta1p0_nsub].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta1p0_nsub].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta1p0_nsub].GetName()+'_sf')],
'_sf_eta1p0_nsub'
)[5]

sf_eta1p0to2p4_nsub=scalefactor2(
  [input_histos_data[ptSFcount_index][index_yy_eta1p0to2p4_nsub].Clone(input_histos_data[ptSFcount_index][index_yy_eta1p0to2p4_nsub].GetName()+'_sf'),input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4_nsub].Clone(input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4_nsub].GetName()+'_sf')],
[added_mc[ptSFcount_index][index_yy_eta1p0to2p4_nsub].Clone(added_mc[ptSFcount_index][index_yy_eta1p0to2p4_nsub].GetName()+'_sf'),added_mc[ptSFcount_index][index_nn_eta1p0to2p4_nsub].Clone(added_mc[ptSFcount_index][index_nn_eta1p0to2p4_nsub].GetName()+'_sf')],
[added_mc_signal[ptSFcount_index][index_yy_eta1p0to2p4_nsub].Clone(added_mc_signal[ptSFcount_index][index_yy_eta1p0to2p4_nsub].GetName()+'_sf'),added_mc_signal[ptSFcount_index][index_nn_eta1p0to2p4_nsub].Clone(added_mc_signal[ptSFcount_index][index_nn_eta1p0to2p4_nsub].GetName()+'_sf')],
[added_mc_DmB[ptSFcount_index][index_yy_eta1p0to2p4_nsub].Clone(added_mc_DmB[ptSFcount_index][index_yy_eta1p0to2p4_nsub].GetName()+'_sf'),added_mc_DmB[ptSFcount_index][index_nn_eta1p0to2p4_nsub].Clone(added_mc_DmB[ptSFcount_index][index_nn_eta1p0to2p4_nsub].GetName()+'_sf')],
'_sf_eta1p0to2p4_nsub'
)[5]


index_cutflow1_eta1p0=cut_names.index("cutflow_mass_eta1p0")
index_cutflow1_eta1p0to2p4=cut_names.index("cutflow_mass_eta1p0to2p4")
index_cutflow2_eta1p0=cut_names.index("cutflow_mass_htt_eta1p0")
index_cutflow2_eta1p0to2p4=cut_names.index("cutflow_mass_htt_eta1p0to2p4")
index_cutflow3_eta1p0=cut_names.index("cutflow_mass_htt_nsub_eta1p0")
index_cutflow3_eta1p0to2p4=cut_names.index("cutflow_mass_htt_nsub_eta1p0to2p4")

#cutflow-like SFs
sf_cutflow1_eta1p0=scalefactor2(
[input_histos_data[ptSFcount_index][index_cutflow1_eta1p0] , input_histos_data[ptSFcount_index][index_nn_eta1p0]],
[added_mc         [ptSFcount_index][index_cutflow1_eta1p0] , added_mc         [ptSFcount_index][index_nn_eta1p0]],
[added_mc_signal  [ptSFcount_index][index_cutflow1_eta1p0] , added_mc_signal  [ptSFcount_index][index_nn_eta1p0]],
[added_mc_DmB     [ptSFcount_index][index_cutflow1_eta1p0] , added_mc_DmB     [ptSFcount_index][index_nn_eta1p0]],
'_sf_cutflow1_eta1p0'
)[5]
sf_cutflow2_eta1p0=scalefactor2(
[input_histos_data[ptSFcount_index][index_cutflow2_eta1p0] , input_histos_data[ptSFcount_index][index_cutflow1_eta1p0]],
[added_mc         [ptSFcount_index][index_cutflow2_eta1p0] , added_mc         [ptSFcount_index][index_cutflow1_eta1p0]],
[added_mc_signal  [ptSFcount_index][index_cutflow2_eta1p0] , added_mc_signal  [ptSFcount_index][index_cutflow1_eta1p0]],
[added_mc_DmB     [ptSFcount_index][index_cutflow2_eta1p0] , added_mc_DmB     [ptSFcount_index][index_cutflow1_eta1p0]],
'_sf_cutflow2_eta1p0'
)[5]
sf_cutflow3_eta1p0=scalefactor2(
[input_histos_data[ptSFcount_index][index_cutflow3_eta1p0] , input_histos_data[ptSFcount_index][index_cutflow2_eta1p0]],
[added_mc         [ptSFcount_index][index_cutflow3_eta1p0] , added_mc         [ptSFcount_index][index_cutflow2_eta1p0]],
[added_mc_signal  [ptSFcount_index][index_cutflow3_eta1p0] , added_mc_signal  [ptSFcount_index][index_cutflow2_eta1p0]],
[added_mc_DmB     [ptSFcount_index][index_cutflow3_eta1p0] , added_mc_DmB     [ptSFcount_index][index_cutflow2_eta1p0]],
'_sf_cutflow3_eta1p0'
)[5]

sf_cutflow1_eta1p0to2p4=scalefactor2(
[input_histos_data[ptSFcount_index][index_cutflow1_eta1p0to2p4] , input_histos_data[ptSFcount_index][index_nn_eta1p0to2p4]],
[added_mc         [ptSFcount_index][index_cutflow1_eta1p0to2p4] , added_mc         [ptSFcount_index][index_nn_eta1p0to2p4]],
[added_mc_signal  [ptSFcount_index][index_cutflow1_eta1p0to2p4] , added_mc_signal  [ptSFcount_index][index_nn_eta1p0to2p4]],
[added_mc_DmB     [ptSFcount_index][index_cutflow1_eta1p0to2p4] , added_mc_DmB     [ptSFcount_index][index_nn_eta1p0to2p4]],
'_sf_cutflow1_eta1p0to2p4'
)[5]
sf_cutflow2_eta1p0to2p4=scalefactor2(
[input_histos_data[ptSFcount_index][index_cutflow2_eta1p0to2p4] , input_histos_data[ptSFcount_index][index_cutflow1_eta1p0to2p4]],
[added_mc         [ptSFcount_index][index_cutflow2_eta1p0to2p4] , added_mc         [ptSFcount_index][index_cutflow1_eta1p0to2p4]],
[added_mc_signal  [ptSFcount_index][index_cutflow2_eta1p0to2p4] , added_mc_signal  [ptSFcount_index][index_cutflow1_eta1p0to2p4]],
[added_mc_DmB     [ptSFcount_index][index_cutflow2_eta1p0to2p4] , added_mc_DmB     [ptSFcount_index][index_cutflow1_eta1p0to2p4]],
'_sf_cutflow2_eta1p0to2p4'
)[5]
sf_cutflow3_eta1p0to2p4=scalefactor2(
[input_histos_data[ptSFcount_index][index_cutflow3_eta1p0to2p4] , input_histos_data[ptSFcount_index][index_cutflow2_eta1p0to2p4]],
[added_mc         [ptSFcount_index][index_cutflow3_eta1p0to2p4] , added_mc         [ptSFcount_index][index_cutflow2_eta1p0to2p4]],
[added_mc_signal  [ptSFcount_index][index_cutflow3_eta1p0to2p4] , added_mc_signal  [ptSFcount_index][index_cutflow2_eta1p0to2p4]],
[added_mc_DmB     [ptSFcount_index][index_cutflow3_eta1p0to2p4] , added_mc_DmB     [ptSFcount_index][index_cutflow2_eta1p0to2p4]],
'_sf_cutflow3_eta1p0to2p4'
)[5]


print 'sf_eta1p0'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_eta1p0.GetBinContent(i),"%.2f" % sf_eta1p0.GetBinError(i)
print 'sf_eta1p0to2p4'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_eta1p0to2p4.GetBinContent(i),"%.2f" % sf_eta1p0to2p4.GetBinError(i)
print 'sf_eta1p0_nsub'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_eta1p0_nsub.GetBinContent(i),"%.2f" % sf_eta1p0_nsub.GetBinError(i)
print 'sf_eta1p0to2p4_nsub'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_eta1p0to2p4_nsub.GetBinContent(i),"%.2f" % sf_eta1p0to2p4_nsub.GetBinError(i)
print '\n'
print 'sf_cutflow1_eta1p0'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_cutflow1_eta1p0.GetBinContent(i),"%.2f" % sf_cutflow1_eta1p0.GetBinError(i)
print 'sf_cutflow2_eta1p0'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_cutflow2_eta1p0.GetBinContent(i),"%.2f" % sf_cutflow2_eta1p0.GetBinError(i)
print 'sf_cutflow3_eta1p0'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_cutflow3_eta1p0.GetBinContent(i),"%.2f" % sf_cutflow3_eta1p0.GetBinError(i)
print '\n'
print 'sf_cutflow1_eta1p0to2p4'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_cutflow1_eta1p0to2p4.GetBinContent(i),"%.2f" % sf_cutflow1_eta1p0to2p4.GetBinError(i)
print 'sf_cutflow2_eta1p0to2p4'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_cutflow2_eta1p0to2p4.GetBinContent(i),"%.2f" % sf_cutflow2_eta1p0to2p4.GetBinError(i)
print 'sf_cutflow3_eta1p0to2p4'
for i in range(2,len(SF_bins)):
  print ScaleFactorsNames[i-1],"%.2f" % sf_cutflow3_eta1p0to2p4.GetBinContent(i),"%.2f" % sf_cutflow3_eta1p0to2p4.GetBinError(i)
  #added_mc.append(cut_sublist)
  #added_mc_signal.append(cut_sublist_signal)
  #added_mc_background.append(cut_sublist_background)
  #added_mc_SoverB.append(cut_sublist_SoverB)
  #added_mc_DoverMC.append(cut_sublist_DoverMC)
  #added_mc_DmBoverS.append(cut_sublist_DmBoverS)
  #added_mc_DmB.append(cut_sublist_DmB)


#def scalefactor2(data,mc,signal,dmb,title):

  #return [SFbin_DoverD,SFbin_MCoverMC,SFbin_DmBoverDmB,SFbin_SoverS,SFbin,SFbin_NoBkg]

mc_sf=[]
for process_name_index in range(0,len(process_names_mc)):
  mc_sf_tmp=[input_merged_mc[process_name_index][ptSFcount_index][index_yy].Clone(input_merged_mc[process_name_index][ptSFcount_index][index_yy].GetName()+'_sf'),input_merged_mc[process_name_index][ptSFcount_index][index_nn].Clone(input_merged_mc[process_name_index][ptSFcount_index][index_nn].GetName()+'_sf')]
  mc_sf.append(mc_sf_tmp)
#structure: mc_sf[process_name_index][yy,nn]


mc_sf_ttbar_modup=copy_sf_lists(mc_sf,'ttbar_varup')
mc_sf_ttbar_moddown=copy_sf_lists(mc_sf,'ttbar_vardown')
norm_up=[]
norm_down=[]
for i in range(1,len(SF_bins)):
  norm_up.append([])
  norm_down.append([])
for process_name_index in range(0,len(process_names_mc)):
  process_name=process_names_mc[process_name_index]
  process_name_good=process_name.replace('+','_').replace(',','_').replace('-','_')
  if process_name in process_names_ttbar:
    mc_sf_ttbar_modup[process_name_index][0].Scale(1.15)
    mc_sf_ttbar_modup[process_name_index][1].Scale(1.15)
    mc_sf_ttbar_moddown[process_name_index][0].Scale(0.85)
    mc_sf_ttbar_moddown[process_name_index][1].Scale(0.85)
  if process_name in process_names_bkgnottbar:
    #varup
    mc_sf_modup=copy_sf_lists(mc_sf,process_name_good+'_varup')
    mc_sf_modup[process_name_index][0].Scale(1.5)
    mc_sf_modup[process_name_index][1].Scale(1.5)
    added_modup=getadded(mc_sf_modup,data_sf,process_name_good+'_varup')
    sf_modup=scalefactor2(data_sf,added_modup[0],added_modup[2],added_modup[3],process_name_good+'_varup')
    #vardown
    mc_sf_moddown=copy_sf_lists(mc_sf,process_name_good+'_vardown')
    mc_sf_moddown[process_name_index][0].Scale(0.5)
    mc_sf_moddown[process_name_index][1].Scale(0.5)
    added_moddown=getadded(mc_sf_moddown,data_sf,process_name_good+'_vardown')
    sf_moddown=scalefactor2(data_sf,added_moddown[0],added_moddown[2],added_moddown[3],process_name_good+'_vardown')
    #differences
    #print process_name_good
    #print 'up'
    sf_diff_histo_up=sf_modup[5].Clone('sf_diff_histo_up_'+process_name_good)
    sf_diff_histo_up.Add(SFbin_NoBkg,-1.0)
    for i in range(1,len(SF_bins)):
      variation=sf_diff_histo_up.GetBinContent(i)
      #print variation
      if variation>0:
	norm_up[i-1].append(variation)
      else:
	norm_down[i-1].append(variation)
    #print 'down'
    sf_diff_histo_down=sf_moddown[5].Clone('sf_diff_histo_down_'+process_name_good)
    sf_diff_histo_down.Add(SFbin_NoBkg,-1.0)
    for i in range(1,len(SF_bins)):
      variation=sf_diff_histo_down.GetBinContent(i)
      #print variation
      if variation>0:
	norm_up[i-1].append(variation)
      else:
	norm_down[i-1].append(variation)
added_ttbar_modup=getadded(mc_sf_ttbar_modup,data_sf,'ttbar_varup')
sf_ttbar_modup=scalefactor2(data_sf,added_ttbar_modup[0],added_ttbar_modup[2],added_ttbar_modup[3],'ttbar_varup')
added_ttbar_moddown=getadded(mc_sf_ttbar_moddown,data_sf,'ttbar_vardown')
sf_ttbar_moddown=scalefactor2(data_sf,added_ttbar_moddown[0],added_ttbar_moddown[2],added_ttbar_moddown[3],'ttbar_vardown')
#print 'ttbar'
sf_diff_histo_ttbar_up=sf_ttbar_modup[5].Clone('sf_diff_histo_up_ttbar')
sf_diff_histo_ttbar_up.Add(SFbin_NoBkg,-1.0)
sf_diff_histo_ttbar_down=sf_ttbar_moddown[5].Clone('sf_diff_histo_down_ttbar')
sf_diff_histo_ttbar_down.Add(SFbin_NoBkg,-1.0)
#print 'up'
for i in range(1,len(SF_bins)):
  variation= sf_diff_histo_ttbar_up.GetBinContent(i)
  #print variation
  if variation>0:
    norm_up[i-1].append(variation)
  else:
    norm_down[i-1].append(variation)
#print 'down'
for i in range(1,len(SF_bins)):
  variation= sf_diff_histo_ttbar_down.GetBinContent(i)
  #print variation
  if variation>0:
    norm_up[i-1].append(variation)
  else:
    norm_down[i-1].append(variation)
#print norm_up
#print norm_down
total_norm_up=[]
total_norm_down=[]
SFbin_NoBkg_list=[]
for i in range(1,len(SF_bins)):
  norm_up_tmp=0
  for j in norm_up[i-1]:
    norm_up_tmp=norm_up_tmp+j*j
  total_norm_up.append(sqrt(norm_up_tmp))
  norm_down_tmp=0
  for j in norm_down[i-1]:
    norm_down_tmp=norm_down_tmp+j*j
  total_norm_down.append(sqrt(norm_down_tmp))
  SFbin_NoBkg_list.append(SFbin_NoBkg.GetBinContent(i))
#print total_norm_up
#print total_norm_down
#print '\n\n'


#SFbin_NoBkg_list
systematic_err=TGraphAsymmErrors(3,array('d',[0.5,1.5,2.5]),array('d',SFbin_NoBkg_list[1:]),array('d',[0.5]*3),array('d',[0.5]*3),array('d',total_norm_down[1:]),array('d',total_norm_up[1:]))
systematic_err.Write()
#def scalefactor2(data,mc,signal,dmb,title):
#  return [SFbin_DoverD,SFbin_MCoverMC,SFbin_DmBoverDmB,SFbin_SoverS,SFbin,SFbin_NoBkg]

#def getadded(mc_sf_list,data_sf_list,title):
#  return [allmc,allbkg,allsignal,alldatambkg]
  
 



 
#  process_name=process_names_mc[process_name_index]
  
  
SFbin_yn_over_nn=added_mc_DoverMC[ptSFcount_index][index_yn].Clone('SFbin_yn_over_nn')
SFbin_ny_over_nn=added_mc_DoverMC[ptSFcount_index][index_ny].Clone('SFbin_ny_over_nn')
SFbin_yy_over_nn=added_mc_DoverMC[ptSFcount_index][index_yy].Clone('SFbin_yy_over_nn')
SFbinNoBkg_yy_over_nn=added_mc_DmBoverS[ptSFcount_index][index_yy].Clone('SFbinNoBkg_yy_over_nn')
SFbin_yn_ny_over_yn=added_mc_DoverMC[ptSFcount_index][index_yn_ny].Clone('SFbin_yn_ny_over_yn')
SFbin_yn_over_nn.Divide(added_mc_DoverMC[ptSFcount_index][index_nn])
SFbin_ny_over_nn.Divide(added_mc_DoverMC[ptSFcount_index][index_nn])
SFbin_yy_over_nn.Divide(added_mc_DoverMC[ptSFcount_index][index_nn])
SFbinNoBkg_yy_over_nn.Divide(added_mc_DmBoverS[ptSFcount_index][index_nn])
SFbin_yn_ny_over_yn.Divide(added_mc_DoverMC[ptSFcount_index][index_yn])
SF_yn_over_nn=added_mc_DoverMC[nevts_index][index_yn].Clone('SF_yn_over_nn')
SF_ny_over_nn=added_mc_DoverMC[nevts_index][index_ny].Clone('SF_ny_over_nn')
SF_yy_over_nn=added_mc_DoverMC[nevts_index][index_yy].Clone('SF_yy_over_nn')
SFNoBkg_yy_over_nn=added_mc_DmBoverS[nevts_index][index_yy].Clone('SFNoBkg_yy_over_nn')
SF_yn_ny_over_yn=added_mc_DoverMC[nevts_index][index_yn_ny].Clone('SF_yn_ny_over_yn')
SF_yn_over_nn.Divide(added_mc_DoverMC[nevts_index][index_nn])
SF_ny_over_nn.Divide(added_mc_DoverMC[nevts_index][index_nn])
SF_yy_over_nn.Divide(added_mc_DoverMC[nevts_index][index_nn])
SFNoBkg_yy_over_nn.Divide(added_mc_DmBoverS[nevts_index][index_nn])
SF_yn_ny_over_yn.Divide(added_mc_DoverMC[nevts_index][index_yn])
SF_string_base='#left|#frac{DATA}{MC}#right|_{%s}=%.3f#pm%.3f'
DoMC_string_base='#left|#frac{DATA}{MC}#right|_{%s}=%.3f#pm%.3f'
DoMC_nn_string=DoMC_string_base%('No cuts',added_mc_DoverMC[nevts_index][index_nn].GetBinContent(1),added_mc_DoverMC[nevts_index][index_nn].GetBinError(1))
DoMC_yn_string=DoMC_string_base%('HTT no mass',added_mc_DoverMC[nevts_index][index_yn].GetBinContent(1),added_mc_DoverMC[nevts_index][index_yn].GetBinError(1))
DoMC_ny_string=DoMC_string_base%('mass only',added_mc_DoverMC[nevts_index][index_ny].GetBinContent(1),added_mc_DoverMC[nevts_index][index_ny].GetBinError(1))
DoMC_yy_string=DoMC_string_base%('HTT with mass',added_mc_DoverMC[nevts_index][index_yy].GetBinContent(1),added_mc_DoverMC[nevts_index][index_yy].GetBinError(1))
DoMC_yn_ny_string=DoMC_string_base%('HTT && mass',added_mc_DoverMC[nevts_index][index_yn_ny].GetBinContent(1),added_mc_DoverMC[nevts_index][index_yn_ny].GetBinError(1))
DoMCcanvas=TCanvas('Scale_Factors')
DoMClatex=TLatex()
DoMClatex.DrawLatex(0.02,0.8,DoMC_nn_string)
DoMClatex.DrawLatex(0.52,0.8,DoMC_yy_string)
DoMClatex.DrawLatex(0.02,0.5,DoMC_yn_string)
DoMClatex.DrawLatex(0.52,0.5,DoMC_ny_string)
DoMClatex.DrawLatex(0.02,0.2,DoMC_yn_ny_string)
DoMClatex.Draw()
DoMCcanvas.Write()
SFbinFS_yn_over_nn=TH1F('SFbinFS_yn_over_nn','Binned SF #frac{HTT, no mass cut}{no HTT, no mass cut};p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
SFbinFS_ny_over_nn=TH1F('SFbinFS_ny_over_nn','Binned SF #frac{no HTT, mass cut}{no HTT, no mass cut};p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
SFbinFS_yy_over_nn=TH1F('SFbinFS_yy_over_nn','HepTopTagger scale factor;p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
SFNoBkgbinFS_yy_over_nn=TH1F('SFNoBkgbinFS_yy_over_nn','HepTopTagger scale factor;p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
SFbinFS_yn_ny_over_yn=TH1F('SFbinFS_yn_ny_over_yn','Binned SF #frac{HTT, mass cut}{HTT, no mass cut};p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
SFbinFS=TH1F('SFbinFS','HepTopTagger scale factor;p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
SFbinFS_NoBkg=TH1F('SFbinFS_NoBkg_2','HepTopTagger scale factor;p_{T} range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)

def makeSFbinFS(_SFbin,title):
  _SFbinFS=TH1F('SFbinFS_'+title,'Binned SF;#eta range [GeV];SF',len(SF_bins)-2,0,len(SF_bins)-2)
  for i in range(2,len(SF_bins)):
    _SFbinFS.SetBinContent(i-1,_SFbin.GetBinContent(i))
    _SFbinFS.SetBinError(i-1,_SFbin.GetBinError(i))
    _SFbinFS.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  _SFbinFS.GetXaxis().SetLabelSize(0.07)
  _SFbinFS.SetStats(kFALSE)
  _SFbinFS.SetLineWidth(2)
  return _SFbinFS
  
#etabins_names=["eta0p5","eta2p4","eta0p5to1p0","eta1p0to2p4"]
etabins_names=["eta0p5","eta0p5to1p0","eta1p0to2p4","eta2p4"]
SFbinFS_eta=[]
for i in range(len(sf_eta)):
  sf_eta[i].Write()
  SFbinFS_eta.append(makeSFbinFS(sf_eta[i],'SFbinFS_'+etabins_names[i]))
  SFbinFS_eta[-1].Write()

SFetabinFS_eta=[]
for pt_bin in range(2,len(SF_bins)):
  title=str(SF_bins[pt_bin-1])
  _SFetabinFS=TH1F('SFbinFS_'+title,'Binned SF;p_{T} range [GeV];SF',len(SF_etabins),0,len(SF_etabins))
  for eta_bin in range(len(SF_etabins)):
    _SFetabinFS.SetBinContent(eta_bin+1,SFbinFS_eta[eta_bin].GetBinContent(pt_bin-1))
    _SFetabinFS.SetBinError(eta_bin+1,SFbinFS_eta[eta_bin].GetBinError(pt_bin-1))
    _SFetabinFS.GetXaxis().SetBinLabel(eta_bin+1,ScaleFactorsEtaNames[eta_bin])
  SFetabinFS_eta.append(_SFetabinFS)
  SFetabinFS_eta[-1].SetLineWidth(2)
  SFetabinFS_eta[-1].Write()    

for i in range(2,len(SF_bins)):
  SFbinFS_yn_over_nn.SetBinContent(i-1,SFbin_yn_over_nn.GetBinContent(i))
  SFbinFS_yn_over_nn.SetBinError(i-1,SFbin_yn_over_nn.GetBinError(i))
  SFbinFS_yn_over_nn.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  SFbinFS_ny_over_nn.SetBinContent(i-1,SFbin_ny_over_nn.GetBinContent(i))
  SFbinFS_ny_over_nn.SetBinError(i-1,SFbin_ny_over_nn.GetBinError(i))
  SFbinFS_ny_over_nn.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  SFbinFS_yy_over_nn.SetBinContent(i-1,SFbin_yy_over_nn.GetBinContent(i))
  SFbinFS_yy_over_nn.SetBinError(i-1,SFbin_yy_over_nn.GetBinError(i))
  SFbinFS_yy_over_nn.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  #print ScaleFactorsNames[i-1],SFbin_yy_over_nn.GetBinContent(i),SFbin_yy_over_nn.GetBinError(i)
  SFNoBkgbinFS_yy_over_nn.SetBinContent(i-1,SFbinNoBkg_yy_over_nn.GetBinContent(i))
  SFNoBkgbinFS_yy_over_nn.SetBinError(i-1,SFbinNoBkg_yy_over_nn.GetBinError(i))
  SFNoBkgbinFS_yy_over_nn.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  #print ScaleFactorsNames[i-1],SFNoBkgbinFS_yy_over_nn.GetBinContent(i),SFNoBkgbinFS_yy_over_nn.GetBinError(i)
  SFbinFS_yn_ny_over_yn.SetBinContent(i-1,SFbin_yn_ny_over_yn.GetBinContent(i))
  SFbinFS_yn_ny_over_yn.SetBinError(i-1,SFbin_yn_ny_over_yn.GetBinError(i))
  SFbinFS_yn_ny_over_yn.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  SFbinFS.SetBinContent(i-1,SFbin.GetBinContent(i))
  SFbinFS.SetBinError(i-1,SFbin.GetBinError(i))
  SFbinFS.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  #print ScaleFactorsNames[i-1],SFbin.GetBinContent(i),SFbin.GetBinError(i)
  SFbinFS_NoBkg.SetBinContent(i-1,SFbin_NoBkg.GetBinContent(i))
  SFbinFS_NoBkg.SetBinError(i-1,SFbin_NoBkg.GetBinError(i))
  SFbinFS_NoBkg.GetXaxis().SetBinLabel(i-1,ScaleFactorsNames[i-1])
  print ScaleFactorsNames[i-1],SFbin_NoBkg.GetBinContent(i),SFbin_NoBkg.GetBinError(i)
  
#gStyle.SetOptStat(0)
SFbinFS_yn_over_nn.GetXaxis().SetLabelSize(0.07)
SFbinFS_ny_over_nn.GetXaxis().SetLabelSize(0.07)
SFbinFS_yy_over_nn.GetXaxis().SetLabelSize(0.07)
SFNoBkgbinFS_yy_over_nn.GetXaxis().SetLabelSize(0.07)
SFbinFS_yn_ny_over_yn.GetXaxis().SetLabelSize(0.07)
SFbinFS.GetXaxis().SetLabelSize(0.07)
SFbinFS_NoBkg.GetXaxis().SetLabelSize(0.07)
SFbinFS_yn_over_nn.SetStats(kFALSE)
SFbinFS_ny_over_nn.SetStats(kFALSE)
SFbinFS_yy_over_nn.SetStats(kFALSE)
SFNoBkgbinFS_yy_over_nn.SetStats(kFALSE)
SFbinFS_yn_ny_over_yn.SetStats(kFALSE)
SFbinFS.SetStats(kFALSE)
SFbinFS_NoBkg.SetStats(kFALSE)
SFbinFS_yn_over_nn.SetLineWidth(2)
SFbinFS_ny_over_nn.SetLineWidth(2)
SFbinFS_yy_over_nn.SetLineWidth(2)
SFNoBkgbinFS_yy_over_nn.SetLineWidth(2)
SFbinFS_yn_ny_over_yn.SetLineWidth(2)
SFbinFS.SetLineWidth(2)
SFbinFS_NoBkg.SetLineWidth(2)
SFbinFS_yn_over_nn.Write()
SFbinFS_ny_over_nn.Write()
SFbinFS_yy_over_nn.Write()
SFNoBkgbinFS_yy_over_nn.Write()
SFbinFS_yn_ny_over_yn.Write()


SFbinFS_NoBkg.GetXaxis().SetLabelSize(0.1)
SFbinFS_NoBkg.GetXaxis().SetTitleSize(0.06)
SFbinFS_NoBkg.GetXaxis().SetTitleOffset(1.1)
SFbinFS_NoBkg.GetYaxis().SetLabelSize(0.06)
SFbinFS_NoBkg.GetYaxis().SetTitleSize(0.06)
SFbinFS_NoBkg.GetYaxis().SetTitleOffset(1.1)
SFbinFS_NoBkg_c=TCanvas('SFbinFS_NoBkg')
SFbinFS_NoBkg_c.SetLeftMargin(0.15)
SFbinFS_NoBkg_c.SetRightMargin(0.05)
SFbinFS_NoBkg_c.SetBottomMargin(0.15)
SFbinFS_NoBkg_c.SetTopMargin(0.05)
SFbinFS_NoBkg.SetTitle('')
SFbinFS_NoBkg.Draw()
SFbinFS_NoBkg_c.Write()
SFbinFS.Write()
SFbinFS_NoBkg.Write()
sfcanvas=TCanvas('SF_canvas')
#sfcanvas=TCanvas('SF_canvas')
sfcanvas.Divide(2,2)
sfcanvas.GetPad(1).SetTopMargin(0.15)
sfcanvas.GetPad(2).SetTopMargin(0.15)
sfcanvas.GetPad(3).SetTopMargin(0.15)
sfcanvas.GetPad(4).SetTopMargin(0.15)

sfcanvas.cd(1)
SFbinFS_yn_over_nn.Draw()
sfcanvas.cd(2)
SFbinFS_ny_over_nn.Draw()
sfcanvas.cd(3)
SFbinFS_yy_over_nn.Draw()
sfcanvas.cd(4)
SFbinFS_yn_ny_over_yn.Draw()
sfcanvas.Write()

SFbinFS_NoBkg_canvas=TCanvas('SFbinFS_NoBkg_canvas')
systematic_err.SetFillStyle(3002)
systematic_err.SetFillColor(kOrange+7)
SFbinFS_NoBkg.Draw()
systematic_err.Draw('2')
SFbinFS_NoBkg_canvas.Write()
#SFbinFS_NoBkg_canvas.SaveAs('')


#print 'close file'
#outfile.Close()
#sys.exit('ok') 


#make legend
print 'make legend'
#legend=TLegend(0.8,0.2,0.999,0.93)
#legend.SetFillColor(kWhite)

#legend = TLegend(0.5,0.55,0.84,0.84,'HEPTopTagger',"brNDC")
legend = TLegend(0.6392529,0.3480872,0.94,0.8849879,'',"brNDC")#'HEP Top Tagger'
#legend = TLegend(0.65,0.35,0.94,0.8849879,'HEPTopTagger',"brNDC")
legend.SetBorderSize(0)
legend.SetTextFont(62)
legend.SetLineColor(1)
legend.SetLineStyle(1)
legend.SetLineWidth(1)
legend.SetFillColor(0)
legend.SetFillStyle(1001)

legend.AddEntry(input_histos_data[0][0],'Data','p')
for process_name_index in list(reversed(range(len(process_names_mc)))):
  legend.AddEntry(input_merged_mc[process_name_index][0][0],process_names_mc[process_name_index],'f')
#cmslabel=TLatex(0.3,0.87,"CMS Preliminary #sqrt{s} = 8TeV  19.7 fb^{-1}")
#cmslabel.SetNDC()
#cmslabel= TLatex(0.15,0.95,"#scale[1.0]{CMS Preliminary #sqrt{s} = 8 TeV, 19.7 fb^{-1}}");
cmslabel= TLatex(0.1637931,0.9122276,"CMS Preliminary #sqrt{s} = 8 TeV, 19.7 fb^{-1}");
cmslabel.SetNDC()
cmslabel.SetTextFont(42)
cmslabel.SetLineWidth(2)
cmslabel.SetTextSize(0.09079903)
cmslabelsim= TLatex(0.1637931,0.9122276,"CMS Simulation #sqrt{s} = 8 TeV");
cmslabelsim.SetNDC()
cmslabelsim.SetTextFont(42)
cmslabelsim.SetLineWidth(2)
cmslabelsim.SetTextSize(0.09079903)

cmslabel2= TLatex(0.1566092,0.9427966,"CMS Preliminary #sqrt{s} = 8 TeV, 19.7 fb^{-1}");
cmslabel2.SetNDC()
cmslabel2.SetTextFont(42)
cmslabel2.SetLineWidth(2)
cmslabel2.SetTextSize(0.05508475)
cmslabelsim2= TLatex(0.1566092,0.9427966,"CMS Simulation #sqrt{s} = 8 TeV");
cmslabelsim2.SetNDC()
cmslabelsim2.SetTextFont(42)
cmslabelsim2.SetLineWidth(2)
cmslabelsim2.SetTextSize(0.05508475)
#cmslabel.Draw()

uno=0.1810345
due=0.52
tre=0.63
quattro=0.8698547

infolabel=TPaveText(uno,due,tre,quattro,"NDC")
infolabel.SetBorderSize(0)
infolabel.SetTextFont(42)
infolabel.SetLineColor(1)
infolabel.SetLineStyle(1)
infolabel.SetLineWidth(1)
infolabel.SetFillColor(0)
infolabel.SetFillStyle(1001)
infolabel.SetTextAlign()
infolabel.AddText("HEP Top Tagger")
infolabel.AddText("CA R=1.5 |#eta|<2.4")
infolabel.AddText("p_{T}>200 GeV/c")
#infolabel.AddText("HEP W mass selection")
infolabel.AddText("t#bar{t} simulated with MADGRAPH")

infolabel_htt=TPaveText(uno,due,tre,quattro,"NDC")
infolabel_htt.SetBorderSize(0)
infolabel_htt.SetTextFont(42)
infolabel_htt.SetLineColor(1)
infolabel_htt.SetLineStyle(1)
infolabel_htt.SetLineWidth(1)
infolabel_htt.SetFillColor(0)
infolabel_htt.SetFillStyle(1001)
infolabel_htt.SetTextAlign()
infolabel_htt.AddText("HEP Top Tagger")
infolabel_htt.AddText("CA R=1.5 |#eta|<2.4")
infolabel_htt.AddText("p_{T}>200 GeV/c")
infolabel_htt.AddText("HEP W mass selection")
infolabel_htt.AddText("t#bar{t} simulated with MADGRAPH")

infolabel_300=TPaveText(uno,due,tre,quattro,"NDC")
infolabel_300.SetBorderSize(0)
infolabel_300.SetTextFont(42)
infolabel_300.SetLineColor(1)
infolabel_300.SetLineStyle(1)
infolabel_300.SetLineWidth(1)
infolabel_300.SetFillColor(0)
infolabel_300.SetFillStyle(1001)
infolabel_300.SetTextAlign()
infolabel_300.AddText("HEP Top Tagger")
infolabel_300.AddText("CA R=1.5 |#eta|<2.4")
infolabel_300.AddText("p_{T}>300 GeV/c")
infolabel_300.AddText("t#bar{t} simulated with MADGRAPH")

infolabel_400=TPaveText(uno,due,tre,quattro,"NDC")
infolabel_400.SetBorderSize(0)
infolabel_400.SetTextFont(42)
infolabel_400.SetLineColor(1)
infolabel_400.SetLineStyle(1)
infolabel_400.SetLineWidth(1)
infolabel_400.SetFillColor(0)
infolabel_400.SetFillStyle(1001)
infolabel_400.SetTextAlign()
infolabel_400.AddText("HEP Top Tagger")
infolabel_400.AddText("CA R=1.5 |#eta|<2.4")
infolabel_400.AddText("p_{T}>400 GeV/c")
infolabel_400.AddText("t#bar{t} simulated with MADGRAPH")

infolabel_htt300=TPaveText(uno,due,tre,quattro,"NDC")
infolabel_htt300.SetBorderSize(0)
infolabel_htt300.SetTextFont(42)
infolabel_htt300.SetLineColor(1)
infolabel_htt300.SetLineStyle(1)
infolabel_htt300.SetLineWidth(1)
infolabel_htt300.SetFillColor(0)
infolabel_htt300.SetFillStyle(1001)
infolabel_htt300.SetTextAlign()
infolabel_htt300.AddText("HEP Top Tagger")
infolabel_htt300.AddText("CA R=1.5 |#eta|<2.4")
infolabel_htt300.AddText("p_{T}>300 GeV/c")
infolabel_htt300.AddText("HEP W mass selection")
infolabel_htt300.AddText("t#bar{t} simulated with MADGRAPH")

infolabel_htt400=TPaveText(uno,due,tre,quattro,"NDC")
infolabel_htt400.SetBorderSize(0)
infolabel_htt400.SetTextFont(42)
infolabel_htt400.SetLineColor(1)
infolabel_htt400.SetLineStyle(1)
infolabel_htt400.SetLineWidth(1)
infolabel_htt400.SetFillColor(0)
infolabel_htt400.SetFillStyle(1001)
infolabel_htt400.SetTextAlign()
infolabel_htt400.AddText("HEP Top Tagger")
infolabel_htt400.AddText("CA R=1.5 |#eta|<2.4")
infolabel_htt400.AddText("p_{T}>400 GeV/c")
infolabel_htt400.AddText("HEP W mass selection")
infolabel_htt400.AddText("t#bar{t} simulated with MADGRAPH")

uno2d=0.1748148
due2d=0.7003484
tre2d=0.72
quattro2d=0.9100346

infolabel2d=TPaveText(uno2d,due2d,tre2d,quattro2d,"NDC")
infolabel2d.SetBorderSize(0)
infolabel2d.SetTextFont(42)
infolabel2d.SetLineColor(1)
infolabel2d.SetLineStyle(1)
infolabel2d.SetLineWidth(1)
infolabel2d.SetFillColor(0)
infolabel2d.SetFillStyle(1001)
infolabel2d.SetTextAlign()
infolabel2d.AddText("HEP Top Tagger")
infolabel2d.AddText("CA R=1.5 |#eta|<2.4")
infolabel2d.AddText("p_{T}>200 GeV/c")
#infolabel.AddText("HEP W mass selection")
infolabel2d.AddText("t#bar{t} simulated with MADGRAPH")

infolabel2d_300=TPaveText(uno2d,due2d,tre2d,quattro2d,"NDC")
infolabel2d_300.SetBorderSize(0)
infolabel2d_300.SetTextFont(42)
infolabel2d_300.SetLineColor(1)
infolabel2d_300.SetLineStyle(1)
infolabel2d_300.SetLineWidth(1)
infolabel2d_300.SetFillColor(0)
infolabel2d_300.SetFillStyle(1001)
infolabel2d_300.SetTextAlign()
infolabel2d_300.AddText("HEP Top Tagger")
infolabel2d_300.AddText("CA R=1.5 |#eta|<2.4")
infolabel2d_300.AddText("p_{T}>300 GeV/c")
infolabel2d_300.AddText("t#bar{t} simulated with MADGRAPH")

infolabel2d_400=TPaveText(uno2d,due2d,tre2d,quattro2d,"NDC")
infolabel2d_400.SetBorderSize(0)
infolabel2d_400.SetTextFont(42)
infolabel2d_400.SetLineColor(1)
infolabel2d_400.SetLineStyle(1)
infolabel2d_400.SetLineWidth(1)
infolabel2d_400.SetFillColor(0)
infolabel2d_400.SetFillStyle(1001)
infolabel2d_400.SetTextAlign()
infolabel2d_400.AddText("HEP Top Tagger")
infolabel2d_400.AddText("CA R=1.5 |#eta|<2.4")
infolabel2d_400.AddText("p_{T}>400 GeV/c")
infolabel2d_400.AddText("t#bar{t} simulated with MADGRAPH")

infolabel2d_nottbar=TPaveText(uno2d,due2d,tre2d,quattro2d,"NDC")
infolabel2d_nottbar.SetBorderSize(0)
infolabel2d_nottbar.SetTextFont(42)
infolabel2d_nottbar.SetLineColor(1)
infolabel2d_nottbar.SetLineStyle(1)
infolabel2d_nottbar.SetLineWidth(1)
infolabel2d_nottbar.SetFillColor(0)
infolabel2d_nottbar.SetFillStyle(1001)
infolabel2d_nottbar.SetTextAlign()
infolabel2d_nottbar.AddText("HEP Top Tagger")
infolabel2d_nottbar.AddText("CA R=1.5 |#eta|<2.4")
infolabel2d_nottbar.AddText("p_{T}>200 GeV/c")
infolabel2d_nottbar.AddText(" ")

#cutflow
print 'cutflow'
cutflow_names = ["nocutshists","nleptbtagshists","njetshists","probeselehists","htcuthists","etmisshists","NOheptoptag_NOmasscut_hists","heptoptag_masscut_hists"]
cutflow_positions = []
for i in range(len(cutflow_names)):
  cutflow_positions.append(cut_names.index(cutflow_names[i]))
  
cutflow_data=TH1F('cutflow_data','cutflow_data',len(cutflow_names),0,len(cutflow_names))
cutflow_mc=[]
cutflow_stack=THStack('cutflow_stack','')

for i in range(len(cutflow_names)):
  cutflow_name=cutflow_names[i]
  cutflow_position=cutflow_positions[i]
  cutflow_data.GetXaxis().SetBinLabel(i+1,cutflow_name)
  cutflow_data.SetBinContent(i+1,input_histos_data[nevts_index][cutflow_position].GetBinContent(1))
  #print cutflow_name
  #print 'data',input_histos_data[nevts_index][cutflow_position].GetBinContent(1)
  #print 'mc',added_mc[nevts_index][cutflow_position].GetBinContent(1)
  cutflow_data.SetBinError(i+1,input_histos_data[nevts_index][cutflow_position].GetBinError(1))
cutflow_data.SetLineWidth(2)
cutflow_data.SetLineColor(kBlack)
  
for process_name_index in range(len(process_names_mc)):
  process_name=process_names_mc[process_name_index]
  cutflow_tmp=TH1F('cutflow_'+process_name,'cutflow_'+process_name,len(cutflow_names),0,len(cutflow_names))
  for i in range(len(cutflow_names)):
    #added_histo.Add(input_merged_mc[process_name_index][histogram_name_index][cut_name_index])
    cutflow_name=cutflow_names[i]
    cutflow_position=cutflow_positions[i]
    cutflow_tmp.GetXaxis().SetBinLabel(i+1,cutflow_name)
    cutflow_tmp.SetBinContent(i+1,input_merged_mc[process_name_index][nevts_index][cutflow_position].GetBinContent(1))
    cutflow_tmp.SetBinError(i+1,input_merged_mc[process_name_index][nevts_index][cutflow_position].GetBinError(1))
  cutflow_mc.append(cutflow_tmp)
  
for process_name_index in range(len(process_names_mc)):
  cutflow_mc[process_name_index].SetFillColor(process_colors[process_name_index])
  cutflow_stack.Add(cutflow_mc[process_name_index])

cutflow_added_mc=cutflow_mc[0].Clone('cutflow_added_mc')
for process_name_index in range(1,len(process_names_mc)):
  cutflow_added_mc.Add(cutflow_mc[process_name_index])

#for i in range(1,len(cutflow_names)):
#  print 'data',cutflow_data.GetBinContent(i+1)
#  print 'mc_add',cutflow_added_mc.GetBinContent(i+1)
  
cutflow_pull=cutflow_data.Clone('cutflow_pull')
cutflow_pull.Divide(cutflow_added_mc)
cutflow_pull.Write()
cutflow_pull.SetStats(kFALSE)
cutflow_pull.SetTitle('')
cutflow_pull.GetYaxis().SetLabelSize(0.11)
cutflow_pull.GetYaxis().SetTitle("Data / MC")
cutflow_pull.GetYaxis().SetTitleSize(0.22)
cutflow_pull.GetYaxis().SetTitleOffset(0.23)
cutflow_pull.GetYaxis().SetRangeUser(0.9,1.2)
cutflow_pull.GetYaxis().SetNdivisions(7,2,0)
cutflow_pull.GetXaxis().SetLabelSize(0.22)
cutflow_pull.GetXaxis().SetTitle('')
cutflow_pull.GetXaxis().SetTitleSize(0.22)
cutflow_pull.GetXaxis().SetTitleOffset(0.9)
cutflow_pull.SetLineColor(kBlue+2)
cutflow_pull.SetLineWidth(2)

cutflow_canvas=TCanvas('cutflow_canvas')
cutflow_canvas.Divide(1,2)
cutflow_top_pad=cutflow_canvas.GetPad(1)
cutflow_bottom_pad=cutflow_canvas.GetPad(2)
cutflow_top_pad.SetPad( 0.0, 0.25, 1.0, 1.0 )
cutflow_bottom_pad.SetPad( 0.0, 0.0, 1.0, 0.25 )
cutflow_top_pad.SetTopMargin(0.07)
#cutflow_top_pad.SetBottomMargin(0.03)
cutflow_top_pad.SetBottomMargin(0.0)#0.013)
cutflow_top_pad.SetLeftMargin(0.12)
cutflow_top_pad.SetRightMargin(0.1)
#cutflow_bottom_pad.SetTopMargin(0.03)
cutflow_bottom_pad.SetTopMargin(0.0)
cutflow_bottom_pad.SetBottomMargin(0.42)
cutflow_bottom_pad.SetLeftMargin(0.12)
cutflow_bottom_pad.SetRightMargin(0.1)
cutflow_canvas.cd(1)
cutflow_stack.Draw('hist')
cutflow_data.Draw('same')
legend.Draw()
##stacked_mc[histogram_name_index].GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
#stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetTitle(histogram_yaxes[histogram_name_index])
cutflow_stack.GetXaxis().SetTitle('')
cutflow_stack.GetXaxis().SetLabelOffset(9999)
cutflow_stack.GetXaxis().SetLabelSize(0)
#stacked_mc[histogram_name_index][cut_name_index].SetTitle(histogram_descriptions[histogram_name_index])
cutflow_stack.GetYaxis().SetTitleSize(0.07)
cutflow_stack.GetYaxis().SetLabelSize(0.07)
cutflow_stack.GetYaxis().SetTitleOffset(0.9)
#    cmslabel.Draw()
cutflow_canvas.cd(2)
cutflow_pull.Draw()
cutflow_line1=TLine(cutflow_pull.GetXaxis().GetXmin(),1.0,cutflow_pull.GetXaxis().GetXmax(),1.0)
cutflow_line1.SetLineStyle(2)
cutflow_line1.Draw()
cutflow_line2=TLine(cutflow_pull.GetXaxis().GetXmin(),2.0,cutflow_pull.GetXaxis().GetXmax(),2.0)
cutflow_line2.SetLineStyle(2)
cutflow_line2.Draw()
cutflow_canvas.Write()

#2d plots pheno-style
print '2d plots pheno-style'
ptJetMin = 200.
massWindowLower = 0.85
massWindowUpper = 1.15
cutCondition2 = 0.35
cutCondition3 = 0.35
topmass = 172.3
wmass = 80.4
rmin = massWindowLower*wmass/topmass
rmax = massWindowUpper*wmass/topmass
rcenter = wmass/topmass
#print rmin,rmax
htt_cut_line=[]
htt_cut_line.append(TF1("htt_cut_line1","sqrt(1-[0]*[0]*(1+(tan(x))**2))",0,atan(sqrt((1-pow(cutCondition2,2))/pow(rmin,2)-1))))
htt_cut_line.append(TF1("htt_cut_line2","sqrt(1-[0]*[0]*(1+(tan(x))**2))",0,atan(sqrt((1-pow(cutCondition2,2))/pow(rmax,2)-1))))
htt_cut_line.append(TF1("htt_cut_line3","sqrt(1-[0]*[0]*(1+(tan(x))**2))",0,atan(sqrt((1-pow(cutCondition2,2))/pow(rcenter,2)-1))))
htt_cut_line.append(TF1("htt_cut_line4","sqrt(1-[0]*[0]*(1+1/(tan(x))**2))",atan(1/sqrt((1-pow(cutCondition3,2))/pow(rmin,2)-1)),1.5))
htt_cut_line.append(TF1("htt_cut_line5","sqrt(1-[0]*[0]*(1+1/(tan(x))**2))",atan(1/sqrt((1-pow(cutCondition3,2))/pow(rmax,2)-1)),1.5))
htt_cut_line.append(TF1("htt_cut_line6","sqrt(1-[0]*[0]*(1+1/(tan(x))**2))",atan(1/sqrt((1-pow(cutCondition3,2))/pow(rcenter,2)-1)),1.5))
htt_cut_line.append(TLine(0.2,rmin,1.3,rmin))
htt_cut_line.append(TLine(0.2,rmax,1.3,rmax))
htt_cut_line.append(TLine(0.2,rcenter,1.3,rcenter))
htt_cut_line.append(TLine(0.2,rmin,0.2,rmax))
htt_cut_line.append(TLine(1.3,rmin,1.3,rmax))
htt_cut_line.append(TLine(atan(sqrt((1-pow(cutCondition2,2))/pow(rmin,2)-1)),cutCondition2,atan(sqrt((1-pow(cutCondition2,2))/pow(rmax,2)-1)),cutCondition2))
htt_cut_line.append(TLine(atan(1/sqrt((1-pow(cutCondition3,2))/pow(rmin,2)-1)),cutCondition3,atan(1/sqrt((1-pow(cutCondition3,2))/pow(rmax,2)-1)),cutCondition3))
htt_cut_line[0].SetNpx(100000)
htt_cut_line[1].SetNpx(100000)
htt_cut_line[2].SetNpx(100000)
htt_cut_line[3].SetNpx(100000)
htt_cut_line[4].SetNpx(100000)
htt_cut_line[5].SetNpx(100000)
htt_cut_line[0].SetParameter(0,rmin)
htt_cut_line[0].SetLineColor(kBlack)
htt_cut_line[0].SetLineStyle(1)
htt_cut_line[0].SetLineWidth(2)
htt_cut_line[1].SetParameter(0,rmax)
htt_cut_line[1].SetLineColor(kBlack)
htt_cut_line[1].SetLineStyle(1)
htt_cut_line[1].SetLineWidth(2)
htt_cut_line[2].SetParameter(0,rcenter)
htt_cut_line[2].SetLineColor(kGray+2)
htt_cut_line[2].SetLineStyle(1)
htt_cut_line[2].SetLineWidth(1)
htt_cut_line[3].SetParameter(0,rmin)
htt_cut_line[3].SetLineColor(kBlack)
htt_cut_line[3].SetLineStyle(1)
htt_cut_line[3].SetLineWidth(2)
htt_cut_line[4].SetParameter(0,rmax)
htt_cut_line[4].SetLineColor(kBlack)
htt_cut_line[4].SetLineStyle(1)
htt_cut_line[4].SetLineWidth(2)
htt_cut_line[5].SetParameter(0,rcenter)
htt_cut_line[5].SetLineColor(kGray+2)
htt_cut_line[5].SetLineStyle(1)
htt_cut_line[5].SetLineWidth(1)
htt_cut_line[6].SetLineColor(kBlack)
htt_cut_line[6].SetLineStyle(1)
htt_cut_line[6].SetLineWidth(2)
htt_cut_line[7].SetLineColor(kBlack)
htt_cut_line[7].SetLineStyle(1)
htt_cut_line[7].SetLineWidth(2)
htt_cut_line[8].SetLineColor(kGray+2)
htt_cut_line[8].SetLineStyle(1)
htt_cut_line[8].SetLineWidth(1)
htt_cut_line[9].SetLineColor(kBlack)
htt_cut_line[9].SetLineStyle(1)
htt_cut_line[9].SetLineWidth(2)
htt_cut_line[10].SetLineColor(kBlack)
htt_cut_line[10].SetLineStyle(1)
htt_cut_line[10].SetLineWidth(2)
htt_cut_line[11].SetLineColor(kBlack)
htt_cut_line[11].SetLineStyle(1)
htt_cut_line[11].SetLineWidth(2)
htt_cut_line[12].SetLineColor(kBlack)
htt_cut_line[12].SetLineStyle(1)
htt_cut_line[12].SetLineWidth(2)

Pheno2DPlot=[]#=TCanvas('Pheno2DPlot')
index_200=cut_names.index("pt200hists")
index_250=cut_names.index("pt250hists")
index_300=cut_names.index("pt300hists")
index_350=cut_names.index("pt350hists")
index_400=cut_names.index("pt400hists")

Pheno2DInputList=[input_histos_data[htt2d_index][index_yy],input_histos_data[htt2d_index][index_nn],added_mc[htt2d_index][index_yy],added_mc_signal[htt2d_index][index_yy],added_mc_background[htt2d_index][index_yy],added_mc[htt2d_index][index_nn],added_mc_signal[htt2d_index][index_nn],added_mc_background[htt2d_index][index_nn],
#added_mc_signal[htt2d_index][index_matched],added_mc_background[htt2d_index][index_matched],
#added_mc_signal[htt2d_index][index_unmatched],added_mc_background[htt2d_index][index_unmatched],
#added_mc_signal[htt2d_index][index_matched_htt],added_mc_background[htt2d_index][index_matched_htt],
#added_mc_signal[htt2d_index][index_unmatched_htt],added_mc_background[htt2d_index][index_unmatched_htt],
#added_mc_signal[htt2d_index][index_matched_pt],added_mc_background[htt2d_index][index_matched_pt],
#added_mc_signal[htt2d_index][index_unmatched_pt],added_mc_background[htt2d_index][index_unmatched_pt],
#added_mc_signal[htt2d_index][index_matched_htt_pt],added_mc_background[htt2d_index][index_matched_htt_pt],
#added_mc_signal[htt2d_index][index_unmatched_htt_pt],added_mc_background[htt2d_index][index_unmatched_htt_pt],
]
Pheno2DInputList.append(added_mc_signal[htt2d_index][index_200])
Pheno2DInputList.append(added_mc_background[htt2d_index][index_200])
Pheno2DInputList.append(input_histos_data[htt2d_index][index_200])
Pheno2DInputList.append(added_mc_signal[htt2d_index][index_250])
Pheno2DInputList.append(added_mc_background[htt2d_index][index_250])
Pheno2DInputList.append(input_histos_data[htt2d_index][index_250])
Pheno2DInputList.append(added_mc_signal[htt2d_index][index_300])
Pheno2DInputList.append(added_mc_background[htt2d_index][index_300])
Pheno2DInputList.append(input_histos_data[htt2d_index][index_300])
Pheno2DInputList.append(added_mc_signal[htt2d_index][index_350])
Pheno2DInputList.append(added_mc_background[htt2d_index][index_350])
Pheno2DInputList.append(input_histos_data[htt2d_index][index_350])
Pheno2DInputList.append(added_mc_signal[htt2d_index][index_400])
Pheno2DInputList.append(added_mc_background[htt2d_index][index_400])
Pheno2DInputList.append(input_histos_data[htt2d_index][index_400])

for j in Pheno2DInputList:
  print j.GetName()
  pheno_canvas=TCanvas('Pheno2DPlot_'+j.GetName(),'',428,120,679,606)

  j.GetXaxis().SetLabelSize(0.06)
  j.GetXaxis().SetTitleSize(0.06)
  j.GetXaxis().SetTitleOffset(1.1)
  j.GetYaxis().SetLabelSize(0.06)
  j.GetYaxis().SetTitleSize(0.06)
  j.GetYaxis().SetTitleOffset(1.1)
  j.GetZaxis().SetLabelSize(0.05)
  pheno_canvas.SetLeftMargin(0.15)
  pheno_canvas.SetRightMargin(0.12)
  pheno_canvas.SetBottomMargin(0.15)
  pheno_canvas.SetTopMargin(0.05)
  #pheno_canvas.SetLeftMargin(0.1494253)
  pheno_canvas.SetTopMargin(0.07415254)
  #pheno_canvas.SetBottomMargin(0.1504237)
  #print j.GetName()
  if j.GetName()=='HTT2D_NOheptoptag_NOmasscut_hists' or j.GetName()=='HTT2D_heptoptag_masscut_hists':
    j.Rebin2D(2,2)
  if j.GetName()=='HTT2D_pt400hists_Signal_Add':
    j.Rebin2D(2,2)
   
  j.SetStats(kFALSE)
#  j.Rebin2D(2,2)
  gStyle.SetNumberContours(255)
  gStyle.SetPalette(55)
  #j.GetXaxis().SetRangeUser(0,1.5)
  #j.GetYaxis().SetRangeUser(0,1.5)
  j.GetXaxis().SetRangeUser(0,1.5)
  j.GetYaxis().SetRangeUser(0,1.3)
  j.Draw('COLZ')
  for i in htt_cut_line:
    i.Draw('SAME')
  if '_Add' in j.GetName():
    cmslabelsim2.Draw()
  else:
    cmslabel2.Draw()
  if j.GetName()=='HTT2D_NOheptoptag_NOmasscut_hists':
    infolabel2d_nottbar.Draw()
    pheno_canvas.SaveAs('pdf/'+j.GetName()+'.pdf')
  if j.GetName()=='HTT2D_NOheptoptag_NOmasscut_hists_Signal_Add':
    infolabel2d.Draw()
    pheno_canvas.SaveAs('pdf/'+j.GetName()+'.pdf')
  if j.GetName()=='HTT2D_NOheptoptag_NOmasscut_hists_Background_Add':
    infolabel2d_nottbar.Draw()
    pheno_canvas.SaveAs('pdf/'+j.GetName()+'.pdf')
  if j.GetName()=='HTT2D_pt300hists_Signal_Add':
    infolabel2d_300.Draw()
    pheno_canvas.SaveAs('pdf/'+j.GetName()+'.pdf')
  if j.GetName()=='HTT2D_pt400hists_Signal_Add':
    infolabel2d_400.Draw()
    pheno_canvas.SaveAs('pdf/'+j.GetName()+'.pdf')
  pheno_canvas.Write()
  Pheno2DPlot.append(pheno_canvas)
#.Clone(input_histos_data[htt2d_index][index_yy].GetName()+'_2')
#input_histos_data[htt2d_index][index_yy].SetStats(kFALSE)
#input_histos_data[htt2d_index][index_yy].Draw('COLZ')
#for i in htt_cut_line:
  #i.Draw('SAME')
#Pheno2DPlot.Write()

   #TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10);
    #if(atan(m13/m12)>0.2 && atan(m13/m12)<1.3 && m23/mjet>rmin &&
#m23/mjet<rmax) keep=1;

    ##2 condition
    #cond2left=pow(rmin,2)*(1+pow((m13/m12),2))
    #cond2cent=1-pow(m23/mjet,2)
    #cond2right=pow(rmax,2)*(1+pow(m13/m12,2))

    #if(cond2left<cond2cent && cond2cent<cond2right &&
#m23/mjet>cutCondition2) keep=1;

    ##3 condition
    #cond3left=pow(rmin,2)*(1+pow((m12/m13),2))
    #cond3cent=1-pow(m23/mjet,2)
    #cond3right=pow(rmax,2)*(1+pow(m12/m13,2))

#gStyle.SetOptStat('ioue')
#make pull
print 'make pull'
pulls=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  cut_sublist=[]
  for cut_name_index in range(len(cut_names)):
    cut_name=cut_names[cut_name_index]
    pull=input_histos_data[histogram_name_index][cut_name_index].Clone(histogram_name+'_'+cut_name+'_Pull')
    pull.Divide(added_mc[histogram_name_index][cut_name_index])
    pull.SetStats(kFALSE)
    pull.SetTitle('')
    pull.GetYaxis().SetLabelSize(0.22)
    pull.GetYaxis().SetTitle("Data / MC")
    pull.GetYaxis().SetTitleSize(0.22)
    pull.GetYaxis().SetTitleOffset(0.23)
    pull.GetYaxis().SetRangeUser(0.3,1.7)
    #if histogram_name in ['var1_HTT','var2_HTT','var3_HTT']:
    #pull.GetYaxis().SetRangeUser(0.7,1.3)
    pull.GetYaxis().SetNdivisions(3,2,0)
    pull.GetXaxis().SetLabelSize(0.22)
    pull.GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
    pull.GetXaxis().SetTitleSize(0.22)
    pull.GetXaxis().SetTitleOffset(1.1)
    
    
    pull.GetYaxis().SetLabelSize(0.22)
    pull.GetYaxis().SetTitleSize(0.22)
    pull.GetYaxis().SetTitleOffset(0.38)
    pull.GetXaxis().SetLabelSize(0.22)
    pull.GetXaxis().SetTitleSize(0.22)
    if histogram_name=='var1_HTT':
      pull.GetXaxis().SetTitleSize(0.2)
    
    #pull.SetLineColor(kBlue+2)
    #pull.SetLineWidth(2)
    pull.SetLineColor(1)
    pull.SetLineStyle(1)
    pull.SetLineWidth(1)
    pull.SetMarkerColor(1)
    pull.SetMarkerStyle(8)
    pull.SetMarkerSize(1)
    cut_sublist.append(pull)
  pulls.append(cut_sublist)
#structure: pulls[histogram_name_index][cut_name_index]

pulls[topmass_index][index_nn].Write()
pulls[topmass_index][index_yy].Write()
pulls[toppt_index][index_nn].Write()
pulls[toppt_index][index_yy].Write()
pulls[histogram_names.index('LeptToppt')][cut_names.index('after_tpr_hists')].Write()

#compare mc and data
print 'compare mc and data'
canvases=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  cut_sublist=[]
  for cut_name_index in range(len(cut_names)):
    cut_name=cut_names[cut_name_index]
    tmp_canvas=TCanvas(histogram_name+'_'+cut_name+'_Canvas','')
    tmp_canvas.Divide(1,2)
    top_pad=tmp_canvas.GetPad(1)
    bottom_pad=tmp_canvas.GetPad(2)
    top_pad.SetPad( 0.0, 0.30, 1.0, 1.0 )
    bottom_pad.SetPad( 0.0, 0.0, 1.0, 0.30 )
    #top_pad.SetTopMargin(0.15)
    ##top_pad.SetBottomMargin(0.03)
    #top_pad.SetBottomMargin(0.0)#0.013)
    #top_pad.SetLeftMargin(0.16)
    #top_pad.SetRightMargin(0.03)
    
    top_pad.SetLeftMargin(0.1594828)
    top_pad.SetRightMargin(0.05028735)
    top_pad.SetTopMargin(0.1119855)
    top_pad.SetBottomMargin(0.0)
    
    #bottom_pad.SetTopMargin(0.03)
    #bottom_pad.SetTopMargin(0.0)
    #bottom_pad.SetBottomMargin(0.5)
    #bottom_pad.SetLeftMargin(0.16)
    #bottom_pad.SetRightMargin(0.03)
    
    bottom_pad.SetLeftMargin(0.1594828)
    bottom_pad.SetRightMargin(0.05028735)
    bottom_pad.SetTopMargin(0)
    bottom_pad.SetBottomMargin(0.5014125)
    
    tmp_canvas.cd(1)

    stacked_mc[histogram_name_index][cut_name_index].Draw("hist")
    input_histos_data[histogram_name_index][cut_name_index].Draw("sameEX0")
    
    #stacked_mc[histogram_name_index].GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetTitle(histogram_yaxes[histogram_name_index])
    stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetTitle('')
    stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetLabelOffset(9999)
    stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetLabelSize(0)
    stacked_mc[histogram_name_index][cut_name_index].SetMinimum(0.1)
    stacked_mc[histogram_name_index][cut_name_index].SetTitle('')#histogram_descriptions[histogram_name_index])
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetTitleSize(0.07)
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetLabelSize(0.07)
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetTitleOffset(0.9)
    
    stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetLabelOffset(9999)
    stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetLabelSize(0)
    stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetTitleSize(0.035)
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetLabelSize(0.1)
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetTitleSize(0.1)
    stacked_mc[histogram_name_index][cut_name_index].GetYaxis().SetTitleOffset(0.85)
    
    maximum=max(stacked_mc[histogram_name_index][cut_name_index].GetMaximum(),input_histos_data[histogram_name_index][cut_name_index].GetMaximum())
    
    stacked_mc[histogram_name_index][cut_name_index].SetMaximum(maximum*1.7)
    #if histogram_name=='MassTop':
     # stacked_mc[histogram_name_index][cut_name_index].SetMaximum(1500)
    #if histogram_name=='var1_HTT':
      #stacked_mc[histogram_name_index][cut_name_index].SetMaximum(3000)
    #if histogram_name=='var2_HTT':
      #stacked_mc[histogram_name_index][cut_name_index].SetMaximum(3000)
    #if histogram_name=='var3_HTT':
      #stacked_mc[histogram_name_index][cut_name_index].SetMaximum(1800)
    if histogram_name=='var1_HTT':
      linemin=TLine(0.2,0,0.2,stacked_mc[histogram_name_index][cut_name_index].GetMaximum())
      linemax=TLine(1.3,0,1.3,stacked_mc[histogram_name_index][cut_name_index].GetMaximum())
      linemin.SetLineWidth(3)
      linemin.SetLineColor(kRed)
      linemax.SetLineWidth(3)
      linemax.SetLineColor(kRed)
      #linemin.Draw()
      #linemax.Draw()
    if histogram_name=='var2_HTT':
      linemin=TLine(0.4,0,0.4,stacked_mc[histogram_name_index][cut_name_index].GetMaximum())
      linemax=TLine(0.54,0,0.54,stacked_mc[histogram_name_index][cut_name_index].GetMaximum())
      linemin.SetLineWidth(3)
      linemin.SetLineColor(kRed)
      linemax.SetLineWidth(3)
      linemax.SetLineColor(kRed)
      #linemin.Draw()
      #linemax.Draw()
    if histogram_name=='var3_HTT':
      stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(20.,150.)
    if histogram_name in ['MassTop']:
      stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,349.9)
    if histogram_name in ['m01']:
      stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,249.9)
    if histogram_name in ['m02']:
      stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,199.9)
    if histogram_name in ['m12']:
      stacked_mc[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,159.9)
    legend.Draw()
    cmslabel.Draw()
    #infolabel.Draw()
    if cut_name == "NOheptoptag_NOmasscut_hists":
      infolabel.Draw()
    if cut_name == "heptoptag_NOmasscut_hists":
      infolabel_htt.Draw()   
    if cut_name == "pt300hists":
      infolabel_300.Draw()
    if cut_name == "pt400hists":
      infolabel_400.Draw()
    if cut_name == "pt300histshtt":
      infolabel_htt300.Draw()
    if cut_name == "pt400histshtt":
      infolabel_htt400.Draw()
       
    tmp_canvas.cd(2)
    
    xmax=stacked_mc[histogram_name_index][cut_name_index].GetXaxis().GetXmax()
    xmin=stacked_mc[histogram_name_index][cut_name_index].GetXaxis().GetXmin()
    if histogram_name=='var3_HTT':
      xmin=20.
      xmax=150.
      pulls[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(20.,149.9)
    if histogram_name in ['MassTop']:
      xmin=0.
      xmax=350.
      pulls[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,349.9)
    if histogram_name in ['m01']:
      xmin=0.
      xmax=250.
      pulls[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,249.9)
    if histogram_name in ['m02']:
      xmin=0.
      xmax=200.
      pulls[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,199.9)
    if histogram_name in ['m12']:
      xmin=0.
      xmax=160.
      pulls[histogram_name_index][cut_name_index].GetXaxis().SetRangeUser(0.,159.9)
    pulls[histogram_name_index][cut_name_index].Draw('EX0') 
    line1=TLine(xmin,1.0,xmax,1.0)
    line1.SetLineStyle(2)
    line1.Draw()
    #line2=TLine(stacked_mc[histogram_name_index][cut_name_index].GetXaxis().GetXmin(),2.0,stacked_mc[histogram_name_index][cut_name_index].GetXaxis().GetXmax(),2.0)
    #line2.SetLineStyle(2)
    #line2.Draw()
    canvases.append(tmp_canvas)
    #if (histogram_name in ['Toppt','MassTop','Pt_all_sub','m01','mW','m012']) and cut_name=="masswindowhists":
    #  tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.png')
      #tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.pdf')
    if histogram_name in ['Toppt','MassTop','var1_HTT','var2_HTT','var3_HTT','m01','m02','m12','LeptToppt'] and cut_name in ["heptoptag_masscut_hists","NOheptoptag_NOmasscut_hists","heptoptag_NOmasscut_hists","eta0p5","eta2p4","eta0p5to1p0","eta1p0to2p4","pt250hists","pt300hists","pt350hists","pt400hists","after_tpr_hists","eta1p0_400","eta1p0to2p4_400","pt300histshtt","pt400histshtt"]:#,"eta1p0","eta1p0_HTT"]#"heptoptag_masscut_hists_notpr","NOheptoptag_NOmasscut_hists_notpr","pt200hists","pt250hists","pt300hists","pt350hists","pt400hists","ptlowhists"]:#'N_pv','N_pv200','N_pv300','N_pv400','N_pv500','N_pv600','Toppt_2','m012','dRsubjet'"pt300histshtt","pt400histshtt",
      tmp_canvas.Write()
      if histogram_name in ['Toppt','MassTop','var1_HTT','var2_HTT','var3_HTT','m01','m02','m12'] and cut_name in ["NOheptoptag_NOmasscut_hists","heptoptag_NOmasscut_hists","pt300hists","pt400hists","pt300histshtt","pt400histshtt"]:
        tmp_canvas.SaveAs('pdf/'+tmp_canvas.GetName()+'.pdf')
        tmp_canvas.SaveAs('pdf/'+tmp_canvas.GetName()+'.C')
      #if histogram_name in ["subTrackNPixelHits","subTrackMomentum","subTrackJetDistVal","subTrackDecayLenVal","subTrackSip3dVal","subTrackSip3dSig","subJetNSecondaryVertices","subCSV","subFlightDistance3dSig"]:
      # top_pad.SetLogy()
  
#close file  
print 'close file'
outfile.Close()
#sys.exit('ok') 
