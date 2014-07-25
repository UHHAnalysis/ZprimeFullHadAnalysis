#include "TH1.h"
#include "TFile.h"
#include <algorithm> 

using namespace std;

PDFUncertaintyHistos(){

  const int nproc=29;//16

  TString process[nproc] = {"ttbar", "Zprime500","Zprime500w","Zprime750","Zprime750w","Zprime1000","Zprime1000w","Zprime1250","Zprime1250w","Zprime1500","Zprime1500w","Zprime2000","Zprime2000w","Zprime3000","Zprime3000w","Zprime4000","Zprime4000w","RSG700","RSG1000","RSG1200","RSG1400","RSG1500","RSG1600","RSG1800","RSG2000","RSG2500","RSG3000","RSG3500","RSG4000"};
  TString filename[nproc] = {"TTbar", "ZP500W5","ZP500W50","ZP750W7p5","ZP750W75","ZP1000W10","ZP1000W100","ZP1250W12p5","ZP1250W125","ZP1500W15","ZP1500W150","ZP2000W20","ZP2000W200","ZP3000W30","ZP3000W300","ZP4000W40","ZP4000W400","RSG700","RSG1000","RSG1200","RSG1400","RSG1500","RSG1600","RSG1800","RSG2000","RSG2500","RSG3000","RSG3500","RSG4000"};

  //TString process[nproc] = {"zp500w1p", "zp750w1p", "zp1000w1p","zp1250w1p", "zp1500w1p", "zp2000w1p", "zp3000w1p","zp4000w1p", "zp500w10p", "zp750w10p", "zp1000w10p", "zp1250w10p", "zp1500w10p", "zp2000w10p", "zp3000w10p", "zp4000w10p"};
  //TString filename[nproc] = {"ZP500w5", "ZP750w7p5", "ZP1000w10", "ZP1250w12p5", "ZP1500w15", "ZP2000w20" ,"ZP3000w30","ZP4000w40", "ZP500w50", "ZP750w75", "ZP1000w100", "ZP1250w125" , "ZP1500w150", "ZP2000w200" ,"ZP3000w300", "ZP4000w400"};

  TString directory = "/nfs/dust/cms/user/usaiem/ZprimeFullHad/preselection/";
  
  // TFile *outfile = new TFile("thetapdf.root","RECREATE");
  TFile *outfile = new TFile("mjthetapdf.root","RECREATE");
  //TFile *outfile = new TFile("theta_histograms_pdf_signal.root","RECREATE");
  
  for(int i=0; i<nproc; ++i){

    TString mcdata = "MC";
    std::cout << process[i] <<endl;

    
    TFile * infile_default = new TFile("/nfs/dust/cms/user/usaiem/ZprimeFullHad/BackgroundCycle.MC."+filename[i]+".root");
    infile_default->cd();
    // TH1F* mtt_0btag_default = (TH1F*) infile_default->Get("HTDatasetHistos/MeasuredMtt0");
    // TH1F* mtt_1btag_default = (TH1F*) infile_default->Get("HTDatasetHistos/MeasuredMtt1");
    // TH1F* mtt_2btag_default = (TH1F*) infile_default->Get("HTDatasetHistos/MeasuredMtt2");
    TH1F* mtt_0btag_default = (TH1F*) infile_default->Get("QuadJetDatasetHistos/MeasuredMtt0");
    TH1F* mtt_1btag_default = (TH1F*) infile_default->Get("QuadJetDatasetHistos/MeasuredMtt1");
    TH1F* mtt_2btag_default = (TH1F*) infile_default->Get("QuadJetDatasetHistos/MeasuredMtt2");

    int Npdf;
    if(process[i]=="ttbar"){
      Npdf=52;
    }
    else
      Npdf=44;

    const int Np=Npdf;

    TH1F* mtt_0btag[Np];
    TH1F* mtt_1btag[Np];
    TH1F* mtt_2btag[Np];

    for(int index=1; index<=Npdf; ++index){

      TString name =  directory+"/BackgroundCycle.MC."+filename[i]+"_";
      name += index;
      name += ".root";
      
      std::cout<< name << std::endl;
      TFile * infile = new TFile(name);
      infile->cd();

      // mtt_0btag[index-1] = (TH1F*)infile->Get("HTDatasetHistos/MeasuredMtt0");
      // mtt_1btag[index-1] = (TH1F*)infile->Get("HTDatasetHistos/MeasuredMtt1");
      // mtt_2btag[index-1] = (TH1F*)infile->Get("HTDatasetHistos/MeasuredMtt2");
      mtt_0btag[index-1] = (TH1F*)infile->Get("QuadJetDatasetHistos/MeasuredMtt0");
      mtt_1btag[index-1] = (TH1F*)infile->Get("QuadJetDatasetHistos/MeasuredMtt1");
      mtt_2btag[index-1] = (TH1F*)infile->Get("QuadJetDatasetHistos/MeasuredMtt2");

      //infile->Close();
    }

    TH1F* mtt_0btag_plus = (TH1F*) mtt_0btag_default->Clone(); 
    TH1F* mtt_1btag_plus = (TH1F*) mtt_1btag_default->Clone(); 
    TH1F* mtt_2btag_plus = (TH1F*) mtt_2btag_default->Clone();
    TH1F* mtt_0btag_minus = (TH1F*) mtt_0btag_default->Clone(); 
    TH1F* mtt_1btag_minus = (TH1F*) mtt_1btag_default->Clone();
    TH1F* mtt_2btag_minus = (TH1F*) mtt_2btag_default->Clone();
    mtt_0btag_plus->Reset();
    mtt_1btag_plus->Reset();  
    mtt_2btag_plus->Reset();
    mtt_0btag_minus->Reset();
    mtt_1btag_minus->Reset();
    mtt_2btag_minus->Reset();

    for(int index=0; index<Npdf/2; ++index){
      
      for(int b=0; b<=mtt_0btag_default->GetNbinsX(); ++b){
	double var1 = mtt_0btag[2*index]->GetBinContent(b)-mtt_0btag_default->GetBinContent(b);
	double var2 = mtt_0btag[2*index+1]->GetBinContent(b)-mtt_0btag_default->GetBinContent(b);
	//std::cout << var1 << "  " << var2 <<std::endl;
	mtt_0btag_plus->SetBinContent(b,mtt_0btag_plus->GetBinContent(b) + pow(std::max(max(var1,var2),0.),2) );
	mtt_0btag_minus->SetBinContent(b,mtt_0btag_minus->GetBinContent(b) + pow(std::max(std::max(-1*var1,-1*var2),0.),2) );
      }
      for(int b=0; b<=mtt_1btag_default->GetNbinsX(); ++b){
	double var1 = mtt_1btag[2*index]->GetBinContent(b)-mtt_1btag_default->GetBinContent(b);
	double var2 = mtt_1btag[2*index+1]->GetBinContent(b)-mtt_1btag_default->GetBinContent(b);
	mtt_1btag_plus->SetBinContent(b,mtt_1btag_plus->GetBinContent(b) + pow(std::max(max(var1,var2),0.),2) );
	mtt_1btag_minus->SetBinContent(b,mtt_1btag_minus->GetBinContent(b) + pow(std::max(std::max(-1*var1,-1*var2),0.),2) );
      }
      for(int b=0; b<=mtt_2btag_default->GetNbinsX(); ++b){
	double var1 = mtt_2btag[2*index]->GetBinContent(b)-mtt_2btag_default->GetBinContent(b);
	double var2 = mtt_2btag[2*index+1]->GetBinContent(b)-mtt_2btag_default->GetBinContent(b);
	mtt_2btag_plus->SetBinContent(b,mtt_2btag_plus->GetBinContent(b) + pow(std::max(max(var1,var2),0.),2) );
	mtt_2btag_minus->SetBinContent(b,mtt_2btag_minus->GetBinContent(b) + pow(std::max(std::max(-1*var1,-1*var2),0.),2) );
      }

    }
    for(int b=0; b<=mtt_0btag_default->GetNbinsX(); ++b){
      mtt_0btag_plus->SetBinContent(b, sqrt(mtt_0btag_plus->GetBinContent(b)));
      mtt_0btag_minus->SetBinContent(b, sqrt(mtt_0btag_minus->GetBinContent(b)));  

      mtt_0btag_plus->SetBinContent(b, mtt_0btag_default->GetBinContent(b) + mtt_0btag_plus->GetBinContent(b));
      mtt_0btag_minus->SetBinContent(b, mtt_0btag_default->GetBinContent(b) - mtt_0btag_minus->GetBinContent(b));  
    }
    for(int b=0; b<=mtt_1btag_default->GetNbinsX(); ++b){
      mtt_1btag_plus->SetBinContent(b, sqrt(mtt_1btag_plus->GetBinContent(b)));
      mtt_1btag_minus->SetBinContent(b, sqrt(mtt_1btag_minus->GetBinContent(b)));  

      mtt_1btag_plus->SetBinContent(b, mtt_1btag_default->GetBinContent(b) + mtt_1btag_plus->GetBinContent(b));
      mtt_1btag_minus->SetBinContent(b, mtt_1btag_default->GetBinContent(b) - mtt_1btag_minus->GetBinContent(b)); 
    }
    for(int b=0; b<=mtt_2btag_default->GetNbinsX(); ++b){
      mtt_2btag_plus->SetBinContent(b, sqrt(mtt_2btag_plus->GetBinContent(b)));
      mtt_2btag_minus->SetBinContent(b, sqrt(mtt_2btag_minus->GetBinContent(b)));  

      mtt_2btag_plus->SetBinContent(b, mtt_2btag_default->GetBinContent(b) + mtt_2btag_plus->GetBinContent(b));
      mtt_2btag_minus->SetBinContent(b, mtt_2btag_default->GetBinContent(b) - mtt_2btag_minus->GetBinContent(b)); 
    }

    // mtt_0btag_plus->SetName("httbtag0__"+process[i]+"__pdf__plus");
    // mtt_1btag_plus->SetName("httbtag1__"+process[i]+"__pdf__plus");
    // mtt_2btag_plus->SetName("httbtag2__"+process[i]+"__pdf__plus"); 
    // mtt_0btag_minus->SetName("httbtag0__"+process[i]+"__pdf__minus");
    // mtt_1btag_minus->SetName("httbtag1__"+process[i]+"__pdf__minus"); 
    // mtt_2btag_minus->SetName("httbtag2__"+process[i]+"__pdf__minus");
    mtt_0btag_plus->SetName("mjhttbtag0__"+process[i]+"__pdf__plus");
    mtt_1btag_plus->SetName("mjhttbtag1__"+process[i]+"__pdf__plus");
    mtt_2btag_plus->SetName("mjhttbtag2__"+process[i]+"__pdf__plus"); 
    mtt_0btag_minus->SetName("mjhttbtag0__"+process[i]+"__pdf__minus");
    mtt_1btag_minus->SetName("mjhttbtag1__"+process[i]+"__pdf__minus"); 
    mtt_2btag_minus->SetName("mjhttbtag2__"+process[i]+"__pdf__minus"); 

    outfile->cd();
    mtt_0btag_plus->Write();
    mtt_1btag_plus->Write();
    mtt_2btag_plus->Write();
    mtt_0btag_minus->Write();
    mtt_1btag_minus->Write();
    mtt_2btag_minus->Write();

  }

}

