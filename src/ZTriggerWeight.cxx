#include "include/ZTriggerWeight.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "SFrameTools/include/EventCalc.h"

ZTriggerWeight::ZTriggerWeight(TString filename_mc, TString mode){

  //file_mc = new TFile(filename_mc);

//  h_mc=(TH1F*) file_mc->Get("triggerSF");
  h_ht=new TH1F("h_ht","HLT_HT750",25,0,2000);
  h_quad=new TH1F("h_quad","HLT_QuadJet50",25,0,500);
   h_quad->SetBinContent(2,0.4955357);
   h_quad->SetBinContent(3,0.6839759);
   h_quad->SetBinContent(4,0.9060282);
   h_quad->SetBinContent(5,0.9602375);
   h_quad->SetBinContent(6,0.9924242);
   h_quad->SetBinContent(7,1.011859);
   h_quad->SetBinContent(8,0.9655172);
   h_quad->SetBinContent(9,1.1);
   h_quad->SetBinContent(10,1);
   h_quad->SetBinError(2,0.3313248);
   h_quad->SetBinError(3,0.04989849);
   h_quad->SetBinError(4,0.02072731);
   h_quad->SetBinError(5,0.01675328);
   h_quad->SetBinError(6,0.01578304);
   h_quad->SetBinError(7,0.01718527);
   h_quad->SetBinError(8,0.03388301);
   h_quad->SetBinError(9,0.07416198);
   h_quad->SetMinimum(0);
   h_quad->SetMaximum(1.01);
   h_quad->SetEntries(548.0842);
   h_quad->SetStats(0);

   h_ht->SetBinContent(8,0.8013334);
   h_ht->SetBinContent(9,0.1238472);
   h_ht->SetBinContent(10,0.3399262);
   h_ht->SetBinContent(11,0.6343169);
   h_ht->SetBinContent(12,0.8677037);
   h_ht->SetBinContent(13,1);
   h_ht->SetBinContent(14,1.015151);
   h_ht->SetBinContent(15,1);
   h_ht->SetBinContent(16,1);
   h_ht->SetBinContent(17,1.047619);
   h_ht->SetBinContent(18,1);
   h_ht->SetBinContent(19,1);
   h_ht->SetBinContent(20,1);
   h_ht->SetBinContent(21,1);
   h_ht->SetBinError(8,0.5308073);
   h_ht->SetBinError(9,0.07232107);
   h_ht->SetBinError(10,0.06318039);
   h_ht->SetBinError(11,0.06047583);
   h_ht->SetBinError(12,0.0421346);
   h_ht->SetBinError(14,0.01526587);
   h_ht->SetBinError(17,0.04873965);
   h_ht->SetMinimum(0);
   h_ht->SetMaximum(1.01);
   h_ht->SetEntries(468.0175);
   h_ht->SetStats(0);
  
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
{
//  file_mc->Close();
  delete h_ht;
  delete h_quad;
}

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
