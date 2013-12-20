from ROOT import TFile,TCanvas,gROOT,gStyle
gStyle.SetNumberContours(255)
gStyle.SetPalette(55)
f=TFile('/afs/naf.desy.de/user/u/usai/code/SFrame/ZprimeFullHadAnalysis/heptoptagvalhistos.root','READ')
gROOT.SetBatch()
histohash=f.GetListOfKeys()
histokeyiter=histohash.MakeIterator()
key=histokeyiter()
while key:
  obj=key.ReadObj()
  if obj.ClassName()=='TCanvas':
    obj.SaveAs('/afs/naf.desy.de/user/u/usai/scratch/pdf/'+obj.GetName()+'.pdf')
  else:
    if 'HTT2D' in obj.GetName():
      key=histokeyiter()
      continue
    c=TCanvas(obj.GetName())
    obj.Draw()
    c.SaveAs('/afs/naf.desy.de/user/u/usai/scratch/pdf/'+obj.GetName()+'.pdf')
  key=histokeyiter()
f.Close()