#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void Draw(TString files)
{
    TChain *chain = new TChain("variables");
    chain->Add(files);
    RooRealVar Mbc("Mbc", "M_{bc}", 5.3, 5.434, "GeV/c^{2}");
    RooRealVar deltaE("deltaE", "#Delta E", -0.4, 0.4, "GeV");
    RooArgSet *varset = new RooArgSet(deltaE, Mbc);
    RooDataSet data("data", "data", chain, *varset);
    data.Print();
    
    Mbc.setRange("full_range", 5.25, 5.45);
    deltaE.setRange("full_range", -0.4, 0.4);

    RooRealVar mean("mean", "de signal mean", 5.315, 5.25, 5.45);
    RooRealVar sigma_delta1("sigma_delta1", "sigma_delta1", 0.00348,0.00347,0.00349);
    RooRealVar alpha1("alpha1", "alpha1", 0.616,0.615,0.617);
    RooRealVar n1("n1", "n1", 1.027,1.026,1.028);
    RooCBShape sig1("sig1", "Signal component 1", Mbc, mean, sigma_delta1, alpha1, n1);

    RooFitResult *de_result = new RooFitResult("de_result", "de_result");
    de_result = sig1.fitTo(data, Timer(true), Save(true));
    TCanvas *canvas = new TCanvas("canvas", "c1", 1600, 900);
    canvas->Clear();
    RooPlot *plot_Mbc = Mbc.frame(Bins(50), Name("plot_Mbc"), Range("full_range"), Title("plot_Mbc"));
    data.plotOn(plot_Mbc, Name("data_hist"), CutRange("full_range"), MarkerColor(kBlack));
    sig1.plotOn(plot_Mbc, Name("Mbc_fit_result"), ProjectionRange("full_range"), Components("sig1"), LineColor(kBlue), LineStyle(kSolid));
    sig1.paramOn(plot_Mbc, Layout(0.13, 0.6, 0.7), Format("NE",AutoPrecision(1)));
    sig1.Print("t");
    plot_Mbc->Draw("");

    TString imagename = "Fitting_eeggg_Mbc_signal" + ".png";
    canvas->SaveAs(imagename);
}