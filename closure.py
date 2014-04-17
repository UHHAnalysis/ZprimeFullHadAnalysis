from math import sqrt
from os import system
from ROOT import TFile,kRed,kBlue,gROOT,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange,TLine
gROOT.SetBatch()

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
  legend=TLegendlegend=TLegend(0.6,0.5,0.989,0.89)
  legend.SetFillColor(kWhite)
  legend.SetBorderSize(0)
  legend.AddEntry(measured,'measured','l')
  legend.AddEntry(predicted,'predicted','l')
  comparecanvas=TCanvas('closure_'+histo_name+'_'+folder,'',600,600)
  comparecanvas.Divide(1,2)
  top_pad=comparecanvas.GetPad(1)
  bottom_pad=comparecanvas.GetPad(2)
  top_pad.SetPad( 0.0, 0.30, 1.0, 1.0 )
  bottom_pad.SetPad( 0.0, 0.0, 1.0, 0.30 )
  measured.SetLineWidth(3)
  predicted.SetLineWidth(3)
  measured.SetLineColor(kBlue)
  predicted.SetLineColor(kRed)
  top_pad.cd()
  measured.Draw()
  predicted.Draw('SAME')
  legend.Draw()
  bottom_pad.cd()
  ratio.Draw()
  line.Draw('same')
  comparecanvas.Write('closure_'+histo_name+'_'+folder)
  comparecanvas.SaveAs('pdf/closure_'+histo_name+'_'+folder+'.pdf')

for i in ['Mtt0','Mtt1','Mtt2']:
  for j in [htfolder,mjfolder]:
    doClosure(i,j,2)
  
bkg_file.Close()
f.Close()
outfile.Close()