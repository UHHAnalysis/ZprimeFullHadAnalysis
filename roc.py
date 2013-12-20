from ROOT import TFile,kRed,kBlue,gROOT,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange,TGraph,kTeal,TH2D,TH1F,gStyle,TGraphErrors,kGray,kAzure,Double,TGraphSmooth,TLatex
from array import array
from operator import itemgetter
gROOT.SetBatch()

#f_mistag=TFile('/scratch/hh/dust/naf/cms/user/usai/preselectionTEST2/SemileptonicPreselectionCycle.MC.QCD15to3000.root', "READ")
#f_eff_1=TFile('/scratch/hh/dust/naf/cms/user/usai/preselectionTEST2/SemileptonicPreselectionCycle.MC.TTbarEff_1.root', "READ")
f_mistag=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/RocCycle.MC.QCD15to3000.root', "READ")
f_eff_1=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/RocCycle.MC.TTbarEff_1.root', "READ")
f_eff_2=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/RocCycle.MC.TTbarEff_2.root', "READ")
#f_eff_2=TFile('/scratch/hh/dust/naf/cms/user/usai/preselectionTEST2/SemileptonicPreselectionCycle.MC.TTbarEff_2.root', "READ")
#f_eff_3=TFile('/scratch/hh/dust/naf/cms/user/usai/preselectionTEST2/SemileptonicPreselectionCycle.MC.TTbarEff_3.root', "READ")
titlepostfix='_2'
outfile=TFile("roc"+titlepostfix+".root", "RECREATE")
roc_ptbins = [200,400,600,800,1000,10000]
max_den_ptbin=50#len(roc_ptbins)
max_num_ptbin=50
ndivisions=50
mapdivisions=100
#cut_base = 'histoNoCut/'
cut_base = 'NoCutsHistos/'
den_name_eff = "eff_all"
den_name_mistag = "mistag_all"
num_name_eff = ["eff_roc_tagged200","eff_roc_tagged400","eff_roc_tagged600","eff_roc_tagged800"]
num_name_mistag = ["mistag_roc_tagged200","mistag_roc_tagged400","mistag_roc_tagged600","mistag_roc_tagged800"]

nsteps=50;
wmin=0.0;
wmax=0.5;
nsubmin=0.0;
nsubmax=1.0;
csvmin=0.0;
csvmax=1.0;
nsub_step=(nsubmax-nsubmin)/nsteps;
w_step=(wmax-wmin)/nsteps;
csv_step=(csvmax-csvmin)/nsteps;

den_histo_eff = f_eff_1.Get(cut_base+den_name_eff).Clone('eff_all_merged')
den_histo_eff.Add(f_eff_2.Get(cut_base+den_name_eff))
#den_histo_eff.Add(f_eff_3.Get(cut_base+den_name_eff))
den_histo_mistag = f_mistag.Get(cut_base+den_name_mistag)

num_histo_mistag = []
for i in range(len(num_name_mistag)):
  num_histo_mistag.append(f_mistag.Get(cut_base+num_name_mistag[i]))

num_histo_eff = []
for i in range(len(num_name_eff)):
  num_histo_eff_tmp=f_eff_1.Get(cut_base+num_name_eff[i]).Clone(num_name_eff[i]+'_merged')
  num_histo_eff_tmp.Add(f_eff_2.Get(cut_base+num_name_eff[i]))
  #num_histo_eff_tmp.Add(f_eff_3.Get(cut_base+num_name_eff[i]))
  num_histo_eff.append(num_histo_eff_tmp)

for i in range(50):
  w_value=w_step*i+w_step/2.0
  nsub_value=nsubmin+nsub_step*i+nsub_step/2.0
  csv_value=csvmin+csv_step*i+csv_step/2.0
  print 'i=',i+1,'w=',w_value,'nsub=',nsub_value,'csv=',csv_value
  
