#!/usr/bin/env python
#from subprocess import check_output,call
from os import system
from ROOT import TFile,gROOT,THStack,TCanvas,TLegend,kRed,kYellow,kWhite,TLatex,kBlue
from sys import argv

print 'setup'

dolimits=True
doplots=True
dolimitplot=False

gROOT.SetBatch()
postfix=''
path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
process_list_signal_wide=['ZAnalysisCycle.MC.ZP750W75.root','ZAnalysisCycle.MC.ZP500W50.root','ZAnalysisCycle.MC.P4000W400.root','ZAnalysisCycle.MC.ZP3000W300.root','ZAnalysisCycle.MC.ZP1000W100.root','ZAnalysisCycle.MC.ZP1250W125.root','ZAnalysisCycle.MC.ZP1500W150.root','ZAnalysisCycle.MC.ZP2000W200.root']
#process_list_signal_narrow=['ZAnalysisCycle.MC.ZP750W7p5.root','ZAnalysisCycle.MC.ZP500W5.root','ZAnalysisCycle.MC.ZP4000W40.root','ZAnalysisCycle.MC.ZP3000W30.root','ZAnalysisCycle.MC.ZP1000W10.root','ZAnalysisCycle.MC.ZP1250W12p5.root','ZAnalysisCycle.MC.ZP1500W15.root','ZAnalysisCycle.MC.ZP2000W20.root']
process_list_signal_narrow=['ZAnalysisCycle.MC.ZP500W5.root','ZAnalysisCycle.MC.ZP750W7p5.root','ZAnalysisCycle.MC.ZP1000W10.root','ZAnalysisCycle.MC.ZP1250W12p5.root','ZAnalysisCycle.MC.ZP1500W15.root','ZAnalysisCycle.MC.ZP2000W20.root','ZAnalysisCycle.MC.ZP3000W30.root']
process_names_signal_narrow=[]
for i in range(len(process_list_signal_narrow)):
  process_names_signal_narrow.append(process_list_signal_narrow[i].split('.')[2].split('W')[0][2:])
print process_names_signal_narrow
process_list_ttbar=['ZAnalysisCycle.MC.TTbarHad.root','ZAnalysisCycle.MC.TTbarLept.root','ZAnalysisCycle.MC.TTbarSemi.root']
process_list_qcd=['ZAnalysisCycle.MC.QCD_HT-1000ToInf.root','ZAnalysisCycle.MC.QCD_HT-100To250.root','ZAnalysisCycle.MC.QCD_HT-250To500.root','ZAnalysisCycle.MC.QCD_HT-500To1000.root']
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
  command_list='hadd -v 0 -f '+path_base+outputname+'.root'
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
ttbar_filename=hadd(process_list_ttbar,'theta_ttbar')
qcd_filename=hadd(process_list_qcd,'theta_qcd')
ttbar_file=TFile(ttbar_filename,'READ')
background_filename=path_base+'BackgroundCycle.DATA.DATA.root'
data_filename=path_base+'ZAnalysisCycle.DATA.DATA.root'
qcd_file=TFile(qcd_filename,'READ')
backgound_file=TFile(background_filename,'READ')
data_file=TFile(data_filename,'READ')
signal_files=[]
for i in range(len(process_list_signal_narrow)):
  tmp_file=TFile(path_base+process_list_signal_narrow[i],'READ')
  signal_files.append(tmp_file)

