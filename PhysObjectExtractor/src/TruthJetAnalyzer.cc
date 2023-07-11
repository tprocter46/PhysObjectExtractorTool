// -*- C++ -*-
//
// Package:    TruthJetAnalyzer
// Class:      TruthJetAnalyzer
//

// system include files
#include <memory>
#include <TMath.h>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Ref.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "math.h"

//classes to extract PFJet information
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourInfo.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourInfoMatching.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"


//classes to save data
#include "TTree.h"
#include "TFile.h"
#include<vector>

#include "TRandom3.h"


//
// class declaration
//

class TruthJetAnalyzer : public edm::EDAnalyzer {
public:
  explicit TruthJetAnalyzer(const edm::ParameterSet&);
  ~TruthJetAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;  
       
  //declare the input tag for PFJetCollection
  edm::InputTag jetInput;
  
  // ----------member data ---------------------------    

  int numjet; //number of jets in the event
  TTree *mtree;
  std::vector<float> jet_e;
  std::vector<float> jet_pt;
  std::vector<float> jet_px;
  std::vector<float> jet_py;
  std::vector<float> jet_pz;
  std::vector<float> jet_eta;
  std::vector<float> jet_phi;
  std::vector<float> jet_ch;
  std::vector<float> jet_mass;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

TruthJetAnalyzer::TruthJetAnalyzer(const edm::ParameterSet& iConfig)
{
//now do what ever initialization is needed
  jetInput = iConfig.getParameter<edm::InputTag>("InputCollection");
  edm::Service<TFileService> fs;
  mtree = fs->make<TTree>("Events", "Events");
                           
  mtree->Branch("numberjet",&numjet);
  mtree->GetBranch("numberjet")->SetTitle("Number of Jets");
  mtree->Branch("jet_e",&jet_e);
  mtree->GetBranch("jet_e")->SetTitle("Uncorrected Jet Energy");
  mtree->Branch("jet_pt",&jet_pt);
  mtree->GetBranch("jet_pt")->SetTitle("Uncorrected Transverse Jet Momentum");
  mtree->Branch("jet_px",&jet_px);
  mtree->GetBranch("jet_px")->SetTitle("X-Component of Jet Momentum");
  mtree->Branch("jet_py",&jet_py); 
  mtree->GetBranch("jet_py")->SetTitle("Y-Component of Jet Momentum");
  mtree->Branch("jet_pz",&jet_pz);
  mtree->GetBranch("jet_pz")->SetTitle("Z-Component of Jet Momentum");
  mtree->Branch("jet_eta",&jet_eta);
  mtree->GetBranch("jet_eta")->SetTitle("Jet Eta");
  mtree->Branch("jet_phi",&jet_phi);
  mtree->GetBranch("jet_phi")->SetTitle("Jet Phi");
  mtree->Branch("jet_ch",&jet_ch);
  mtree->GetBranch("jet_ch")->SetTitle("Jet Charge");
  mtree->Branch("jet_mass",&jet_mass);
  mtree->GetBranch("jet_mass")->SetTitle("Jet Mass");
  
}

TruthJetAnalyzer::~TruthJetAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//
// None left any more!

void
TruthJetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;

  Handle<reco::PFJetCollection> myjets;
  iEvent.getByLabel(jetInput, myjets);

  Handle<reco::JetFlavourInfoMatchingCollection> injets;
  iEvent.getByLabel(InputTag("jetFlavourInfosAK5PFJets"), injets);

  numjet = 0;
  jet_e.clear();
  jet_pt.clear();
  jet_px.clear();
  jet_py.clear();
  jet_pz.clear();
  jet_eta.clear();
  jet_phi.clear();
  jet_ch.clear();
  jet_mass.clear();
  
  if(myjets.isValid()){
    int min_pt = 20;

    for (reco::PFJetCollection::const_iterator itjet=myjets->begin(); itjet!=myjets->end(); ++itjet){
      reco::Candidate::LorentzVector uncorrJet = itjet->p4();
      
      if (uncorrJet.pt() >= min_pt){
       
        jet_e.push_back(itjet->energy());
        jet_pt.push_back(itjet->pt());
        jet_px.push_back(itjet->px());
        jet_py.push_back(itjet->py());
        jet_pz.push_back(itjet->pz());
        jet_eta.push_back(itjet->eta());
        jet_phi.push_back(itjet->phi());
        jet_ch.push_back(itjet->charge());
        jet_mass.push_back(itjet->mass());
	      ++numjet;
      }
    }
  }
  
  mtree->Fill();
  return;
  
}

// ------------ method called once each job just before starting event loop  ------------
void
TruthJetAnalyzer::beginJob()
{}

// ------------ method called once each job just after ending the event loop  ------------
void
TruthJetAnalyzer::endJob()
{}

// ------------ method called when starting to processes a run  ------------
void
TruthJetAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{}

// ------------ method called when ending the processing of a run  ------------
void
TruthJetAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{}
// ------------ method called when starting to processes a luminosity block  ------------
void
TruthJetAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TruthJetAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TruthJetAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
 //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TruthJetAnalyzer);
