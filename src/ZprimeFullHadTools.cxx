#include "include/ZprimeFullHadTools.h"

ZprimeFullHadSelection::ZprimeFullHadSelection(int TopTag1,int TopTag2,int BTag1,int BTag2,int NsubjettinessTag1,int NsubjettinessTag2,int useDeltaY,E_BtagType BTagType1,E_BtagType BTagType2,double NsubCut1,double NsubCut2,double deltaY,double minPt1,double minPt2)
{
  m_TopTag1 = TopTag1;
  m_TopTag2 = TopTag2;
  m_BTag1 = BTag1;
  m_BTag2 = BTag2;
  m_NsubjettinessTag1 = NsubjettinessTag1;
  m_NsubjettinessTag2 = NsubjettinessTag2;
  m_useDeltaY = useDeltaY;
  m_BTagType1 = BTagType1;
  m_BTagType2 = BTagType2;
  m_NsubCut1 = NsubCut1;
  m_NsubCut2 = NsubCut2;
  m_deltaY = deltaY;
  m_minPt1 = minPt1;
  m_minPt2 = minPt2;
}

bool ZprimeFullHadSelection::pass(BaseCycleContainer *bcc)
{
  std::vector<int> index = getTopJetsIndices(bcc, m_TopTag1, m_TopTag2, m_BTag1, m_BTag2, m_NsubjettinessTag1, m_NsubjettinessTag2, m_useDeltaY, m_BTagType1, m_BTagType2, m_NsubCut1, m_NsubCut2, m_deltaY, m_minPt1, m_minPt2);
  return checkIndices(index);//(index[0]!=-1 && index[1]!=-1 && index[0]!=index[1]); 
}

std::string ZprimeFullHadSelection::description()
{
    return "Z prime full hadronic selection";
}

std::vector<int> getTopJetsIndices(BaseCycleContainer *bcc,int m_TopTag1,int m_TopTag2,int m_BTag1,int m_BTag2,int m_NsubjettinessTag1,int m_NsubjettinessTag2,int m_useDeltaY,E_BtagType m_BTagType1,E_BtagType m_BTagType2,double m_NsubCut1,double m_NsubCut2,double m_deltaY,double m_minPt1,double m_minPt2,
				   std::vector<bool> heptoptag_list,
				   std::vector<int> btag_list,
				   std::vector<double> nsubjettiness_list)
{
  int index1=-1,index2=-1;
  
  /////////first topjet
  for (unsigned int i=0; i<bcc->topjets->size(); i++)
  {
    bool isTopTagged = false, isBTagged = false, isNsubTagged = false;
    if (heptoptag_list.size()>0)
    {
      isTopTagged = heptoptag_list[i];
      isBTagged = (btag_list[i]>0);
      isNsubTagged = (nsubjettiness_list[i]<m_NsubCut1);
    }
    else
    {
      if (m_TopTag1!=0) {isTopTagged = PtHepTopTag(bcc->toptagjets->at(i),m_minPt1);}
      //bool isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType1,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
      if (m_BTag1!=0) {isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType1)>0;}
      //if (m_BTag1!=0) {isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType1,"mean","/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZBTagEff.root")>0;}
      if (m_NsubjettinessTag1!=0)
      {
	int indexCA15 = getMatchedCA15Index(bcc, i);
	if (indexCA15>=0) isNsubTagged = ((bcc->topjets->at(indexCA15).tau3()/bcc->topjets->at(indexCA15).tau2())<m_NsubCut1);
      }
    }
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = true;//bcc->toptagjets->at(i).pt()>m_minPt1;
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
  if (index1==-1) return {-1,-1};
  
  
  /////////second topjet 
  for (unsigned int i=0; i<bcc->topjets->size(); i++)
  {
    bool isTopTagged = false, isBTagged = false, isNsubTagged = false;
    if (heptoptag_list.size()>0)
    {
      isTopTagged = heptoptag_list[i];
      isBTagged = (btag_list[i]>0);
      isNsubTagged = (nsubjettiness_list[i]<m_NsubCut1);
    }
    else
    {
      if (m_TopTag2!=0) {isTopTagged = PtHepTopTag(bcc->toptagjets->at(i),m_minPt2);}
      //bool isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType2,"mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>0;
      if (m_BTag2!=0) {isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType2)>0;}
      //if (m_BTag2!=0) {isBTagged = subJetBTag(bcc->toptagjets->at(i),m_BTagType2,"mean","/scratch/hh/dust/naf/cms/user/usai/ZprimeFullHad/ZBTagEff.root")>0;}
      if (m_NsubjettinessTag2!=0)
      {
	int indexCA15 = getMatchedCA15Index(bcc, i);
	if (indexCA15>=0) isNsubTagged = ((bcc->topjets->at(indexCA15).tau3()/bcc->topjets->at(indexCA15).tau2())<m_NsubCut2);
      }
    }
    bool TopTagCond = false, BTagCond = false, NsubCond = false;
    bool ptCond = true;//bcc->toptagjets->at(i).pt()>m_minPt2;
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
    bool separation=false, separationCondition=false;
    if (m_useDeltaY!=0) {
      std::vector<int> rindices={index1,i};
      separation=rapidityCut(bcc,rindices, m_deltaY);
    }
    switch (m_useDeltaY)
    {
      case  0:                  separationCondition=true; break;
      case  1: if ( separation) separationCondition=true; break;
      case -1: if (!separation) separationCondition=true; break;
    }
    if (TopTagCond && BTagCond && NsubCond && ptCond && separationCondition)
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
  //std::vector<int> a = {index1,index2};
  //a.push_back(index1);
  //a.push_back(index2);
  return {index1,index2}; 
}

