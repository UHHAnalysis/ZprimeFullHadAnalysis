from os import system
from ROOT import TFile,gROOT,THStack,TCanvas,TLegend,kRed,kYellow,kWhite,TLatex,kBlue,TIter,TList
from sys import argv
#setup
print 'setup'
gROOT.SetBatch()
path_base='/nfs/dust/cms/user/usaiem/ZprimeFullHad/'
process_list_ttbar=['BackgroundCycle.MC.TTbarHad.root','BackgroundCycle.MC.TTbarLept.root','BackgroundCycle.MC.TTbarSemi.root']
process_list_qcd=['BackgroundCycle.MC.QCD_HT-1000ToInf.root','BackgroundCycle.MC.QCD_HT-250To500.root','BackgroundCycle.MC.QCD_HT-500To1000.root']#,'BackgroundCycle.MC.QCD_HT-100To250.root']
process_data='BackgroundCycle.DATA.DATA'
den_name="den_mistag"
num_name="num_mistag"
folder="BaseHistos"
histo_massshape_name="mass_shape"
#csvcat=['CSV0-L','CSVL-M','CSVM-1']
postfix=''
if len(argv[1:])>0:
  postfix='_'+argv[1]
outfile=TFile("bkg"+postfix+".root","RECREATE")
  
for i in ['HEPTagger','CMSTagger']:
  for j in ['MassShape','Mistag']:
    outfile.mkdir(i+'/'+j)
  
print 'hadd plots'

def hadd(inputlist,outputname):
  command_list='hadd -f '+path_base+outputname+'.root'# -v 0
  for i in inputlist:
    command_list+=' '+path_base+i
  system(command_list)
  return path_base+outputname+'.root'
ttbar_filename=hadd(process_list_ttbar,'bkg_ttbar')
qcd_filename=hadd(process_list_qcd,'bkg_qcd')
ttbar_file=TFile(ttbar_filename,'READ')
qcd_file=TFile(qcd_filename,'READ')
data_file=TFile(path_base+process_data+'.root','READ')

qcdflat_file=TFile(path_base+'BackgroundCycle.MC.QCDFlat.root','READ')
qcd250to500_file=TFile(path_base+'BackgroundCycle.MC.QCD_HT-250To500.root','READ')
qcd500to1000_file=TFile(path_base+'BackgroundCycle.MC.QCD_HT-500To1000.root','READ')
qcd1000toInf_file=TFile(path_base+'BackgroundCycle.MC.QCD_HT-1000ToInf.root','READ')

print 'produce hist'

def slice_and_save(sample,histo):
  #histo_stack=0
  
  if '2' in histo.ClassName():
    #histoXY=histo.Project3D('yx')
    #histoXY.Write(histoXY.GetName())
    #histo_stack=THStack(histoXY,'x','Stack_'+histo.GetName(),'')
    #else:
    histo_stack=THStack(histo,'x','Stack_'+histo.GetName(),'')
    histo_1d=histo_stack.GetHists()
    #outfile.cd()
    histo_stack.Write(histo_stack.GetName()+'_'+sample)
    nextinlist=TIter(histo_1d)
    obj=nextinlist()
    while obj:
      obj.Write(obj.GetName()+'_'+sample)
      obj=nextinlist()
  else:
    histo.Write(histo.GetName()+'_'+sample)

def getMistag(sample,sample_file,useCMS=False,isData=False,namepostfix=''):
  num_histo=sample_file.Get(folder+"/"+num_name+namepostfix).Clone('Numerator')#.Clone('Numerator_'+sample)
  den_histo=sample_file.Get(folder+"/"+den_name+namepostfix).Clone('Denominator')#.Clone('Denominator_'+sample)
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
  if '3' in mistag_histo.ClassName():
    numXY=num_histo.Project3D('yx')
    denXY=den_histo.Project3D('yx')
    mistagXY=numXY.Clone('Mistag')
    mistagXY.Divide(numXY,denXY,1,1,'B')
    slice_and_save(sample,mistagXY)
  #mass_shape2D.Write(folder+mass_shape2D.GetName()+'_'+sample)
  #mass_shapeStack.Write(folder+mass_shapeStack.GetName()+'_'+sample)
  #nextinlist=TList(GetListOfPrimitives())
  #obj=nextinlist()
  #while obj:
    #obj.Write(folder+obj.GetName()+'_'+sample)
    #obj=nextinlist()
  
