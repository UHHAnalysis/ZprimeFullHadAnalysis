from ROOT import TFile,kRed,kBlue,gROOT,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange
gROOT.SetBatch()

name='Mistag'
f=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/test/RocCycle.MC.QCD15to3000.root', "READ")
f2=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/test/eff.root', "READ")
#f2=TFile('heptoptagvalhistos.root', "READ")
outfile=TFile("npv.root", "RECREATE")
def getMistag(path,cuttype,name):
  if name=='Mistag':
    filename=f
  else:
    filename=f2
  htt_all=filename.Get('NoCutsHistos/Npv'+path+'_all')
  htt_tagged=filename.Get('NoCutsHistos/Npv'+path+'_'+cuttype+'_tagged')
  mistag=htt_all.Clone(name+path+cuttype)
  mistag.SetStats(kFALSE)
  mistag.SetLineColor(kBlack)
  mistag.SetLineWidth(2)
  mistag.Divide(htt_tagged,htt_all,1,1,'B')
  mistag.GetYaxis().SetTitle(name)
  mistag.GetXaxis().SetTitle('Pileup')
  #canvas=TCanvas(name+'_canvas')

  #mistag.Draw()
  mistag.Write()
  #canvas.Write()
  #canvas.SaveAs(name+'.pdf')
def getRate(path):
  rate=f2.Get('N_pv'+path+'_SoverS').Clone('Rate'+path)
  rate.SetStats(kFALSE)
  rate.SetLineColor(kBlack)
  rate.SetLineWidth(2)
  rate.GetYaxis().SetTitle('Rate')
  rate.GetXaxis().SetTitle('Pileup')
  rate.Write()
  #canvas2=TCanvas('Rate_canvas')
  #rate.Draw()
  #canvas2.SaveAs('Rate.pdf')
  #canvas2.Write()

cuttypes=['htt','httcsv','httnsub','httnsubcsv']
paths=['200','300','400','500','600']
names=['Mistag','Efficiency']
for name in names:
  for path in paths:
    for cuttype in cuttypes:
      getMistag(path,cuttype,name)
#getRate(i)
outfile.Close()