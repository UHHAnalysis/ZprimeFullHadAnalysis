#!/usr/bin/env python
#from subprocess import check_output,call
from os import system
from ROOT import TFile,gROOT,THStack,TCanvas,TLegend,kRed,kYellow,kWhite,TLatex,kBlue,TLine,TGraphAsymmErrors,kOrange,kGray
from sys import argv

print 'setup'

dolimits=False
doplots=True
dolimitplot=False

gROOT.SetBatch()
#postfix=''
path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
process_list_signal_wide=['BackgroundCycle.MC.ZP750W75.root','BackgroundCycle.MC.ZP500W50.root','BackgroundCycle.MC.ZP4000W400.root','BackgroundCycle.MC.ZP3000W300.root','BackgroundCycle.MC.ZP1000W100.root','BackgroundCycle.MC.ZP1250W125.root','BackgroundCycle.MC.ZP1500W150.root','BackgroundCycle.MC.ZP2000W200.root']
#process_list_signal_narrow=['BackgroundCycle.MC.ZP750W7p5.root','BackgroundCycle.MC.ZP500W5.root','BackgroundCycle.MC.ZP4000W40.root','BackgroundCycle.MC.ZP3000W30.root','BackgroundCycle.MC.ZP1000W10.root','BackgroundCycle.MC.ZP1250W12p5.root','BackgroundCycle.MC.ZP1500W15.root','BackgroundCycle.MC.ZP2000W20.root']
process_list_signal_narrow=['BackgroundCycle.MC.ZP500W5.root','BackgroundCycle.MC.ZP750W7p5.root','BackgroundCycle.MC.ZP1000W10.root','BackgroundCycle.MC.ZP1250W12p5.root','BackgroundCycle.MC.ZP1500W15.root','BackgroundCycle.MC.ZP2000W20.root','BackgroundCycle.MC.ZP3000W30.root']
process_names_signal_narrow=[]
for i in range(len(process_list_signal_narrow)):
  process_names_signal_narrow.append(process_list_signal_narrow[i].split('.')[2].split('W')[0][2:])
print process_names_signal_narrow
process_list_ttbar=['BackgroundCycle.MC.TTbarHad.root','BackgroundCycle.MC.TTbarLept.root','BackgroundCycle.MC.TTbarSemi.root']
process_list_qcd=['BackgroundCycle.MC.QCD_HT-1000ToInf.root','BackgroundCycle.MC.QCD_HT-250To500.root','BackgroundCycle.MC.QCD_HT-500To1000.root']#,'BackgroundCycle.MC.QCD_HT-100To250.root'
histo_name='Mtt'
categories=['0btag','1btag','2btag']
#categories=['2btag']
#cut_list=['m','l','mn','ln','my','ly','mny','lny']
cut_list=['m','cms','htt','httcms']
base_histoname='had'
us='_'
outfile=TFile('outfile.root','RECREATE')

#histo_folder_list=['NoCutsHistos','TriggerHistos','had_0btag_m','had_1btag_m','had_2btag_m',,'had_2btag_lny','antitag_den','antitag_num_l','antitag_num_m','antitag_num_ln','antitag_num_mn']

histo_folder_list=['NoCutsHistos','had_0btag_m','had_1btag_m','had_2btag_m','had_012btag_m','had_0btag_cms','had_1btag_cms','had_2btag_cms','had_012btag_cms','had_0btag_htt','had_1btag_htt','had_2btag_htt','had_012btag_htt','had_0btag_httcms','had_1btag_httcms','had_2btag_httcms','had_012btag_httcms','antitag_den','antitag_num_l','antitag_num_m','antitag_num_ln','antitag_num_mn']

histo_name_list=["Ntopjets","SumOfTopCandidatesPt","LeadingTopCandidatePt","SubLeadingTopCandidatePt","TopCandidate1Pt","TopCandidate2Pt","Mtt","Nevts","ptNevts","toppt","DeltaY","DeltaPhi","DeltaR","Nsub"]

for i in histo_folder_list:
  outfile.mkdir(i)
outfile.mkdir('studies')

