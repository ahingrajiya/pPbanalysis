void plotting()
{
    TFile *f1 = new TFile("output_jet.root", "READ");
    TFile *f2 = new TFile("output_trk.root", "READ");
    TH1D *h1 = (TH1D *)f1->Get("hist_jetpt");
    TH1D *h2 = (TH1D *)f1->Get("hist_jeteta");
    TH1D *h3 = (TH1D *)f1->Get("hist_jetphi");
    TH1D *h4 = (TH1D *)f1->Get("hist_jetrawpt");
    TH1D *h5 = (TH1D *)f1->Get("hist_corrpt");
    TH2D *h6 = (TH2D *)f2->Get("hist_trketaphi");
    TH2D *h7 = (TH2D *)f2->Get("hist_gentrketaphi");
    TH2D *h8 = (TH2D *)f1->Get("hist_jetengscale");
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1");
    c1->SetLogy();
    h1->SetMarkerStyle(27);
    h1->SetMarkerSize(2.0);
    h1->SetMarkerColor(2);
    h4->SetMarkerStyle(43);
    h4->SetMarkerSize(2.0);
    h4->SetMarkerColor(3);
    h5->SetMarkerStyle(31);
    h5->SetMarkerSize(2.0);
    h1->Draw();
    h4->Draw("SAME");
    h5->Draw("SAME");

    auto *legend = new TLegend(0.7, 0.7, 1.0, 1.0);
    legend->AddEntry(h1, "Jet Pt from Forest", "p");
    legend->AddEntry(h4, "RawPt from Forest", "p");
    legend->AddEntry(h5, "Corrected RawPt", "p");

    legend->Draw();

    TCanvas *c2 = new TCanvas("c2", "c2");
    h6->SetTitle("Track Phi-Eta for Pythia8 at pthat>15GeV");
    h6->SetXTitle("#phi");
    h6->SetYTitle("#eta");
    h6->Draw("COLZ");

    TCanvas *c3 = new TCanvas("c3", "c3");
    h7->SetXTitle("#phi");
    h7->SetYTitle("#eta");
    h7->Draw("COLZ");

    TCanvas *c4 = new TCanvas("c4", "c4");
    h8->SetTitle("Jet Energy Scale for Pythia8 at pthat>15GeV");
    h8->SetXTitle("GenPt");
    h8->SetYTitle("RecoPt/GenPt");
    h8->Draw("COLZ");

    TCanvas *c5 = new TCanvas("c5", "c5");
    TH1D *h8x = h8->ProjectionX();
    h8x->SetTitle("Jet Energy Scale X Projection");
    h8x->SetXTitle("GenPt");
    c5->SetLogy();
    h8x->Draw();

    TCanvas *c6 = new TCanvas("c6", "c6");
    TH1D *h8y = h8->ProjectionY();
    h8y->SetTitle("Jet Energy Scale Y Projection");
    h8y->SetXTitle("RecoPt/GenPt");
    c6->SetLogy();
    h8y->Draw();
    // h1_d->SetMarkerStyle(8);c4
    // h1_d->SetMarkerColor(2);
    // h1_d->Draw("SAME");
}