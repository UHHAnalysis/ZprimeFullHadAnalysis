#include "include/ZprimeFullHadTools.h"

ZprimeFullHadSelection::ZprimeFullHadSelection(int TopTag1,int TopTag2,int BTag1,int BTag2,int NsubjettinessTag1,int NsubjettinessTag2,E_BtagType BTagType1,E_BtagType BTagType2,double minPt)
{
  m_TopTag1 = TopTag1;
  m_TopTag2 = TopTag2;
  m_BTag1 = BTag1;
  m_BTag2 = BTag2;
  m_NsubjettinessTag1 = NsubjettinessTag1;
  m_NsubjettinessTag2 = NsubjettinessTag2;
  m_BTagType1 = BTagType1;
  m_BTagType2 = BTagType2;
  m_minPt = minPt;
}

bool ZprimeFullHadSelection::pass(BaseCycleContainer *bcc)
{
/*  int index1=-1,index2=-1;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    bool isTopTagged = HepTopTag(bcc->toptagjets->at(i));
    //bool isBTagged = subJetBTag(bcc->toptagjets->at(i),e_CSVM,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
    bool isBTagged = subJetBTag(bcc->toptagjets->at(i),e_CSVM)>0;
    bool isNsubTagged = bcc->toptagjets->at(i).tau3()/bcc->toptagjets->at(i).tau2()<0.6;
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = bcc->toptagjets->at(i).pt()>m_minPt;
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
	if (bcc->toptagjets->at(i).pt()>bcc->toptagjets->at(index1).pt()) index1=i;
      }
    }
  }
  
  if (index1==-1) return false;
   
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
    bool isTopTagged = HepTopTag(bcc->toptagjets->at(i));
//     bool isBTagged = subJetBTag(bcc->toptagjets->at(i),e_CSVM,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
    bool isBTagged = subJetBTag(bcc->toptagjets->at(i),e_CSVM)>0;
    bool isNsubTagged = bcc->toptagjets->at(i).tau3()/bcc->toptagjets->at(i).tau2()<0.6;
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = bcc->toptagjets->at(i).pt()>m_minPt;
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
	  if (bcc->toptagjets->at(i).pt()>bcc->toptagjets->at(index2).pt()) index2=i;
	}
      }
    }
  }*/
  std::vector<int> index = getTopJetsIndices(bcc, m_TopTag1,  m_TopTag2,  m_BTag1,  m_BTag2,  m_NsubjettinessTag1,  m_NsubjettinessTag2, m_BTagType1, m_BTagType2,  m_minPt);
  return (index[0]!=-1 && index[1]!=-1 && index[0]!=index[1]); 
}

std::string ZprimeFullHadSelection::description()
{
    return "Z prime full hadronic selection";
}

std::vector<int> getTopJetsIndices(BaseCycleContainer *bcc,int m_TopTag1,int m_TopTag2,int m_BTag1,int m_BTag2,int m_NsubjettinessTag1,int m_NsubjettinessTag2,E_BtagType m_BTagType1,E_BtagType m_BTagType2,double m_minPt)
{
  int index1=-1,index2=-1;
//   cout<<bcc->toptagjets<<endl;
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)
  {
//     cout<<1<<endl;
    bool isTopTagged = HepTopTag(bcc->toptagjets->at(i));
//     bool isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType1,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
    bool isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType1)>0;
    int indexCA15 = getMatchedCA15Index(bcc, i);
    bool isNsubTagged = false;
//     cout<<2<<endl;
    if (indexCA15>=0) isNsubTagged = ((bcc->topjets->at(indexCA15).tau3()/bcc->topjets->at(indexCA15).tau2())<0.6);
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = bcc->toptagjets->at(i).pt()>m_minPt;
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
	if (bcc->toptagjets->at(i).pt()>bcc->toptagjets->at(index1).pt()) index1=i;
      }
    }
  }
  
  //if (index1==-1) return false;
   
  for (unsigned int i=0; i<bcc->toptagjets->size(); i++)  
  {
    bool isTopTagged = HepTopTag(bcc->toptagjets->at(i));
//     bool isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType2,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
    bool isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType2)>0;
    int indexCA15 = getMatchedCA15Index(bcc, i);
    bool isNsubTagged = false;
    if (indexCA15>=0) isNsubTagged = ((bcc->topjets->at(indexCA15).tau3()/bcc->topjets->at(indexCA15).tau2())<0.6);
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = bcc->toptagjets->at(i).pt()>m_minPt;
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
	  if (bcc->toptagjets->at(i).pt()>bcc->toptagjets->at(index2).pt()) index2=i;
	}
      }
    }
  }
  std::vector<int> a;
  a.push_back(index1);
  a.push_back(index2);
  return a; 
}

void printTrigger(BaseCycleContainer *bcc)
{
  std::cout<<"##########"<<std::endl;
  for(unsigned int i=0; i<bcc->triggerNames_actualrun.size(); ++i)
  { //if(bcc->triggerResults->at(i))
    std::cout<<bcc->triggerNames_actualrun.at(i)<<" "<<bcc->triggerResults->at(i)<<std::endl;
  }
  std::cout<<"##########"<<std::endl;
}

int getMatchedCA15Index(BaseCycleContainer *bcc, int indexHTT)
{
  double minDeltaR = double_infinity();
  int index = -1;
  for (unsigned int i=0; i<bcc->topjets->size(); i++)
  {
    double deltaR = bcc->toptagjets->at(indexHTT).deltaR(bcc->topjets->at(i));
    if (deltaR<minDeltaR)
    {
      minDeltaR = deltaR;
      index = i;
    }
  }
  return index;
}

bool checkIndices(std::vector<int> index)
{
  return (index[0]!=-1 && index[1]!=-1 && index[0]!=index[1]); 
}