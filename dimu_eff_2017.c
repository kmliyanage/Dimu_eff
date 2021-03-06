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




void dimu_eff_2017(){
    
    gStyle->SetGridColor(kGray+2); //grid color
    gStyle->SetGridWidth(1);

    
    TFile *file1 = new TFile("out.root", "RECREATE");
    TList *l = new TList();
    
    
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
        gStyle->SetOptStat(0); //turn off stst box
        gStyle->SetOptFit(111); // fit parameters: chi2,parameter value,parameter error
        
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
                
                ////////////////////Binomial error/////////////////////////
                myhist[j][n]->SetBinError(i+1, sqrt(ratio*(1.0-ratio)/den));
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
            
            
            myhist[j][n]->Draw("SAMESPE hist");
            myhist[j][n]->GetYaxis()->SetRangeUser(-1.05, 1.05);
            c->Update();
            pad1->Update();
            
            
            if(j==3){
                //for fitting
                //----------------------old functions------------------------//
                //TF1 *inclusive_low = new TF1("inclusive_low","pol4",120,300);
                //TF1 *inclusive_high = new TF1("inclusive_high","pol9",250,6000);
                //TF1 *bb_low = new TF1("bb_low","pol2",120,220);
                //TF1 *bb_high = new TF1("bb_high","pol3",220,6000);
                //TF1 *be_low = new TF1("be_low","pol4",120,460);
                //TF1 *be_high = new TF1("be_high","pol6",460,6000);
            
                //----------------------new functions------------------------//
                TF1 *inclusive_low = new TF1("inclusive_low","[0] - [1]*1.0/TMath::Exp((x-[2])/[3]) + [4]*TMath::Power(x,[5])",120,800);
                inclusive_low->SetParameters(1.14,0.2258,110,34.11,-6.146,-0.4085);
                TF1 *inclusive_high = new TF1("inclusive_high","[0] + [1]/(TMath::Power((x+[2]),3)) - x*x/[3]",800,6000);
                inclusive_high->SetParameters(0.8643,-5.068e+08,791,1.836e+09);
                TF1 *bb_low = new TF1("bb_low","[0] - [1]*1.0/TMath::Exp((x-[2])/[3]) + [4]*TMath::Power(x,[5])",120,600);
                bb_low->SetParameters(2.13,0.1313,110.9,20.31,-2.387,-0.03616);
                TF1 *bb_high = new TF1("bb_high","[0] + [1]/(x+[2]) - [3]*x",600,6000);
                bb_high->SetParameters(4.931,-5.55e+04,1.157e+04,0.0002108);
                TF1 *be_low = new TF1("be_low","[0] - [1]*1.0/TMath::Exp((x-[2])/[3]) + [4]*TMath::Power(x,[5])",120,450);
                be_low->SetParameters(13.39,6.696,-4.855e+06,-7.431e+06,-108.8,-1.138);
                TF1 *be_high = new TF1("be_high","[0] + [1]*TMath::Power(x,[2])*1.0/TMath::Exp((x-[3])/[4])",450,6000);
                be_high->SetParameters(0.3148,0.04447,1.42,-5108,713.5);
                
           
                
                if(n==0){
                    
                    
                    //When a histogram is fitted with more than one function in different ranges, the last fit replaces the previous fits and you cannot get the stat boxes of all. So take a clone for each fit.This makes a clone (see Clone below) of the histogram. Once the clone is drawn, the original histogram may be modified or deleted without affecting the aspect of the clone.
                    TH1F* copy_of_h1 = (TH1F*)myhist[j][n]->Clone("mycopy_of_h1");
                    copy_of_h1->Draw("SAMESPE hist");
                    copy_of_h1->Fit("inclusive_low", "R");
                    inclusive_low->SetLineColor(kRed-7);
                    inclusive_low->SetLineWidth(2);
                    inclusive_low->Draw("SAME");
                    
                    //TList *st1 = (TList*)myhist[j][n]->GetListOfFunctions()->FindObject("stats");
                    //st1->Draw("SAME");
                    myhist[j][n]->Fit("inclusive_high", "R");
                    inclusive_high->SetLineColor(kRed-7);
                    inclusive_high->SetLineWidth(2);
                    inclusive_high->Draw("SAME");
                    //TList *st2 = (TList*)copy_of_h1->GetListOfFunctions()->FindObject("stats");
                   // st2->Draw("SAME");
                    
                }
                if(n==1){
                    TH1F* copy_of_h2 = (TH1F*)myhist[j][n]->Clone("mycopy_of_h2");
                    copy_of_h2->Draw("SAMESPE hist");
                    copy_of_h2->Fit("bb_low", "R");
                    bb_low->SetLineColor(kRed-7);
                    bb_low->SetLineWidth(2);
                    bb_low->Draw("SAME");
                    myhist[j][n]->Fit("bb_high", "R");
                    bb_high->SetLineColor(kRed-7);
                    bb_high->SetLineWidth(2);
                    bb_high->Draw("SAME");
                }
                if(n==2){
                    TH1F* copy_of_h3 = (TH1F*)myhist[j][n]->Clone("mycopy_of_h3");
                    copy_of_h3->Draw("SAMESPE hist");
                    copy_of_h3->Fit("be_low", "R");
                    be_low->SetLineColor(kRed-7);
                    be_low->SetLineWidth(2);
                    be_low->Draw("SAME");
                    myhist[j][n]->Fit("be_high", "R");
                    be_high->SetLineColor(kRed-7);
                    be_high->SetLineWidth(2);
                    be_high->Draw("SAME");
                }
            }
            c->Update();
            pad1->Update();
        }
        
        TLegend *l1 = new TLegend(0.3,0.45,0.6,0.6);
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
        
        TPaveText* tText1 = new TPaveText(0.25, 0.90, 0.4, 0.95, "brNDC");
        tText1->SetBorderSize(1);
        tText1->SetFillColor(0);
        tText1->SetFillStyle(0);
        TText *t1 = tText1->AddText("Fit for low mass range");
        tText1->SetTextSize(0.005);
        tText1->Draw();
        
        TPaveText* tText2 = new TPaveText(0.25, 0.90, 0.4, 0.95, "brNDC");
        tText2->SetBorderSize(1);
        tText2->SetFillColor(0);
        tText2->SetFillStyle(0);
        TText *t2 = tText2->AddText("Fit for high mass range");
        tText2->SetTextSize(0.005);
        tText2->Draw();
        
        //TList *st = (TList*)myhist[3][n]->GetListOfFunctions()->FindObject("stats");
        //TList *st = (TList*)myhist[3][n]->GetListOfFunctions();
        //st->SetX1NDC(0.15);
        //st->SetX2NDC(0.5);
        // st->SetY1NDC(0.15);
        // st->SetY2NDC(0.5);
        //st->SetName("fit");
        //st->SetTitle("fit1");
        //st->Draw();
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

