#ifndef ZprimeFullHadTools_H
#define ZprimeFullHadTools_H

#include "SFrameTools/include/Objects.h"
#include "SFrameTools/include/Utils.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "SFrameTools/include/Selection.h"
#include "SFrameTools/include/EventCalc.h"
#include "SFrameTools/include/BaseHists.h"


class ZprimeFullHadSelection: public SelectionModule {
public:
    ZprimeFullHadSelection(int,int,int,int,int,int,int,E_BtagType,E_BtagType,double,double,double,double,double);
    ~ZprimeFullHadSelection() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:
    int m_TopTag1;
    int m_TopTag2;
    int m_BTag1;
    int m_BTag2;
    int m_NsubjettinessTag1;
    int m_NsubjettinessTag2;
    int m_useDeltaY;
    E_BtagType m_BTagType1;
    E_BtagType m_BTagType2;
    double m_NsubCut1;
    double m_NsubCut2;
    double m_deltaY;
    double m_minPt1;
    double m_minPt2;
};

class ZprimeFullHadHists : public BaseHists {

public:
   /// Named constructor
   ZprimeFullHadHists(const char* name);

   /// Default destructor
   ~ZprimeFullHadHists();

   void Init();

   void setIndices(std::vector<int>);
   void Fill();
   void Fill2(std::vector<int>,string version="");

   void Finish();

private:
  std::vector<int> TopJetIndices;
}; // class ZprimeFullHadHists

// class RapidityCutSelection: public SelectionModule {
// public:
//     RapidityCutSelection(int,int,int,int,int,int,E_BtagType,E_BtagType,double);
//     ~RapidityCutSelection() {};
// 
//     virtual bool pass(BaseCycleContainer*);
//     virtual std::string description();
// 
// private:
//     int m_TopTag1;
//     int m_TopTag2;
//     int m_BTag1;
//     int m_BTag2;
//     int m_NsubjettinessTag1;
//     int m_NsubjettinessTag2;
//     E_BtagType m_BTagType1;
//     E_BtagType m_BTagType2;
//     double m_minPt;
// };

void printTrigger(BaseCycleContainer *);
std::vector<int> getTopJetsIndices(BaseCycleContainer *bcc,int m_TopTag1,int m_TopTag2,int m_BTag1,int m_BTag2,int m_NsubjettinessTag1,int m_NsubjettinessTag2,int m_useDeltaY,E_BtagType m_BTagType1,E_BtagType m_BTagType2,double m_NsubCut1,double m_NsubCut2,double m_deltaY,double m_minPt1,double m_minPt2,
				   std::vector<bool> heptoptag_list = std::vector<bool>(),
				   std::vector<int> btag_list = std::vector<int>(),
				   std::vector<double> nsubjettiness_list = std::vector<double>());
int getMatchedCA15Index(BaseCycleContainer *bcc, int indexHTT);
bool checkIndices(std::vector<int>);
float deltaY(BaseCycleContainer *,std::vector<int>);
bool rapidityCut(BaseCycleContainer *,std::vector<int>, double value=1.0);
float getNsub(BaseCycleContainer *,int);
bool MassHepTopTag(TopJet topjet, double mlow=140.0, double mhigh=250.0);
bool MassHepTopTag(TopJet topjet, double minpt, double mlow, double mhigh);
bool BareHepTopTag(TopJet topjet);
bool HepTopTagNoMassCut(TopJet topjet);
bool MassAndPtCut(TopJet topjet,double minpt=200.0, double mlow=140.0, double mhigh=250.0);
bool variableMassHepTopTag(TopJet topjet, double ptJetMin = 200., double massWindowLower = 0.85, double massWindowUpper = 1.15, double cutCondition2 = 0.35, double cutCondition3 = 0.35, double mlow=140.0, double mhigh=250.0);
void makeCategories(BaseCycleContainer * bcc, ZprimeFullHadHists * inclusive_btag, ZprimeFullHadHists * zero_btag, ZprimeFullHadHists * one_btag, ZprimeFullHadHists * two_btag, E_BtagType m_BTagType, int use_nsubjettiness, int use_deltay,
		    std::vector<bool> heptoptag_list,
		    std::vector<int> btag_list,
		    std::vector<double> nsubjettiness_list, string version="");
double TopJetMass(TopJet topjet);

//for HepTopTagger validation
class NHadTopJetSelection2: public SelectionModule {
public:
    NHadTopJetSelection2(int min_nparticle, int max_nparticle=int_infinity(),  double ptmin=0., double etamax=double_infinity(), double deltaphi=2*PI/3);
    ~NHadTopJetSelection2() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:
    int m_min_nparticle;
    int m_max_nparticle;
    double m_ptmin;
    double m_etamax;
    double m_deltaphi;
};
class heptoptag_masscut_Selection: public SelectionModule {
public:
    heptoptag_masscut_Selection();
    ~heptoptag_masscut_Selection() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:
  
};
int findTheHighestPtGoodTopJet(BaseCycleContainer *bcc);

class heptoptag_NOmasscut_Selection: public SelectionModule {
public:
    heptoptag_NOmasscut_Selection();
    ~heptoptag_NOmasscut_Selection() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:

};

class NAntiMuonSubBTagSelection2: public SelectionModule {
public:

  NAntiMuonSubBTagSelection2(int min_nbtag, int max_nbtag=int_infinity(), E_BtagType type=e_CSVM, double ptmin=0., double etamax=double_infinity() );
    ~NAntiMuonSubBTagSelection2() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:
    int m_min_nbtag;
    int m_max_nbtag;
    E_BtagType m_type;
    double m_ptmin;
    double m_etamax;
};
class NMuonBTagSelection2: public SelectionModule {
public:

  NMuonBTagSelection2(int min_nbtag, int max_nbtag=int_infinity(), E_BtagType type=e_CSVM, double ptmin=0., double etamax=double_infinity() );
    ~NMuonBTagSelection2() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:
    int m_min_nbtag;
    int m_max_nbtag;
    E_BtagType m_type;
    double m_ptmin;
    double m_etamax;
};

class NTopJetSelection2: public SelectionModule {
public:
    NTopJetSelection2(int min_nparticle, int max_nparticle=int_infinity(),  double ptmin=0., double etamax=double_infinity());
    ~NTopJetSelection2() {};

    virtual bool pass(BaseCycleContainer*);
    virtual std::string description();

private:
    int m_min_nparticle;
    int m_max_nparticle;
    double m_ptmin;
    double m_etamax;
};
#endif