void printTrigger(BaseCycleContainer *bcc)
{
  std::cout<<"##########"<<std::endl;
  for(unsigned int i=0; i<bcc->triggerNames_actualrun.size(); ++i)
  { //if(bcc->triggerResults->at(i))
  if(!bcc->triggerNames_actualrun.at(i).find("HLT_HT750"))
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
  if (minDeltaR>1) return -1; else
  return index;
}

bool checkIndices(std::vector<int> index)
{
  return (index[0]!=-1 && index[1]!=-1 && index[0]!=index[1]); 
}

float deltaY(TopJet j1,TopJet j2)
{
  return fabs(j1.v4().Rapidity()-j2.v4().Rapidity());
}

float getMtt(TopJet j1,TopJet j2)
{
//   return (j1.v4()+j2.v4()).M();
  
  
  LorentzVector allsubjets(0,0,0,0);
  
  for(int j=0; j<j1.numberOfDaughters(); ++j)
  {
    allsubjets += j1.subjets()[j].v4();
  }
  
  for(int j=0; j<j2.numberOfDaughters(); ++j)
  {
    allsubjets += j2.subjets()[j].v4();
  }
  
  if(!allsubjets.isTimelike())
  {
    return 0.0;
  }
  
  else
  {
    return allsubjets.M();
  }
  
}

bool rapidityCut(BaseCycleContainer * bcc,std::vector<int> index, double value)
{
  double mass=getMtt(bcc->toptagjets->at(index[0]),bcc->toptagjets->at(index[1]));
  if (mass<2000) return true;
  else return deltaY(bcc->toptagjets->at(index[0]),bcc->toptagjets->at(index[1]))<value;
}

float getNsub(BaseCycleContainer * bcc,int index)
{
  int indexCA15 = getMatchedCA15Index(bcc, index);
  if (indexCA15>=0)  return bcc->topjets->at(indexCA15).tau3()/bcc->topjets->at(indexCA15).tau2();
  else               return 1000;
}

float getCMSNsub(BaseCycleContainer * bcc,int index)
{
  return bcc->higgstagjets->at(index).tau3()/bcc->higgstagjets->at(index).tau2();
}

bool variableMassHepTopTag(TopJet topjet, double ptJetMin, double massWindowLower, double massWindowUpper, double cutCondition2, double cutCondition3, double mlow, double mhigh)
{

  TopJet nextjet=topjet;
  
  double mjet;
  double ptjet;
  int nsubjets;
  
  double topmass=172.3;
  double wmass=80.4;
  
  nsubjets=nextjet.numberOfDaughters();
  
  LorentzVector allsubjets(0,0,0,0);
  
  for(int j=0; j<nextjet.numberOfDaughters(); ++j) {
    allsubjets += nextjet.subjets()[j].v4();
  }
  if(!allsubjets.isTimelike()) {
    mjet=0;
    return false;
  }
  
  mjet = allsubjets.M();
  ptjet= nextjet.pt();
    
  double m12, m13, m23;
  
  //The subjetcs have to be three
  if(nsubjets==3) {
    
    std::vector<Particle> subjets = nextjet.subjets();
    sort(subjets.begin(), subjets.end(), HigherPt());
    
    m12 = 0;
    if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
      m12=(subjets[0].v4()+subjets[1].v4()).M();
    m13 = 0;
    if( (subjets[0].v4()+subjets[2].v4()).isTimelike() )
      m13=(subjets[0].v4()+subjets[2].v4()).M();
    m23 = 0;
    if( (subjets[1].v4()+subjets[2].v4()).isTimelike()  )
      m23 = (subjets[1].v4()+subjets[2].v4()).M();
    
  } else {
    return false;
  }
  
  double rmin=massWindowLower*wmass/topmass;
  double rmax=massWindowUpper*wmass/topmass;
  
  int keep=0;
  
  //Conditions on the subjects: at least one has to be true
  //1 condition
  if(atan(m13/m12)>0.2 && atan(m13/m12)<1.3 && m23/mjet>rmin && m23/mjet<rmax) keep=1;
  
  //2 condition
  double cond2left=pow(rmin,2)*(1+pow((m13/m12),2));
  double cond2cent=1-pow(m23/mjet,2);
  double cond2right=pow(rmax,2)*(1+pow(m13/m12,2));
  
  if(cond2left<cond2cent && cond2cent<cond2right && m23/mjet>cutCondition2) keep=1;
  
  //3 condition
  double cond3left=pow(rmin,2)*(1+pow((m12/m13),2));
  double cond3cent=1-pow(m23/mjet,2);
  double cond3right=pow(rmax,2)*(1+pow(m12/m13,2));
  
  if(cond3left<cond3cent && cond3cent<cond3right && m23/mjet>cutCondition3) keep=1;
  
  if( mjet < mlow || mjet > mhigh) keep=0;
  
  //Final requirement: at least one of the three subjets conditions and total pt
  if(keep==1 && ptjet>ptJetMin) {
    return true;
  } else {
    return false;
  }
  
}

float getHT50(BaseCycleContainer * bcc)
{
  float ht=0.0;
  for(unsigned int i=0; i<bcc->jets->size(); ++i)
  {
    if (bcc->jets->at(i).pt()>=50.0)
    {
      ht+=bcc->jets->at(i).pt();
    }
  }
  return ht;
}

bool PtHepTopTag(TopJet t, float minimumpt)
{
 return variableHepTopTag(t, minimumpt, 0.85, 1.15, 0.35, 0.35); 
}

bool MassHepTopTag(TopJet topjet, double mlow, double mhigh)
{
  return variableMassHepTopTag(topjet, 200., 0.85, 1.15, 0.35, 0.35, mlow, mhigh);
}

bool BareHepTopTag(TopJet topjet)
{
  return MassHepTopTag(topjet,0.,0.,100000.);
}

bool HepTopTagNoMassCut(TopJet topjet)
{
  return MassHepTopTag(topjet,200.,0.,100000.);
}

bool MassHepTopTag(TopJet topjet, double minpt, double mlow, double mhigh)
{
  return variableMassHepTopTag(topjet, minpt, 0.85, 1.15, 0.35, 0.35, mlow, mhigh);
}

bool MassAndPtCut(TopJet topjet,double minpt, double mlow, double mhigh)
{ 
  double mjet=TopJetMass(topjet);
//   LorentzVector allsubjets(0,0,0,0);
//   
//   for(int j=0; j<topjet.numberOfDaughters(); ++j) {
//     allsubjets += topjet.subjets()[j].v4();
//   }
//   
//   if(!allsubjets.isTimelike()) {
//     mjet=0;
//     return false;
//   }
//   
//   mjet = allsubjets.M();
  
  return topjet.pt()>minpt && mjet>mlow && mjet<mhigh;
}






bool MassHepTopTagWithMatch(TopJet topjet, double mlow, double mhigh)
{
  return variableMassHepTopTagWithMatch(topjet, 200., 0.85, 1.15, 0.35, 0.35, mlow, mhigh);
}
bool MassHepTopTagWithMatch(TopJet topjet, double minpt, double mlow, double mhigh)
{
  return variableMassHepTopTagWithMatch(topjet, minpt, 0.85, 1.15, 0.35, 0.35, mlow, mhigh);
}
bool BareHepTopTagWithMatch(TopJet topjet)
{
  return MassHepTopTagWithMatch(topjet,0.,0.,100000.);
}
bool HepTopTagNoMassCutWithMatch(TopJet topjet)
{
  return MassHepTopTagWithMatch(topjet,200.,0.,100000.);
}
bool MassAndPtCutWithMatch(TopJet topjet,double minpt, double mlow, double mhigh)
{
    EventCalc* calc = EventCalc::Instance();
  
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
  double deltarmin = double_infinity();
  
  TopJet nextjet;
  
  for(unsigned int it=0; it<bcc->toptagjets->size();++it){

    TopJet top4jet=bcc->toptagjets->at(it);
    
    if(top4jet.deltaR(topjet) < deltarmin){
      deltarmin = top4jet.deltaR(topjet);
      nextjet = top4jet;
    }
    
  }
  
  if(deltarmin>=0.3) return 0;
  
    double mjet=TopJetMass(nextjet);
  
  return (nextjet.pt()>minpt && mjet>mlow && mjet<mhigh) ;
  
}
bool variableMassHepTopTagWithMatch(TopJet topjet, double ptJetMin, double massWindowLower, double massWindowUpper, double cutCondition2, double cutCondition3, double mlow, double mhigh)
{
    //Taking the top tag from the proper jet collection

  EventCalc* calc = EventCalc::Instance();
  
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
  double deltarmin = double_infinity();
  
  TopJet nextjet;
  
  for(unsigned int it=0; it<bcc->toptagjets->size();++it){

    TopJet top4jet=bcc->toptagjets->at(it);
    
    if(top4jet.deltaR(topjet) < deltarmin){
      deltarmin = top4jet.deltaR(topjet);
      nextjet = top4jet;
    }
    
  }
  
  if(deltarmin>=0.3) return 0;

  double mjet;
  double ptjet;
  int nsubjets;
  
  double topmass=172.3;
  double wmass=80.4;
  
  nsubjets=nextjet.numberOfDaughters();
  
  LorentzVector allsubjets(0,0,0,0);
  
  for(int j=0; j<nextjet.numberOfDaughters(); ++j) {
    allsubjets += nextjet.subjets()[j].v4();
  }
  if(!allsubjets.isTimelike()) {
    mjet=0;
    return false;
  }
  
  mjet = allsubjets.M();
  ptjet= nextjet.pt();
    
  double m12, m13, m23;
  
  //The subjetcs have to be three
  if(nsubjets==3) {
    
    std::vector<Particle> subjets = nextjet.subjets();
    sort(subjets.begin(), subjets.end(), HigherPt());
    
    m12 = 0;
    if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
      m12=(subjets[0].v4()+subjets[1].v4()).M();
    m13 = 0;
    if( (subjets[0].v4()+subjets[2].v4()).isTimelike() )
      m13=(subjets[0].v4()+subjets[2].v4()).M();
    m23 = 0;
    if( (subjets[1].v4()+subjets[2].v4()).isTimelike()  )
      m23 = (subjets[1].v4()+subjets[2].v4()).M();
    
  } else {
    return false;
  }
  
  double rmin=massWindowLower*wmass/topmass;
  double rmax=massWindowUpper*wmass/topmass;
  
  int keep=0;
  
  //Conditions on the subjects: at least one has to be true
  //1 condition
  if(atan(m13/m12)>0.2 && atan(m13/m12)<1.3 && m23/mjet>rmin && m23/mjet<rmax) keep=1;
  
  //2 condition
  double cond2left=pow(rmin,2)*(1+pow((m13/m12),2));
  double cond2cent=1-pow(m23/mjet,2);
  double cond2right=pow(rmax,2)*(1+pow(m13/m12,2));
  
  if(cond2left<cond2cent && cond2cent<cond2right && m23/mjet>cutCondition2) keep=1;
  
  //3 condition
  double cond3left=pow(rmin,2)*(1+pow((m12/m13),2));
  double cond3cent=1-pow(m23/mjet,2);
  double cond3right=pow(rmax,2)*(1+pow(m12/m13,2));
  
  if(cond3left<cond3cent && cond3cent<cond3right && m23/mjet>cutCondition3) keep=1;
  
  if( nextjet.v4().M() < mlow || nextjet.v4().M() > mhigh) keep=0;
  
  //Final requirement: at least one of the three subjets conditions and total pt
  if(keep==1 && ptjet>ptJetMin) {
    return true;
  } else {
    return false;
  }
  
}
bool PtHepTopTagWithMatch(TopJet t, float minimumpt)
{
  return variableHepTopTagWithMatch(t, minimumpt, 0.85, 1.15, 0.35, 0.35);
}

bool HepTopTagInverted_mw(TopJet topjet)
{
  //Taking the top tag from the proper jet collection

  EventCalc* calc = EventCalc::Instance();
  
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
  double deltarmin = double_infinity();
  
  TopJet nextjet;
  
  for(unsigned int it=0; it<bcc->toptagjets->size();++it){

    TopJet top4jet=bcc->toptagjets->at(it);
    
    if(top4jet.deltaR(topjet) < deltarmin){
      deltarmin = top4jet.deltaR(topjet);
      nextjet = top4jet;
    }
    
  }
  
  if(deltarmin>=0.3) return 0;


    double mjet;
    double ptjet;
    int nsubjets;

    double topmass=172.3;
    double wmass=80.4;

    nsubjets=nextjet.numberOfDaughters();

    LorentzVector allsubjets(0,0,0,0);

    for(int j=0; j<nextjet.numberOfDaughters(); ++j) {
        allsubjets += nextjet.subjets()[j].v4();
    }
    if(!allsubjets.isTimelike()) {
        mjet=0;
        return false;
    }

    mjet = allsubjets.M();
    ptjet= nextjet.pt();

    double m12, m13, m23;

    //The subjetcs have to be three
    if(nsubjets==3) {

        std::vector<Particle> subjets = nextjet.subjets();
        sort(subjets.begin(), subjets.end(), HigherPt());

        m12 = 0;
        if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
            m12=(subjets[0].v4()+subjets[1].v4()).M();
        m13 = 0;
        if( (subjets[0].v4()+subjets[2].v4()).isTimelike() )
            m13=(subjets[0].v4()+subjets[2].v4()).M();
        m23 = 0;
        if( (subjets[1].v4()+subjets[2].v4()).isTimelike()  )
            m23 = (subjets[1].v4()+subjets[2].v4()).M();

    } else {
        return false;
    }

    double rmin=0.85*wmass/topmass;
    double rmax=1.15*wmass/topmass;

    int keep=0;


    if (m23/mjet <= 0.35) keep = 1; 

    //invert top mass window
    if( mjet < 140. || mjet > 250.) keep=0;


    //Final requirement: at least one of the three subjets conditions and total pt
    if(keep==1 && ptjet>200.) {
        return true;
    } else {
        return false;
    }

}




void makeCategories(BaseCycleContainer * bcc, ZprimeFullHadHists * inclusive_btag, ZprimeFullHadHists * zero_btag, ZprimeFullHadHists * one_btag, ZprimeFullHadHists * two_btag, E_BtagType m_BTagType, int use_nsubjettiness, int use_deltay,
		    std::vector<bool> heptoptag_list,
		    std::vector<int> btag_list,
		    std::vector<double> nsubjettiness_list, string version)
{
  std::vector<int> Indices,Indices2,Indices3;
  double ptcut=200.0,nsubcut=0.7,ycut=1.0;  
  Indices=getTopJetsIndices(bcc,1,1,1,1,use_nsubjettiness,use_nsubjettiness,use_deltay,m_BTagType,m_BTagType,nsubcut,nsubcut,ycut,ptcut,ptcut,heptoptag_list,btag_list,nsubjettiness_list);
  if (checkIndices(Indices)){//2 btag cat
  two_btag->Fill2(Indices,version);
  inclusive_btag->Fill2(Indices,version);
  }
  else{
    Indices2=getTopJetsIndices(bcc,1,1,1,0,use_nsubjettiness,use_nsubjettiness,use_deltay,m_BTagType,m_BTagType,nsubcut,nsubcut,ycut,ptcut,ptcut,heptoptag_list,btag_list,nsubjettiness_list);
    if (checkIndices(Indices2)){//1 btag cat
      one_btag->Fill2(Indices2,version);
      inclusive_btag->Fill2(Indices2,version);
    }
    else{
      Indices3=getTopJetsIndices(bcc,1,1,0,0,use_nsubjettiness,use_nsubjettiness,use_deltay,m_BTagType,m_BTagType,nsubcut,nsubcut,ycut,ptcut,ptcut,heptoptag_list,btag_list,nsubjettiness_list);
      if(checkIndices(Indices3)){//0 btag cat
        zero_btag->Fill2(Indices3,version);
	inclusive_btag->Fill2(Indices3,version);
      }
    }
  }
}

bool makeCMSCategories(BaseCycleContainer * bcc, ZprimeFullHadHists * inclusive_btag, ZprimeFullHadHists * zero_btag, ZprimeFullHadHists * one_btag, ZprimeFullHadHists * two_btag,
		    std::vector<bool> toptag_list,
		    std::vector<int> btag_list,
		    std::vector<double> nsubjettiness_list)
{
  bool iscmsgood=false;
  std::vector<int> Indices,Indices2,Indices3;
  Indices=getCMSTopJetsIndices(bcc,1,1,toptag_list,btag_list,nsubjettiness_list);
  if (checkIndices(Indices)){//2 btag cat
  two_btag->Fill2(Indices,"",true);
  inclusive_btag->Fill2(Indices,"",true);
  iscmsgood=true;
  }
  else{
    Indices2=getCMSTopJetsIndices(bcc,1,0,toptag_list,btag_list,nsubjettiness_list);
    if (checkIndices(Indices2)){//1 btag cat
      one_btag->Fill2(Indices2,"",true);
      inclusive_btag->Fill2(Indices2,"",true);
      iscmsgood=true;
    }
    else{
      Indices3=getCMSTopJetsIndices(bcc,0,0,toptag_list,btag_list,nsubjettiness_list);
      if(checkIndices(Indices3)){//0 btag cat
         zero_btag->Fill2(Indices3,"",true);
	 inclusive_btag->Fill2(Indices3,"",true);
	 iscmsgood=true;
      }
    }
  }
  return iscmsgood;
}

double TopJetMass(TopJet topjet)
{
  double mjet;
  LorentzVector allsubjets(0,0,0,0);
  
  for(int j=0; j<topjet.numberOfDaughters(); ++j)
  {
    allsubjets += topjet.subjets()[j].v4();
  }
  
  if(!allsubjets.isTimelike())
  {
    return 0.0;
  }
  else
  {
    return allsubjets.M();
  }

//   if(!topjet.v4().isTimelike())
//   {
//     return 0.0;
//   }
//   else
//   {
//     return topjet.v4().M();
//   }

// return topjet.v4().M();
  
}

float getMaxCSV(TopJet t)
{
  std::vector<float> csv = t.btagsub_combinedSecondaryVertex();
//   cout<<csv[0]<<" "<<csv[1]<<" "<<csv[2]<<endl;
//   cout<<*max_element(std::begin(csv), std::end(csv))<<endl;
  return *max_element(std::begin(csv), std::end(csv)); 
}

std::vector<int> getCMSTopJetsIndices(BaseCycleContainer *bcc, int m_BTag1,int m_BTag2,
  		    std::vector<bool> toptag_list,
		    std::vector<int> btag_list,
		    std::vector<double> nsubjettiness_list)
{
  int index1=-1,index2=-1;
  /////////first topjet
  for (unsigned int i=0; i<bcc->higgstagjets->size(); i++)
  {
    
    bool isTopTagged = false, isBTagged = false, isNsubTagged = false;
    if (toptag_list.size()>0)
    {
      isTopTagged = toptag_list[i];
      isBTagged = (btag_list[i]>0);
      isNsubTagged = (nsubjettiness_list[i]<0.7);
    }
    else
    {
      double mjet=0; int nsubjets=0; double mmin=0;
      isTopTagged = TopTag(bcc->higgstagjets->at(i),mjet,nsubjets,mmin);
      isBTagged = subJetBTag(bcc->higgstagjets->at(i),e_CSVM)>0;
      isNsubTagged = (getCMSNsub(bcc,i)<0.7);
    }  
    
    if (m_BTag1==0) isBTagged = true;
    
    bool ptCond = bcc->higgstagjets->at(i).pt()>400.0;
    if ( isTopTagged && isBTagged && isNsubTagged && ptCond )
    {
      if (index1==-1)
      {
	index1=i;
      }
      else
      {
	if (bcc->higgstagjets->at(i).pt()>bcc->higgstagjets->at(index1).pt()) index1=i;
      }
    }
  }
  if (index1==-1) return {-1,-1};
  /////////second topjet
  for (unsigned int i=0; i<bcc->higgstagjets->size(); i++)
  {
    
    bool isTopTagged = false, isBTagged = false, isNsubTagged = false;
    if (toptag_list.size()>0)
    {
      isTopTagged = toptag_list[i];
      isBTagged = (btag_list[i]>0);
      isNsubTagged = (nsubjettiness_list[i]<0.7);
    }
    else
    {
      double mjet=0; int nsubjets=0; double mmin=0;
      isTopTagged = TopTag(bcc->higgstagjets->at(i),mjet,nsubjets,mmin);
      isBTagged = subJetBTag(bcc->higgstagjets->at(i),e_CSVM)>0;
      isNsubTagged = (getCMSNsub(bcc,i)<0.7);
    }  
    
    if (m_BTag2==0) isBTagged = true;
    
    bool ptCond = bcc->higgstagjets->at(i).pt()>400.0;
    bool yCond = (deltaY(bcc->higgstagjets->at(index1),bcc->higgstagjets->at(i))<1.0);
    bool phiCond = (bcc->higgstagjets->at(index1).deltaPhi(bcc->higgstagjets->at(i))>2.1);
    if ( isTopTagged && isBTagged && isNsubTagged && ptCond && yCond && phiCond)
    {
      if (i!=index1)
      {
	if (index2==-1)
	{
	  index2=i;
	}
	else
	{
	  if (bcc->higgstagjets->at(i).pt()>bcc->higgstagjets->at(index1).pt()) index2=i;
	}
      }
    }
  }
  return {index1,index2}; 
}

bool TopTag(TopJet t)
{
  double mjet=0; int nsubjets=0; double mmin=0;
  return TopTag(t,mjet,nsubjets,mmin);
}

//htt validation stuff
NHadTopJetSelection2::NHadTopJetSelection2(int min_nparticle, int max_nparticle, double ptmin, double etamax, double deltaphi)
{
    m_min_nparticle=min_nparticle;
    m_max_nparticle=max_nparticle;
    m_ptmin=ptmin;
    m_etamax=etamax;
    m_deltaphi=deltaphi;
}

bool NHadTopJetSelection2::pass(BaseCycleContainer *bcc)
{
    int nparticle=0;
    for(unsigned int i=0; i<bcc->toptagjets->size(); ++i) {
        if(bcc->toptagjets->at(i).pt()>m_ptmin && fabs(bcc->toptagjets->at(i).eta())<m_etamax && bcc->toptagjets->at(i).deltaR(bcc->muons->at(0))>m_deltaphi) nparticle++;
    }
    return nparticle>=m_min_nparticle && nparticle<=m_max_nparticle;
}

std::string NHadTopJetSelection2::description()
{
    char s[100];
    sprintf(s, "%d <= N(CA-jets) <= %d, with pt>%.1f GeV, |eta|<%.1f, |deltaphi(topjet,muon)|<%.1f",m_min_nparticle,m_max_nparticle,m_ptmin,m_etamax,m_deltaphi);

    return s;
}

heptoptag_masscut_Selection::heptoptag_masscut_Selection(){}
bool heptoptag_masscut_Selection::pass(BaseCycleContainer *bcc)
{
  int TheGoodTopJet=findTheHighestPtGoodTopJet(bcc);
  if (TheGoodTopJet<0) return false;
  return MassHepTopTag(bcc->toptagjets->at(TheGoodTopJet),140.0,250.0);
//return HepTopTag(bcc->toptagjets->at(TheGoodTopJet));
  
}
std::string heptoptag_masscut_Selection::description(){return "HEPTopTag with top mass cut";}

int findTheHighestPtGoodTopJet(BaseCycleContainer *bcc)
{
  double limpt=0;
  int indexjet=-99999;
  //int countjets=0;  
  std::vector<Particle> subjets_top;
  std::vector<float> btagsub_combinedSecondaryVertex_top;
  std::vector<int> flavorsub_top;
  for(unsigned int i=0; i<bcc->toptagjets->size(); ++i)
  {
    //int jettagged=0;
/*    
    subjets_top=bcc->toptagjets->at(i).subjets();
    btagsub_combinedSecondaryVertex_top=bcc->toptagjets->at(i).btagsub_combinedSecondaryVertex();
    for(unsigned int j=0; j < btagsub_combinedSecondaryVertex_top.size(); ++j)
    {  
      float test=btagsub_combinedSecondaryVertex_top[j];
      //if(test>0.244) jettagged=1;
      if(test>0.679) jettagged=1;
      //if(test>0.898) jettagged=1;
    }*/
   // if(subJetBTagOne(bcc->toptagjets->at(i), e_CSVM, "mean","/scratch/hh/dust/naf/cms/user/usai/heptoptagval/ttbarsemiforspecialSF.root")>=1) jettagged=1;
    
    
    /*jettagged=0;
    if(HepTopTag(bcc->toptagjets->at(i))){jettagged=1;}*/
    if(bcc->muons->size()>0)
    {
      double deltaphi=bcc->toptagjets->at(i).deltaR(bcc->muons->at(0));
      if(/*jettagged&&*/(deltaphi>(PI/2))&&(bcc->toptagjets->at(i).pt()>200.)&&(fabs(bcc->toptagjets->at(i).eta())<2.4))
      {
	//countjets=countjets+1;
	if(bcc->toptagjets->at(i).pt()>limpt)
	{
	  indexjet=i;
	  limpt=bcc->toptagjets->at(i).pt();
	}
      }
    } 
  }//loop over top jets 
  return indexjet;
}

heptoptag_NOmasscut_Selection::heptoptag_NOmasscut_Selection(){}
bool heptoptag_NOmasscut_Selection::pass(BaseCycleContainer *bcc)
{
  int TheGoodTopJet=findTheHighestPtGoodTopJet(bcc);
  if (TheGoodTopJet<0) return false;
  return HepTopTagNoMassCut(bcc->toptagjets->at(TheGoodTopJet));
}
std::string heptoptag_NOmasscut_Selection::description(){return "HEPTopTag without top mass cut";}

NAntiMuonSubBTagSelection2::NAntiMuonSubBTagSelection2(int min_nbtag, int max_nbtag, E_BtagType type, double ptmin, double etamax )
{
    m_min_nbtag=min_nbtag;
    m_max_nbtag=max_nbtag;
    m_type=type;
    m_ptmin=ptmin;
    m_etamax=etamax;
}

bool NAntiMuonSubBTagSelection2::pass(BaseCycleContainer *bcc)
{
    int nbtag=0;

    //Assumes to have only one muon

    for(unsigned int i=0; i<bcc->toptagjets->size(); ++i) {
      int jettagged=0;

/*      std::vector<Particle> subjets_top;
      std::vector<float> btagsub_combinedSecondaryVertex_top;
      subjets_top=bcc->toptagjets->at(i).subjets();
      btagsub_combinedSecondaryVertex_top=bcc->toptagjets->at(i).btagsub_combinedSecondaryVertex();
      for(unsigned int j=0; j < btagsub_combinedSecondaryVertex_top.size(); ++j){

	float test=btagsub_combinedSecondaryVertex_top[j];

	if(m_type==e_CSVL && test>0.244) jettagged=1;
	if(m_type==e_CSVM && test>0.679) jettagged=1;
	if(m_type==e_CSVT && test>0.898) jettagged=1;
	
      }*/
      if(subJetBTag(bcc->toptagjets->at(i), e_CSVM, "mean" ,"/nfs/dust/cms/user/usaiem/ZprimeFullHad/subjetbtageff.root")>=1) jettagged=1;

      
      
      if(bcc->muons->size() != 1){
	std::cout << "ATTENTION!!! muon size " << bcc->muons->size() << std::endl;
      }

      double deltaphi=bcc->toptagjets->at(i).deltaR(bcc->muons->at(0));
      
      if(jettagged&&(deltaphi>(PI/2))&&(bcc->toptagjets->at(i).pt()>m_ptmin)&&(fabs(bcc->toptagjets->at(i).eta())<m_etamax)){

	nbtag++;

      }

    }

    if(nbtag<m_min_nbtag) return false;
    if(nbtag>m_max_nbtag) return false;
    return true;
}

std::string NAntiMuonSubBTagSelection2::description()
{
    char s[100];
    sprintf(s, "%d <= number of sub-b-tagged top jets in the muon anti-hemisphere <= %d",m_min_nbtag,m_max_nbtag);
    return s;
}

NMuonBTagSelection2::NMuonBTagSelection2(int min_nbtag, int max_nbtag, E_BtagType type, double ptmin, double etamax )
{
    m_min_nbtag=min_nbtag;
    m_max_nbtag=max_nbtag;
    m_type=type;
    m_ptmin=ptmin;
    m_etamax=etamax;
}

bool NMuonBTagSelection2::pass(BaseCycleContainer *bcc)
{
    int nbtag=0;

    //Assumes to have only one muon

    for(unsigned int i=0; i<bcc->jets->size(); ++i) {
      int jettagged=0;
      if(m_type==e_CSVL && bcc->jets->at(i).btag_combinedSecondaryVertex()>0.244) jettagged=1;
      if(m_type==e_CSVM && bcc->jets->at(i).btag_combinedSecondaryVertex()>0.679) jettagged=1;
      if(m_type==e_CSVT && bcc->jets->at(i).btag_combinedSecondaryVertex()>0.898) jettagged=1;

      if(bcc->muons->size() != 1){
	std::cout << "ATTENTION!!! muon size " << bcc->muons->size() << std::endl;
      }

      double deltaphi=bcc->jets->at(i).deltaR(bcc->muons->at(0));
      
      if(jettagged&&(deltaphi<(PI/2))&&(bcc->jets->at(i).pt()>m_ptmin)&&(fabs(bcc->jets->at(i).eta())<m_etamax)){

	nbtag++;

      }

    }

    if(nbtag<m_min_nbtag) return false;
    if(nbtag>m_max_nbtag) return false;
    return true;
}

std::string NMuonBTagSelection2::description()
{
    char s[100];
    sprintf(s, "%d <= number of b-tags in the muon hemisphere <= %d",m_min_nbtag,m_max_nbtag);
    return s;
}

NTopJetSelection2::NTopJetSelection2(int min_nparticle, int max_nparticle, double ptmin, double etamax)
{
    m_min_nparticle=min_nparticle;
    m_max_nparticle=max_nparticle;
    m_ptmin=ptmin;
    m_etamax=etamax;
}

bool NTopJetSelection2::pass(BaseCycleContainer *bcc)
{
    int nparticle=0;
    for(unsigned int i=0; i<bcc->toptagjets->size(); ++i) {
        if(bcc->toptagjets->at(i).pt()>m_ptmin && fabs(bcc->toptagjets->at(i).eta())<m_etamax) nparticle++;
    }
    return nparticle>=m_min_nparticle && nparticle<=m_max_nparticle;
}


std::string NTopJetSelection2::description()
{
    char s[100];
    sprintf(s, "%d <= N(CA-jets) <= %d, with pt>%.1f GeV, |eta|<%.1f",m_min_nparticle,m_max_nparticle,m_ptmin,m_etamax);

    return s;
}