print 'hadd plots'
def hadd(inputlist,outputname):
  command_list='hadd  -f '+path_base+outputname+'.root'#-v 0
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
ttbar_filename=hadd(process_list_ttbar,'theta_ttbar')
qcd_filename=hadd(process_list_qcd,'theta_qcd')
data_filename=path_base+'BackgroundCycle.DATA.DATA.root'
#background_filename=path_base+'BackgroundCycle.DATA.DATA.root'
#backgroundtt_filename=path_base+'bkg_ttbar.root'
#background_file=TFile(background_filename,'READ')
#backgroundtt_file=TFile(backgroundtt_filename,'READ')
ttbar_file=TFile(ttbar_filename,'READ')
qcd_file=TFile(qcd_filename,'READ')
data_file=TFile(data_filename,'READ')
bkg_file=TFile('bkg.root','READ')
signal_files=[]
for i in range(len(process_list_signal_narrow)):
  tmp_file=TFile(path_base+process_list_signal_narrow[i],'READ')
  signal_files.append(tmp_file)

if doplots:
  print 'make histos'

  
  def make_plot(histo_name):
    zf=1
    legend=TLegend(0.8,0.5,0.945,0.895)
    legend.SetFillColor(kWhite)
    legend.SetBorderSize(0)
    legend.SetFillStyle(0)
    stack=THStack(histo_name+us+'stack','')
    #ttbar_histo=ttbar_file.Get(cut_name+'/'+histo_name).Clone('ttbar'+us+histo_name+us+cut_name)
    #qcd_histo=qcd_file.Get(cut_name+'/'+histo_name).Clone('qcd'+us+histo_name+us+cut_name)
    #data_histo=data_file.Get(cut_name+'/'+histo_name).Clone('data'+us+histo_name+us+cut_name)
    bkg_histo_name=histo_name
    measured_histo_name='Measured'+histo_name
    #if '_0btag_' in cut_name:
      #bkg_histo_name='Mtt0'
      #measured_histo_name='MeasuredMtt0'
    #elif '_1btag_' in cut_name:
      #bkg_histo_name='Mtt1'
      #measured_histo_name='MeasuredMtt1'
    #elif '_2btag_' in cut_name:
      #bkg_histo_name='Mtt2'
      #measured_histo_name='MeasuredMtt2'
    #elif '_012btag_' in cut_name:
      #bkg_histo_name='Mtt012'
      #measured_histo_name='MeasuredMtt012'
    data_histo=data_file.Get('BaseHistos/'+measured_histo_name).Clone('data'+us+histo_name)
    bkg_histo=data_file.Get('BaseHistos/'+bkg_histo_name).Clone('bkg'+us+histo_name)#background_file.Get('BaseHistos/'+bkg_histo_name).Clone('bkg'+us+histo_name+us+cut_name)
    ###mistag error propagation
    if histo_name=='Mtt0' or histo_name=='Mtt1' or histo_name=='Mtt2':
      mistag_matrix=bkg_file.Get("HEPTagger/Mistag/data_htt/Mistag_data_htt")
      errmtt=data_file.Get('BaseHistos/Err'+histo_name)
      for mtt_bin in range(1,bkg_histo.GetNbinsX()+1):
	a1 = 0.0
	a2 = 0.0
	den = 0.0
        for pt_bin in range(1,bkg_histo.GetNbinsY()+1):
	  for csv_bin in range(1,bkg_histo.GetNbinsZ()+1):
	    a1 += mistagH->GetBinContent(bin1, bin2, bin3) * sqrt(arrayForErrors[tag][bin0][bin1][bin2][bin3])
	    a2 += mistagH->GetBinError(bin1, bin2, bin3) * arrayForErrors[tag][bin0][bin1][bin2][bin3]
	    den += mistagH->GetBinContent(bin1, bin2, bin3) * arrayForErrors[tag][bin0][bin1][bin2][bin3]
    
    ###
    
    ttbar_histo=ttbar_file.Get('BaseHistos/'+measured_histo_name).Clone('ttbar'+us+histo_name)
    ttbkg_histo=ttbar_file.Get('BaseHistos/'+bkg_histo_name)
    qcd_histo=qcd_file.Get('BaseHistos/'+measured_histo_name).Clone('qcd'+us+histo_name)
    bkg_histo.Add(ttbkg_histo,-1.0)########################################
    sum_mc=ttbar_histo.Clone('sum_mc'+us+histo_name)
    sum_mc.Add(bkg_histo)
    err=TGraphAsymmErrors(sum_mc)
    sum_mc_noerr=sum_mc.Clone('sum_mc_noerr'+us+histo_name)
    for i in range(1,sum_mc_noerr.GetNbinsX()+1):
      sum_mc_noerr.SetBinError(i,0)
    
    data_histo_noerr=data_histo.Clone('data_noerr'+us+histo_name)
    for i in range(1,data_histo_noerr.GetNbinsX()+1):
      data_histo_noerr.SetBinError(i,0)
    ratio_histo_nodataerr=data_histo_noerr.Clone('ratio_nodataerr'+us+histo_name)
    ratio_histo_nodataerr.Divide(sum_mc)
    for i in range(1,ratio_histo_nodataerr.GetNbinsX()+1):
      ratio_histo_nodataerr.SetBinContent(i,1)
    err_ratio=TGraphAsymmErrors(ratio_histo_nodataerr)
    
    ratio_histo=data_histo.Clone('ratio'+us+histo_name)
    ratio_histo.Divide(sum_mc_noerr)
    ratio_histo.SetLineColor(1)
    ratio_histo.SetLineStyle(1)
    ratio_histo.SetLineWidth(1)
    ratio_histo.SetMarkerColor(1)
    ratio_histo.SetMarkerStyle(8)
    ratio_histo.SetMarkerSize(1)
    ratio_histo.SetStats(0)
    ratio_histo.SetTitle('') 
    ratio_histo.GetYaxis().SetLabelSize(0.16333)
    ratio_histo.GetYaxis().SetTitleSize(0.16333)
    ratio_histo.GetYaxis().SetTitleOffset(0.4928)
    ratio_histo.GetXaxis().SetLabelSize(0.16333)
    ratio_histo.GetXaxis().SetTitleSize(0.16333)
    ratio_histo.GetXaxis().SetTitleOffset(1.3)
    ratio_histo.GetYaxis().SetTitle('Data/MC')
    #ratio_histo.GetXaxis().SetTitle('m_{t#bar{t}} [GeV]')
    ratio_histo.GetYaxis().SetRangeUser(-0.25,2.25)
    ratio_histo.GetYaxis().SetNdivisions(3,2,0)
    ratio_histo.GetXaxis().SetRangeUser(ratio_histo.GetXaxis().GetXmin(),ratio_histo.GetXaxis().GetXmax()*zf)
    line1=TLine(ratio_histo.GetXaxis().GetXmin(),1.0,ratio_histo.GetXaxis().GetXmax()*zf,1.0)
    line1.SetLineStyle(2)
    ttbar_histo.SetFillColor(kRed)
    qcd_histo.SetFillColor(kYellow)
    bkg_histo.SetFillColor(kYellow)
    ttbar_histo.SetLineColor(kRed)
    qcd_histo.SetLineColor(kYellow)
    bkg_histo.SetLineColor(kYellow)
    ttbar_histo.SetMarkerColor(kRed)
    qcd_histo.SetMarkerColor(kYellow)
    bkg_histo.SetMarkerColor(kYellow)
    data_histo.SetLineColor(1)
    data_histo.SetLineStyle(1)
    data_histo.SetLineWidth(1)
    data_histo.SetMarkerColor(1)
    data_histo.SetMarkerStyle(8)
    data_histo.SetMarkerSize(1)
    #data_histo.GetXaxis().SetRangeUser(data_histo.GetXaxis().GetXmin(),data_histo.GetXaxis().GetXmax()*zf)
    legend.AddEntry(data_histo,'Data','pEX0')
    legend.AddEntry(ttbar_histo,'t#bar{t}','f')
    #legend.AddEntry(qcd_histo,'QCD MC','f')
    legend.AddEntry(bkg_histo,'NTMJ','f')
    stack.Add(ttbar_histo)
    #stack.Add(qcd_histo)
    stack.Add(bkg_histo)
    cmslabel=TLatex(0.15,0.925,"CMS Preliminary #sqrt{s} = 8TeV  19.7 fb^{-1}")
    #cmslabel=TLatex(0.15,0.925,"Private work")
    cmslabel.SetTextSize(0.07)
    cmslabel.SetNDC()
    cmslabel.SetTextFont(42)
    #cmslabel.SetLineWidth(5)
    signal1000=signal_files[process_names_signal_narrow.index('1000')].Get('BaseHistos/'+measured_histo_name).Clone('ZP1000'+us+histo_name)
    signal2000=signal_files[process_names_signal_narrow.index('2000')].Get('BaseHistos/'+measured_histo_name).Clone('ZP2000'+us+histo_name)
    signal3000=signal_files[process_names_signal_narrow.index('3000')].Get('BaseHistos/'+measured_histo_name).Clone('ZP3000'+us+histo_name)
    signal1000.SetLineWidth(3)
    signal1000.SetLineStyle(1)
    signal2000.SetLineWidth(3)
    signal2000.SetLineStyle(1)
    signal3000.SetLineWidth(3)
    signal3000.SetLineStyle(1)
    signal1000.SetLineColor(9)
    signal2000.SetLineColor(28)
    signal3000.SetLineColor(8)
    signal1000.Scale(3.0)
    signal2000.Scale(3.0)
    signal3000.Scale(3.0)
    legend.AddEntry(signal1000,"Z' 1TeV",'l')
    legend.AddEntry(signal2000,"Z' 2TeV",'l')
    legend.AddEntry(signal3000,"Z' 3TeV",'l')
    canvas=TCanvas(histo_name+us+'canvas','',0,0,600,600)#,'',100,100)
    canvas.Divide(1,2)
    top_pad=canvas.GetPad(1)
    bottom_pad=canvas.GetPad(2)
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
    top_pad.cd()
    stack.Draw('hist')
    err.SetFillStyle(3145)
    err.SetFillColor(kGray)
    err.Draw('2')
    data_histo.Draw("sameEX0")
    stack.SetMinimum(0.1)
    stack.GetXaxis().SetTitle(signal1000.GetXaxis().GetTitle())
    stack.GetYaxis().SetTitle('Events')
    stack.GetYaxis().SetLabelSize(0.07)
    stack.GetYaxis().SetTitleSize(0.07)
    stack.GetYaxis().SetTitleOffset(1.15)
    stack.GetXaxis().SetLabelSize(0.07)
    stack.GetXaxis().SetTitleSize(0.07)
    stack.GetXaxis().SetTitleOffset(1.0)
    
    #stack.GetYaxis().SetLabelSize(0.045)
    #stack.GetYaxis().SetTitleSize(0.045)
    #stack.GetYaxis().SetTitleOffset(1.9)
    #stack.GetXaxis().SetLabelSize(0.045)
    #stack.GetXaxis().SetTitleSize(0.045)
    #stack.GetXaxis().SetTitleOffset(1.5)
    
    stack.GetXaxis().SetRangeUser(stack.GetXaxis().GetXmin(),stack.GetXaxis().GetXmax()*zf)
    signal1000.Draw('samehisto')
    signal2000.Draw('samehisto')
    signal3000.Draw('samehisto')
    legend.Draw()
    cmslabel.Draw()
    bottom_pad.cd()
    err_ratio.SetFillStyle(1001)
    err_ratio.SetFillColor(kGray)
    ratio_histo.Draw('EX0')
    err_ratio.Draw('same2')
    ratio_histo.Draw('sameEX0')
    line1.Draw()
    #outfile.cd(cut_name)
    outfile.cd()
    canvas.Write()
    canvas.SaveAs('pdf/'+canvas.GetName()+'.pdf')
    
  #for i in range(len(histo_name_list)):
  #  for j in range(len(histo_folder_list)):
  make_plot('Mtt012')
  make_plot('Mtt0')
  make_plot('Mtt1')
  make_plot('Mtt2')
  
  make_plot('Jet1pT012')
  make_plot('Jet1pT0')
  make_plot('Jet1pT1')
  make_plot('Jet1pT2')
  make_plot('Jet2pT012')
  make_plot('Jet2pT0')
  make_plot('Jet2pT1')
  make_plot('Jet2pT2')

  make_plot('Jet1eta012')
  make_plot('Jet1eta0')
  make_plot('Jet1eta1')
  make_plot('Jet1eta2')
  make_plot('Jet2eta012')
  make_plot('Jet2eta0')
  make_plot('Jet2eta1')
  make_plot('Jet2eta2')

  make_plot('Jet1csv012')
  make_plot('Jet1csv0')
  make_plot('Jet1csv1')
  make_plot('Jet1csv2')
  make_plot('Jet2csv012')
  make_plot('Jet2csv0')
  make_plot('Jet2csv1')
  make_plot('Jet2csv2')
  
  #stack1=THStack('ZP1000stack','')
  #stack2=THStack('ZP2000stack','')
  #histo_name_list.index("SubLeadingTopCandidatePt")
  #sig1htt=signal_files[process_names_signal_narrow.index('1250')].Get('had_012btag_m/SubLeadingTopCandidatePt').Clone('sig1htt')
  #sig2htt=signal_files[process_names_signal_narrow.index('2000')].Get('had_012btag_m/SubLeadingTopCandidatePt').Clone('sig2htt')
  #sig1cms=signal_files[process_names_signal_narrow.index('1250')].Get('had_012btag_cms/SubLeadingTopCandidatePt').Clone('sig1cms')
  #sig2cms=signal_files[process_names_signal_narrow.index('2000')].Get('had_012btag_cms/SubLeadingTopCandidatePt').Clone('sig2cms')
  ##sig1htt.SetFillColor(kBlue)
  ##sig2htt.SetFillColor(kBlue)
  ##sig1cms.SetFillColor(kRed)
  ##sig2cms.SetFillColor(kRed)
  #sig1htt.SetLineColor(kBlue)
  #sig2htt.SetLineColor(kBlue)
  #sig1cms.SetLineColor(kRed)
  #sig2cms.SetLineColor(kRed)
  #sig1htt.SetLineWidth(3)
  #sig2htt.SetLineWidth(3)
  #sig1cms.SetLineWidth(3)
  #sig2cms.SetLineWidth(3)
  #stack1.Add(sig1htt)
  #stack1.Add(sig1cms)
  #stack2.Add(sig2htt)
  #stack2.Add(sig2cms)
  #cs1=TCanvas('cs1')
  #stack1.Draw('histnostack')
  #stack1.GetXaxis().SetTitle('p_{T} GeV')
  #stack1.GetYaxis().SetTitle('Events')
  #cs1.SaveAs('pdf/stack1.pdf')
  #cs2=TCanvas('cs2')
  #stack2.Draw('histnostack')
  #stack2.GetXaxis().SetTitle('p_{T} GeV')
  #stack2.GetYaxis().SetTitle('Events')
  #cs2.SaveAs('pdf/stack2.pdf')
  
  
