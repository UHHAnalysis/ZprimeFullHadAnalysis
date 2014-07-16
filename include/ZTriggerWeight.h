#ifndef ZTriggerWeight_H
#define ZTriggerWeight_H

#include "SFrameTools/include/Objects.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "include/ZprimeFullHadTools.h"

#include <algorithm>

#include "TH1.h"
#include "TFile.h"

class ZTriggerWeight{

 public:
  ZTriggerWeight(){};

  ZTriggerWeight(TString filename_mc, TString mode);

  ~ZTriggerWeight(){};

//  double produceWeight(BaseCycleContainer * bcc);
  double produceWeightHT(BaseCycleContainer * bcc);
  double produceWeightQuadJet(BaseCycleContainer * bcc);
  void Close();
 private:

//  TH1F *h_mc;
  TH1F *h_ht, *h_quad;
  TString m_mode;
  //TFile *file_mc;

};



#endif
