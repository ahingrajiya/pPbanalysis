void weights()
{
    TFile *f1 = new TFile("HiForest_PYTHIA_pPB.root", "READ");
    TTree *t1 = (TTree *)f1->Get("hiEvtAnalyzer/HiTree");
    TH1D *weights = new TH1D("weights", "weights", 10000, 0., 2.);
    Float_t weight;
    t1->SetBranchAddress("weight", &weight);
    Int_t nentries = (int)t1->GetEntries();
    for (int i = 0; i < nentries; i++)
    {
        t1->GetEntry(i);
        weights->Fill(weight);
    }
    weights->Draw();
}