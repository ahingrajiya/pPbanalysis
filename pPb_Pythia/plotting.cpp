void plotting()
{
    TFile *f1 = new TFile("output_jet.root", "READ");
    TFile *f2 = new TFile("output_trk.root", "READ");
    TFile *f3 = new TFile("output.root", "READ");
    // TH1D *h1 = (TH1D *)f1->Get("hist_jetpt");
    // TH1D *h2 = (TH1D *)f1->Get("hist_jeteta");
    // TH1D *h3 = (TH1D *)f1->Get("hist_jetphi");
    // TH1D *h4 = (TH1D *)f1->Get("hist_jetrawpt");
    // TH1D *h5 = (TH1D *)f1->Get("hist_genjetpt");
    // TH1D *h6 = (TH1D *)f1->Get("hist_genjeteta");
    // TH1D *h7 = (TH1D *)f1->Get("hist_genjetphi");

    TH1D *h1_d = (TH1D *)f3->Get("hist_jetpt");
    TH1D *h2_d = (TH1D *)f3->Get("hist_jeteta");
    TH1D *h3_d = (TH1D *)f3->Get("hist_jetphi");
    TH1D *h4_d = (TH1D *)f3->Get("hist_jetrawpt");
    TH1D *h5_d = (TH1D *)f3->Get("hist_genjetpt");
    TH1D *h6_d = (TH1D *)f3->Get("hist_genjeteta");
    TH1D *h7_d = (TH1D *)f3->Get("hist_genjetphi");

    h1_d->Draw();
    // h1_d->SetMarkerStyle(8);
    // h1_d->SetMarkerColor(2);
    // h1_d->Draw("SAME");
}