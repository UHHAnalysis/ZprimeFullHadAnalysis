from ROOT import TFile,kRed,kBlue,gROOT,TCanvas,TLegend,kWhite,kGreen,kFALSE,kBlack,kViolet,kOrange
gROOT.SetBatch()

f=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/test/RocCycle.MC.QCD15to3000.root', "READ")
f2=TFile('/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/test/eff.root', "READ")
#f2=TFile('heptoptagvalhistos.root', "READ")
outfile=TFile("nsub.root", "RECREATE")
def getNsub(name):
  if name=='QCD':
    filename=f
  else:
    filename=f2
  htt_all=filename.Get('NoCutsHistos/Nsub')
  htt_tagged=filename.Get('NoCutsHistos/Nsub_tagged')
  jmhtt_all=filename.Get('NoCutsHistos/Jetmass')
  jmhtt_tagged=filename.Get('NoCutsHistos/Jetmass_tagged')
  htt_all.Scale(1/htt_all.Integral())
  htt_tagged.Scale(1/htt_tagged.Integral())
  jmhtt_all.Scale(1/jmhtt_all.Integral())
  jmhtt_tagged.Scale(1/jmhtt_tagged.Integral())
  outfile.cd()
  htt_all.Write('NSUB_'+name)
  htt_tagged.Write('NSUB_HTT_'+name)
  jmhtt_all.Write('JETMASS_'+name)
  jmhtt_tagged.Write('JETMASS_HTT_'+name)

names=['QCD','TTBAR']
for name in names:
  getNsub(name)
outfile.Close()