def get_eff_mistag(pt_index,x_index,y_index,z_index):
  #mistag_den=den_histo_mistag.Integral(pt_index,max_den_ptbin)
  #eff_den=den_histo_eff.Integral(pt_index,max_den_ptbin)
  #mistag_num=num_histo_mistag[type_index].Integral(x_index,x_index,y_index,y_index,pt_index+1,50)
  #eff_num=num_histo_eff[type_index].Integral(x_index,x_index,y_index,y_index,pt_index+1,50)
  #err_mistag_den=Double(0)
  #err_eff_den=Double(0)
  #err_mistag_num=Double(0)
  #err_eff_num=Double(0)
  #mistag_den=den_histo_mistag.IntegralAndError(pt_index+1,max_den_ptbin,err_mistag_den)
  #eff_den=den_histo_eff.IntegralAndError(pt_index+1,max_den_ptbin,err_eff_den)
  #mistag_num=num_histo_mistag[type_index].IntegralAndError(x_index,x_index,y_index,y_index,pt_index+1,50,err_mistag_num)
  #eff_num=num_histo_eff[type_index].IntegralAndError(x_index,x_index,y_index,y_index,pt_index+1,50,err_eff_num)
  
  #mistag_den=den_histo_mistag.GetBinContent(pt_index+1)
  #eff_den=den_histo_eff.GetBinContent(pt_index+1)
  #mistag_num=num_histo_mistag[type_index].GetBinContent(x_index,y_index,pt_index+1)
  #eff_num=num_histo_eff[type_index].GetBinContent(x_index,y_index,pt_index+1)
  #err_mistag_den=den_histo_mistag.GetBinError(pt_index+1)
  #err_eff_den=den_histo_eff.GetBinError(pt_index+1)
  #err_mistag_num=num_histo_mistag[type_index].GetBinError(x_index,y_index,pt_index+1)
  #err_eff_num=num_histo_eff[type_index].GetBinError(x_index,y_index,pt_index+1)
  #print eff_num, mistag_num
  
  err_mistag_den=Double(0)
  err_eff_den=Double(0)
  mistag_den=den_histo_mistag.IntegralAndError(pt_index+1,max_den_ptbin,err_mistag_den)
  eff_den=den_histo_eff.IntegralAndError(pt_index+1,max_den_ptbin,err_eff_den)
  
  mistag_num=num_histo_mistag[pt_index-1].GetBinContent(x_index,y_index,z_index)
  eff_num=num_histo_eff[pt_index-1].GetBinContent(x_index,y_index,z_index)
  err_mistag_num=num_histo_mistag[pt_index-1].GetBinError(x_index,y_index,z_index)
  err_eff_num=num_histo_eff[pt_index-1].GetBinError(x_index,y_index,z_index)
  #print eff_num, mistag_num
  
  var_w_count=x_index-1
  var_nsub_count=y_index-1
  var_csv_count=z_index-1

  w_value=w_step*var_w_count+w_step/2.0
  nsub_value=nsubmin+nsub_step*var_nsub_count+nsub_step/2.0
  csv_value=csvmin+csv_step*var_csv_count+csv_step/2.0
  
  if eff_den<0.0000000000001:
    eff_den=0.0000000000001
  if mistag_den<0.0000000000001:
    mistag_den=0.0000000000001
  if eff_num<0.0000000000001:
    eff_num=0.0000000000001
  if mistag_num<0.0000000000001:
    mistag_num=0.0000000000001
  return [eff_num/eff_den,mistag_num/mistag_den,(err_eff_num/eff_num+err_eff_den/eff_den)*(eff_num/eff_den),(err_mistag_num/mistag_num+err_mistag_den/mistag_den)*(mistag_num/mistag_den),w_value,nsub_value,csv_value,x_index,y_index,z_index]


  
def make_tgraph(pt_index,xfix=0,yfix=0,zfix=0):
  #effs=[]
  #mistags=[]
  pairs=[]
  print 'getting pairs'
  xran=range(1,ndivisions+1)
  yran=range(1,ndivisions+1)
  zran=range(1,ndivisions+1)
  if xfix!=0:
    xran=[xfix]
  if yfix!=0:
    yran=[yfix]
  if zfix!=0:
    zran=[zfix]
  for x in xran:
    print x
    for y in yran:
      for z in zran:
	pair= get_eff_mistag(pt_index,x,y,z)
        #effs.append(pair[0])
        #mistags.append(pair[1])
        pairs.append(pair)
  print 'sorting'
  sorted_pairs=sorted(pairs, key=itemgetter(0))
  print len(sorted_pairs)
  roc_pairs=[]
  print 'minimizing'
  for i in range(len(sorted_pairs)):
    if i%1000==0: print i,len(roc_pairs)
    if len(roc_pairs)==0:
      roc_pairs.append(sorted_pairs[i])
    else:
      if sorted_pairs[i][1]<=roc_pairs[-1][1]:
        ctrl_list=[]
        if len(roc_pairs)<10000:
	  ctrl_list=reversed(range(len(roc_pairs)))
	else:
	  ctrl_list=reversed(range(len(roc_pairs)-10000,len(roc_pairs)))
	for j in ctrl_list:
	  if sorted_pairs[i][1]<=roc_pairs[j][1]:
	    roc_pairs.pop(j)
	roc_pairs.append(sorted_pairs[i])
      else:
	roc_pairs.append(sorted_pairs[i])
  #print roc_pairs
  sorted_effs=[]
  sorted_mistags=[]
  sorted_err_effs=[]
  sorted_err_mistags=[]
  for i in range(len(roc_pairs)):
    print 'e=',roc_pairs[i][0],'m=',roc_pairs[i][1],'w=',roc_pairs[i][4],'n=',roc_pairs[i][5],'c=',roc_pairs[i][6],roc_pairs[i][7],roc_pairs[i][8],roc_pairs[i][9]
    sorted_effs.append(roc_pairs[i][0])
    sorted_mistags.append(roc_pairs[i][1])
    sorted_err_effs.append(roc_pairs[i][2])
    sorted_err_mistags.append(roc_pairs[i][3])
  return [sorted_effs,sorted_mistags,sorted_err_effs,sorted_err_mistags]
  #tmp_graph=TGraph(len(roc_pairs),array('d',sorted_effs),array('d',sorted_mistags))

