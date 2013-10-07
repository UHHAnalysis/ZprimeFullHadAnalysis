#ifndef ZprimeFullHadTools_H
#define ZprimeFullHadTools_H

#include "SFrameTools/include/Objects.h"
#include "SFrameTools/include/Utils.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "SFrameTools/include/Selection.h"
#include "SFrameTools/include/EventCalc.h"

class ZprimeFullHadSelection: public SelectionModule {
public:
    ZprimeFullHadSelection(int,int,int,int,int,int,double);
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
    double m_minPt;
};

void printTrigger(BaseCycleContainer *);
std::vector<int> getTopJetsIndices(BaseCycleContainer *bcc,int m_TopTag1,int m_TopTag2,int m_BTag1,int m_BTag2,int m_NsubjettinessTag1,int m_NsubjettinessTag2,double m_minPt);

#endif