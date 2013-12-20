#ifndef RocHists_H
#define RocHists_H

// ROOT include(s):
#include <TObject.h>
#include <TString.h>
#include "TH2.h"

// Local include(s):
#include "SFrameTools/include/BaseHists.h"

/**
 *   SemileptonicPreselection class for booking and filling histograms
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

class RocHists : public BaseHists {

public:
   /// Named constructor
   RocHists(const char* name);

   /// Default destructor
   ~RocHists();

   void Init();

   void Fill();

   void Finish();
   
   void SetIdVersion(TString s);

private:
 TString idVersion;
}; // class RocHists


#endif // RocHists_H