#def getMistag2(sample,sample_file,useCMS=False,isData=False):
  #num_histo=sample_file.Get(folder+"/num_mistagMeasured").Clone('Numerator')#.Clone('Numerator_'+sample)
  #den_histo=sample_file.Get(folder+"/den_mistagMeasured").Clone('Denominator')#.Clone('Denominator_'+sample)
  #if isData:
    #num_histo.Add(ttbar_file.Get(folder+"/"+num_name),-1.0)
    #den_histo.Add(ttbar_file.Get(folder+"/"+den_name),-1.0)
  #mistag_histo=num_histo.Clone('Mistag')#.Clone('Mistag_'+sample)
  #mistag_histo.Divide(num_histo,den_histo,1,1,'B')
  #outfolder='HEPTagger/Mistag'
  #if useCMS:
    #outfolder='CMSTagger/Mistag'
  #outfile.mkdir(outfolder+'/'+sample)
  #outfile.cd(outfolder+'/'+sample)
  #slice_and_save(sample,num_histo)
  #slice_and_save(sample,den_histo)
  #slice_and_save(sample,mistag_histo)
  ##mass_shape2D.Write(folder+mass_shape2D.GetName()+'_'+sample)
  ##mass_shapeStack.Write(folder+mass_shapeStack.GetName()+'_'+sample)
  ##nextinlist=TList(GetListOfPrimitives())
  ##obj=nextinlist()
  ##while obj:
    ##obj.Write(folder+obj.GetName()+'_'+sample)
    ##obj=nextinlist()
  
def getMassShape(sample,sample_file,useCMS=False,isData=False,histoname=''):
  histomassshapename=histo_massshape_name
  if histoname!='':
    histomassshapename=histoname
  mass_shape=sample_file.Get(folder+'/'+histomassshapename)
  if isData:
    mass_shape.Add(ttbar_file.Get(folder+"/"+histomassshapename),-1.0)
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
 
def getMassShape2D(sample,sample_file,useCMS=False,isData=False):
  mass_shape=sample_file.Get(folder+'/'+histo_massshape_name+'2D')
  if isData:
    mass_shape.Add(ttbar_file.Get(folder+"/"+histo_massshape_name+'2D'),-1.0)
  #mass_shapeStack=THStack(mass_shape2D,'x','Stack','')
  #mass_shape1D=mass_shapeStack.GetHists()
  outfolder='HEPTagger/MassShape2D'
  if useCMS:
    outfolder='CMSTagger/MassShape2D'
  outfile.mkdir(outfolder+'/'+sample)
  outfile.cd(outfolder+'/'+sample)
  #slice_and_save(sample,mass_shape2D,folder)
  slice_and_save(sample,mass_shape)
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
getMistag('qcdflat',        qcdflat_file, use_htt, no_ttbar_subtraction)
getMistag('qcd250to500',    qcd250to500_file, use_htt, no_ttbar_subtraction)
getMistag('qcd500to1000',   qcd500to1000_file, use_htt, no_ttbar_subtraction)
#getMistag('qcd500to1000Measured',   qcd500to1000_file, use_htt, no_ttbar_subtraction,'Measured')
#getMistag('qcd500to1000Tag',   qcd500to1000_file, use_htt, no_ttbar_subtraction,'Tag')

#getMistag('qcd500to1000R',   qcd500to1000_file, use_htt, no_ttbar_subtraction,'R')
#getMistag('qcd500to1000Rmw',   qcd500to1000_file, use_htt, no_ttbar_subtraction,'Rmw')
#getMistag('qcd500to1000Invmw',   qcd500to1000_file, use_htt, no_ttbar_subtraction,'Invmw')
#getMistag('qcd500to1000Nomw',   qcd500to1000_file, use_htt, no_ttbar_subtraction,'Nomw')

getMistag('qcd1000toInf',   qcd1000toInf_file, use_htt, no_ttbar_subtraction)
#getMistag('qcd1000toInfMeasured',   qcd1000toInf_file, use_htt, no_ttbar_subtraction,'Measured')
#getMistag('qcd1000toInfTag',   qcd1000toInf_file, use_htt, no_ttbar_subtraction,'Tag')
#getMistag('ttbar_cms',      ttbar_file, use_cms, no_ttbar_subtraction)
#getMistag('qcd_cms',        qcd_file,   use_cms, no_ttbar_subtraction)
#getMistag('data_cms',       data_file,  use_cms, ttbar_subtraction)
#getMistag('data_cms_nosub', data_file,  use_cms, no_ttbar_subtraction)

