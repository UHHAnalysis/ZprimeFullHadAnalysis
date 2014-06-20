#!/usr/bin/env python
#from subprocess import check_output,call
from os import system
from ROOT import TFile,gROOT,THStack,TCanvas,TLegend,kRed,kYellow,kWhite,TLatex,kBlue,TLine,TGraphAsymmErrors,kOrange,kGray,kBlack,TH1F
from sys import argv
from math import sqrt
from array import array

print 'setup'

dolimits=False
doplots=True
dothetafile=True
dolimitplot=False

gROOT.SetBatch()
#postfix=''
path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
process_list_signal_wide=['BackgroundCycle.MC.ZP750W75.root','BackgroundCycle.MC.ZP500W50.root','BackgroundCycle.MC.ZP4000W400.root','BackgroundCycle.MC.ZP3000W300.root','BackgroundCycle.MC.ZP1000W100.root','BackgroundCycle.MC.ZP1250W125.root','BackgroundCycle.MC.ZP1500W150.root','BackgroundCycle.MC.ZP2000W200.root']
#process_list_signal_narrow=['BackgroundCycle.MC.ZP750W7p5.root','BackgroundCycle.MC.ZP500W5.root','BackgroundCycle.MC.ZP4000W40.root','BackgroundCycle.MC.ZP3000W30.root','BackgroundCycle.MC.ZP1000W10.root','BackgroundCycle.MC.ZP1250W12p5.root','BackgroundCycle.MC.ZP1500W15.root','BackgroundCycle.MC.ZP2000W20.root']
process_list_signal_narrow=['BackgroundCycle.MC.ZP750W7p5.root','BackgroundCycle.MC.ZP1000W10.root','BackgroundCycle.MC.ZP1250W12p5.root','BackgroundCycle.MC.ZP1500W15.root','BackgroundCycle.MC.ZP2000W20.root','BackgroundCycle.MC.ZP3000W30.root']
process_list_signal_narrow_bcup=['BackgroundCycle.MC.ZP750W7p5_bcup.root','BackgroundCycle.MC.ZP1000W10_bcup.root','BackgroundCycle.MC.ZP1250W12p5_bcup.root','BackgroundCycle.MC.ZP1500W15_bcup.root','BackgroundCycle.MC.ZP2000W20_bcup.root','BackgroundCycle.MC.ZP3000W30_bcup.root']
process_list_signal_narrow_bcdown=['BackgroundCycle.MC.ZP750W7p5_bcdown.root','BackgroundCycle.MC.ZP1000W10_bcdown.root','BackgroundCycle.MC.ZP1250W12p5_bcdown.root','BackgroundCycle.MC.ZP1500W15_bcdown.root','BackgroundCycle.MC.ZP2000W20_bcdown.root','BackgroundCycle.MC.ZP3000W30_bcdown.root']
process_list_signal_narrow_lightup=['BackgroundCycle.MC.ZP750W7p5_lightup.root','BackgroundCycle.MC.ZP1000W10_lightup.root','BackgroundCycle.MC.ZP1250W12p5_lightup.root','BackgroundCycle.MC.ZP1500W15_lightup.root','BackgroundCycle.MC.ZP2000W20_lightup.root','BackgroundCycle.MC.ZP3000W30_lightup.root']
process_list_signal_narrow_lightdown=['BackgroundCycle.MC.ZP750W7p5_lightdown.root','BackgroundCycle.MC.ZP1000W10_lightdown.root','BackgroundCycle.MC.ZP1250W12p5_lightdown.root','BackgroundCycle.MC.ZP1500W15_lightdown.root','BackgroundCycle.MC.ZP2000W20_lightdown.root','BackgroundCycle.MC.ZP3000W30_lightdown.root']
process_lists_signal_narrow=[process_list_signal_narrow,process_list_signal_narrow_bcup,process_list_signal_narrow_bcdown,process_list_signal_narrow_lightup,process_list_signal_narrow_lightdown]

process_names_signal_narrow=[]
for i in range(len(process_list_signal_narrow)):
  process_names_signal_narrow.append(process_list_signal_narrow[i].split('.')[2].split('W')[0][2:])
