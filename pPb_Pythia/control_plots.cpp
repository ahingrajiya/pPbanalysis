#include "JetCorrector.h"
#include "JetUncertainty.h"
void control_plots()
{
    TFile *f1 = new TFile("HiForest_PYTHIA_pPb.root", "READ");

    TTree *tree_jets_3 = (TTree *)f1->Get("hiEvtAnalyzer/HiTree");
    tree_jets_3->SetBranchStatus("*", 0);
    tree_jets_3->SetBranchStatus("weight", 1);

    Float_t weight;

    tree_jets_3->SetBranchAddress("weight", &weight);

    TTree *tree_jets = (TTree *)f1->Get("ak4PFJetAnalyzer/t");
    tree_jets->AddFriend(tree_jets_3);
    tree_jets->SetBranchStatus("*", 0); // disable all branches -> to be quick
    tree_jets->SetBranchStatus("jtpt", 1);
    tree_jets->SetBranchStatus("jteta", 1);
    tree_jets->SetBranchStatus("jtphi", 1);
    tree_jets->SetBranchStatus("rawpt", 1);
    tree_jets->SetBranchStatus("genpt", 1);
    tree_jets->SetBranchStatus("geneta", 1);
    tree_jets->SetBranchStatus("genphi", 1);
    tree_jets->SetBranchStatus("nref", 1);

    Float_t jtpt[1000], jteta[1000], jtphi[1000], rawpt[1000], genpt[1000], genphi[1000], geneta[1000];
    Int_t nref, nentries;
    tree_jets->SetBranchAddress("jtpt", &jtpt);
    tree_jets->SetBranchAddress("jteta", &jteta);
    tree_jets->SetBranchAddress("jtphi", &jtphi);
    tree_jets->SetBranchAddress("rawpt", &rawpt);
    tree_jets->SetBranchAddress("genpt", &genpt);
    tree_jets->SetBranchAddress("geneta", &geneta);
    tree_jets->SetBranchAddress("genphi", &genphi);
    tree_jets->SetBranchAddress("nref", &nref);

    TH1D *hist_jetpt = new TH1D("hist_jetpt", "JetPt", 50, 0.0, 120.0);
    hist_jetpt->Sumw2();
    TH1D *hist_corrpt = new TH1D("hist_corrpt", "CorrectedPt", 50, 0.0, 120.0);
    hist_corrpt->Sumw2();
    TH1D *hist_jeteta = new TH1D("hist_jeteta", "JetEta", 50, -6., 6.);
    hist_jeteta->Sumw2();
    TH1D *hist_jetphi = new TH1D("hist_jetphi", "JetPhi", 35, -3.5, 3.5);
    hist_jeteta->Sumw2();
    TH1D *hist_jetrawpt = new TH1D("hist_jetrawpt", "JetRawPt", 50, 0.0, 120.0);
    hist_jetrawpt->Sumw2();
    TH1D *hist_genjetpt = new TH1D("hist_genjetpt", "GenJetPt", 50, 0.0, 200.0);
    hist_genjetpt->Sumw2();
    TH1D *hist_genjeteta = new TH1D("hist_genjeteta", "GenJetEta", 50, -6., 6.);
    hist_genjeteta->Sumw2();
    TH1D *hist_genjetphi = new TH1D("hist_genjetphi", "GenJetPhi", 35, -3.5, 3.5);
    hist_genjetphi->Sumw2();
    TH2D *hist_jetengscale = new TH2D("hist_jetengscale", "Jet Energy Scale", 100, 0., 120., 100, 0., 5.);
    hist_jetengscale->Sumw2();

    vector<string> Files;
    Files.push_back("JEC_File_AK4PF_PYTHIA8_pthat15_unembedded.txt");

    JetCorrector JEC(Files);

    TFile *f2 = new TFile("output_jet.root", "RECREATE");

    nentries = (int)tree_jets->GetEntries();
    for (int i = 0; i < nentries; i++) // Event loop for HLT_PAAK4CaloJet40_Eta5p1_v1 trigger
    {
        tree_jets->GetEntry(i);
        tree_jets_3->GetEntry(i);

        for (int j = 0; j < nref; j++)
        {
            if (jtpt[j] < 10.0)
                continue;
            JEC.SetJetPT(rawpt[j]);
            JEC.SetJetEta(jteta[j]);
            JEC.SetJetPhi(jtphi[j]);

            Float_t jtpt_corr = JEC.GetCorrectedPT();
            hist_jetpt->Fill(jtpt[j]);
            hist_jeteta->Fill(jteta[j]);
            hist_jetphi->Fill(jtphi[j]);
            hist_jetrawpt->Fill(rawpt[j]);
            hist_corrpt->Fill(jtpt_corr);
        }

        for (int k = 0; k < nref; k++)
        {
            if (genpt[k] < 10.0)
                continue;
            hist_genjetpt->Fill(genpt[k]);
            hist_genjeteta->Fill(geneta[k]);
            hist_genjetphi->Fill(genphi[k]);
        }

        for (int l = 0; l < nref; l++)
        {
            if (jtpt[l] < 10.0)
                continue;
            if (genpt[l] < 10.0)
                continue;
            JEC.SetJetPT(rawpt[l]);
            JEC.SetJetEta(jteta[l]);
            JEC.SetJetPhi(jtphi[l]);
            Float_t jtpt_corr = JEC.GetCorrectedPT();
            hist_jetengscale->Fill(genpt[l], jtpt_corr / genpt[l]);
        }
    }
    hist_jetpt->Write();
    hist_jeteta->Write();
    hist_jetphi->Write();
    hist_jetrawpt->Write();
    hist_corrpt->Write();
    hist_genjeteta->Write();
    hist_genjetphi->Write();
    hist_genjetpt->Write();
    hist_jetengscale->Write();
    gStyle->SetOptStat(0);
    hist_jetengscale->Draw("SURF2");

    f2->Write();
    f2->Close();
}