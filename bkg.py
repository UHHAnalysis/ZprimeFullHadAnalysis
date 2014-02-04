from os import system
from ROOT import TFile,gROOT,THStack,TCanvas,TLegend,kRed,kYellow,kWhite,TLatex,kBlue,TIter,TList
from sys import argv
#setup
print 'setup'
gROOT.SetBatch()
path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
process_list_ttbar=['BackgroundCycle.MC.TTbarHad.root','BackgroundCycle.MC.TTbarLept.root','BackgroundCycle.MC.TTbarSemi.root']
process_list_qcd=['BackgroundCycle.MC.QCD_HT-1000ToInf.root','BackgroundCycle.MC.QCD_HT-250To500.root','BackgroundCycle.MC.QCD_HT-500To1000.root']#'BackgroundCycle.MC.QCD_HT-100To250.root',
process_data='BackgroundCycle.DATA.DATA'
den_name="den_mistag"
num_name="num_mistag"
folder="BaseHistos"
histo_massshape_name="mass_shape"
csvcat=['CSV0-L','CSVL-M','CSVM-1']
postfix=''
outfile=TFile("bkg"+postfix+".root","RECREATE")
if len(argv[1:])>0:
  postfix='_'+argv[1]

for i in ['HEPTagger','CMSTagger']:
  for j in ['MassShape','Mistag']:
    outfile.mkdir(i+'/'+j)
  
print 'hadd plots'

def hadd(inputlist,outputname):
  command_list='hadd -v 0 -f '+path_base+outputname+'.root'
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
ttbar_filename=hadd(process_list_ttbar,'bkg_ttbar')
qcd_filename=hadd(process_list_qcd,'bkg_qcd')
ttbar_file=TFile(ttbar_filename,'READ')
qcd_file=TFile(qcd_filename,'READ')
data_file=TFile(path_base+process_data+'.root','READ')

print 'produce hist'

def slice_and_save(sample,histo):
  histo_stack=THStack(histo,'x','Stack_'+histo.GetName(),'')
  histo_1d=histo_stack.GetHists()
  #outfile.cd()
  histo.Write(histo.GetName()+'_'+sample)
  histo_stack.Write(histo_stack.GetName()+'_'+sample)
  nextinlist=TIter(histo_1d)
  obj=nextinlist()
  while obj:
    obj.Write(obj.GetName()+'_'+sample)
    obj=nextinlist()

def getMistag(sample,sample_file,useCMS=False,isData=False):
  num_histo=sample_file.Get(folder+"/"+num_name).Clone('Numerator')#.Clone('Numerator_'+sample)
  den_histo=sample_file.Get(folder+"/"+den_name).Clone('Denominator')#.Clone('Denominator_'+sample)
  if isData:
    num_histo.Add(ttbar_file.Get(folder+"/"+num_name),-1.0)
    den_histo.Add(ttbar_file.Get(folder+"/"+den_name),-1.0)
  mistag_histo=num_histo.Clone('Mistag')#.Clone('Mistag_'+sample)
  mistag_histo.Divide(num_histo,den_histo,1,1,'B')
  outfolder='HEPTagger/Mistag'
  if useCMS:
    outfolder='CMSTagger/Mistag'
  outfile.mkdir(outfolder+'/'+sample)
  outfile.cd(outfolder+'/'+sample)
  slice_and_save(sample,num_histo)
  slice_and_save(sample,den_histo)
  slice_and_save(sample,mistag_histo)
  #mass_shape2D.Write(folder+mass_shape2D.GetName()+'_'+sample)
  #mass_shapeStack.Write(folder+mass_shapeStack.GetName()+'_'+sample)
  #nextinlist=TList(GetListOfPrimitives())
  #obj=nextinlist()
  #while obj:
    #obj.Write(folder+obj.GetName()+'_'+sample)
    #obj=nextinlist()
  
  
def getMassShape(sample,sample_file,useCMS=False,isData=False):
  mass_shape=sample_file.Get(folder+'/'+histo_massshape_name)
  #mass_shapeStack=THStack(mass_shape2D,'x','Stack','')
  #mass_shape1D=mass_shapeStack.GetHists()
  outfolder='HEPTagger/MassShape'
  if useCMS:
    outfolder='CMSTagger/MassShape'
  outfile.mkdir(outfolder+'/'+sample)
  outfile.cd(outfolder+'/'+sample)
  #slice_and_save(sample,mass_shape2D,folder)
  mass_shape.Write(mass_shape.GetName()+'_'+sample)
  #mass_shape2D.Write(folder+mass_shape2D.GetName()+'_'+sample)
  #mass_shapeStack.Write(folder+mass_shapeStack.GetName()+'_'+sample)
  #nextinlist=TList(GetListOfPrimitives())
  #obj=nextinlist()
  #while obj:
    #obj.Write(folder+obj.GetName()+'_'+sample)
    #obj=nextinlist()
    

use_cms=True
use_htt=False
ttbar_subtraction=True
no_ttbar_subtraction=False
getMistag('ttbar_htt',      ttbar_file, use_htt, no_ttbar_subtraction)
getMistag('qcd_htt',        qcd_file,   use_htt, no_ttbar_subtraction)
getMistag('data_htt',       data_file,  use_htt, ttbar_subtraction)
getMistag('data_htt_nosub', data_file,  use_htt, no_ttbar_subtraction)
#getMistag('ttbar_cms',      ttbar_file, use_cms, no_ttbar_subtraction)
#getMistag('qcd_cms',        qcd_file,   use_cms, no_ttbar_subtraction)
#getMistag('data_cms',       data_file,  use_cms, ttbar_subtraction)
#getMistag('data_cms_nosub', data_file,  use_cms, no_ttbar_subtraction)

getMassShape('ttbar_htt',      ttbar_file, use_htt, no_ttbar_subtraction)
getMassShape('qcd_htt',        qcd_file,   use_htt, no_ttbar_subtraction)
getMassShape('data_htt',       data_file,  use_htt, ttbar_subtraction)
getMassShape('data_htt_nosub', data_file,  use_htt, no_ttbar_subtraction)
#getMassShape('ttbar_cms',      ttbar_file, use_cms, no_ttbar_subtraction)
#getMassShape('qcd_cms',        qcd_file,   use_cms, no_ttbar_subtraction)
#getMassShape('data_cms',       data_file,  use_cms, ttbar_subtraction)
#getMassShape('data_cms_nosub', data_file,  use_cms, no_ttbar_subtraction)

print 'make plots'

def make_plot(name,name_list):
  histo_list=[]
  c=TCanvas(name)
  legend=TLegend(0.8,0.2,0.999,0.93)
  legend.SetBorderSize(0)
  legend.SetTextFont(62)
  legend.SetLineColor(1)
  legend.SetLineStyle(1)
  legend.SetLineWidth(1)
  legend.SetFillColor(0)
  legend.SetFillStyle(1001)
  for i in range(len(name_list)):
    histo_list.append(outfile.Get(name_list[i]))
    histo_list[-1].SetStats(kFALSE)
    histo_list[-1].SetLineWidth(3)
    histo_list[-1].SetLineColor(i+1)
    legend.AddEntry(histo_list[-1],name_list[i],'l')
    if i==0:
      histo_list[-1].Draw()
    else:
      histo_list[-1].Draw('SAME')
  legend.Draw()  
  c.Write(name)

print 'close files'
ttbar_file.Close()
qcd_file.Close()
data_file.Close()
outfile.Close()

  