if doplots:
  print 'make histos'

  
  def make_plot(histo_name,cut_name):
    legend=TLegend(0.7,0.6,0.989,0.89)
    legend.SetFillColor(kWhite)
    legend.SetBorderSize(0)
    stack=THStack(histo_name+us+cut_name+us+'stack','')
    ttbar_histo=ttbar_file.Get(cut_name+'/'+histo_name).Clone('ttbar'+us+histo_name+us+cut_name)
    qcd_histo=qcd_file.Get(cut_name+'/'+histo_name).Clone('qcd'+us+histo_name+us+cut_name)
    data_histo=data_file.Get(cut_name+'/'+histo_name).Clone('data'+us+histo_name+us+cut_name)
    bkg_histo_name=''
    if '_0btag_' in cut_name:
      bkg_histo_name='Mtt0'
    elif '_1btag_' in cut_name:
      bkg_histo_name='Mtt1'
    elif '_2btag_' in cut_name:
      bkg_histo_name='Mtt2'
    bkg_histo=backgound_file.Get('BaseHistos/'+bkg_histo_name).Clone('bkg'+us+histo_name+us+cut_name)
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
    legend.AddEntry(data_histo,'Data','f')
    legend.AddEntry(ttbar_histo,'t#bar{t}','f')
    #legend.AddEntry(qcd_histo,'QCD','f')
    legend.AddEntry(bkg_histo,'Data driven QCD','f')
    stack.Add(ttbar_histo)
    #stack.Add(qcd_histo)
    stack.Add(bkg_histo)
    cmslabel=TLatex(0.15,0.925,"CMS Preliminary #sqrt{s} = 8TeV  19.7 fb^{-1}")
    cmslabel.SetTextSize(0.07)
    cmslabel.SetNDC()
    cmslabel.SetTextFont(42)
    #cmslabel.SetLineWidth(5)
    signal1000=signal_files[process_names_signal_narrow.index('1000')].Get(cut_name+'/'+histo_name).Clone('ZP1000'+us+histo_name+us+cut_name)
    signal2000=signal_files[process_names_signal_narrow.index('2000')].Get(cut_name+'/'+histo_name).Clone('ZP2000'+us+histo_name+us+cut_name)
    signal3000=signal_files[process_names_signal_narrow.index('3000')].Get(cut_name+'/'+histo_name).Clone('ZP3000'+us+histo_name+us+cut_name)
    signal1000.SetLineWidth(2)
    signal1000.SetLineStyle(2)
    signal2000.SetLineWidth(2)
    signal2000.SetLineStyle(3)
    signal3000.SetLineWidth(2)
    signal3000.SetLineStyle(4)
    signal1000.Scale(10.0)
    signal2000.Scale(10.0)
    signal3000.Scale(10.0)
    legend.AddEntry(signal1000,"Z' 1TeV #times 10",'l')
    legend.AddEntry(signal2000,"Z' 2TeV #times 10",'l')
    legend.AddEntry(signal3000,"Z' 3TeV #times 10",'l')
    canvas=TCanvas(histo_name+us+cut_name+us+'canvas')#,'',100,100)
    canvas.SetLeftMargin(0.15)
    canvas.SetRightMargin(0.01)
    canvas.SetTopMargin(0.10)
    canvas.SetBottomMargin(0.15)
    stack.Draw('hist')
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
    signal1000.Draw('samehisto')
    signal2000.Draw('samehisto')
    signal3000.Draw('samehisto')
    legend.Draw()
    cmslabel.Draw()
    outfile.cd(cut_name)
    canvas.Write()
    canvas.SaveAs('pdf/'+canvas.GetName()+'.pdf')
    
  #for i in range(len(histo_name_list)):
  #  for j in range(len(histo_folder_list)):
  make_plot('Mtt','had_0btag_m')
  make_plot('Mtt','had_1btag_m')
  make_plot('Mtt','had_2btag_m')
  
  stack1=THStack('ZP1000stack','')
  stack2=THStack('ZP2000stack','')
  histo_name_list.index("SubLeadingTopCandidatePt")
  sig1htt=signal_files[process_names_signal_narrow.index('1250')].Get('had_012btag_m/SubLeadingTopCandidatePt').Clone('sig1htt')
  sig2htt=signal_files[process_names_signal_narrow.index('2000')].Get('had_012btag_m/SubLeadingTopCandidatePt').Clone('sig2htt')
  sig1cms=signal_files[process_names_signal_narrow.index('1250')].Get('had_012btag_cms/SubLeadingTopCandidatePt').Clone('sig1cms')
  sig2cms=signal_files[process_names_signal_narrow.index('2000')].Get('had_012btag_cms/SubLeadingTopCandidatePt').Clone('sig2cms')
  #sig1htt.SetFillColor(kBlue)
  #sig2htt.SetFillColor(kBlue)
  #sig1cms.SetFillColor(kRed)
  #sig2cms.SetFillColor(kRed)
  sig1htt.SetLineColor(kBlue)
  sig2htt.SetLineColor(kBlue)
  sig1cms.SetLineColor(kRed)
  sig2cms.SetLineColor(kRed)
  sig1htt.SetLineWidth(3)
  sig2htt.SetLineWidth(3)
  sig1cms.SetLineWidth(3)
  sig2cms.SetLineWidth(3)
  stack1.Add(sig1htt)
  stack1.Add(sig1cms)
  stack2.Add(sig2htt)
  stack2.Add(sig2cms)
  cs1=TCanvas('cs1')
  stack1.Draw('histnostack')
  stack1.GetXaxis().SetTitle('p_{T} GeV')
  stack1.GetYaxis().SetTitle('Events')
  cs1.SaveAs('pdf/stack1.pdf')
  cs2=TCanvas('cs2')
  stack2.Draw('histnostack')
  stack2.GetXaxis().SetTitle('p_{T} GeV')
  stack2.GetYaxis().SetTitle('Events')
  cs2.SaveAs('pdf/stack2.pdf')
  
  
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
  model_strings=""
  for i in range(len(process_list_signal_narrow)):
    model_strings+="    model.add_lognormal_uncertainty('signal"+process_names_signal_narrow[i]+"_rate', 0.15, 'ZP"+process_names_signal_narrow[i]+"')\n"
  theta_config = open(path_base+theta_input_name+'.py', 'w')
  #theta_config.write("def get_model():\n\
    #model = build_model_from_rootfile('"+path_base+theta_input_name+'.root'+"')\n\
    #model.fill_histogram_zerobins()\n\
    #model.set_signal_processes('ZP*')\n\
    #model.add_lognormal_uncertainty('ttbar_rate', 0.15, 'ttbar')\n\
    #model.add_lognormal_uncertainty('qcd_rate', 0.15, 'qcd')\n\
