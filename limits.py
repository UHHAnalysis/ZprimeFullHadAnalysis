#!/usr/bin/env python
#from subprocess import check_output,call
from os import system
from ROOT import TFile,gROOT,THStack,TCanvas,TLegend,kRed,kYellow,kWhite,TLatex
from sys import argv

print 'setup'

dolimits=True
doplots=False
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
  command_list='hadd -f '+path_base+outputname+'.root'
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
ttbar_filename=hadd(process_list_ttbar,'theta_ttbar')
qcd_filename=hadd(process_list_qcd,'theta_qcd')
ttbar_file=TFile(ttbar_filename,'READ')
qcd_file=TFile(qcd_filename,'READ')
signal_files=[]
for i in range(len(process_list_signal_narrow)):
  tmp_file=TFile(path_base+process_list_signal_narrow[i],'READ')
  signal_files.append(tmp_file)

if doplots:
  print 'make histos'

  
  def make_plot(histo_name,cut_name):
    legend=TLegend(0.6,0.6,0.9,0.9)
    legend.SetFillColor(kWhite)
    legend.SetBorderSize(0)
    stack=THStack(histo_name+us+cut_name+us+'stack','')
    ttbar_histo=ttbar_file.Get(cut_name+'/'+histo_name).Clone('ttbar'+us+histo_name+us+cut_name)
    qcd_histo=qcd_file.Get(cut_name+'/'+histo_name).Clone('qcd'+us+histo_name+us+cut_name)
    ttbar_histo.SetFillColor(kRed)
    qcd_histo.SetFillColor(kYellow)
    ttbar_histo.SetLineColor(kRed)
    qcd_histo.SetLineColor(kYellow)
    ttbar_histo.SetMarkerColor(kRed)
    qcd_histo.SetMarkerColor(kYellow)
    legend.AddEntry(ttbar_histo,'t#bar{t}','f')
    legend.AddEntry(qcd_histo,'QCD','f')
    stack.Add(ttbar_histo)
    stack.Add(qcd_histo)
    cmslabel=TLatex(0.3,0.87,"CMS Preliminary #sqrt{s} = 8TeV  19.7 fb^{-1}")
    cmslabel.SetNDC()
    signal1000=signal_files[process_names_signal_narrow.index('1000')].Get(cut_name+'/'+histo_name).Clone('ZP1000'+us+histo_name+us+cut_name)
    signal2000=signal_files[process_names_signal_narrow.index('2000')].Get(cut_name+'/'+histo_name).Clone('ZP2000'+us+histo_name+us+cut_name)
    signal3000=signal_files[process_names_signal_narrow.index('3000')].Get(cut_name+'/'+histo_name).Clone('ZP3000'+us+histo_name+us+cut_name)
    signal1000.SetLineWidth(2)
    signal1000.SetLineStyle(2)
    signal2000.SetLineWidth(2)
    signal2000.SetLineStyle(3)
    signal3000.SetLineWidth(2)
    signal3000.SetLineStyle(4)
    legend.AddEntry(signal1000,"Z'1TeV",'l')
    legend.AddEntry(signal2000,"Z'2TeV",'l')
    legend.AddEntry(signal3000,"Z'3TeV",'l')
    canvas=TCanvas(histo_name+us+cut_name+us+'canvas')
    stack.Draw('hist')
    signal1000.Draw('samel')
    signal2000.Draw('samel')
    signal3000.Draw('samel')
    legend.Draw()
    cmslabel.Draw()
    outfile.cd(cut_name)
    canvas.Write()
    canvas.SaveAs('pdf/'+canvas.GetName()+'.pdf')
    
  make_plot(histo_name_list[1],histo_folder_list[1])
    
  
  
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

  cut_types=['cms','htt']
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
plot_exp.write_txt('"+path_base+theta_input_name+'.txt'+"')\n\
report.write_html('"+path_base+"htmlout"+us+theta_input_name+"')")
  theta_config.close()

    #model.add_lognormal_uncertainty('signal1000_rate', 0.15, 'ZP1000')\n\
    #model.add_lognormal_uncertainty('signal1250_rate', 0.15, 'ZP1250')\n\
    #model.add_lognormal_uncertainty('signal1500_rate', 0.15, 'ZP1500')\n\
    #model.add_lognormal_uncertainty('signal2000_rate', 0.15, 'ZP2000')\n\
    #model.add_lognormal_uncertainty('signal3000_rate', 0.15, 'ZP3000')\n\
  
  system('python /afs/desy.de/user/u/usaiem/xxl-af-cms/theta/utils2/theta-auto.py '+path_base+theta_input_name+'.py')

  print 'make limit plots'