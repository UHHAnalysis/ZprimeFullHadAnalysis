from ROOT import TFile
f=TFile('heptoptagvalhistos_mcatnlo.root','READ')
h=f.Get('LeptToppt_after_tpr_hists_Pull')
v=[]
for i in range(h.GetNbinsX()):
  v.append(h.GetBinContent(i+1))
print v
