void control_plots_tracks()
{
    TFile *f1 = new TFile("HiForest_PYTHIA_pPb.root", "READ");
    TTree *tree_jets_3 = (TTree *)f1->Get("hiEvtAnalyzer/HiTree");
    tree_jets_3->SetBranchStatus("*", 0);
    tree_jets_3->SetBranchStatus("weight", 1);

    Float_t weight;

    tree_jets_3->SetBranchAddress("weight", &weight);

    TTree *tree_jets = (TTree *)f1->Get("HiGenParticleAna/hi");
    tree_jets->AddFriend(tree_jets_3);
    tree_jets->SetBranchStatus("*", 0); // disable all branches -> to be quick
    tree_jets->SetBranchStatus("pt", 1);
    tree_jets->SetBranchStatus("eta", 1);
    tree_jets->SetBranchStatus("phi", 1);
    tree_jets->SetBranchStatus("chg", 1);

    std::vector<float> *phi = new std::vector<float>();
    std::vector<float> *eta = new std::vector<float>();
    std::vector<int> *chg = new std::vector<int>();
    std::vector<float> *pt = new std::vector<float>();
    tree_jets->SetBranchAddress("pt", &pt);
    tree_jets->SetBranchAddress("eta", &eta);
    tree_jets->SetBranchAddress("phi", &phi);
    tree_jets->SetBranchAddress("chg", &chg);

    TTree *tree_jets_2 = (TTree *)f1->Get("ppTrack/trackTree");
    tree_jets_2->AddFriend(tree_jets_3);
    tree_jets_2->SetBranchStatus("*", 0); // disable all branches -> to be quick
    tree_jets_2->SetBranchStatus("trkPt", 1);
    tree_jets_2->SetBranchStatus("trkEta", 1);
    tree_jets_2->SetBranchStatus("trkPhi", 1);
    tree_jets_2->SetBranchStatus("trkCharge", 1);
    tree_jets_2->SetBranchStatus("nTrk", 1);
    tree_jets_2->SetBranchStatus("highPurity", 1);
    tree_jets_2->SetBranchStatus("trkPtError", 1);
    tree_jets_2->SetBranchStatus("trkDxy1", 1);
    tree_jets_2->SetBranchStatus("trkDxyError1", 1);
    tree_jets_2->SetBranchStatus("trkDz1", 1);
    tree_jets_2->SetBranchStatus("trkDzError1", 1);

    Float_t trkPt[1000], trkPhi[1000], trkEta[1000], trkPtError[1000], trkdcaxy[1000], trkdcaxyerr[1000], trkdcaz[1000], trkdcazerr[1000];
    Int_t nTrk, trkCharge[1000], nentries1, nentries2;
    Bool_t highPurity[1000];

    tree_jets_2->SetBranchAddress("trkPt", &trkPt);
    tree_jets_2->SetBranchAddress("trkEta", &trkEta);
    tree_jets_2->SetBranchAddress("trkPhi", &trkPhi);
    tree_jets_2->SetBranchAddress("trkCharge", &trkCharge);
    tree_jets_2->SetBranchAddress("nTrk", &nTrk);
    tree_jets_2->SetBranchAddress("highPurity", &highPurity);
    tree_jets_2->SetBranchAddress("trkPtError", &trkPtError);
    tree_jets_2->SetBranchAddress("trkDxy1", &trkdcaxy);
    tree_jets_2->SetBranchAddress("trkDxyError1", &trkdcaxyerr);
    tree_jets_2->SetBranchAddress("trkDz1", &trkdcaz);
    tree_jets_2->SetBranchAddress("trkDzError1", &trkdcazerr);

    TH1D *hist_gentrkpt = new TH1D("hist_gentrkpt", "GenTrackPt", 1000, 0.0, 100.0);
    hist_gentrkpt->Sumw2();
    TH1D *hist_gentrketa = new TH1D("hist_gentrketa", "GenTrackEta", 100, -5., 5.);
    hist_gentrketa->Sumw2();
    TH1D *hist_gentrkphi = new TH1D("hist_gentrkphi", "GenTrackPhi", 100, -3.5, 3.5);
    hist_gentrkphi->Sumw2();
    TH1D *hist_trkpt = new TH1D("hist_trkpt", "TrackPt", 1000, 0.0, 100.0);
    hist_trkpt->Sumw2();
    TH1D *hist_trketa = new TH1D("hist_trketa", "TrackEta", 100, -5., 5.);
    hist_trketa->Sumw2();
    TH1D *hist_trkphi = new TH1D("hist_trkphi", "TrackPhi", 100, -3.5, 3.5);
    hist_trkphi->Sumw2();
    TH2D *hist_trketaphi = new TH2D("hist_trketaphi", "Phi and Eta for tracks", 100, -3.2, 3.2, 100, -2.5, 2.5);
    hist_trketaphi->Sumw2();
    TH2D *hist_gentrketaphi = new TH2D("hist_gentrketaphi", "Phi and Eta for gen tracks", 100, -3.2, 3.2, 100, -2.5, 2.5);
    hist_gentrketaphi->Sumw2();

    TFile *f2 = new TFile("output_trk.root", "RECREATE");

    nentries1 = (int)tree_jets->GetEntries();
    nentries2 = (int)tree_jets_2->GetEntries();

    for (int i = 0; i < nentries1; i++) // Event loop for HLT_PAAK4CaloJet40_Eta5p1_v1 trigger
    {
        tree_jets->GetEntry(i);

        for (int j = 0; j < phi->size(); j++)
        {
            if (fabs(eta->at(j)) > 2.4)
                continue;
            if (pt->at(j) <= 0.4)
                continue;
            if (fabs(chg->at(j)) == 0.0)
                continue;
            hist_gentrkpt->Fill(pt->at(j));
            hist_gentrketa->Fill(eta->at(j));
            hist_gentrkphi->Fill(phi->at(j));
            hist_gentrketaphi->Fill(phi->at(j), eta->at(j));
        }
    }

    for (int i = 0; i < nentries2; i++) // Event loop for HLT_PAAK4CaloJet40_Eta5p1_v1 trigger
    {
        tree_jets_2->GetEntry(i);

        for (int j = 0; j < nTrk; j++)
        {
            if (fabs(trkEta[j]) > 2.4)
                continue;
            if (trkPt[j] <= 0.4)
                continue;
            if (fabs(trkCharge[j]) == 0.0)
                continue;
            if (highPurity[j] == kFALSE)
                continue;
            if (trkPtError[j] / trkPt[j] >= 0.1)
                continue;
            if (trkdcaxy[j] / trkdcaxyerr[j] >= 3.0)
                continue;
            if (trkdcaz[j] / trkdcazerr[j] >= 3.0)
                continue;
            hist_trkpt->Fill(trkPt[j]);
            hist_trketa->Fill(trkEta[j]);
            hist_trkphi->Fill(trkPhi[j]);
            hist_trketaphi->Fill(trkPhi[j], trkEta[j]);
        }
    }
    float dphi = hist_trketaphi->GetYaxis()->GetBinWidth(10);
    float deta = hist_trketaphi->GetXaxis()->GetBinWidth(10);
    hist_trketaphi->Scale(1. / (nentries2 * dphi * deta));

    float gendphi = hist_gentrketaphi->GetYaxis()->GetBinWidth(10);
    float gendeta = hist_gentrketaphi->GetXaxis()->GetBinWidth(10);
    hist_gentrketaphi->Scale(1. / (nentries1 * gendphi * gendeta));

    hist_trkpt->Write();
    hist_trketa->Write();
    hist_trkphi->Write();
    hist_gentrkpt->Write();
    hist_gentrketa->Write();
    hist_gentrkphi->Write();
    hist_trketaphi->Write();
    hist_gentrketaphi->Write();

    f2->Write();
    f2->Close();
}