#include "include/ZprimeFullHadTools.h"

ZprimeFullHadSelection::ZprimeFullHadSelection(int TopTag1,int TopTag2,int BTag1,int BTag2,int NsubjettinessTag1,int NsubjettinessTag2,double minPt)
{
  m_TopTag1 = TopTag1;
  m_TopTag2 = TopTag2;
  m_BTag1 = BTag1;
  m_BTag2 = BTag2;
  m_NsubjettinessTag1 = NsubjettinessTag1;
  m_NsubjettinessTag2 = NsubjettinessTag2;
  m_minPt = minPt;
}

bool ZprimeFullHadSelection::pass(BaseCycleContainer *bcc)
{
  int index1=-1,index2=-1;
  for (unsigned int i=0; i<bcc->topjets->size(); i++)
  {
    bool isTopTagged = HepTopTag(bcc->topjets->at(i));
    bool isBTagged = subJetBTag(bcc->topjets->at(i),e_CSVM,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
    bool isNsubTagged = bcc->topjets->at(i).tau3()/bcc->topjets->at(i).tau2()<0.6;
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = bcc->topjets->at(i).pt()>m_minPt;
    switch (m_TopTag1)
    {
      case  0:                   TopTagCond=true; break;
      case  1: if ( isTopTagged) TopTagCond=true; break;
      case -1: if (!isTopTagged) TopTagCond=true; break;
    }
    switch (m_BTag1)
    {
      case  0:                 BTagCond=true; break;
      case  1: if ( isBTagged) BTagCond=true; break;
      case -1: if (!isBTagged) BTagCond=true; break;
    }
    switch (m_NsubjettinessTag1)
    {
      case  0:                    NsubCond=true; break;
      case  1: if ( isNsubTagged) NsubCond=true; break;
      case -1: if (!isNsubTagged) NsubCond=true; break;
    }
    if (TopTagCond && BTagCond && NsubCond && ptCond)
    {
      if (index1==-1)
      {
	index1=i;
      }
      else
      {
	if (bcc->topjets->at(i).pt()>bcc->topjets->at(index1).pt()) index1=i;
      }
    }
  }
  
  if (index1==-1) return false;
   
  for (unsigned int i=0; i<bcc->topjets->size(); i++)
  {
    bool isTopTagged = HepTopTag(bcc->topjets->at(i));
    bool isBTagged = subJetBTag(bcc->topjets->at(i),e_CSVM,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
    bool isNsubTagged = bcc->topjets->at(i).tau3()/bcc->topjets->at(i).tau2()<0.6;
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = bcc->topjets->at(i).pt()>m_minPt;
    switch (m_TopTag2)
    {
      case  0:                   TopTagCond=true; break;
      case  1: if ( isTopTagged) TopTagCond=true; break;
      case -1: if (!isTopTagged) TopTagCond=true; break;
    }
    switch (m_BTag2)
    {
      case  0:                 BTagCond=true; break;
      case  1: if ( isBTagged) BTagCond=true; break;
      case -1: if (!isBTagged) BTagCond=true; break;
    }
    switch (m_NsubjettinessTag2)
    {
      case  0:                    NsubCond=true; break;
      case  1: if ( isNsubTagged) NsubCond=true; break;
      case -1: if (!isNsubTagged) NsubCond=true; break;
    }
    if (TopTagCond && BTagCond && NsubCond && ptCond)
    {
      if (i!=index1)
      {
	if (index2==-1)
	{
	  index2=i;
	}
	else
	{
	  if (bcc->topjets->at(i).pt()>bcc->topjets->at(index2).pt()) index2=i;
	}
      }
    }
  }
  
  return (index1!=-1 && index2!=-1 && index1!=index2); 
}

std::string ZprimeFullHadSelection::description()
{
    return "Z prime full hadronic selection";
}

void printTrigger(BaseCycleContainer *bcc)
{
  std::cout<<"##########"<<std::endl;
  for(unsigned int i=0; i<bcc->triggerNames_actualrun.size(); ++i)
  { if(bcc->triggerResults->at(i))
    std::cout<<bcc->triggerNames_actualrun.at(i)<<" "<<bcc->triggerResults->at(i)<<std::endl;
  }
  std::cout<<"##########"<<std::endl;
}