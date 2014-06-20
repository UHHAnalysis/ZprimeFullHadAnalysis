#include "include/ZTriggerWeight.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "SFrameTools/include/EventCalc.h"

ZTriggerWeight::ZTriggerWeight(TString filename_mc, TString mode){

  file_mc = new TFile(filename_mc);

//  h_mc=(TH1F*) file_mc->Get("triggerSF");
  h_ht=(TH1F*) file_mc->Get("sf_1xCSVL_ht");
  h_quad=(TH1F*) file_mc->Get("sf_1xCSVL_quad");
  
  m_mode=mode;

}

//double ZTriggerWeight::produceWeight(BaseCycleContainer* bcc){
//
//  double HTSubJets = 0.;
//
//  std::vector<Particle> subjets_top;
//
//  for (unsigned int itj = 0; itj < bcc->topjets->size(); itj++){
//   if(bcc->topjets->at(itj).pt()<150.) continue;
//   TopJet topjet = bcc->topjets->at(itj);
//   subjets_top=topjet.subjets();
//   for (unsigned int subj = 0; subj < subjets_top.size(); subj++){
//     HTSubJets += subjets_top.at(subj).pt();
//   }
//  }
// 
//  if(HTSubJets>800.){
//    return 1.;
//  }
//  else{
//    int bin=h_mc->GetXaxis()->FindBin(HTSubJets);
//    double weight=h_mc->GetBinContent(bin);
//    double addweight=fabs(1.-weight)*0.5;
//    if(m_mode=="up"){
//      weight=weight+addweight;
//    }
//    if(m_mode=="down"){
//      weight=weight-addweight;
//    }
//
//    return weight;
//  }
//
//}

void ZTriggerWeight::Close()
{file_mc->Close();}

double ZTriggerWeight::produceWeightHT(BaseCycleContainer* bcc)
{
  double ht50 = getHT50(bcc);
  
  int bin=h_ht->FindFixBin(ht50);
  double weight=h_ht->GetBinContent(bin);
  double addweight=fabs(1.-weight)*0.5;
  
  if(m_mode=="up"){
    weight=weight+addweight;
  }
  if(m_mode=="down"){
    weight=weight-addweight;
  }
  
  return weight;
  
}


double ZTriggerWeight::produceWeightQuadJet(BaseCycleContainer* bcc)
{
  double pt4 = 0;
  if (bcc->jets->size()>3)
  {
    pt4=bcc->jets->at(3).pt();
  }
  
  int bin=h_quad->FindFixBin(pt4);
  double weight=h_quad->GetBinContent(bin);
  double addweight=fabs(1.-weight)*0.5;
  
  if(m_mode=="up"){
    weight=weight+addweight;
  }
  if(m_mode=="down"){
    weight=weight-addweight;
  }
  
  return weight;
  
}