#print process_names_signal_narrow
process_list_ttbar=['BackgroundCycle.MC.TTbar.root']#['BackgroundCycle.MC.TTbarHad.root','BackgroundCycle.MC.TTbarLept.root','BackgroundCycle.MC.TTbarSemi.root']
process_list_ttbar_bcup=['BackgroundCycle.MC.TTbarHad_bcup.root','BackgroundCycle.MC.TTbarLept_bcup.root','BackgroundCycle.MC.TTbarSemi_bcup.root']
process_list_ttbar_bcdown=['BackgroundCycle.MC.TTbarHad_bcdown.root','BackgroundCycle.MC.TTbarLept_bcdown.root','BackgroundCycle.MC.TTbarSemi_bcdown.root']
process_list_ttbar_lightup=['BackgroundCycle.MC.TTbarHad_lightup.root','BackgroundCycle.MC.TTbarLept_lightup.root','BackgroundCycle.MC.TTbarSemi_lightup.root']
process_list_ttbar_lightdown=['BackgroundCycle.MC.TTbarHad_lightdown.root','BackgroundCycle.MC.TTbarLept_lightdown.root','BackgroundCycle.MC.TTbarSemi_lightdown.root']
process_list_qcd=['BackgroundCycle.MC.QCD_HT-1000ToInf.root','BackgroundCycle.MC.QCD_HT-250To500.root','BackgroundCycle.MC.QCD_HT-500To1000.root']#,'BackgroundCycle.MC.QCD_HT-100To250.root'
process_list_data=['BackgroundCycle.DATA.MJDATAB.root','BackgroundCycle.DATA.MJDATAC.root','BackgroundCycle.DATA.MJDATAD.root']
#process_list_data=['BackgroundCycle.DATA.MJDATAD.root']
systematics=['','_bcup','_bcdown','_lightup','_lightdown','_scaleup','_scaledown','_httup','_httdown','_subjecup','_subjecdown','_topjerup','_topjerdown','_topjecup','_topjecdown','_topptup','_topptdown']#,'_puup','_pudown']#],'_subjerup','_subjerdown'
theta_sys=['','__btagbc__plus','__btagbc__minus','__btaglight__plus','__btaglight__minus','__q2__plus','__q2__minus','__htt__plus','__htt__minus','__subjec__plus','__subjec__minus','__jer__plus','__jer__minus','__jec__plus','__jec__minus','__toppt__plus','__toppt__minus']#,'__pu__plus','__pu__minus']
ttbar_only_sys=['_scaleup','_scaledown','_topptup','_topptdown']
#theta_signal=['Zprime500','Zprime500w','Zprime750','Zprime750w','Zprime1000','Zprime1000w','Zprime1250','Zprime1250w','Zprime1500','Zprime1500w','Zprime2000','Zprime2000w','Zprime3000','Zprime3000w','Zprime4000','Zprime4000w',"RSG700","RSG1000","RSG1200","RSG1400","RSG1500","RSG1600","RSG1800","RSG2000","RSG2500","RSG3000","RSG3500","RSG4000"]#
theta_signal=['Zprime500','Zprime750','Zprime1000','Zprime1250','Zprime1500','Zprime2000','Zprime3000','Zprime4000']#
#theta_signal=['Zprime500w','Zprime750w','Zprime1000w','Zprime1250w','Zprime1500w','Zprime2000w','Zprime3000w','Zprime4000w']#
#theta_signal=["RSG700","RSG1000","RSG1200","RSG1400","RSG1500","RSG1600","RSG1800","RSG2000","RSG2500","RSG3000","RSG3500","RSG4000"]#
cyclename="BackgroundCycle.MC."
#process_namelist=["ZP500W5","ZP500W50","ZP750W7p5","ZP750W75","ZP1000W10","ZP1000W100","ZP1250W12p5","ZP1250W125","ZP1500W15","ZP1500W150","ZP2000W20","ZP2000W200","ZP3000W30","ZP3000W300","ZP4000W40","ZP4000W400","RSG700","RSG1000","RSG1200","RSG1400","RSG1500","RSG1600","RSG1800","RSG2000","RSG2500","RSG3000","RSG3500","RSG4000"]#
process_namelist=["ZP500W5","ZP750W7p5","ZP1000W10","ZP1250W12p5","ZP1500W15","ZP2000W20","ZP3000W30","ZP4000W40"]#
#process_namelist=["ZP500W50","ZP750W75","ZP1000W100","ZP1250W125","ZP1500W150","ZP2000W200","ZP3000W300","ZP4000W400"]#
#process_namelist=["RSG700","RSG1000","RSG1200","RSG1400","RSG1500","RSG1600","RSG1800","RSG2000","RSG2500","RSG3000","RSG3500","RSG4000"]#

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

#folder='BaseHistos/'
htfolder='HTDatasetHistos/'
mjfolder='QuadJetDatasetHistos/'

for i in histo_folder_list:
  outfile.mkdir(i)
outfile.mkdir('studies')

