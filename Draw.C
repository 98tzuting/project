#include "TFile.h"
#include "TTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <TH1D.h>
#include <TAttLine.h>
#include <TStyle.h>
using namespace std;

void Draw()
{
    auto c1 = new TCanvas("c", "BPRE");
    TFile *file = new TFile("/home/tzuting/SKIM_eeppg_1.root");
    TTree *tree = (TTree *)file->Get("variables"); 
    int entries = (int)tree->GetEntries();
    TH1F *Bs0_deltaE = new TH1F("Bs0_deltaE","",100,-0.4,0.4);
    Double_t deltaE;
    tree->SetBranchAddress("deltaE",&deltaE);
    for(int i =0;i<entries;i++)
    {
        tree->GetEntry(i);
        Bs0_deltaE->Fill(deltaE);
    }
    gStyle->SetOptStat(111111);
    Bs0_deltaE->SetFillColor(kBlue); 
    Bs0_deltaE->Draw(); 
    Bs0_deltaE->SetTitle("deltaE");
    Bs0_deltaE->GetXaxis()->SetTitle("deltaE(GeV)");
    Bs0_deltaE->GetYaxis()->SetTitle("Event");
    Bs0_deltaE->GetYaxis()->SetTitleFont(62); 
    Bs0_deltaE->GetXaxis()->SetTitleFont(62);

    c1->SaveAs("deltaE.png");
}