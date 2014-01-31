#!/usr/bin/env python
from ROOT import TFile,gROOT,TGraph,TLegend,TCanvas,kBlack,kRed,kBlue,kGreen,kWhite,kGray,kViolet
from array import array
from operator import itemgetter
gROOT.SetBatch()

def getPoints(textfile):
  pairs=[]
  f=open(textfile,'r')
  lines=f.readlines()
  for line in lines[1:]:
    tmp_values=line.split(' ')
    values = filter(None, tmp_values)
    pairs.append([float(values[0])/1000,float(values[1])])#values[2] is band 0 low, values[3] is band 0 high, etc.
  sorted_pairs=sorted(pairs, key=itemgetter(0))
  transposed_pairs=map(list, zip(*sorted_pairs))
  f.close()
  return transposed_pairs

xj = [1.0 , 1.5, 2.0, 3.0]
xs = [0.5,0.625,0.75,1.0,1.25,1.5,2.0,3.0]

approved = [xj,[ 1.35, 0.138, 0.0406, 0.0167 ]]
semiapproved=[xs,[1.91,0.75,0.56,0.35,0.18,0.10,0.034,0.011]]
zero12T = [xj,[ 0.337923, 0.051674, 0.023365, 0.015538 ]]
zero12TDY = [xj,[ 0.331, 0.0526, 0.02074, 0.013285 ]]
zero12TNsub = [xj,[ 0.295444, 0.043939, 0.018019, 0.012209 ]]
zero12TNsubDY = [xj,[ 0.293, 0.0466, 0.0177, 0.0153 ]]
twoT = [xj,[0.359, 0.05528, 0.02544, 0.02167]]
twoTNsub = [xj,[ 0.3272, 0.0521, 0.02204, 0.02042 ]]

limit_legend_names=['B2G-12-006','B2G-12-005',"Justin's CMSTT","Emanuele's CMSTT","Emanuele's CMSTT+HTT","HTT"]
#limit_legend_names=["Justin's CMSTT","Emanuele's CMSTT","Emanuele's CMSTT+HTT","HTT"]
limit_colors=[kGray,kBlack,kGreen,kRed,kViolet,kBlue]
#limit_colors=[kRed,kBlue,kGreen,kViolet]
limit_points=[semiapproved,approved]#,zero12TNsubDY]
#limit_points=[zero12TNsubDY]
limit_paths=["/nfs/dust/cms/user/usaiem/ZprimeFullHad/justin.txt","/nfs/dust/cms/user/usaiem/ZprimeFullHad/zphad_012btag_cms.txt","/nfs/dust/cms/user/usaiem/ZprimeFullHad/zphad_012btag_cms_htt.txt","/nfs/dust/cms/user/usaiem/ZprimeFullHad/zphad_012btag_m.txt"]
for i in range(len(limit_paths)):
  limit_points.append(getPoints(limit_paths[i]))

c=TCanvas('limitcanvas','')
c.SetLogy()
legend=TLegend(0.65,0.35,0.999,0.93)
legend.SetFillColor(kWhite)
graphs=[]
for i in range(len(limit_points)):
  graph=TGraph(len(limit_points[i][0]),array('d',limit_points[i][0]),array('d',limit_points[i][1]))
  graph.SetTitle('')
  graph.SetLineWidth(2)
  graph.SetLineColor(limit_colors[i])
  legend.AddEntry(graph,limit_legend_names[i],'l')
  if i==0:
    graph.SetMinimum(0.005)
    graph.SetMaximum(40)
    graph.GetXaxis().SetTitle("m_{Z'} [TeV]")
    graph.GetYaxis().SetTitle("Expected limit #sigma_{Z'} [pb]")
    graph.GetXaxis().SetLimits(0.4,3.1)
    graph.Draw('al')
  else:
    graph.Draw('l')
  graphs.append(graph)
legend.Draw()
c.SaveAs('pdf/zphad_limit.pdf')  

  
  
##print f_m_limit,f_mn_limit
#b2gs=TGraph(len(xs),array('d',xs),array('d',semiapproved))
#b2gs.SetTitle('')
#b2gs.SetLineWidth(2)
#b2gs.SetLineColor(kGray)
#b2g=TGraph(len(xj),array('d',xj),array('d',approved))
#b2g.SetTitle('')
#b2g.SetLineWidth(2)
#b2g.SetLineColor(kBlack)
#j_m=TGraph(len(xj),array('d',xj),array('d',zero12T))
#j_m.SetLineWidth(2)
#j_m.SetLineColor(kRed)
#j_mn=TGraph(len(xj),array('d',xj),array('d',zero12TNsub))
#j_mn.SetLineWidth(2)
#j_mn.SetLineColor(kRed)
#m=TGraph(len(x),array('d',x),array('d',f_m_limit))
#m.SetLineWidth(2)
#m.SetLineColor(kBlue)
#mn=TGraph(len(x),array('d',x),array('d',f_mn_limit))
#mn.SetLineWidth(2)
#mn.SetLineColor(kGreen)
#legend=TLegend(0.7,0.5,0.999,0.93)
#legend.SetFillColor(kWhite)
#legend.AddEntry(b2g,'B2G-12-005','l')
#legend.AddEntry(b2gs,'B2G-12-006','l')
#legend.AddEntry(j_m,"Justin's CMSTT",'l')
#legend.AddEntry(m,"Emanuele's CMSTT",'l')
#legend.AddEntry(mn,"Emanuele's CMSTT+HTT",'l')

#c1=TCanvas('m')
#c1.SetLogy()
#b2g.Draw('al')
#b2g.GetXaxis().SetLimits(0.4,3.1)
#b2g.GetYaxis().SetRangeUser(0.005,40.)
#b2g.GetXaxis().SetTitle("m_{Z'} [TeV]")
#b2g.GetYaxis().SetTitle("Expected limit #sigma_{Z'} [pb]")
#b2gs.Draw('l')
#j_m.Draw('l')
#m.Draw('l')
#legend.Draw()
##c1.SaveAs('pdf/zphad_012btag_cms'+postfix+'.pdf')

#c2=TCanvas('mn')
#c2.SetLogy()
#b2g.Draw('al')
#b2gs.Draw('l')
#j_mn.Draw('l')
#m.Draw('l')
#mn.Draw('l')
#legend.Draw()
#c2.SaveAs('pdf/zphad_012btag_cms2'+postfix+'.pdf')
#c2.SaveAs('pdf/zphad_012btag_cms2'+postfix+'.png')