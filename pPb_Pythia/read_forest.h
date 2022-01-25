#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TVector3.h"
#include <TRandom1.h>
#include <vector>
#include <TLorentzVector.h>
#include "THnSparse.h"
#include "TRandom3.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <map>
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TSystem.h"
#include <stdlib.h>

Float_t jtpt[1000], jteta[1000], jtphi[1000], rawpt[1000], genpt[1000], genphi[1000], geneta[1000];
Int_t nref, nentries;

void read_jet_tree(TTree *tree1, bool isMC)
{
    tree1->SetBranchStatus("*", 0);

    tree1->SetBranchStatus("jtpt", 1);
    tree1->SetBranchStatus("jteta", 1);
    tree1->SetBranchStatus("jtphi", 1);
    tree1->SetBranchStatus("rawpt", 1);
    tree1->SetBranchStatus("genpt", 1);
    tree1->SetBranchStatus("geneta", 1);
    tree1->SetBranchStatus("genphi", 1);
    tree1->SetBranchStatus("nref", 1);

    tree1->SetBranchAddress("jtpt", &jtpt);
    tree1->SetBranchAddress("jteta", &jteta);
    tree1->SetBranchAddress("jtphi", &jtphi);
    tree1->SetBranchAddress("rawpt", &rawpt);
    tree1->SetBranchAddress("genpt", &genpt);
    tree1->SetBranchAddress("geneta", &geneta);
    tree1->SetBranchAddress("genphi", &genphi);
    tree1->SetBranchAddress("nref", &nref);
}

Float_t trkPt[1000], trkPhi[1000], trkEta[1000], trkPtError[1000], trkdcaxy[1000], trkdcaxyerr[1000], trkdcaz[1000], trkdcazerr[1000];
Int_t nTrk, trkCharge[1000], nentries1, nentries2;
Bool_t highPurity[1000];

void read_tracks(TTree *tree2, bool isMC)
{
    tree2->SetBranchStatus("*", 0);

    tree2->SetBranchStatus("trkPt", 1);
    tree2->SetBranchStatus("trkEta", 1);
    tree2->SetBranchStatus("trkPhi", 1);
    tree2->SetBranchStatus("trkCharge", 1);
    tree2->SetBranchStatus("nTrk", 1);
    tree2->SetBranchStatus("highPurity", 1);
    tree2->SetBranchStatus("trkPtError", 1);
    tree2->SetBranchStatus("trkDxy1", 1);
    tree2->SetBranchStatus("trkDxyError1", 1);
    tree2->SetBranchStatus("trkDz1", 1);
    tree2->SetBranchStatus("trkDzError1", 1);

    tree2->SetBranchAddress("trkPt", &trkPt);
    tree2->SetBranchAddress("trkEta", &trkEta);
    tree2->SetBranchAddress("trkPhi", &trkPhi);
    tree2->SetBranchAddress("trkCharge", &trkCharge);
    tree2->SetBranchAddress("nTrk", &nTrk);
    tree2->SetBranchAddress("highPurity", &highPurity);
    tree2->SetBranchAddress("trkPtError", &trkPtError);
    tree2->SetBranchAddress("trkDxy1", &trkdcaxy);
    tree2->SetBranchAddress("trkDxyError1", &trkdcaxyerr);
    tree2->SetBranchAddress("trkDz1", &trkdcaz);
    tree2->SetBranchAddress("trkDzError1", &trkdcazerr);
}

std::vector<float> *phi = new std::vector<float>();
std::vector<float> *eta = new std::vector<float>();
std::vector<int> *chg = new std::vector<int>();
std::vector<float> *pt = new std::vector<float>();

void read_gen_tracks(TTree *tree3, bool isMC)
{
    tree3->SetBranchStatus("*", 0); // disable all branches -> to be quick
    tree3->SetBranchStatus("pt", 1);
    tree3->SetBranchStatus("eta", 1);
    tree3->SetBranchStatus("phi", 1);
    tree3->SetBranchStatus("chg", 1);

    tree3->SetBranchAddress("pt", &pt);
    tree3->SetBranchAddress("eta", &eta);
    tree3->SetBranchAddress("phi", &phi);
    tree3->SetBranchAddress("chg", &chg);
}