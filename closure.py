from math import sqrt
from os import system
import ROOT
from ROOT import TFile,kRed,kBlue,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange,TLine
ROOT.gROOT.SetBatch()
ROOT.gROOT.LoadMacro("tdrstyle.C");
ROOT.gROOT.ProcessLine( 'setTDRStyle();')
#setTDRStyle()
ROOT.gROOT.LoadMacro("CMS_lumi.C+");

#f=TFile('dust/theta_qcd.root', "READ")
#f=TFile('dust/BackgroundCycle.MC.QCD_HT-500To1000.root', "READ")

outfile=TFile("closure.root", "RECREATE")
path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
process_list_qcd=['BackgroundCycle.MC.QCD_HT-500To1000.root','BackgroundCycle.MC.QCD_HT-1000ToInf.root','BackgroundCycle.MC.QCD_HT-250To500.root']#,
def hadd(inputlist,outputname):
  command_list='hadd -f '+path_base+outputname+'.root'# -v 0
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
qcd_filename=hadd(process_list_qcd,'clo_qcd')

bkg_file=TFile('bkg.root','READ')
f=TFile(qcd_filename, "READ")
mjfolder='QuadJetDatasetHistos'
htfolder='HTDatasetHistos'

def doClosure(histo_name,folder,rebin):
  measured=f.Get(folder+'/Measured'+histo_name).Clone('measured_'+histo_name+'_'+folder)
  predicted=f.Get(folder+'/'+histo_name).Clone('predicted_'+histo_name+'_'+folder)
  mistag_matrix=bkg_file.Get(folder+"/Mistag/qcd_htt/Mistag_qcd_htt")
  errmtt=f.Get(folder+'/Err'+histo_name)
  for mtt_bin in range(1,errmtt.GetNbinsX()+1):
    a1 = 0.0
    a2 = 0.0
    den = 0.0
    for pt_bin in range(1,errmtt.GetNbinsY()+1):
      for csv_bin in range(1,errmtt.GetNbinsZ()+1):
	#print errmtt.GetBinContent(mtt_bin,pt_bin,csv_bin)
	a1 += mistag_matrix.GetBinContent(pt_bin,csv_bin) * sqrt(errmtt.GetBinContent(mtt_bin,pt_bin,csv_bin))
	a2 += mistag_matrix.GetBinError(pt_bin,csv_bin) * errmtt.GetBinContent(mtt_bin,pt_bin,csv_bin)
	den += mistag_matrix.GetBinContent(pt_bin,csv_bin) * errmtt.GetBinContent(mtt_bin,pt_bin,csv_bin)
    dx=0.0
    if  den>0.0:
      dx = sqrt(a1*a1+a2*a2)/den
      predicted.SetBinError(mtt_bin, dx * predicted.GetBinContent(mtt_bin))
  outfile.cd()
  measured.Rebin(rebin)
  predicted.Rebin(rebin)
  ratio=measured.Clone('ratio_'+histo_name+'_'+folder)
  ratioden=predicted.Clone('ratioden_'+histo_name+'_'+folder)
  ratio.Divide(ratioden)
  ratio.GetYaxis().SetRangeUser(0.0,2.0)
  ratio.SetLineWidth(3)
  
  measured.SetStats(0)
  predicted.SetStats(0)
  ratio.SetStats(0)
  measured.SetTitle('')
  predicted.SetTitle('')
  ratio.SetTitle('')
  
  line=TLine(0,1.0,4000,1.0)  
  legend=TLegendlegend=TLegend(0.5,0.3,0.98,0.6)
  if folder==htfolder:
   legend.SetHeader('HEP Tagger, H_{T}>800 GeV')
  if folder==mjfolder:
   legend.SetHeader('HEP Tagger, H_{T}<800 GeV')
  legend.SetFillColor(kWhite)
  legend.SetBorderSize(0)
  legend.SetFillStyle(0)
  legend.SetTextFont(42)
  legend.SetTextSize(0.05)
  legend.AddEntry(measured,'Selected','l')
  legend.AddEntry(predicted,'Predicted','l')
  comparecanvas=TCanvas('closure_'+histo_name+'_'+folder,'',600,600)
  comparecanvas.Divide(1,2)
  top_pad=comparecanvas.GetPad(1)
  bottom_pad=comparecanvas.GetPad(2)
  top_pad.SetPad( 0.0, 0.30, 1.0, 1.0 )
  bottom_pad.SetPad( 0.0, 0.0, 1.0, 0.30 )
  #top_pad.SetLeftMargin(0.18)#0.15
  #top_pad.SetRightMargin(0.05)#0.01
  #top_pad.SetTopMargin(0.13)#0.10
  #top_pad.SetBottomMargin(0.15)#0.0
  top_pad.SetLeftMargin(0.15)#
  top_pad.SetRightMargin(0.05)#
  top_pad.SetTopMargin(0.10)#
  top_pad.SetBottomMargin(0.0)#
  bottom_pad.SetLeftMargin(0.15)
  bottom_pad.SetRightMargin(0.05)
  bottom_pad.SetTopMargin(0.0)
  bottom_pad.SetBottomMargin(0.45)
  measured.SetLineWidth(3)
  predicted.SetLineWidth(3)
  measured.SetLineColor(kBlue)
  predicted.SetLineColor(kRed)
  top_pad.cd()
  measured.Draw()


  measured.SetMinimum(0.1)
  measured.SetMaximum(measured.GetMaximum()*1.2)
  measured.GetXaxis().SetTitle("a")#ttbar_histo.GetXaxis().GetTitle())
  measured.GetYaxis().SetTitle('Events')
  measured.GetYaxis().SetLabelSize(0.07)
  measured.GetYaxis().SetTitleSize(0.07)
  measured.GetYaxis().SetTitleOffset(1.15)
  measured.GetXaxis().SetLabelSize(0.07)
  measured.GetXaxis().SetTitleSize(0.07)
  measured.GetXaxis().SetTitleOffset(1.0)

  predicted.Draw('SAME')

  legend.Draw()

  ROOT.extraText='Simulation'
  ROOT.writeExtraText = True  
  ROOT.extraText='Simulation'   
  if folder==htfolder:
    ROOT.CMS_lumi( top_pad, 2, 33 )
  if folder==mjfolder:
    ROOT.CMS_lumi( top_pad, 1, 33 )
  bottom_pad.cd()

  ratio.SetLineColor(1)
  ratio.SetLineStyle(1)
  ratio.SetLineWidth(1)
  ratio.SetMarkerColor(1)
  ratio.SetMarkerStyle(8)
  ratio.SetMarkerSize(1)
  ratio.SetStats(0)
  ratio.SetTitle('') 
  ratio.GetYaxis().SetLabelSize(0.16333)
  ratio.GetYaxis().SetTitleSize(0.16333)
  ratio.GetYaxis().SetTitleOffset(0.4928)
  ratio.GetXaxis().SetLabelSize(0.16333)
  ratio.GetXaxis().SetTitleSize(0.16333)
  ratio.GetXaxis().SetTitleOffset(1.3)
  ratio.GetYaxis().SetTitle('Sel./Pred.')
  #ratio.GetXaxis().SetTitle('m_{t#bar{t}} [GeV]')
  ratio.GetYaxis().SetRangeUser(-0.25,2.25)
  ratio.GetYaxis().SetNdivisions(3,2,0)
  #ratio.GetXaxis().SetRangeUser(ratio.GetXaxis().GetXmin(),ratio.GetXaxis().GetXmax()*zf)
  line.SetLineStyle(2)




  ratio.Draw()
  line.Draw('same')
  comparecanvas.Write('closure_'+histo_name+'_'+folder)
  comparecanvas.SaveAs('pdf/closure_'+histo_name+'_'+folder+'.pdf')

for i in ['Mtt0','Mtt1','Mtt2','Mtt012']:
  for j in [htfolder,mjfolder]:
    doClosure(i,j,2)
  
bkg_file.Close()
f.Close()
outfile.Close()