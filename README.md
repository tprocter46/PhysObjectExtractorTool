# Physics Objects Extractor Tool (POET) - 2012_jetdumper

## bjetdumper? What is this branch?

This fork of POET uses the 2012 branch as the basis for extracting various variables that are/may be useful for trainning a surrogate Neural Net to replicate the results of the CMS 8(7?!)TeV CSV b-tagger.

Why 2012? Because the MiniAOD used for Run-2 onwards does not have as much truth information.

At the moment, the code dumps jet 4-momenta for truth and  PF jets, along with the b-score for and the "true" hadron information. (Other variables are also dumped, this may be changed). Any other useful jet variables for tagging would require a bit more work.

This is accomplished by very minor tweaks to JetAnalyzer.cc; and the creation of a TruthJetAnalyzer.cc, based on JetAnalyzer.cc, but acting on GenJets not PFJets and with some of the other complexity stripped out.

The procedure for running the code is unchanged to normal POET (see POET docs). In the python folder, I provide a script (convert2h5.py) that turns the root ntuples into hdf5 pandas dataframes. I do not reccoment running this in the CMSSW docker container like the rest of the code; I just store it here for convenience (requires uproot and pandas).

As a disclaimer: I am not a member of CMS; it is possible I have misunderstood things about CMSSW; refer to CMS experts if you want to know how things really work.
I am using the CMS Open Data. Huge credit to CMS for not just providing this data for Open science but supporting it with all these tools.
Please contact me if you have any questions/ideas about what I've done and would like to discuss further!

I leave the rest of the readme intact below for your perusal.

## Description

This POET repository contains packages that verse instructions and examples on how to extract physics (objects) information from Run 1 (AOD format) CMS open/legacy data and methods or tools needed for processing them. These objects can be: electrons, muons, photons, jets, tracks, etc.

Please check out the `README` in each package for further instructions and the [physics object pages](https://cms-opendata-guide.web.cern.ch/analysis/selection/objects/objects/) in the CMS open data guide.

## References

Muons

* [Muon IDs and Isolation](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId)
* [Muon Analysis](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMuonAnalysis)

Taus

* [Tau IDs](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookPFTauTagging#Legacy_Tau_ID_Run_I)
* [Tau Discriminators](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NutShellRecipeFor5312AndNewer)

Jets

* [JEC+JER main documentation](https://arxiv.org/abs/1607.03663.pdf): Includes jet pt resolution functions and scale factors (Fig 41) applied for JER
* [Application of Hybrid Smearing Method](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/src/JetAnalyzer.cc#L243-L270)
* [JER Scale Factor Instructions](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideJetResolution)
* [JER Scale Factor Lookup Table](https://github.com/adrager/cmssw/blob/JetResolution53/CondFormats/JetMETObjects/data/JetResolutionInputAK5PF.txt)
* [Read in JEC+JER Code](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/src/JetAnalyzer.cc#L119-L143)
* [Apply JEC+JER Code](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/src/JetAnalyzer.cc#L226-L270)
* [Produce JEC Text Files Code](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/JEC/jec_cfg.py)
* [Read JEC+JER in Config](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/python/poet_cfg.py#L125-L141)

* [BTagging CSV.csv File/Table](https://twiki.cern.ch/twiki/bin/view/CMSPublic/BtagRecommendation2011OpenData#Methods_to_Apply)
* [BTagging Help Understand CSV.csv](https://twiki.cern.ch/twiki/bin/view/CMSPublic/BTagCalibration) 
* [BTagging Weight Calculating Methods](https://twiki.cern.ch/twiki/bin/view/CMSPublic/BtagRecommendation2011OpenData#Methods_to_Apply_b_Tagging_Effic)
* [Application of Scale Factor Lookup Tables](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/src/JetAnalyzer.cc#L335-L357)

Photons
* [Photon ID Paper](https://cms-physics.web.cern.ch/cms-physics/public/EGM-10-006-pas.pdf)
* [Photon ID Code](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/src/PhotonAnalyzer.cc#L166-L242)

Electrons
* [Electron ID Twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/EgammaPublicData)
* [Electron ID Code](https://github.com/cms-legacydata-analyses/PhysObjectExtractorTool/blob/master/PhysObjectExtractor/src/ElectronAnalyzer.cc#L168-L212)

