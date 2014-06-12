from ROOT import TFile,gROOT,TGraph,TCanvas
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

outfile=TFile('outputfile.root','RECREATE')
textfilepath="/nfs/dust/cms/user/usaiem/ZprimeFullHad/zphad_012btag_cms.txt"
points=getPoints(textfilepath)
graph=TGraph(len(points[0]),array('d',points[0]),array('d',points[1]))
c=TCanvas()
c.SetLogy()
graph.Draw('al')
c.SaveAs('limitplot.pdf')
graph.Write()
c.Write()
outfile.Close()