#ifndef ZBTagEff_H
#define ZBTagEff_H

// ROOT include(s):
#include <TObject.h>
#include <TString.h>

// Local include(s):
#include "SFrameTools/include/BaseHists.h"

/**
 *   Class for booking and filling btag histograms
 *
 *   
 *   @version $Revision: 1.1 $
 */

class ZBTagEff : public BaseHists {

public:
   /// Named constructor
  ZBTagEff(const char* name);

   /// Default destructor
   ~ZBTagEff();

   void Init();

   void Fill();

   void Finish();

private:

}; // class ZBTagEff

#endif // ZBTagEff_H
