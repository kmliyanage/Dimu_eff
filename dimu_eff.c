//
//  dimu_eff.c
//  
//
//  Created by Kalpanie Liyanage on 2/20/21.
//


#include <stdio.h>
#include "TFile.h"
#include "TFrame.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "TChain.h"
#include "TTree.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TROOT.h"
#include "TMath.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLine.h"
#include "TList.h"
#include "TH1F.h"
#include "TPaveStats.h"
#include "TGaxis.h"
#include "TText.h"
#include <TString.h>
#include "TMath.h"




void dimu_eff(){
    
    
    TFile *file1 = new TFile("out.root", "RECREATE");
    TList *l = new TList();
    
    gStyle->SetOptStat(0);
    TFile *mc = TFile::Open("DY_effi_2017.root");
    
    mc->cd("Our2018OppSignEfficiency");
    
    
   
    
   
    //Variable bin widths
    const int NMBINS = 55;
    double Mbins[NMBINS+1];
    
    for (int ibin = 0; ibin <=25; ibin++){
        Mbins[ibin] = 0.0 + (1000.0-0.0)*ibin/25.0;
    }
    for (int ibin = 1; ibin <=10; ibin++){
        Mbins[ibin+25] = 1000.0 + (2000.0-1000.0)*ibin/10.0;
    }
    for (int ibin = 1; ibin <=20; ibin++){
        Mbins[ibin+35] = 2000.0 + (6000.0-2000.0)*ibin/20.0;
    }
    
  /*
    for (int ibin = 0; ibin <56; ibin++){
        std::cout<<Mbins[ibin]<<",";
    }
  
    
    TH1F* Acceptance = new TH1F("Acceptance", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Acceptance->Sumw2();
    TH1F* Acceptance_BB = new TH1F("Acceptance_BB", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Acceptance_BB->Sumw2();
    TH1F* Acceptance_BE = new TH1F("Acceptance_BE", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Acceptance_BE->Sumw2();
    
    TH1F* Trigger = new TH1F("Trigger", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Trigger->Sumw2();
    TH1F* Trigger_BB = new TH1F("Trigger_BB", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Trigger_BB->Sumw2();
    TH1F* Trigger_BE = new TH1F("Trigger_BE", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Trigger_BE->Sumw2();
    
    TH1F* Reco = new TH1F("Reco", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Reco->Sumw2();
    TH1F* Reco_BB = new TH1F("Reco_BB", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Reco_BB->Sumw2();
    TH1F* Reco_BE = new TH1F("Reco_BE", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    Reco_BE->Sumw2();
    
    TH1F* AccEffi = new TH1F("AccEffi", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    AccEffi->Sumw2();
    TH1F* AccEffi_BB = new TH1F("AccEffi_BB", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    AccEffi_BB->Sumw2();
    TH1F* AccEffi_BE = new TH1F("AccEffi_BE", " ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
    AccEffi_BE->Sumw2();
    
    */
    
    const int effi = 4;
    const int eta = 3;
    TH1F* histos[effi][eta]; //To access histograms from TFile
    TH1F* myhist[effi][eta]; //To create my histograms
    
    
    TString effis[effi] =  {
        "Acceptance",
        "TrigWrtAcc",
        "RecoWrtAccTrig",
        "TotalReco",
    };
    
    TString etas[eta] =  {
        "",
        "_bb",
        "_e",
    };
    
    for(int n=0 ; n<eta ; n++){
        
        TCanvas *c = new TCanvas("DATA_MC", "DATA_MC",  1000, 1000);
        c->cd();
        
        TPad* pad1 = new TPad("pad1", "pad1",  0, 0, 1, 1);
        pad1->Draw();
        pad1->cd();
        pad1->SetTicks();
        pad1->SetGrid();
        
        
        
        
        
        for(int j=0 ; j<effi ; j++){
            
            TString r = effis[j] + etas[n];
            std::cout<<r<<std::endl;
            
            TString histname = "my" + effis[j] + etas[n];
            std::cout<<histname<<std::endl;
            myhist[j][n] = new TH1F(histname," ;m(#mu^{+}#mu^{-})[GeV];Efficiency", NMBINS, Mbins);
            myhist[j][n]->Sumw2();
            
            TH1F *h1 = (TH1F*)gDirectory->Get("Num"+r);
            h1->Sumw2();
            
            TH1F *h2 = (TH1F*)gDirectory->Get("Den"+r);
            h2->Sumw2();
            
            TAxis *axis = h1->GetXaxis();
            for(int i = 0; i <  NMBINS+1; i++){
                int bmin = axis->FindBin(Mbins[i]);
                int bmax = axis->FindBin(Mbins[i+1]);
                double num = h1->Integral(bmin,bmax);
                double den = h2->Integral(bmin,bmax);
                
                //For error calculation in integrated bins
                double num_er,den_er;
                Double_t integral_n = h1->IntegralAndError(bmin, bmax, num_er, "");
                Double_t integral_d = h2->IntegralAndError(bmin, bmax, den_er, "");
                
                
                num -= h1->GetBinContent(bmin)*(Mbins[i]-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
                num -= h1->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-Mbins[i+1])/axis->GetBinWidth(bmax);
                den -= h2->GetBinContent(bmin)*(Mbins[i]-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
                den -= h2->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-Mbins[i+1])/axis->GetBinWidth(bmax);
                double ratio = num/den;
                if(den==0.0) ratio=0.0;
                std::cout<<bmin<<"  "<<bmax<<"  "<<num<<"   "<<integral_n<<"+-"<<num_er<<"   "<<den<<"   "<<integral_d<<"+-"<<den_er<<"   "<<ratio<<std::endl;
                
                myhist[j][n]->SetBinContent(i+1,ratio);
                //myhist[j][n]->SetBinError(i+1, 0.00001);
                myhist[j][n]->SetBinError(i+1, ratio*sqrt((num_er*num_er)/(num*num) + (den_er*den_er)/(den*den)));
                if(num==0.0 || den==0.0) myhist[j][n]->SetBinError(i+1, 0.0);
               
            }
            
            //setting markers
            if(j==0){ //Acceptance
                myhist[j][n]->SetMarkerStyle(22);
                myhist[j][n]->SetMarkerColor(kBlue);
                myhist[j][n]->SetLineColor(kBlue);
                myhist[j][n]->SetMarkerSize(1.05);
            }
            else if(j==1){ //Trigger
                myhist[j][n]->SetMarkerStyle(23);
                myhist[j][n]->SetMarkerColor(kGreen+1);
                myhist[j][n]->SetLineColor(kGreen+1);
                myhist[j][n]->SetMarkerSize(1.05);
            }
            else if(j==2){ //Reco
                myhist[j][n]->SetMarkerStyle(21);
                myhist[j][n]->SetMarkerColor(kRed);
                myhist[j][n]->SetLineColor(kRed);
                myhist[j][n]->SetMarkerSize(1.05);
            }
            else{ //Accpetance*Effi
                myhist[j][n]->SetMarkerStyle(20);
                myhist[j][n]->SetMarkerColor(kBlack);
                myhist[j][n]->SetLineColor(kBlack);
                myhist[j][n]->SetMarkerSize(1.05);
            }
            
            
            myhist[j][n]->Draw("SAMEPE hist");
            myhist[j][n]->GetYaxis()->SetRangeUser(0.0, 1.05);
            c->Update();
            pad1->Update();
            
        }
        
        TLegend *l1 = new TLegend(0.3,0.15,0.6,0.3);
        l1->SetBorderSize(0);
        l1->SetLineWidth(0);
        l1->SetLineStyle(0);
        l1->SetLineColor(0);
        //l1->SetTextFont(42);
        //l1->SetTextFont(42);
        l1->SetTextSize(0.025);
        //l1->SetMargin(0.12);
        l1->AddEntry(myhist[0][n], "Acceptance(within #eta category)", "pe2");
        l1->AddEntry(myhist[1][n], "Trigger Fired / Acceptance", "pe2");
        l1->AddEntry(myhist[2][n], "Reco+ID Efficiency / (Acceptance x Trigger Fired)", "pe2");
        l1->AddEntry(myhist[3][n], "Total Acceptance x Efficiency", "pe2");
        l1->Draw();
        c->Update();
        pad1->Update();
        
        c->SaveAs(etas[n]+"2017.pdf","pdf");
        c->SaveAs(etas[n]+"2017.root","root");
    }
    
    mc->Close();
   
    /*
    file1->cd();
    for(int n=0 ; n<eta ; n++){
        for(int j=0 ; j<effi ; j++){
            l->Add(myhist[j][n]);
            l->Write("histlist", TObject::kSingleKey);
        }
    }
    */
    file1->Write();
    file1->Close();
    
    
   
   
    
}

