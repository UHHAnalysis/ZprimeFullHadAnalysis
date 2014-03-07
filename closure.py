from ROOT import TFile,kRed,kBlue,gROOT,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange,TLine
gROOT.SetBatch()

#f=TFile('dust/theta_qcd.root', "READ")
f=TFile('dust/BackgroundCycle.MC.QCD_HT-500To1000.root', "READ")
outfile=TFile("closure.root", "RECREATE")

ratio0=f.Get('BaseHistos/MeasuredMtt0').Clone('ratio0')
ratio0den=f.Get('BaseHistos/Mtt0').Clone('ratio0den')
ratio1=f.Get('BaseHistos/MeasuredMtt1').Clone('ratio1')
ratio1den=f.Get('BaseHistos/Mtt1').Clone('ratio1den')
ratio2=f.Get('BaseHistos/MeasuredMtt2').Clone('ratio2')
ratio2den=f.Get('BaseHistos/Mtt2').Clone('ratio2den')

outfile.cd()
#ratio0.Rebin(2)
#ratio0den.Rebin(2)
#ratio1.Rebin(4)
#ratio1den.Rebin(4)
#ratio2.Rebin(4)
#ratio2den.Rebin(4)
ratio0.Divide(ratio0den)
ratio0.GetYaxis().SetRangeUser(0.,2.)
ratio0.SetLineWidth(3)
#ratio0.Write('zero')
#ratiocanvas0=TCanvas()
#ratio0.Draw()
line=TLine(0,1.0,4000,1.0)
#line.Draw('same')
#ratiocanvas0.Write('ratio0')
ratio1.Divide(ratio1den)
ratio1.GetYaxis().SetRangeUser(0.,2.)
ratio1.SetLineWidth(3)
#ratio1.Write('uno')
ratio2.Divide(ratio2den)
ratio2.GetYaxis().SetRangeUser(0.,2.)
ratio2.SetLineWidth(3)
#ratio2.Write('due')

measured0=f.Get('BaseHistos/MeasuredMtt0').Clone('measured0')
predicted0=f.Get('BaseHistos/Mtt0').Clone('predicted0')
measured1=f.Get('BaseHistos/MeasuredMtt1').Clone('measured1')
predicted1=f.Get('BaseHistos/Mtt1').Clone('predicted1')
measured2=f.Get('BaseHistos/MeasuredMtt2').Clone('measured2')
predicted2=f.Get('BaseHistos/Mtt2').Clone('predicted2')

legend=TLegendlegend=TLegend(0.6,0.5,0.989,0.89)
legend.SetFillColor(kWhite)
legend.SetBorderSize(0)
legend.AddEntry(measured0,'measured','l')
legend.AddEntry(predicted0,'predicted','l')

comparecanvas0=TCanvas('comparecanvas0','',600,600)
comparecanvas0.Divide(1,2)
top_pad0=comparecanvas0.GetPad(1)
bottom_pad0=comparecanvas0.GetPad(2)
top_pad0.SetPad( 0.0, 0.30, 1.0, 1.0 )
bottom_pad0.SetPad( 0.0, 0.0, 1.0, 0.30 )
measured0.SetLineWidth(3)
predicted0.SetLineWidth(3)
measured0.SetLineColor(kBlue)
predicted0.SetLineColor(kRed)
top_pad0.cd()
measured0.Draw()
predicted0.Draw('SAME')
legend.Draw()
bottom_pad0.cd()
ratio0.Draw()
line.Draw('same')
comparecanvas0.Write('compare0')

comparecanvas1=TCanvas('comparecanvas1','',600,600)
comparecanvas1.Divide(1,2)
top_pad1=comparecanvas1.GetPad(1)
bottom_pad1=comparecanvas1.GetPad(2)
top_pad1.SetPad( 0.0, 0.30, 1.0, 1.0 )
bottom_pad1.SetPad( 0.0, 0.0, 1.0, 0.30 )
measured1.SetLineWidth(3)
predicted1.SetLineWidth(3)
measured1.SetLineColor(kBlue)
predicted1.SetLineColor(kRed)
top_pad1.cd()
measured1.Draw()
predicted1.Draw('SAME')
legend.Draw()
bottom_pad1.cd()
ratio1.Draw()
line.Draw('same')
comparecanvas1.Write('compare1')

comparecanvas2=TCanvas('comparecanvas2','',600,600)
comparecanvas2.Divide(1,2)
top_pad2=comparecanvas2.GetPad(1)
bottom_pad2=comparecanvas2.GetPad(2)
top_pad2.SetPad( 0.0, 0.30, 1.0, 1.0 )
bottom_pad2.SetPad( 0.0, 0.0, 1.0, 0.30 )
measured2.SetLineWidth(3)
predicted2.SetLineWidth(3)
measured2.SetLineColor(kBlue)
predicted2.SetLineColor(kRed)
top_pad2.cd()
measured2.Draw()
predicted2.Draw('SAME')
legend.Draw()
bottom_pad2.cd()
ratio2.Draw()
line.Draw('same')
comparecanvas2.Write('compare2')


#comparecanvas2=TCanvas()
#measured2.SetLineWidth(3)
#predicted2.SetLineWidth(3)
#measured2.SetLineColor(kBlue)
#predicted2.SetLineColor(kRed)
#measured2.Draw()
#predicted2.Draw('SAME')
#comparecanvas2.Write('compare2')

f.Close()
outfile.Close()