def getPoints(type_index,pt_index):
  #mistagden=f_mistag.Get(cut_base+'mistag_all').GetBinContent(pt_index+1)
  #effden=f_eff_1.Get(cut_base+'eff_all').GetBinContent(pt_index+1)
  #effden+=(f_eff_2.Get(cut_base+'eff_all').GetBinContent(pt_index+1))
  mistagden=f_mistag.Get(cut_base+'mistag_all').Integral(pt_index+1,max_den_ptbin)
  effden=f_eff_1.Get(cut_base+'eff_all').Integral(pt_index+1,max_den_ptbin)
  effden+=(f_eff_2.Get(cut_base+'eff_all').Integral(pt_index+1,max_den_ptbin))
  typepostfix=''
  if type_index==1:
    typepostfix='_cvsl'
  if type_index==2:
    typepostfix='_cvsm'
  #mistagnum=f_mistag.Get(cut_base+'mistag_tagged'+typepostfix).GetBinContent(pt_index+1)
  #effnum=f_eff_1.Get(cut_base+'eff_tagged'+typepostfix).GetBinContent(pt_index+1)
  #effnum+=(f_eff_2.Get(cut_base+'eff_tagged'+typepostfix).GetBinContent(pt_index+1))
  mistagnum=f_mistag.Get(cut_base+'mistag_tagged'+typepostfix).Integral(pt_index+1,max_den_ptbin)
  effnum=f_eff_1.Get(cut_base+'eff_tagged'+typepostfix).Integral(pt_index+1,max_den_ptbin)
  effnum+=(f_eff_2.Get(cut_base+'eff_tagged'+typepostfix).Integral(pt_index+1,max_den_ptbin))
  return [[effnum/effden],[mistagnum/mistagden]]
  