if dolimits:
  print 'make theta root file'


  def make_theta_rootfile(theta_root_filename,cut_types):
    limits_input_file=TFile(path_base+theta_root_filename+".root","RECREATE")
    #limits_input_file.cd()
    for cut_type in cut_types:
      cut_index=cut_list.index(cut_type)
      for category_index in range(len(categories)):
         ttbar_histo=ttbar_file.Get(base_histoname+us+categories[category_index]+us+cut_list[cut_index]+'/Mtt').Clone(base_histoname+us+cut_list[cut_index]+categories[category_index]+us+us+'ttbar')
         ttbar_histo.Rebin(2)
         qcd_histo=qcd_file.Get(base_histoname+us+categories[category_index]+us+cut_list[cut_index]+'/Mtt').Clone(base_histoname+us+cut_list[cut_index]+categories[category_index]+us+us+'qcd')
         qcd_histo.Rebin(2)
         ttbar_histo.Write()
         qcd_histo.Write()
         signal_histos=[]
         for i in range(len(process_list_signal_narrow)):
	   tmp_histo =signal_files[i].Get(base_histoname+us+categories[category_index]+us+cut_list[cut_index]+'/Mtt').Clone(base_histoname+us+cut_list[cut_index]+categories[category_index]+us+us+process_list_signal_narrow[i].split('.')[2].split('W')[0])
	   tmp_histo.Rebin(2)
	   signal_histos.append(tmp_histo)
	   tmp_histo.Write()
    limits_input_file.Close()

  #cut_types=['cms','htt']['m']
  cut_types=['m']
  catstring=''
  for i in range(len(categories)):
    catstring+=categories[i].split('btag')[0]
  catstring+='btag'
  theta_input_name='zphad'+us+catstring
  for i in range(len(cut_types)):
    theta_input_name+=us+cut_types[i]
  
  make_theta_rootfile(theta_input_name,cut_types)
    
  print 'theta'
  
  postfix='ca15jet'
  
  model_strings=""
  for i in range(len(process_list_signal_narrow)):
    model_strings+="    model.add_lognormal_uncertainty('signal"+process_names_signal_narrow[i]+"_rate', 0.15, 'ZP"+process_names_signal_narrow[i]+"')\n"
  theta_config = open(path_base+theta_input_name+'.py', 'w')
  theta_config.write("def get_model():\n\
    model = build_model_from_rootfile('"+path_base+theta_input_name+'.root'+"')\n\
    model.fill_histogram_zerobins()\n\
    model.set_signal_processes('ZP*')\n\
    model.add_lognormal_uncertainty('ttbar_rate', 0.15, 'ttbar')\n\
    model.add_lognormal_uncertainty('qcd_rate', 0.15, 'qcd')\n\
"+model_strings+"\
    for p in model.processes:\n\
        if p == 'qcd': continue\n\
        model.add_lognormal_uncertainty('lumi', 0.026, p)\n\
    return model\n\
model = get_model()\n\
model_summary(model)\n\
plot_exp, plot_obs = asymptotic_cls_limits(model,use_data=False)\n\
plot_exp.write_txt('"+path_base+theta_input_name+us+postfix+'.txt'+"')\n\
report.write_html('"+path_base+"htmlout"+us+theta_input_name+us+postfix+"')")
  #theta_config.write("def get_model():\n\
    #model = build_model_from_rootfile('"+path_base+theta_input_name+'.root'+"',include_mc_uncertainties=True)\n\
    #model.fill_histogram_zerobins()\n\
    #model.set_signal_processes('ZP*')\n\
    #model.add_lognormal_uncertainty('xs_top', math.log(1.15), 'ttbar')\n\
    #model.add_lognormal_uncertainty('qcd_norm', math.log(1.10), 'qcd')\n\