#"+model_strings+"\
    #for p in model.processes:\n\
        #if p == 'qcd': continue\n\
        #model.add_lognormal_uncertainty('lumi', 0.026, p)\n\
    #return model\n\
#model = get_model()\n\
#model_summary(model)\n\
#plot_exp, plot_obs = asymptotic_cls_limits(model,use_data=False)\n\
#plot_exp.write_txt('"+path_base+theta_input_name+'.txt'+"')\n\
#report.write_html('"+path_base+"htmlout"+us+theta_input_name+"')")
  theta_config.write("def get_model():\n\
    model = build_model_from_rootfile('"+path_base+theta_input_name+'.root'+"',include_mc_uncertainties=True)\n\
    model.fill_histogram_zerobins()\n\
    model.set_signal_processes('ZP*')\n\
    model.add_lognormal_uncertainty('xs_top', math.log(1.15), 'ttbar')\n\
    model.add_lognormal_uncertainty('qcd_norm', math.log(1.10), 'qcd')\n\
"+model_strings+"\
    for p in model.processes:\n\
        model.add_lognormal_uncertainty('lumi', math.log(1.045), p)\n\
        model.add_lognormal_uncertainty('btag', math.log(1.05), p)\n\
    return model\n\
model = get_model()\n\
model_summary(model)\n\
plot_exp, plot_obs = asymptotic_cls_limits(model,use_data=False)\n\
plot_exp.write_txt('"+path_base+theta_input_name+'.txt'+"')\n\
report.write_html('"+path_base+"htmlout"+us+theta_input_name+"')")
  theta_config.close()

    #model.add_lognormal_uncertainty('signal1000_rate', 0.15, 'ZP1000')\n\
    #model.add_lognormal_uncertainty('signal1250_rate', 0.15, 'ZP1250')\n\
    #model.add_lognormal_uncertainty('signal1500_rate', 0.15, 'ZP1500')\n\
    #model.add_lognormal_uncertainty('signal2000_rate', 0.15, 'ZP2000')\n\
    #model.add_lognormal_uncertainty('signal3000_rate', 0.15, 'ZP3000')\n\
  
  system('python /afs/desy.de/user/u/usaiem/xxl-af-cms/theta/utils2/theta-auto.py '+path_base+theta_input_name+'.py')
#export PYTHONPATH=/afs/desy.de/user/o/ottjoc/xxl-af-cms/python/python-dateutil-1.5:$PYTHONPATH;
  print 'make limit plots'