print 'hadd plots'
def hadd(inputlist,outputname):
  command_list='hadd -f '+path_base+outputname+'.root'#-v 0
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
ttbar_filename= path_base + process_list_ttbar[0]#hadd(process_list_ttbar,'theta_ttbar')
ttbar_filename_bcup=hadd(process_list_ttbar_bcup,'theta_ttbar_bcup')
ttbar_filename_bcdown=hadd(process_list_ttbar_bcdown,'theta_ttbar_bcdown')
ttbar_filename_lightup=hadd(process_list_ttbar_lightup,'theta_ttbar_lightup')
ttbar_filename_lightdown=hadd(process_list_ttbar_lightdown,'theta_ttbar_lightdown')
mjdata_filename=hadd(process_list_data,'theta_mjdata')
qcd_filename=hadd(process_list_qcd,'theta_qcd')
data_filename=path_base+'BackgroundCycle.DATA.DATA.root'
#background_filename=path_base+'BackgroundCycle.DATA.DATA.root'
#backgroundtt_filename=path_base+'bkg_ttbar.root'
#background_file=TFile(background_filename,'READ')
#backgroundtt_file=TFile(backgroundtt_filename,'READ')
ttbar_file=TFile(ttbar_filename,'READ')

ttbar_file_bcup=TFile(ttbar_filename_bcup,'READ')
ttbar_file_bcdown=TFile(ttbar_filename_bcdown,'READ')
ttbar_file_lightup=TFile(ttbar_filename_lightup,'READ')
ttbar_file_lightdown=TFile(ttbar_filename_lightdown,'READ')
ttbar_files=[ttbar_file,ttbar_file_bcup,ttbar_file_bcdown,ttbar_file_lightup,ttbar_file_lightdown]
qcd_file=TFile(qcd_filename,'READ')
#data_file=0
mjdata_file=TFile(mjdata_filename,'READ')
htdata_file=TFile(data_filename,'READ')
bkg_file=TFile('bkg.root','READ')
signal_files=[]
for i in range(len(process_list_signal_narrow)):
  tmp_file=TFile(path_base+process_list_signal_narrow[i],'READ')
  signal_files.append(tmp_file)