#"+model_strings+"\
    #for p in model.processes:\n\
        #model.add_lognormal_uncertainty('lumi', math.log(1.045), p)\n\
        #model.add_lognormal_uncertainty('btag', math.log(1.05), p)\n\
    #return model\n\
#model = get_model()\n\
#model_summary(model)\n\
#plot_exp, plot_obs = asymptotic_cls_limits(model,use_data=False)\n\
#plot_exp.write_txt('"+path_base+theta_input_name+'.txt'+"')\n\
#report.write_html('"+path_base+"htmlout"+us+theta_input_name+"')")
  theta_config.close()

    #model.add_lognormal_uncertainty('signal1000_rate', 0.15, 'ZP1000')\n\
    #model.add_lognormal_uncertainty('signal1250_rate', 0.15, 'ZP1250')\n\
    #model.add_lognormal_uncertainty('signal1500_rate', 0.15, 'ZP1500')\n\
    #model.add_lognormal_uncertainty('signal2000_rate', 0.15, 'ZP2000')\n\
    #model.add_lognormal_uncertainty('signal3000_rate', 0.15, 'ZP3000')\n\
  
  system('python /afs/desy.de/user/u/usaiem/xxl-af-cms/theta/utils2/theta-auto.py '+path_base+theta_input_name+'.py')
#export PYTHONPATH=/afs/desy.de/user/o/ottjoc/xxl-af-cms/python/python-dateutil-1.5:$PYTHONPATH;
  print 'make limit plots'
