from ROOT import TFile,kRed,kBlue,gROOT,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange,TLatex
gROOT.SetBatch()

#file_list=['sbout_y.root','sbout_noy.root']
file_list=['/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ttbar.root','/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/z.root']


#title_list=['y cut','no y cut']
title_list=['ttbar','signal']

#color_list=[kBlack,kRed,kBlue,kGreen,kOrange]
color_list=[kRed,kBlue,kGreen,kOrange]
##histo_name_list=[['SFbinFS','SFbinFS_NoBkg'],['Toppt_2_DoverD','Toppt_2_DmBoverDmB']]
##histo_name_list=[['SFbinFS_NoBkg']*2,['Toppt_2_SoverS']*2]

#histo_name_list=[["SFbinFS_SFbinFS_eta0p5","SFbinFS_SFbinFS_eta0p5to1p0","SFbinFS_SFbinFS_eta1p0to2p4","SFbinFS_SFbinFS_eta2p4"]]
#histo_name_list=[["SFbinFS_200","SFbinFS_250","SFbinFS_400"]]
histo_name_list=[["Cat_2jet/DeltaY","Cat_2jet/DeltaY"],["Cat_2jet/Nsub","Cat_2jet/Nsub"]]
#histo_name_list=[["sbcanvas2","sbcanvas2"],]

histo_list=[]
tfile_list=[]
for i in range(len(file_list)):
  f=TFile(file_list[i], "READ")
  tfile_list.append(f)
  histo_sublist=[]
  for j in range(len(histo_name_list)):
    h=f.Get(histo_name_list[j][i])
    h.SetLineColor(color_list[i])
    h.SetLineWidth(3)
    h.SetFillColor(kWhite)
    h.SetStats(kFALSE)
    
    #h.GetYaxis().SetTitle("SF")
    #h.GetYaxis().SetTitle("HEPTopTaggerRate")
    
    #h.GetXaxis().SetTitle('p_{T} range')
    #h.GetXaxis().SetTitle('#eta range')
    
    
    h.SetTitle("")
    if i==0:
      h.Scale(0.01)
    #h.SetMaximum(1.5)
    #h.SetMinimum(0.5)
    #h.SetMaximum(0.55)
    #h.SetMinimum(0.15)
    #if j==1:
      #h.SetMaximum(10000)
    #if j==0:
      #h.SetMaximum(5000)
     # h.GetXaxis().SetRangeUser(0.0,750.0)
    histo_sublist.append(h)
  histo_list.append(histo_sublist)
#structure: histo_list[file_list][histo_name_list]
legend=TLegend(0.75,0.85,0.99,0.99)
legend.SetFillColor(kWhite)
for i in range(len(file_list)):
  legend.AddEntry(histo_list[i][0],title_list[i])
canvases=[]
for j in range(len(histo_name_list)):
  canvas=TCanvas(histo_name_list[j][0].replace('/','_')+'_canvas')
  for i in range(len(file_list)):
    #histo_list[i][j].SetLineColor(color_list[i])
    #histo_list[i][j].SetFillColor(kWhite)
    histo_list[i][j].GetXaxis().SetLabelSize(0.06)
    histo_list[i][j].GetXaxis().SetTitleSize(0.06)
    histo_list[i][j].GetXaxis().SetTitleOffset(1.1)
    histo_list[i][j].GetYaxis().SetLabelSize(0.06)
    histo_list[i][j].GetYaxis().SetTitleSize(0.06)
    histo_list[i][j].GetYaxis().SetTitleOffset(1.1)
    if i==0:
      histo_list[i][j].Draw('')
    else:
      histo_list[i][j].Draw('SAME')
  legend.Draw()
  canvas.SetLeftMargin(0.15)
  canvas.SetRightMargin(0.10)
  canvas.SetBottomMargin(0.15)
  canvas.SetTopMargin(0.05)
  #tex = TLatex(0.38,0.96,"CMS Simulation Preliminary, #sqrt{s} = 8 TeV")
  #tex.SetNDC()
  #tex.SetTextAlign(13)
  ##tex.SetTextSize(0.055)
  #tex.SetLineWidth(2)
  #tex.Draw()
  #tex2 = TLatex(0.15,0.85,"#splitline{#mu+jets sample}{(HEPTopTagger subjets)}")
  #tex2.SetNDC()
  #tex2.SetTextAlign(13)
  #tex2.SetTextSize(0.055)
  #tex2.SetLineWidth(2)
  #tex2.Draw()

  #canvas.SaveAs('compareout_'+histo_name_list[j][0].replace('/','_')+'_DmB.pdf')
  #canvas.SaveAs('compareout_'+histo_name_list[j][0].replace('/','_')+'_tpr.pdf')
  canvas.SaveAs('compareout_'+histo_name_list[j][0].replace('/','_')+'_a.pdf')
  canvas.SaveAs('compareout_'+histo_name_list[j][0].replace('/','_')+'_a.C')
  canvases.append(canvas)


  
      
      



#out=TFile("compareout.root", "RECREATE")