getMassShape('ttbar_htt',      ttbar_file, use_htt, no_ttbar_subtraction)
getMassShape('qcd_htt',        qcd_file,   use_htt, no_ttbar_subtraction)
getMassShape('qcd500to1000',   qcd500to1000_file,   use_htt, no_ttbar_subtraction)
getMassShape('qcd1000toInf',   qcd1000toInf_file,   use_htt, no_ttbar_subtraction)
getMassShape('data_htt',       data_file,  use_htt, ttbar_subtraction)
getMassShape('data_htt_nosub', data_file,  use_htt, no_ttbar_subtraction)
#getMassShape('qcd_htt_jec',        qcd_file,   use_htt, no_ttbar_subtraction, "mass_shapeJEC")
#getMassShape('ttbar_cms',      ttbar_file, use_cms, no_ttbar_subtraction)
#getMassShape('qcd_cms',        qcd_file,   use_cms, no_ttbar_subtraction)
#getMassShape('data_cms',       data_file,  use_cms, ttbar_subtraction)
#getMassShape('data_cms_nosub', data_file,  use_cms, no_ttbar_subtraction)

#getMassShape2D('ttbar_htt',      ttbar_file, use_htt, no_ttbar_subtraction)
#getMassShape2D('qcd_htt',        qcd_file,   use_htt, no_ttbar_subtraction)
#getMassShape2D('data_htt',       data_file,  use_htt, ttbar_subtraction)
#getMassShape2D('data_htt_nosub', data_file,  use_htt, no_ttbar_subtraction)
outfile.cd()
#ckhisto=qcd500to1000_file.Get('BaseHistos/mistag_crosscheck')
#slice_and_save('ck',ckhisto)

print 'make plots'

def make_plot(name,name_list,legend_list,normalize=False,thefile=0):
  histo_list=[]
  c=TCanvas(name,'',600,600)
  legend=TLegend(0.8,0.2,0.999,0.93)
  legend.SetBorderSize(0)
  legend.SetTextFont(62)
  legend.SetLineColor(1)
  legend.SetLineStyle(1)
  legend.SetLineWidth(1)
  legend.SetFillColor(0)
  legend.SetFillStyle(1001)
  for i in range(len(name_list)):
    if thefile==0:
      histo_list.append(outfile.Get(name_list[i]))
    else:
      histo_list.append(thefile.Get(name_list[i]))
    if normalize:
      histo_list[-1].Scale(1.0/histo_list[-1].Integral())
    histo_list[-1].SetStats(0)
    histo_list[-1].SetLineWidth(3)
    histo_list[-1].SetLineColor(i+1)
    legend.AddEntry(histo_list[-1],legend_list[i],'l')
    if i==0:
      histo_list[-1].Draw()
    else:
      histo_list[-1].Draw('SAME')
  legend.Draw()
  outfile.cd()
  c.Write(name)


#thisfile=TFile('dust/BackgroundCycle.MC.ZP500W5.root','READ')
#make_plot('comp_sgn_500',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP750W7p5.root','READ')
#make_plot('comp_sgn_750',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP1000W10.root','READ')
#make_plot('comp_sgn_1000',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP1250W12p5.root','READ')
#make_plot('comp_sgn_1250',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP1500W15.root','READ')
#make_plot('comp_sgn_1500',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP2000W20.root','READ')
#make_plot('comp_sgn_2000',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP3000W30.root','READ')
#make_plot('comp_sgn_3000',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

#thisfile=TFile('dust/BackgroundCycle.MC.ZP4000W40.root','READ')
#make_plot('comp_sgn_4000',['BaseHistos/MeasuredMtt012','BaseHistos/MeasuredJECMtt012','BaseHistos/MeasuredHTTMtt012','BaseHistos/MeasuredHTTJECMtt012','BaseHistos/MeasuredAK5Mtt012'],['CA15Filtered no JEC','CA15Filtered JEC','HTT CA15 no JEC','HTT CA15 JEC','3xAK5 in R=1.5'],False,thisfile)
#thisfile.Close()

