#include "read_forest.h"
#include "JetCorrector.h"
#include "JetUncertainty.h"

void jetenergy()
{
    cout << "========File is opening=========" << endl;
    TFile *f1 = new TFile("HiForest_PYTHIA_pPb.root", "READ");
    TTree *tree1 = (TTree *)f1->Get("ak4PFJetAnalyzer/t");
    TTree *tree2 = (TTree *)f1->Get("ppTrack/trackTree");
    TTree *tree3 = (TTree *)f1->Get("HiGenParticleAna/hi");
    cout << "=========File opened. Trees reading completed===========" << endl;

    Int_t nentries = (int)tree1->GetEntries();

    bool isMC = kFALSE;

    read_jet_tree(tree1, isMC);
    // cout << nentries << endl;
    vector<string> Files;
    Files.push_back("JEC_File_AK4PF_PYTHIA8_pthat15_unembedded.txt");

    JetCorrector JEC(Files);

    TH2D *hist_jetenergy = new TH2D("hist_jetenergy", "Jet Energy Scale", 100, 0., 120., 100, 0., 3.);
    gStyle->SetOptStat(0);

    for (int i = 0; i < nentries; i++)
    {
        tree1->GetEntry(i);
        // cout << nref << endl;
        for (int j = 0; j < nref; j++)
        {
            if (jtpt[j] < 10.0)
                continue;
            if (genpt[j] < 10.0)
                continue;
            JEC.SetJetPT(rawpt[j]);
            JEC.SetJetEta(jteta[j]);
            JEC.SetJetPhi(jtphi[j]);
            Float_t jtpt_corr = JEC.GetCorrectedPT();
            hist_jetenergy->Fill(genpt[j], jtpt_corr / genpt[j]);
        }
    }
    hist_jetenergy->FitSlicesY(0, 1, 100, 5);
    TH1D *hist_jetenergy_0 = (TH1D *)gDirectory->Get("hist_jetenergy_0");
    // hist_jetenergy_0->Draw();
    TH1D *hist_jetenergy_1 = (TH1D *)gDirectory->Get("hist_jetenergy_1");
    // hist_jetenergy_1->Draw();
    TH1D *hist_jetenergy_2 = (TH1D *)gDirectory->Get("hist_jetenergy_2");
    // hist_jetenergy_2->Draw();

    TCanvas *c1 = new TCanvas("c1", "Jet Energy Histograms", 1000, 1000);
    c1->Divide(2, 2);
    c1->cd(1);
    hist_jetenergy->SetTitle("Jet Energy Scale for Pythia8 at pthat>15GeV");
    hist_jetenergy->SetXTitle("#frac{RawPt}{GenPt}:");
    hist_jetenergy->SetYTitle("GenPt");
    hist_jetenergy->Draw("SURF2");
    c1->cd(2);
    hist_jetenergy_0->SetMarkerStyle(40);
    hist_jetenergy_0->SetMarkerColor(2);
    hist_jetenergy_0->SetXTitle("GenPt");
    hist_jetenergy_0->Draw();
    c1->cd(3);
    hist_jetenergy_1->SetTitle("Means for bins between 0 and 100 bins");
    hist_jetenergy_1->SetMarkerStyle(40);
    hist_jetenergy_1->SetMarkerColor(2);
    hist_jetenergy_1->SetXTitle("GenPt");
    hist_jetenergy_1->Draw();
    c1->cd(4);
    hist_jetenergy_2->SetTitle("Variance for bins between 0 and 100 bins");
    hist_jetenergy_2->SetMarkerStyle(40);
    hist_jetenergy_2->SetMarkerColor(2);
    hist_jetenergy_2->SetXTitle("GenPt");
    hist_jetenergy_2->Draw();
}
