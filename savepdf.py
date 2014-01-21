from ROOT import TFile,TCanvas,gROOT,gStyle
gStyle.SetNumberContours(255)
gStyle.SetPalette(55)
f=TFile('/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/heptoptagvalhistos.root','READ')
gROOT.SetBatch()
histohash=f.GetListOfKeys()
histokeyiter=histohash.MakeIterator()
key=histokeyiter()
while key:
  obj=key.ReadObj()
  if obj.ClassName()=='TCanvas':
    obj.SaveAs('/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/pdf/'+obj.GetName()+'.pdf')
  else:
    if 'HTT2D' in obj.GetName():
      key=histokeyiter()
      continue
    c=TCanvas(obj.GetName())
    obj.Draw()
    c.SaveAs('/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/pdf/'+obj.GetName()+'.pdf')
  key=histokeyiter()
f.Close()