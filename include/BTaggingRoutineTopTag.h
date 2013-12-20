#ifndef BTaggingRoutineTopTag_H
#define BTaggingRoutineTopTag_H

#include "include/ZprimeFullHadTools.h"
#include "SFrameTools/include/EventCalc.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"


/**
 *  @module to apply data-MC scale factors for b tagging
 *
 *
 */
class BTaggingRoutineTopTag {
public:
    /**
     * constructor
     *
     */
    BTaggingRoutineTopTag(
		    float csvcut, TString mode, TString filename
    );
    ///Default destructor
    ~BTaggingRoutineTopTag() {
      file_mc->Close();
      delete file_mc;
    };

    ///return the weighted correction factor
    double GetScaleWeight();
    
    //void SaveHistos(void);

private:

    float m_csvcut;
    TString m_mode;
    TString m_filename;
    //TH1F * flavourhisto;
    //TH1F * percentagehisto;
    //TH1F * etahisto;
    TFile *file_mc;
                 
};

#endif
