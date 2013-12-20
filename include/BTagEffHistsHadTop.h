#ifndef BTagEffHistsHadTop_H
#define BTagEffHistsHadTop_H

// ROOT include(s):
#include <TObject.h>
#include <TString.h>

// Local include(s):
#include "include/ZprimeFullHadTools.h"
#include "SFrameTools/include/EventCalc.h"
#include <TObject.h>
#include <TString.h>
#include "TH2.h"

/**
 *   Class for booking and filling btag histograms
 *
 *   
 *   @version $Revision: 1.1 $
 */

class BTagEffHistsHadTop : public BaseHists {

public:
   /// Named constructor
  BTagEffHistsHadTop(const char* name);

   /// Default destructor
   ~BTagEffHistsHadTop();

   void Init();

   void Fill();

   void Finish();

private:

}; // class BTagEffHistsHadTop

#endif // BTagEffHistsHadTop_H