make_plot('comp_mistag',['HEPTagger/Mistag/qcd_htt/Mistag_px4_qcd_htt','HEPTagger/Mistag/qcd_htt/Mistag_px3_qcd_htt','HEPTagger/Mistag/qcd_htt/Mistag_px2_qcd_htt','HEPTagger/Mistag/qcd_htt/Mistag_px1_qcd_htt'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

make_plot('comp_mistag_data',['HEPTagger/Mistag/data_htt/Mistag_px4_data_htt','HEPTagger/Mistag/data_htt/Mistag_px3_data_htt','HEPTagger/Mistag/data_htt/Mistag_px2_data_htt','HEPTagger/Mistag/data_htt/Mistag_px1_data_htt'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_mistag500To1000',['HEPTagger/Mistag/qcd500to1000/Mistag_px4_qcd500to1000','HEPTagger/Mistag/qcd500to1000/Mistag_px3_qcd500to1000','HEPTagger/Mistag/qcd500to1000/Mistag_px2_qcd500to1000','HEPTagger/Mistag/qcd500to1000/Mistag_px1_qcd500to1000'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_mistag500To1000Measured',['HEPTagger/Mistag/qcd500to1000Measured/Mistag_px4_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px3_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px2_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px1_qcd500to1000Measured'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_mistag500To1000Tag',['HEPTagger/Mistag/qcd500to1000Tag/Mistag_px4_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px3_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px2_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px1_qcd500to1000Tag'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_mistag1000ToInf',['HEPTagger/Mistag/qcd1000toInf/Mistag_px4_qcd1000toInf','HEPTagger/Mistag/qcd1000toInf/Mistag_px3_qcd1000toInf','HEPTagger/Mistag/qcd1000toInf/Mistag_px2_qcd1000toInf','HEPTagger/Mistag/qcd1000toInf/Mistag_px1_qcd1000toInf'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_mistag1000ToInfMeasured',['HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px4_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px3_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px2_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px1_qcd1000toInfMeasured'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_mistag1000ToInfTag',['HEPTagger/Mistag/qcd1000toInfTag/Mistag_px4_qcd1000toInfTag','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px3_qcd1000toInfTag','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px2_qcd1000toInfTag','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px1_qcd1000toInfTag'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])



#make_plot('comp_mistag_1000ToInfTag_px4',['HEPTagger/Mistag/qcd1000toInf/Mistag_px4_qcd1000toInf','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px4_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px4_qcd1000toInfTag'],['antitag','no requirement','tag'])

#make_plot('comp_mistag_1000ToInfTag_px3',['HEPTagger/Mistag/qcd1000toInf/Mistag_px3_qcd1000toInf','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px3_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px3_qcd1000toInfTag'],['antitag','no requirement','tag'])

#make_plot('comp_mistag_1000ToInfTag_px2',['HEPTagger/Mistag/qcd1000toInf/Mistag_px2_qcd1000toInf','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px2_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px2_qcd1000toInfTag'],['antitag','no requirement','tag'])

#make_plot('comp_mistag_1000ToInfTag_px1',['HEPTagger/Mistag/qcd1000toInf/Mistag_px1_qcd1000toInf','HEPTagger/Mistag/qcd1000toInfMeasured/Mistag_px1_qcd1000toInfMeasured','HEPTagger/Mistag/qcd1000toInfTag/Mistag_px1_qcd1000toInfTag'],['antitag','no requirement','tag'])



#make_plot('comp_mistag_500To1000Tag_px4',['HEPTagger/Mistag/qcd500to1000/Mistag_px4_qcd500to1000','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px4_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px4_qcd500to1000Tag'],['antitag','no requirement','tag'])

#make_plot('comp_mistag_500To1000Tag_px3',['HEPTagger/Mistag/qcd500to1000/Mistag_px3_qcd500to1000','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px3_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px3_qcd500to1000Tag'],['antitag','no requirement','tag'])

#make_plot('comp_mistag_500To1000Tag_px2',['HEPTagger/Mistag/qcd500to1000/Mistag_px2_qcd500to1000','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px2_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px2_qcd500to1000Tag'],['antitag','no requirement','tag'])

#make_plot('comp_mistag_500To1000Tag_px1',['HEPTagger/Mistag/qcd500to1000/Mistag_px1_qcd500to1000','HEPTagger/Mistag/qcd500to1000Measured/Mistag_px1_qcd500to1000Measured','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px1_qcd500to1000Tag'],['antitag','no requirement','tag'])


#make_plot('comp_mistag_500To1000_px4',['HEPTagger/Mistag/qcd500to1000/Mistag_px4_qcd500to1000','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px4_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000R/Mistag_px4_qcd500to1000R','HEPTagger/Mistag/qcd500to1000Rmw/Mistag_px4_qcd500to1000Rmw','HEPTagger/Mistag/qcd500to1000Invmw/Mistag_px4_qcd500to1000Invmw','HEPTagger/Mistag/qcd500to1000Nomw/Mistag_px4_qcd500to1000Nomw'],['antitag','tag','R','Rmw','Invmw','Nomw'])

#make_plot('comp_mistag_500To1000_px3',['HEPTagger/Mistag/qcd500to1000/Mistag_px3_qcd500to1000','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px3_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000R/Mistag_px3_qcd500to1000R','HEPTagger/Mistag/qcd500to1000Rmw/Mistag_px3_qcd500to1000Rmw','HEPTagger/Mistag/qcd500to1000Invmw/Mistag_px3_qcd500to1000Invmw','HEPTagger/Mistag/qcd500to1000Nomw/Mistag_px3_qcd500to1000Nomw'],['antitag','tag','R','Rmw','Invmw','Nomw'])

#make_plot('comp_mistag_500To1000_px2',['HEPTagger/Mistag/qcd500to1000/Mistag_px2_qcd500to1000','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px2_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000R/Mistag_px2_qcd500to1000R','HEPTagger/Mistag/qcd500to1000Rmw/Mistag_px2_qcd500to1000Rmw','HEPTagger/Mistag/qcd500to1000Invmw/Mistag_px2_qcd500to1000Invmw','HEPTagger/Mistag/qcd500to1000Nomw/Mistag_px2_qcd500to1000Nomw'],['antitag','tag','R','Rmw','Invmw','Nomw'])

#make_plot('comp_mistag_500To1000_px1',['HEPTagger/Mistag/qcd500to1000/Mistag_px1_qcd500to1000','HEPTagger/Mistag/qcd500to1000Tag/Mistag_px1_qcd500to1000Tag','HEPTagger/Mistag/qcd500to1000R/Mistag_px1_qcd500to1000R','HEPTagger/Mistag/qcd500to1000Rmw/Mistag_px1_qcd500to1000Rmw','HEPTagger/Mistag/qcd500to1000Invmw/Mistag_px1_qcd500to1000Invmw','HEPTagger/Mistag/qcd500to1000Nomw/Mistag_px1_qcd500to1000Nomw'],['antitag','tag','R','Rmw','Invmw','Nomw'])

#make_plot('comp_data_nosub_mistag',['HEPTagger/Mistag/data_htt_nosub/Mistag_px4_data_htt_nosub','HEPTagger/Mistag/data_htt_nosub/Mistag_px3_data_htt_nosub','HEPTagger/Mistag/data_htt_nosub/Mistag_px2_data_htt_nosub','HEPTagger/Mistag/data_htt_nosub/Mistag_px1_data_htt_nosub'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_data_mistag',['HEPTagger/Mistag/data_htt/Mistag_px4_data_htt','HEPTagger/Mistag/data_htt/Mistag_px3_data_htt','HEPTagger/Mistag/data_htt/Mistag_px2_data_htt','HEPTagger/Mistag/data_htt/Mistag_px1_data_htt'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'])

#make_plot('comp_datamc1_mistag',['HEPTagger/Mistag/data_htt/Mistag_px4_data_htt','HEPTagger/Mistag/qcd_htt/Mistag_px4_qcd_htt'],['Data [CSVM,1]','MC [CSVM,1]'])
#make_plot('comp_datamc2_mistag',['HEPTagger/Mistag/data_htt/Mistag_px3_data_htt','HEPTagger/Mistag/qcd_htt/Mistag_px3_qcd_htt'],['Data [CSVL,CSVM]','MC [CSVL,CSVM]'])
#make_plot('comp_datamc3_mistag',['HEPTagger/Mistag/data_htt/Mistag_px2_data_htt','HEPTagger/Mistag/qcd_htt/Mistag_px2_qcd_htt'],['Data [0,CSVL]','MC [0,CSVL]'])

#make_plot('comp_shape',['HEPTagger/MassShape/qcd_htt/mass_shape_qcd_htt','HEPTagger/MassShape/data_htt/mass_shape_data_htt'],['QCD','DATA'],True)
#make_plot('comp_shape_jec',['HEPTagger/MassShape/qcd_htt/mass_shape_qcd_htt','HEPTagger/MassShape/qcd_htt_jec/mass_shapeJEC_qcd_htt_jec'],['NO JEC','JEC'],True)
#make_plot('comp_qcd_shape',['HEPTagger/MassShape2D/qcd_htt/mass_shape2D_px4_qcd_htt','HEPTagger/MassShape2D/qcd_htt/mass_shape2D_px3_qcd_htt','HEPTagger/MassShape2D/qcd_htt/mass_shape2D_px2_qcd_htt'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'],True)
#make_plot('comp_data_shape',['HEPTagger/MassShape2D/data_htt/mass_shape2D_px4_data_htt','HEPTagger/MassShape2D/data_htt/mass_shape2D_px3_data_htt','HEPTagger/MassShape2D/data_htt/mass_shape2D_px2_data_htt'],['[CSVM,1]','[CSVL,CSVM]','[0,CSVL]','[-1,0]'],True)
  
print 'close files'
ttbar_file.Close()
qcd_file.Close()
data_file.Close()
outfile.Close()

  