if doplots:
  print 'make histos'

  
  def make_plot(histo_name,folder=htfolder): 
    zf=1
    legendstring="HEPTopTagger HT750"
    if folder==mjfolder:
      legendstring="HEPTopTagger QuadJet50"
    legend=TLegend(0.7,0.5,0.945,0.895,legendstring)
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
    if folder==mjfolder:
      data_file=mjdata_file
    else:
      data_file=htdata_file
    data_histo=data_file.Get(folder+measured_histo_name).Clone('data'+us+histo_name)
    bkg_histo=data_file.Get(folder+bkg_histo_name).Clone('bkg'+us+histo_name)#background_file.Get(folder+bkg_histo_name).Clone('bkg'+us+histo_name+us+cut_name)
    bkg_histo_up=bkg_histo.Clone('bkg'+us+histo_name+'_up')
    bkg_histo_down=bkg_histo.Clone('bkg'+us+histo_name+'_down')
    ttbar_histo=ttbar_file.Get(folder+measured_histo_name).Clone('ttbar'+us+histo_name)
    ttbkg_histo=ttbar_file.Get(folder+bkg_histo_name)
    qcd_histo=bkg_histo.Clone("aa")#qcd_file.Get(folder+measured_histo_name).Clone('qcd'+us+histo_name)
    ###mistag error propagation
    sys_diff=[]
    for imtt in range(1,ttbar_histo.GetNbinsX()+1):
      sys_diff.append([])
    for isys in range(1,len(systematics)):
      ttf=TFile(path_base+cyclename+'TTbar'+systematics[isys]+'.root','READ')
      outfile.cd()
      ttbar_tmp=ttf.Get(folder+measured_histo_name).Clone('ttbar'+theta_sys[isys])
      ttbar_tmp.Add(ttbar_histo,-1)
      for imtt in range(1,ttbar_histo.GetNbinsX()+1):
        sys_diff[imtt-1].append(ttbar_tmp.GetBinContent(imtt))
    
    if histo_name=='Mtt0' or histo_name=='Mtt1' or histo_name=='Mtt2':
      #for imtt in range(1,ttbar_histo.GetNbinsX()+1):
      #  sys_diff.append([])
      #for isys in range(1,len(systematics)):
      #  ttf=TFile(path_base+cyclename+'TTbar'+systematics[isys]+'.root','READ')
      #  outfile.cd()
      #  ttbar_tmp=ttf.Get(folder+measured_histo_name).Clone('ttbar'+theta_sys[isys])
      #  ttbar_tmp.Add(ttbar_histo,-1)
      #  for imtt in range(1,ttbar_histo.GetNbinsX()+1):
      #    sys_diff[imtt-1].append(ttbar_tmp.GetBinContent(imtt))
      
      the_pdfsysfilename='thetapdf.root'
      if folder==mjfolder:
        the_pdfsysfilename='mjthetapdf.root'
      pdffile=TFile(the_pdfsysfilename,"READ")
      the_namebase='httbtag'
      if folder==mjfolder:
        the_namebase='mjhttbtag'
      uu='__'
      pdfttbarup=pdffile.Get(the_namebase+histo_name[3]+uu+'ttbar'+uu+'pdf__plus').Clone('pdfup'+the_namebase+histo_name[3])
      pdfttbardown=pdffile.Get(the_namebase+histo_name[3]+uu+'ttbar'+uu+'pdf__minus').Clone('pdfdown'+the_namebase+histo_name[3])
      pdfttbarup.Add(ttbar_histo,-1)
      pdfttbardown.Add(ttbar_histo,-1)
      for imtt in range(1,ttbar_histo.GetNbinsX()+1):
        sys_diff[imtt-1].append(pdfttbarup.GetBinContent(imtt))
        sys_diff[imtt-1].append(pdfttbardown.GetBinContent(imtt))
      #print sys_diff
      mistag_matrix=bkg_file.Get(folder+"Mistag/data_htt/Mistag_data_htt")
      errmtt=data_file.Get(folder+'Err'+histo_name)
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
              dx = sqrt(a1*a1+a2*a2)/ den
                #print mtt_bin,dx
        bkg_histo.SetBinError(mtt_bin, dx * bkg_histo.GetBinContent(mtt_bin))
        bkg_histo_up.SetBinContent(mtt_bin, bkg_histo.GetBinContent(mtt_bin) + dx * bkg_histo.GetBinContent(mtt_bin))
        bkg_histo_down.SetBinContent(mtt_bin, bkg_histo.GetBinContent(mtt_bin) - dx * bkg_histo.GetBinContent(mtt_bin))
    ###
    
    #ttbkg_histo.Scale(0.92*0.95*0.95*0.92)
    bkg_histo.Add(ttbkg_histo,-1.0)######################################## ttbar subtraction
    bkg_histo_up.Add(ttbkg_histo,-1.0)########################################
    bkg_histo_down.Add(ttbkg_histo,-1.0)########################################
    sum_mc=ttbar_histo.Clone('sum_mc'+us+histo_name)
    sum_mc.Add(bkg_histo)
    err=TGraphAsymmErrors(sum_mc)
    sysup=[]
    relsysup=[]
    sysdown=[]
    if True:#histo_name=='Mtt0' or histo_name=='Mtt1' or histo_name=='Mtt2':
      for ierr in range(1,err.GetN()+1):
        eup=0.
        edown=0.
        for i in sys_diff[ierr-1]:
          #print i
          if i<0:
            edown=edown+i*i
          else:
            eup=eup+i*i
        sysup.append(sqrt(eup))
        relsysup.append(sqrt(eup)/(ttbar_histo.GetBinContent(ierr)+0.00000001))
        sysdown.append(sqrt(edown))
        #print eup,err.GetErrorYhigh(ierr)
        lumierr=0.0263*ttbar_histo.GetBinContent(ierr)
        trigerr=0.0202*ttbar_histo.GetBinContent(ierr)
        xserr=0.1618*ttbar_histo.GetBinContent(ierr)
        err.SetPointEYhigh(ierr-1,sqrt(lumierr*lumierr+trigerr*trigerr+xserr*xserr+err.GetErrorYhigh(ierr-1)*err.GetErrorYhigh(ierr-1)+eup))
        err.SetPointEYlow(ierr-1,sqrt(lumierr*lumierr+trigerr*trigerr+xserr*xserr+err.GetErrorYlow(ierr-1)*err.GetErrorYlow(ierr-1)+edown))
    #print relsysup
    sum_mc_noerr=sum_mc.Clone('sum_mc_noerr'+us+histo_name)
    for i in range(1,sum_mc_noerr.GetNbinsX()+1):
      sum_mc_noerr.SetBinError(i,0)
    
    data_histo_noerr=data_histo.Clone('data_noerr'+us+histo_name)
    for i in range(1,data_histo_noerr.GetNbinsX()+1):
      data_histo_noerr.SetBinError(i,0)
    ratio_histo_nodataerr=data_histo_noerr.Clone('ratio_nodataerr'+us+histo_name)
    ratio_histo_nodataerr.Divide(sum_mc)
    ratio_histo_nodataerr2=ratio_histo_nodataerr.Clone('ratio_nodataerr2'+us+histo_name)
    for i in range(1,ratio_histo_nodataerr.GetNbinsX()+1):
      ratio_histo_nodataerr.SetBinContent(i,1)
      #if ratio_histo_nodataerr.GetBinError(i)==0:
	#ratio_histo_nodataerr.SetBinError(i,1.25)
    err_ratio=TGraphAsymmErrors(ratio_histo_nodataerr)
    if True:#histo_name=='Mtt0' or histo_name=='Mtt1' or histo_name=='Mtt2':
      for ierr in range(1,err.GetN()+1):
        if sum_mc.GetBinContent(ierr)>0:
          val=sum_mc.GetBinContent(ierr)
          staterr=sum_mc.GetBinError(ierr)
          #err_ratio.SetPointEYhigh(ierr,sqrt(staterr*staterr/(val*val)+sysup[ierr-1]*sysup[ierr-1]/(val*val)))
          #err_ratio.SetPointEYlow(ierr,sqrt(staterr*staterr/(val*val)+sysdown[ierr-1]*sysdown[ierr-1]/(val*val)))
          #print err.GetErrorYhigh(ierr-1),sqrt(staterr*staterr+sysup[ierr-1]*sysup[ierr-1])
          if data_histo.GetBinContent(ierr)>0:
            err_ratio.SetPointEYhigh(ierr-1,err.GetErrorYhigh(ierr-1)/val)
            err_ratio.SetPointEYlow(ierr-1,err.GetErrorYlow(ierr-1)/val)
          else:
            err_ratio.SetPointEYhigh(ierr-1,0)
            err_ratio.SetPointEYlow(ierr-1,0)

    
    
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
    ratio_histo.GetYaxis().SetTitle('Data/Bkg')
    #ratio_histo.GetXaxis().SetTitle('m_{t#bar{t}} [GeV]')
    ratio_histo.GetYaxis().SetRangeUser(-0.25,2.25)
    ratio_histo.GetYaxis().SetNdivisions(3,2,0)
    #ratio_histo.GetXaxis().SetRangeUser(ratio_histo.GetXaxis().GetXmin(),ratio_histo.GetXaxis().GetXmax()*zf)
    line1=TLine(ratio_histo.GetXaxis().GetXmin(),1.0,ratio_histo.GetXaxis().GetXmax(),1.0)#*zf
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
    cmslabelstring="CMS Preliminary #sqrt{s} = 8TeV  19.7 fb^{-1}"
    if folder==mjfolder:
      cmslabelstring="CMS Preliminary #sqrt{s} = 8TeV  13.8 fb^{-1}"
    cmslabel=TLatex(0.15,0.925,cmslabelstring)
    #cmslabel=TLatex(0.15,0.925,"Private work")
    cmslabel.SetTextSize(0.07)
    cmslabel.SetNDC()
    cmslabel.SetTextFont(42)
    #cmslabel.SetLineWidth(5)
    
    signal1000=signal_files[process_names_signal_narrow.index('750')].Get(folder+measured_histo_name).Clone('ZP1000'+us+histo_name)
    signal2000=signal_files[process_names_signal_narrow.index('1000')].Get(folder+measured_histo_name).Clone('ZP2000'+us+histo_name)
    signal3000=signal_files[process_names_signal_narrow.index('1250')].Get(folder+measured_histo_name).Clone('ZP3000'+us+histo_name)
    signal1000.SetLineWidth(3)
    signal1000.SetLineStyle(1)
    signal2000.SetLineWidth(3)
    signal2000.SetLineStyle(1)
    signal3000.SetLineWidth(3)
    signal3000.SetLineStyle(1)
    signal1000.SetLineColor(28)
    signal2000.SetLineColor(9)
    signal3000.SetLineColor(8)
    signal1000.Scale(3.0)
    signal2000.Scale(3.0)
    signal3000.Scale(3.0)
    legend.AddEntry(signal1000,"Z' 750 GeV 3pb",'l')
    legend.AddEntry(signal2000,"Z' 1.0 TeV 3pb",'l')
    legend.AddEntry(signal3000,"Z' 1.25 TeV 3pb",'l')
    
    mjpostfix=''
    if folder==mjfolder:
      mjpostfix='mj'
    canvas=TCanvas(histo_name+mjpostfix+us+'canvas','',0,0,600,600)#,'',100,100)
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
    stack.SetMaximum(stack.GetMaximum()*1.2)
    stack.GetXaxis().SetTitle("a")#ttbar_histo.GetXaxis().GetTitle())
    stack.GetYaxis().SetTitle('Events')
    stack.GetYaxis().SetLabelSize(0.07)
    stack.GetYaxis().SetTitleSize(0.07)
    stack.GetYaxis().SetTitleOffset(1.15)
    stack.GetXaxis().SetLabelSize(0.07)
    stack.GetXaxis().SetTitleSize(0.07)
    stack.GetXaxis().SetTitleOffset(1.0)
