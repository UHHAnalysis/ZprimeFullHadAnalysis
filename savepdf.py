from ROOT import TFile,TCanvas,gROOT,gStyle
from os import system
gStyle.SetNumberContours(255)
gStyle.SetPalette(55)
f=TFile('/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/heptoptagvalhistos.root','READ')
gROOT.SetBatch()
histohash=f.GetListOfKeys()
histokeyiter=histohash.MakeIterator()
key=histokeyiter()
while key:
  obj=key.ReadObj()
  outname='/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/pdf/'+obj.GetName()+'.pdf'
  if obj.ClassName()=='TCanvas':
    obj.SaveAs(outname)
    obj.SaveAs('/afs/desy.de/user/u/usaiem/code/ZprimeFullHadAnalysis/pdf/'+obj.GetName()+'.C')
  else:
    if 'HTT2D' in obj.GetName():
      key=histokeyiter()
      continue
    c=TCanvas(obj.GetName())
    obj.Draw()
    c.SaveAs(outname)
  system('convert -density 300 -trim '+outname+' '+outname[:-4]+'.png')
  system('mogrify -bordercolor White -border 20 '+outname[:-4]+'.png')
  key=histokeyiter()
f.Close()