def make_canvas(pt_index,title):
  jfile=''
  if pt_index==2:
    jfile='SAVEPLOTS_ROC_TREEMAKER8selected_GenPt400.root'
  if pt_index==3:
    jfile='SAVEPLOTS_ROC_TREEMAKER8selected_GenPt600.root'
  if pt_index==4:
    jfile='SAVEPLOTS_ROC_TREEMAKER8selected_GenPt800.root'
  c=TCanvas(title)
  c.SetLeftMargin(0.15)
  c.SetRightMargin(0.05)
  c.SetBottomMargin(0.15)
  c.SetTopMargin(0.1)
  gs = TGraphSmooth("normal")
  legend=TLegend(0.55,0.2,0.94,0.45)
  legend.SetBorderSize(0)
  legend.SetFillColor(kWhite)
  cmslabel2= TLatex(0.1566092,0.9427966,"Private work");
  cmslabel2.SetTextFont(42)
  cmslabel2.SetLineWidth(2)
  cmslabel2.SetNDC()
  cmslabel2.SetTextSize(0.05508475)
  cmslabel3= TLatex(0.18,0.84,"Matched parton p_{t} > "+title+" GeV/c");
  cmslabel3.SetTextFont(42)
  cmslabel3.SetLineWidth(2)
  cmslabel3.SetNDC()
  cmslabel3.SetTextSize(0.05508475)
  points=make_tgraph(pt_index)
  #tmp_graph0=TGraphErrors(len(points[0]),array('d',points[0]),array('d',points[1]),array('d',points[2]),array('d',points[3]))
  tmp_graph0=TGraph(len(points[0]),array('d',points[0]),array('d',points[1]))
  tmp_smooth=gs.SmoothKern(tmp_graph0,"normal",0.01);
  tmp_graph0=tmp_smooth
  tmp_graph0.GetXaxis().SetLabelSize(0.06)
  tmp_graph0.GetXaxis().SetTitleSize(0.06)
  tmp_graph0.GetXaxis().SetTitleOffset(1.1)
  tmp_graph0.GetYaxis().SetLabelSize(0.06)
  tmp_graph0.GetYaxis().SetTitleSize(0.06)
  tmp_graph0.GetYaxis().SetTitleOffset(1.1)
  #points=make_tgraph(1,pt_index)
  #tmp_graph1=TGraphErrors(len(points[0]),array('d',points[0]),array('d',points[1]),array('d',points[2]),array('d',points[3]))
  #points=make_tgraph(2,pt_index)
  #tmp_graph2=TGraphErrors(len(points[0]),array('d',points[0]),array('d',points[1]),array('d',points[2]),array('d',points[3]))
  #tmp_graph0.SetLineColor(kBlack)
  #tmp_graph0.SetTitle('p_{T}>'+title+'GeV')
  tmp_graph0.SetTitle('')#'p_{T}>'+title+'GeV')
  tmp_graph0.SetLineColor(kBlue)
  #tmp_graph1.SetLineColor(kBlue)
  #tmp_graph2.SetLineColor(kRed)
  tmp_graph0.SetLineWidth(4)
  #tmp_graph1.SetLineWidth(2)
  #tmp_graph2.SetLineWidth(2)
  tmp_graph0.SetMarkerColor(kBlue)
  #tmp_graph1.SetMarkerColor(kBlue)
  #tmp_graph2.SetMarkerColor(kRed)
  tmp_graph0.SetFillColor(kBlue)
  tmp_graph0.SetFillStyle(3190)
  #tmp_graph1.SetFillColor(kBlue)
  #tmp_graph1.SetFillStyle(3190)
  #tmp_graph2.SetFillColor(kRed)
  #tmp_graph2.SetFillStyle(3190)
  legend.AddEntry(tmp_graph0,'HEP + #tau_{3}/#tau_{2} + sub. b-tag optimiz.','l')
  #legend.AddEntry(tmp_graph1,'btag loose','lp')
  #legend.AddEntry(tmp_graph2,'btag medium','lp')
  tmp_graph0.GetXaxis().SetTitle('Top Tag Efficiency')
  tmp_graph0.GetYaxis().SetTitle('Mistag Rate')
  #hh=TH1F('rocroc',';efficiency;mistag',1,0.1,0.6)
  #hh.Fill(0,1000)
  #hh.GetYaxis().SetRangeUser(0,0.2)
  #hh.SetStats(kFALSE)
  #hh.Draw()
  #gStyle.SetOptLogy(1)
  
  op_tmp=get_eff_mistag(pt_index,50,50,1)
  #op_tmp=get_eff_mistag(pt_index,50,50,13)
  #op_tmp=get_eff_mistag(pt_index,18,33,45)
  #op_tmp=get_eff_mistag(pt_index,16,31,35)
  op=[[op_tmp[0]],[op_tmp[1]]]
  op_graph0=TGraph(len(op[0]),array('d',op[0]),array('d',op[1]))
  
  #op_tmp=get_eff_mistag(pt_index,18,33,45)
  op_tmp=get_eff_mistag(pt_index,15,32,34)
  #op_tmp=get_eff_mistag(pt_index,30,40,13)
  op=[[op_tmp[0]],[op_tmp[1]]]
  op_graph1=TGraph(len(op[0]),array('d',op[0]),array('d',op[1]))
  
  #op_tmp=get_eff_mistag(pt_index,50,50,1)
  op_tmp=get_eff_mistag(pt_index,50,50,13)
  #op_tmp=get_eff_mistag(pt_index,18,33,45)
  #op_tmp=get_eff_mistag(pt_index,16,31,35)
  op=[[op_tmp[0]],[op_tmp[1]]]
  op_graph3=TGraph(len(op[0]),array('d',op[0]),array('d',op[1]))
  
  #op=getPoints(0,pt_index)
  #op_graph0=TGraph(len(op[0]),array('d',op[0]),array('d',op[1]))
  #op=getPoints(1,pt_index)
  #op_graph1=TGraph(len(op[0]),array('d',op[0]),array('d',op[1]))
  op=getPoints(2,pt_index)
  op_graph2=TGraph(len(op[0]),array('d',op[0]),array('d',op[1]))
  op_graph0.SetMarkerSize(2)
  op_graph0.SetMarkerStyle(20)
  op_graph0.SetMarkerColor(kBlack)
  op_graph1.SetMarkerSize(2)
  op_graph1.SetMarkerStyle(21)
  op_graph1.SetMarkerColor(kBlack)
  op_graph2.SetMarkerSize(2)
  op_graph2.SetMarkerStyle(22)
  op_graph2.SetMarkerColor(kBlack)
  op_graph3.SetMarkerSize(2)	
  op_graph3.SetMarkerStyle(23)
  op_graph3.SetMarkerColor(kBlack)
  c.SetLogy()
  tmp_graph0.GetXaxis().SetLimits(0.,.55)
  #tmp_graph1.GetXaxis().SetLimits(0.,1.)
  #tmp_graph2.GetXaxis().SetLimits(0.,1.)
  tmp_graph0.GetYaxis().SetRangeUser(0.00004,.11)
  #tmp_graph1.GetYaxis().SetRangeUser(0.0001,.2)
  #tmp_graph2.GetYaxis().SetRangeUser(0.0001,.2)
  tmp_graph0.Draw('alx')
  #tmp_graph4=tmp_graph0.Clone()
  #tmp_graph4.Draw('lp3')
  #tmp_graph1.Draw('lp')
  #tmp_graph2.Draw('lp')
  op_graph0.Draw('p')
  op_graph1.Draw('p')
  op_graph2.Draw('p')
  op_graph3.Draw('p')
  
  #points=make_tgraph(pt_index,0,0,13)
  #tmp_graph1=TGraph(len(points[0]),array('d',points[0]),array('d',points[1]))
  #tmp_graph1.Draw('lp')
  
  if jfile!='':
    jfilef=TFile(jfile, "READ")
    cmstt=jfilef.Get('GROC_CMS_BTAG_TAU32OP')
    cmstt.SetLineColor(kRed)
    cmstt.SetLineWidth(4)
    cmstt.Draw('l')
    legend.AddEntry(cmstt,'CMS + #tau_{3}/#tau_{2} + sub. b-tag optimiz.','l')
  #legend.AddEntry(op_graph0,'HEP WP','p')
  #legend.AddEntry(op_graph1,'HEP + sub. b-tag loose WP','p')
  legend.AddEntry(op_graph1,'HEP tight WP (CSVM + N-subj.)','p')
  legend.AddEntry(op_graph2,'HEP medium WP (CSVM)','p')
  legend.AddEntry(op_graph3,'HEP loose WP (wide HTT bands + CSVL)','p')
  legend.AddEntry(op_graph0,'HEP very loose WP (wide HTT bands)','p')

  legend.Draw()
  #cmslabel2.Draw()
  cmslabel3.Draw()
  c.SaveAs('ROC_'+title+titlepostfix+'.pdf')
  c.SaveAs('ROC_'+title+titlepostfix+'.png')
  outfile.cd()
  #c.Write()
  c.Write('Canvas'+title)
  tmp_graph0.Write('ROC_HTT_BTAG_TAU32_GenPt'+title)
  op_graph0.Write('OPPOINT_VERYLOOSE_GenPt'+title)
  op_graph3.Write('OPPOINT_LOOSE_GenPt'+title)
  op_graph1.Write('OPPOINT_TIGHT_GenPt'+title)
  op_graph2.Write('OPPOINT_MEDIUM_GenPt'+title)

make_canvas(1,'200')
make_canvas(2,'400')
make_canvas(3,'600')
make_canvas(4,'800')
#tmp_graph0.Write()
#effs=[]
#mistags=[]
#pairs=[]
#for x in range(1,ndivisions+1):
  #for y in range(1,ndivisions+1):
    #pair= get_eff_mistag(0,1,x,y)
    #effs.append(pair[0])
    #mistags.append(pair[1])
    #pairs.append(pair)
#sorted_pairs=sorted(pairs, key=itemgetter(0))
#roc_pairs=[]

#mistageff_map = TH2D('mistageff_map',";Eff;Mistag",mapdivisions,min(effs),max(effs),mapdivisions,min(mistags),max(mistags))
#for i in range(len(effs)):
  #mistageff_map.Fill(effs[i],mistags[i])
#c=TCanvas('a')
##tmp_graph.Draw('alp')
#mistageff_map.Draw('COLZ')
#c.SaveAs('c.pdf')
#mistageff_map.Write()
##tmp_graph.Write()
#c.Write()
outfile.Close()

