#ifndef SemileptonicselectionHists_H
#define SemileptonicselectionHists_H

// ROOT include(s):
#include "include/ZprimeFullHadTools.h"
#include "SFrameTools/include/EventCalc.h"
#include <TObject.h>
#include <TString.h>
#include "TH2.h"

// Local include(s):


/**
 *   Semileptonicselection class for booking and filling histograms
 *
 *   This class books and fills a collection of histograms.
 *   It should have a unique name, such that the histograms
 *   of multiple instances of this class are ordered in the
 *   output file. 
 *   Always sort your histograms and used methods topically.
 *   This example collection can be used for data and reconstructed
 *   MC events.
 *   
 *   @version $Revision: 1.2 $
 */

class SemileptonicselectionHists : public BaseHists {

public:
   /// Named constructor
   SemileptonicselectionHists(const char* name);

   /// Default destructor
   ~SemileptonicselectionHists();

   void Init();

   void Fill();

   void Finish();

private:
  //TopPtReweight * m_tpr;

}; // class SemileptonicselectionHists


#endif // SemileptonicselectionHists_H
