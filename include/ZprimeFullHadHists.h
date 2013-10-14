#ifndef ZprimeFullHadHists_H
#define ZprimeFullHadHists_H

#include "SFrameTools/include/BaseHists.h"
#include "include/ZprimeFullHadTools.h"
/**
 *   ZprimeFullHad class for booking and filling histograms
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

class ZprimeFullHadHists : public BaseHists {

public:
   /// Named constructor
   ZprimeFullHadHists(const char* name);

   /// Default destructor
   ~ZprimeFullHadHists();

   void Init();

   void setIndices(std::vector<int>);
   void Fill();
   void Fill2(std::vector<int>);

   void Finish();

private:
  std::vector<int> TopJetIndices;
}; // class ZprimeFullHadHists


#endif // ZprimeFullHadHists_H
