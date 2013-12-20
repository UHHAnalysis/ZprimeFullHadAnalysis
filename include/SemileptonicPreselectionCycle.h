// Dear emacs, this is -*- c++ -*-
#ifndef SemileptonicPreselectionCycle_H
#define SemileptonicPreselectionCycle_H

// SFrame include(s):
#include "SFrameAnalysis/include/AnalysisCycle.h"
#include "SFrameAnalysis/include/Cleaner.h"
#include "ZprimeFullHadTools.h"

/**
 *  @short Selection cycle to perform 
 *         pre-selection for Z'->ttbar analysis
 *  @author Thomas Peiffer
 */


class SemileptonicPreselectionCycle : public AnalysisCycle {

public:
  /// Default constructor
  SemileptonicPreselectionCycle();
  /// Default destructor
  ~SemileptonicPreselectionCycle();

  /// Function called at the beginning of the cycle
  void BeginCycle() throw( SError );
  /// Function called at the end of the cycle
  void EndCycle() throw( SError );

  /// Function called at the beginning of a new input data
  void BeginInputData( const SInputData& ) throw( SError );
  /// Function called after finishing to process an input data
  void EndInputData  ( const SInputData& ) throw( SError );

  /// Function called after opening each new input file
  void BeginInputFile( const SInputData& ) throw( SError );

  /// Function called for every event
  void ExecuteEvent( const SInputData&, Double_t ) throw( SError );

private:
  //
  // Put all your private variables here
  //
  std::string m_CSVOperatingPoint;
  // Macro adding the functions for dictionary generation
  ClassDef( SemileptonicPreselectionCycle, 0 );

}; // class SemileptonicPreselectionCycle

#endif // SemileptonicPreselectionCycle_H

