#include "include/HEPTopTaggerReweight.h"
#include "SFrameTools/include/EventCalc.h"

double HEPTopTaggerReweight::GetScaleWeight(std::vector<int> Indices)
{
    EventCalc* calc = EventCalc::Instance();
    BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
    bool IsRealData = calc->IsRealData();
    double scale_factor = 1.;
    if(!IsRealData)
      {
	  
	  double jetpt=bcc->toptagjets->at(Indices[0]).pt();
	  
	  if(jetpt>200. && jetpt<=250.) scale_factor *= 0.959548632146;
	  if(jetpt>250. && jetpt<=400.) scale_factor *= 0.980234133823;
	  if(jetpt>400.) scale_factor *= 1.0461755891;
	  
	  jetpt=bcc->toptagjets->at(Indices[1]).pt();
	  
	  if(jetpt>200. && jetpt<=250.) scale_factor *= 0.959548632146;
	  if(jetpt>250. && jetpt<=400.) scale_factor *= 0.980234133823;
	  if(jetpt>400.) scale_factor *= 1.0461755891;

	
      }
    //std::cout<<"sf from HEPTopTaggerReweight: "<<scale_factor<<std::endl;
    return scale_factor;
}
