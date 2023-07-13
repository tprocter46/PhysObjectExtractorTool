import uproot
import pandas as pd
import awkward as ak
import argparse
import os

parser = argparse.ArgumentParser(
                    description='Convert ROOT NTuples to hdf5'
                    )
parser.add_argument("-f", dest="file", action="store", help="Input file(s) - comma seperated", metavar="FILE(S)")
parser.add_argument("-c", "--clip", dest="clip", action="store", help="Only consider first CLIP jets per event", default=6, type=int)
parser.add_argument("-o", dest="outfile", action="store", help="Outfile name (default test.hdf5)", default="test.hdf5")

args = parser.parse_args()

CLIP = args.clip

file_list = [args.file]
for file in file_list:
    if (not os.path.exists(file)):
        print("FIle ", file, " does not exist")
        exit()
    f = uproot.open(file)
    jets = f["myjets/Events;1"]
    truthjets = f["mytruthjets/Events;1"]

    df = pd.DataFrame({"truth_pt": ak.flatten(ak.fill_none(ak.pad_none(truthjets["jet_pt"].arrays()[:,"jet_pt"], CLIP, clip = True), -1)),
                "truth_eta": ak.flatten(ak.fill_none(ak.pad_none(truthjets["jet_eta"].arrays()[:,"jet_eta"], CLIP, clip = True), -1)),
                "truth_phi": ak.flatten(ak.fill_none(ak.pad_none(truthjets["jet_phi"].arrays()[:,"jet_phi"], CLIP, clip = True), -1)),
                "truth_mass": ak.flatten(ak.fill_none(ak.pad_none(truthjets["jet_mass"].arrays()[:,"jet_mass"], CLIP, clip = True), -1)),
                "truth_energy": ak.flatten(ak.fill_none(ak.pad_none(truthjets["jet_e"].arrays()[:,"jet_e"], CLIP, clip = True), -1)),
                
                "btag_score": ak.flatten(ak.fill_none(ak.pad_none(jets["jet_btag"].arrays()[:,"jet_btag"], CLIP, clip = True), -1)),
                "had_flavour": ak.flatten(ak.fill_none(ak.pad_none(jets["jet_had_flavour"].arrays()[:,"jet_had_flavour"], CLIP, clip = True), -1)),
                "reco_eta": ak.flatten(ak.fill_none(ak.pad_none(jets["jet_eta"].arrays()[:,"jet_eta"], CLIP, clip = True), -1)),
                "reco_phi": ak.flatten(ak.fill_none(ak.pad_none(jets["jet_phi"].arrays()[:,"jet_phi"], CLIP, clip = True), -1))
                })

    # Filter out jets that don't actually exist
    df = df[df["truth_pt"] > 20]
    # Filter out misaligned jets (where truth and reco are clearly seeing different things)
    df = df[df["truth_eta"] - df["reco_eta"] < 0.2]
    df = df[df["truth_phi"] - df["reco_phi"] < 0.2]

    df.drop("reco_phi", axis = 1, inplace=True)
    df.drop("reco_eta", axis = 1, inplace=True)

    print(len(df), " jets in ", file)
    df.to_hdf("test.hdf5", "btagData")

