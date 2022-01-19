void control_plots()
{
    TFile *f1 = new TFile("HiForest_PYTHIA_pPb.root", "READ");
    TTree *tree_jets = (TTree *)f1->Get("ak4CaloJetAnalyzer/t");
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

    TH1D *hist_jetpt = new TH1D("hist_jetpt", "JetPt", 50, 0.0, 200.0);
    hist_jetpt->Sumw2();
    TH1D *hist_jeteta = new TH1D("hist_jeteta", "JetEta", 50, -6., 6.);
    hist_jeteta->Sumw2();
    TH1D *hist_jetphi = new TH1D("hist_jetphi", "JetPhi", 35, -3.5, 3.5);
    hist_jeteta->Sumw2();
    TH1D *hist_jetrawpt = new TH1D("hist_jetrawpt", "JetRawPt", 50, 0.0, 200.0);
    hist_jetrawpt->Sumw2();
    TH1D *hist_genjetpt = new TH1D("hist_genjetpt", "GenJetPt", 50, 0.0, 200.0);
    hist_genjetpt->Sumw2();
    TH1D *hist_genjeteta = new TH1D("hist_genjeteta", "GenJetEta", 50, -6., 6.);
    hist_genjeteta->Sumw2();
    TH1D *hist_genjetphi = new TH1D("hist_genjetphi", "GenJetPhi", 35, -3.5, 3.5);
    hist_genjetphi->Sumw2();

    TFile *f2 = new TFile("output_jet.root", "RECREATE");

    nentries = (int)tree_jets->GetEntries();
    for (int i = 0; i < nentries; i++) // Event loop for HLT_PAAK4CaloJet40_Eta5p1_v1 trigger
    {
        tree_jets->GetEntry(i);

        for (int j = 0; j < nref; j++)
        {
            if (jtpt[j] < 5.0)
                continue;
            hist_jetpt->Fill(jtpt[j]);
            hist_jeteta->Fill(jteta[j]);
            hist_jetphi->Fill(jtphi[j]);
            hist_jetrawpt->Fill(rawpt[j]);
        }

        for (int k = 0; k < nref; k++)
        {
            if (genpt[k] < 5.0)
                continue;
            hist_genjetpt->Fill(genpt[k]);
            hist_genjeteta->Fill(geneta[k]);
            hist_genjetphi->Fill(genphi[k]);
        }
    }
    hist_jetpt->Write();
    hist_jeteta->Write();
    hist_jetphi->Write();
    hist_jetrawpt->Write();
    hist_genjetpt->Write();
    hist_genjeteta->Write();
    hist_genjetphi->Write();

    f2->Write();
    f2->Close();
}