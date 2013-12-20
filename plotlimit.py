#!/usr/bin/env python
from ROOT import TFile,gROOT,TGraph,TLegend,TCanvas,kBlack,kRed,kBlue,kGreen,kWhite,kGray
from array import array
gROOT.SetBatch()

doy=False

xj = [1.0 , 1.5, 2.0, 3.0]
xs = [0.5,0.625,0.75,1.0,1.25,1.5,2.0,3.0]
x = [0.5,0.75,1.0,1.25,1.5,2.0,3.0]

approved = [ 1.35, 0.138, 0.0406, 0.0167 ]
semiapproved=[1.91,0.75,0.56,0.35,0.18,0.10,0.034,0.011]
zero12T = [ 0.337923, 0.051674, 0.023365, 0.015538 ]
zero12TDY = [ 0.331, 0.0526, 0.02074, 0.013285 ]
zero12TNsub = [ 0.295444, 0.043939, 0.018019, 0.012209 ]
zero12TNsubDY = [ 0.293, 0.0466, 0.0177, 0.0153 ]

postfix=''
if doy:
  zero12T=zero12TDY
  zero12TNsub=zero12TNsubDY
  postfix='y'

twoT = [0.359, 0.05528, 0.02544, 0.02167]
twoTNsub = [ 0.3272, 0.0521, 0.02204, 0.02042 ]
#zero12T=twoT
#zero12TNsub=twoTNsub

f_m = open("/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/zphad_012btag_l"+postfix+".txt", "r" )
f_mn = open("/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/zphad_012btag_ln"+postfix+".txt", "r" )
f_m_lines=f_m.readlines()
f_mn_lines=f_mn.readlines()
f_m.close()
f_mn.close()

f_m_limit=[0.0,0.0,0.0,0.0,0.0,0.0,0.0]
for line in f_m_lines:
  values=line.split(' ')
  clean_values = filter(None, values)
  if clean_values[0]=='500': f_m_limit[0]=float(clean_values[1])
  if clean_values[0]=='750': f_m_limit[1]=float(clean_values[1])
  if clean_values[0]=='1000': f_m_limit[2]=float(clean_values[1])
  if clean_values[0]=='1250': f_m_limit[3]=float(clean_values[1])
  if clean_values[0]=='1500': f_m_limit[4]=float(clean_values[1])
  if clean_values[0]=='2000': f_m_limit[5]=float(clean_values[1])
  if clean_values[0]=='3000': f_m_limit[6]=float(clean_values[1])
print f_m_limit
f_mn_limit=[0.0,0.0,0.0,0.0,0.0,0.0,0.0]
for line in f_mn_lines:
  values=line.split(' ')
  clean_values = filter(None, values)
  if clean_values[0]=='500': f_mn_limit[0]=float(clean_values[1])
  if clean_values[0]=='750': f_mn_limit[1]=float(clean_values[1])
  if clean_values[0]=='1000': f_mn_limit[2]=float(clean_values[1])
  if clean_values[0]=='1250': f_mn_limit[3]=float(clean_values[1])
  if clean_values[0]=='1500': f_mn_limit[4]=float(clean_values[1])
  if clean_values[0]=='2000': f_mn_limit[5]=float(clean_values[1])
  if clean_values[0]=='3000': f_mn_limit[6]=float(clean_values[1])
  
#print f_m_limit,f_mn_limit
b2gs=TGraph(len(xs),array('d',xs),array('d',semiapproved))
b2gs.SetTitle('')
b2gs.SetLineWidth(2)
b2gs.SetLineColor(kGray)
b2g=TGraph(len(xj),array('d',xj),array('d',approved))
b2g.SetTitle('')
b2g.SetLineWidth(2)
b2g.SetLineColor(kBlack)
j_m=TGraph(len(xj),array('d',xj),array('d',zero12T))
j_m.SetLineWidth(2)
j_m.SetLineColor(kRed)
j_mn=TGraph(len(xj),array('d',xj),array('d',zero12TNsub))
j_mn.SetLineWidth(2)
j_mn.SetLineColor(kRed)
m=TGraph(len(x),array('d',x),array('d',f_m_limit))
m.SetLineWidth(2)
m.SetLineColor(kBlue)
mn=TGraph(len(x),array('d',x),array('d',f_mn_limit))
mn.SetLineWidth(2)
mn.SetLineColor(kBlue)
legend=TLegend(0.7,0.5,0.999,0.93)
legend.SetFillColor(kWhite)
legend.AddEntry(b2g,'B2G-12-005','l')
legend.AddEntry(b2gs,'B2G-12-006','l')
legend.AddEntry(j_m,'CMSTT 0+1+2btag excl','l')
legend.AddEntry(m,'HTT 0+1+2btag excl','l')

c1=TCanvas('m')
c1.SetLogy()
b2g.Draw('al')
b2g.GetXaxis().SetLimits(0.4,3.1)
b2g.GetYaxis().SetRangeUser(0.01,40.)
b2g.GetXaxis().SetTitle("m_{Z'} [TeV]")
b2g.GetYaxis().SetTitle("Expected limit #sigma_{Z'} [pb]")
b2gs.Draw('l')
j_m.Draw('l')
m.Draw('l')
legend.Draw()
c1.SaveAs('pdf/zphad_012btag_l'+postfix+'.pdf')

c2=TCanvas('mn')
c2.SetLogy()
b2g.Draw('al')
b2gs.Draw('l')
j_mn.Draw('l')
mn.Draw('l')
legend.Draw()
c2.SaveAs('pdf/zphad_012btag_ln'+postfix+'.pdf')