#stack.GetYaxis().SetRangeUser(stack.GetYaxis().GetXmin(),stack.GetYaxis().GetXmax()*1.5)
    
    #stack.GetYaxis().SetLabelSize(0.045)
    #stack.GetYaxis().SetTitleSize(0.045)
    #stack.GetYaxis().SetTitleOffset(1.9)
    #stack.GetXaxis().SetLabelSize(0.045)
    #stack.GetXaxis().SetTitleSize(0.045)
    #stack.GetXaxis().SetTitleOffset(1.5)
    
    #stack.GetXaxis().SetRangeUser(stack.GetXaxis().GetXmin(),stack.GetXaxis().GetXmax()*zf)
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
    canvas.SaveAs('pdf/'+folder+canvas.GetName()+'.pdf')
    bkg_histo.Write()
    bkg_histo_up.Write()
    bkg_histo_down.Write()
    return [bkg_histo,bkg_histo_up,bkg_histo_down]
    
  #for i in range(len(histo_name_list)):
  #  for j in range(len(histo_folder_list)):
  
  
  
  bkg_histos=[]
  make_plot('Mtt012',htfolder)
  bkg_histos.append(make_plot('Mtt0',htfolder))
  bkg_histos.append(make_plot('Mtt1',htfolder))
  bkg_histos.append(make_plot('Mtt2',htfolder))
  make_plot('Mtt012',mjfolder)
  bkg_histos.append(make_plot('Mtt0',mjfolder))
  bkg_histos.append(make_plot('Mtt1',mjfolder))
  bkg_histos.append(make_plot('Mtt2',mjfolder))
  
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
  
  make_plot("m1")
  make_plot("m2")
  make_plot("Njets")
  make_plot("Njets50")
  make_plot("pT4")
  make_plot("spT4")
  make_plot("sToppT")
  make_plot("HT50")
  #make_plot("HTT2D1")
  #make_plot("HTT2D2")
  
  
  
  
  make_plot('Jet1pT012',mjfolder)
  make_plot('Jet1pT0',mjfolder)
  make_plot('Jet1pT1',mjfolder)
  make_plot('Jet1pT2',mjfolder)
  make_plot('Jet2pT012',mjfolder)
  make_plot('Jet2pT0',mjfolder)
  make_plot('Jet2pT1',mjfolder)
  make_plot('Jet2pT2',mjfolder)

  make_plot('Jet1eta012',mjfolder)
  make_plot('Jet1eta0',mjfolder)
  make_plot('Jet1eta1',mjfolder)
  make_plot('Jet1eta2',mjfolder)
  make_plot('Jet2eta012',mjfolder)
  make_plot('Jet2eta0',mjfolder)
  make_plot('Jet2eta1',mjfolder)
  make_plot('Jet2eta2',mjfolder)

  make_plot('Jet1csv012',mjfolder)
  make_plot('Jet1csv0',mjfolder)
  make_plot('Jet1csv1',mjfolder)
  make_plot('Jet1csv2',mjfolder)
  make_plot('Jet2csv012',mjfolder)
  make_plot('Jet2csv0',mjfolder)
  make_plot('Jet2csv1',mjfolder)
  make_plot('Jet2csv2',mjfolder)
  
  make_plot("m1",mjfolder)
  make_plot("m2",mjfolder)
  make_plot("Njets",mjfolder)
  make_plot("Njets50",mjfolder)
  make_plot("pT4",mjfolder)
  make_plot("spT4",mjfolder)
  #make_plot("pT5",mjfolder)
  #make_plot("spT5",mjfolder)
  make_plot("sToppT",mjfolder)
  make_plot("HT50",mjfolder)
  #make_plot("HTT2D1")
  #make_plot("HTT2D2")
  
  
  
  
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

