ZprimeFullHadAnalysis
=====================

This package contains the SFrame code and the python scripts used in the Z'->ttbar full hadronic analysis with the HEPTopTagger.
Additionally this package contains some files used in HEPTopTagger validation and commissioning.

limits.py --> Main Z' analysis script, plots Data/Bkg and prepares theta files
bkg.py --> Mistag derivation and accessory plots for the background estimate
closure.py --> Background estimate closure test
trigger_studies.py --> Trigger efficiency and scale factors

roc.py --> ROC curves for the HEPTopTagger
subjet3.py --> Data/MC & SF for the HEPTopTagger