if dothetafile:
  print 'make theta root file'
  
  bt_cat=['0','1','2']
  measuredmtt='MeasuredMtt'
  mtt='Mtt'
  
  htnamebase='httbtag'
  mjnamebase='mjhttbtag'
  uu='__'
  limitfile=TFile("htt"+".root","RECREATE")
  limitfile.cd()
  
  def make_comp(mean_histo,up_histo,down_histo,cname,title,trigger='HT750'):
    legend=TLegend(0.65,0.5,0.945,0.895,"HEPTopTagger "+trigger+" "+title)
    legend.SetFillColor(kWhite)
    legend.SetBorderSize(0)
    legend.SetFillStyle(0)
    canvas=TCanvas(cname+us+'canvas','',0,0,600,600)#,'',100,100)
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
    up_histo.SetLineWidth(3)
    down_histo.SetLineWidth(3)
    mean_histo.SetLineWidth(3)
    mean_histo.SetLineColor(kBlack)
    mean_histo.SetFillColor(0)
    up_histo.SetLineColor(kRed)
    down_histo.SetLineColor(kBlue)
    up_histo.GetYaxis().SetTitle('Events')
    up_histo.GetYaxis().SetLabelSize(0.07)
    up_histo.GetYaxis().SetTitleSize(0.07)
    up_histo.GetYaxis().SetTitleOffset(1.15)
    up_histo.GetXaxis().SetLabelSize(0.07)
    up_histo.GetXaxis().SetTitleSize(0.07)
    up_histo.GetXaxis().SetTitleOffset(1.0)
    up_histo.SetStats(0)
    up_histo.SetMinimum(0.1)
    down_histo.SetStats(0)
    mean_histo.SetStats(0)
    up_histo.Draw('histo')
    down_histo.Draw('histoSAME')
    mean_histo.Draw('histoSAME')
    legend.AddEntry(mean_histo,'normal','l')
    legend.AddEntry(up_histo,'up','l')
    legend.AddEntry(down_histo,'down','l')
    legend.Draw()
    bottom_pad.cd()
    upratio_histo=up_histo.Clone(up_histo.GetName()+'ratio')
    downratio_histo=down_histo.Clone(down_histo.GetName()+'ratio')
    upratio_histo.Divide(mean_histo)
    downratio_histo.Divide(mean_histo)
    upratio_histo.SetStats(0)
    downratio_histo.SetStats(0)
    line1=TLine(upratio_histo.GetXaxis().GetXmin(),1.0,upratio_histo.GetXaxis().GetXmax(),1.0)
    upratio_histo.GetYaxis().SetRangeUser(0.4,1.65)
    upratio_histo.GetYaxis().SetNdivisions(3,2,0)
    #downratio_histo.GetYaxis().SetRangeUser(-0.25,2.25)
    #downratio_histo.GetYaxis().SetNdivisions(3,2,0)
    upratio_histo.SetTitle('') 
    upratio_histo.GetYaxis().SetLabelSize(0.16333)
    upratio_histo.GetYaxis().SetTitleSize(0.16333)
    upratio_histo.GetYaxis().SetTitleOffset(0.4928)
    upratio_histo.GetXaxis().SetLabelSize(0.16333)
    upratio_histo.GetXaxis().SetTitleSize(0.16333)
    upratio_histo.GetXaxis().SetTitleOffset(1.3)
    upratio_histo.GetYaxis().SetTitle('Var/Nor')
    upratio_histo.Draw('histo')
    downratio_histo.Draw('histoSAME')
    line1.SetLineStyle(2)
    line1.Draw()
    canvas.SaveAs('pdf/'+cname+'_comp.pdf')
  
  
  disable_mj= False
  removebins= False
  
  def removebin_save(h):
    #hdummy=TH1F( "Mtt0", "Mtt [GeV];Mtt [GeV];Events", 69, 550, 4000 )
    #binlist=hdummy.GetXaxis().GetXbins()
    #print binlist,binlist.GetSize()
    if removebins:
      binlist=range(550,4050,50)
      hnew=h.Rebin(len(binlist)-1,h.GetName(),array('d',binlist))
      #h.Write(h.GetName()+'old')
      if not disable_mj:
	hnew.Write()
    else:
      if not disable_mj:
	h.Write()
   

  for bt in bt_cat:
    
    #merge pdf
    pdffile=TFile('thetapdf.root',"READ")
    mjpdffile=TFile('mjthetapdf.root',"READ")
    pdfttbarup=pdffile.Get(htnamebase+bt+uu+'ttbar'+uu+'pdf__plus')
    pdfttbardown=pdffile.Get(htnamebase+bt+uu+'ttbar'+uu+'pdf__minus')
    mjpdfttbarup=mjpdffile.Get(mjnamebase+bt+uu+'ttbar'+uu+'pdf__plus')
    mjpdfttbardown=mjpdffile.Get(mjnamebase+bt+uu+'ttbar'+uu+'pdf__minus')
    limitfile.cd()
    pdfttbarup.Write()
    pdfttbardown.Write()
    removebin_save(mjpdfttbarup)
    removebin_save(mjpdfttbardown)
    ttf_mean=TFile(path_base+cyclename+'TTbar'+systematics[0]+'.root','READ')
    mean_histo=ttf_mean.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+'ttbar'+'pdf'+'_mean')
    meanmj_histo=ttf_mean.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+'ttbar'+'pdf'+'_mean')
    make_comp(mean_histo,pdfttbarup,pdfttbardown,htnamebase+bt+uu+'ttbar'+'__pdf',bt+'btag')
    make_comp(meanmj_histo,mjpdfttbarup,mjpdfttbardown,mjnamebase+bt+uu+'ttbar'+'__pdf',bt+'btag','QuadJet50')
    for isgn in range(len(process_namelist)):
      pdftmpup=pdffile.Get(htnamebase+bt+uu+theta_signal[isgn]+uu+'pdf__plus')
      pdftmpdown=pdffile.Get(htnamebase+bt+uu+theta_signal[isgn]+uu+'pdf__minus')
      mjpdftmpup=mjpdffile.Get(mjnamebase+bt+uu+theta_signal[isgn]+uu+'pdf__plus')
      mjpdftmpdown=mjpdffile.Get(mjnamebase+bt+uu+theta_signal[isgn]+uu+'pdf__minus')
      limitfile.cd()
      pdftmpup.Write()
      pdftmpdown.Write()
      removebin_save(mjpdftmpup)
      removebin_save(mjpdftmpdown)
    
    htdata_file.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+'DATA').Write()
    a=mjdata_file.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+'DATA')
    removebin_save(a)
    #a.Scale(16.4/13.8)
    #a.Write()
    
    qcdmean=bkg_histos[int(bt)][0].Clone(htnamebase+bt+uu+'qcd')
    qcdmean.Write()
    qcdmisup=bkg_histos[int(bt)][1].Clone(htnamebase+bt+uu+'qcd'+uu+'misErr__plus')
    qcdmisup.Write()
    qcdmisdown=bkg_histos[int(bt)][2].Clone(htnamebase+bt+uu+'qcd'+uu+'misErr__minus')
    qcdmisdown.Write()
    make_comp(qcdmean,qcdmisup,qcdmisdown,htnamebase+bt+uu+'qcd'+uu+'misErr',bt+'btag')
    
    b=bkg_histos[int(bt)+3][0].Clone(mjnamebase+bt+uu+'qcd')
    removebin_save(b)
    #b.Scale(16.4/13.8)
    #b.Write()
    c=bkg_histos[int(bt)+3][1].Clone(mjnamebase+bt+uu+'qcd'+uu+'misErr__plus')
    removebin_save(c)
    #c.Scale(16.4/13.8)
    #c.Write()
    d=bkg_histos[int(bt)+3][2].Clone(mjnamebase+bt+uu+'qcd'+uu+'misErr__minus')
    removebin_save(d)
    #d.Scale(16.4/13.8)
    #d.Write()
    make_comp(b,c,d,mjnamebase+bt+uu+'qcd'+uu+'misErr',bt+'btag','QuadJet50')
    
    for isys in range(len(systematics)):
      ttf=TFile(path_base+cyclename+'TTbar'+systematics[isys]+'.root','READ')
      limitfile.cd()
      ttf.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+'ttbar'+theta_sys[isys]).Write()
      if isys%2==1:
        ttf_mean=TFile(path_base+cyclename+'TTbar'+systematics[0]+'.root','READ')
        ttf_up=TFile(path_base+cyclename+'TTbar'+systematics[isys]+'.root','READ')
        ttf_down=TFile(path_base+cyclename+'TTbar'+systematics[isys+1]+'.root','READ')
        mean_histo=ttf_mean.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+'ttbar'+theta_sys[isys]+'_mean')
        up_histo=ttf_up.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+'ttbar'+theta_sys[isys]+'_up')
        down_histo=ttf_down.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+'ttbar'+theta_sys[isys]+'_down')
        make_comp(mean_histo,up_histo,down_histo,htnamebase+bt+uu+'ttbar'+theta_sys[isys],bt+'btag')

        meanmj_histo=ttf_mean.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+'ttbar'+theta_sys[isys]+'_mean')
        upmj_histo=ttf_up.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+'ttbar'+theta_sys[isys]+'_up')
        downmj_histo=ttf_down.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+'ttbar'+theta_sys[isys]+'_down')
        make_comp(meanmj_histo,upmj_histo,downmj_histo,mjnamebase+bt+uu+'ttbar'+theta_sys[isys],bt+'btag','QuadJet50')
	
        ttf_mean.Close()
        ttf_up.Close()
        ttf_down.Close()
	
      ee=ttf.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+'ttbar'+theta_sys[isys])
      limitfile.cd()
      removebin_save(ee)
      #ee.Scale(16.4/13.8)
      #ee.Write()
      if systematics[isys] in ttbar_only_sys:
        continue
      for isgn in range(len(process_namelist)):
        tmpf=TFile(path_base+cyclename+process_namelist[isgn]+systematics[isys]+'.root','READ')
        limitfile.cd()
        tmpf.Get(htfolder+measuredmtt+bt).Clone(htnamebase+bt+uu+theta_signal[isgn]+theta_sys[isys]).Write()
        ff=tmpf.Get(mjfolder+measuredmtt+bt).Clone(mjnamebase+bt+uu+theta_signal[isgn]+theta_sys[isys])
        removebin_save(ff)
        #ff.Scale(16.4/13.8)
        #ff.Write()
  
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
