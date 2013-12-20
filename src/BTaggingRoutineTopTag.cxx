#include "include/BTaggingRoutineTopTag.h"

BTaggingRoutineTopTag::BTaggingRoutineTopTag(
    float csvcut, TString mode, TString filename
)
{
  m_csvcut = csvcut;
  m_mode = mode;
  m_filename = filename;

/*  flavourhisto = new TH1F("flavourhisto","flavourhisto",22,0,22);
  percentagehisto = new TH1F("percentagehisto","percentagehisto",100,0,1.1);
  etahisto = new TH1F("etahisto","etahisto",100,0,5.5);*/
  file_mc = new TFile(m_filename);
}

/*void BTaggingRoutineTopTag::SaveHistos(void)
{
 TFile * f = new TFile("btagscalejetmon.root","RECREATE");
 flavourhisto->Write();
 percentagehisto->Write();
 etahisto->Write();
 f->Close();
}*/

double BTaggingRoutineTopTag::GetScaleWeight()
{
    
    EventCalc* calc = EventCalc::Instance();
    BaseCycleContainer* bcc = calc->GetBaseCycleContainer();

    double scale_factor = 1.;

    //if(m_csvcut!=0.679||m_mode.CompareTo("default")!=0) return 1.0;
//cout<<m_filename;
    
    //TFile *file_mc = new TFile(m_filename);
    //TFile *file_mc = new TFile("/scratch/hh/dust/naf/cms/user/usai/Semileptonicselection/SemileptonicselectionCycle.MC.singleTtW_2.root");

    //cout << "topjet size " << bcc->topjets->size() << endl;
    int number_not_possible=0;
    for(unsigned int i=0; i<bcc->jets->size(); ++i)
    {
      Jet jet = bcc->jets->at(i);
      double deltaphi=jet.deltaR(bcc->muons->at(0));
      if(!((deltaphi<(PI/2))&&(jet.pt()>30.)&&(fabs(jet.eta())<2.4))) continue;
	//std::vector<Particle> subjets_top;
	//std::vector<float> btagsub_combinedSecondaryVertex_top;
	//std::vector<int> flavorsub_top;

	//subjets_top=topjet.subjets();
      int flavour = abs(jet.flavor());
      
      //bool btag = (jet.btag_combinedSecondaryVertex()>m_csvcut)?true:false;
      //btagsub_combinedSecondaryVertex_top=topjet.btagsub_combinedSecondaryVertex();
      //flavorsub_top=topjet.flavorsub();

      //cout << "subjet size " << btagsub_combinedSecondaryVertex_top.size() << endl;
      
      //	for(unsigned int is=0; is < btagsub_combinedSecondaryVertex_top.size(); ++is)
      
      int possible = 1;
      
      //      float discr=btagsub_combinedSecondaryVertex_top[is];  
      //Particle subjet=subjets_top[is];
      double eta = fabs(jet.eta());
      double pt = jet.pt();
      //int flav = abs(flavorsub_top[is]);

      TF1 *csvm = NULL;
      if(flavour==5)
      {
// 	csvm = new TF1("csvm", "0.726981*((1.+(0.253238*x))/(1.+(0.188389*x)))", 20.0, 800.0);
	csvm = new TF1("csvm", "(0.938887+(0.00017124*x))+(-2.76366e-07*(x*x))", 20.0, 800.0);
      }
      if(flavour==4)
      {
// 	csvm = new TF1("csvm", "0.726981*((1.+(0.253238*x))/(1.+(0.188389*x)))", 20.0, 800.0);
	csvm = new TF1("csvm", "(0.938887+(0.00017124*x))+(-2.76366e-07*(x*x))", 20.0, 800.0);
      }
      if(flavour==1||flavour==2||flavour==3||flavour==21)
      {
	if(eta>=0&&eta<=0.8)
	{
// 	  csvm = new TF1("csvm", "((1.06238+(0.00198635*x))+(-4.89082e-06*(x*x)))+(3.29312e-09*(x*(x*x)))", 20.0, 800.0);
	  csvm = new TF1("csvm", "((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)))", 20.0, 800.0);
	}
	if(eta>0.8&&eta<=1.6)
	{
// 	  csvm = new TF1("csvm", "((1.08048+(0.00110831*x))+(-2.96189e-06*(x*x)))+(2.16266e-09*(x*(x*x)))", 20.0, 800.0);
	  csvm = new TF1("csvm", "((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)))", 20.0, 800.0);
	}
	if(eta>1.6&&eta<=2.4)
	{
// 	  csvm = new TF1("csvm", "((1.09145+(0.000687171*x))+(-2.45054e-06*(x*x)))+(1.7844e-09*(x*(x*x)))", 20.0, 800.0);
	  csvm = new TF1("csvm", "((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)))", 20.0, 800.0);
	}
      }

      TH1F *numpt = NULL;
      TH1F *denpt = NULL;
      TH1F *effipt = NULL;

      if(flavour==5)
      {
	double jetpt_bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800, 1600 };
	denpt=(TH1F*) file_mc->Get("BTagEffJim/pt_bJet");
	numpt=(TH1F*) file_mc->Get("BTagEffJim/pt_bJet_bTag");
	effipt=new TH1F("effipt","effi pt", 17, jetpt_bins);
      }
      else if(flavour==4)
      {
	double jetpt_bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 1600 };
	denpt=(TH1F*) file_mc->Get("BTagEffJim/pt_cJet");
	numpt=(TH1F*) file_mc->Get("BTagEffJim/pt_cJet_bTag");
	effipt=new TH1F("effipt","effi pt", 14, jetpt_bins);
      }
      else if(flavour==1||flavour==2||flavour==3||flavour==21)
      {
	double jetpt_bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 1600 };
	if(eta>=0&&eta<=0.8)
	{
	  denpt=(TH1F*) file_mc->Get("BTagEffJim/pt_lJet_e1");
	  numpt=(TH1F*) file_mc->Get("BTagEffJim/pt_lJet_e1_bTag");
	  effipt=new TH1F("effipt","effi pt", 16, jetpt_bins);
	}
	else if(eta>0.8&&eta<=1.6)
	{
	  denpt=(TH1F*) file_mc->Get("BTagEffJim/pt_lJet_e2");
	  numpt=(TH1F*) file_mc->Get("BTagEffJim/pt_lJet_e2_bTag");
	  effipt=new TH1F("effipt","effi pt", 16, jetpt_bins);
	}
	else if(eta>1.6&&eta<=2.4)
	{
	  denpt=(TH1F*) file_mc->Get("BTagEffJim/pt_lJet_e3");
	  numpt=(TH1F*) file_mc->Get("BTagEffJim/pt_lJet_e3_bTag");
	  effipt=new TH1F("effipt","effi pt", 16, jetpt_bins);
	}
	else
	{
	  possible=0;
	}
      }
      else
      {
	possible=0;
      }

      double scale_subjet=1.;

      if(possible!=1)
      {
	//std::cout<<"not possible "<<flavour<<" "<<eta<<std::endl;
	//cout << "Not possible iteration on sub " << is << " of jet " << i << " with pt " << topjet.pt() << " with csv " << discr << " eta " << subeta << "flav " << flav << " pt " << subpt << endl;
	//flavourhisto->Fill(flavour);
	//etahisto->Fill(eta);
	number_not_possible++;
      }
      else
      {
	//std::cout<<"possible "<<flavour<<" "<<eta<<std::endl;
	effipt->Divide(numpt,denpt,1,1,"B");    
	double SF=0;
	if (csvm->GetXmin() > pt)
	{
	  SF=csvm->Eval(csvm->GetXmin());
	}
	else if (csvm->GetXmax() < pt)
	{
	  SF=csvm->Eval(csvm->GetXmax());
	}
	else
	{
	  SF=csvm->Eval(pt);
	}
	
	float effi;
	int bin;

	if(pt>800)
	{
	  bin=effipt->GetXaxis()->GetNbins();
	}
	else if(pt<20)
	{
	  bin=1;
	}
	else
	{
	  bin=effipt->GetXaxis()->FindBin(pt);
	}
	effi=effipt->GetBinContent(bin);
	bool is_tagged = (jet.btag_combinedSecondaryVertex()>m_csvcut)?true:false;
	//if(discr > m_csvcut) is_tagged=1;
	if(is_tagged)
	{
	  scale_subjet=SF;
	}
	else
	{
	  scale_subjet=(1 - SF * effi) / (1 - effi);
	      //std::cout << "Returning " << scale_factor <<" effi=" << effi<<" SF="<<SF<<std::endl;
	}
	//cout << "Iteration on sub " << is << " of jet " << i << " with pt " << topjet.pt() << " with csv " << discr << " is tagged " << is_tagged << " eta " << subeta << "flav " << flav << " pt " << subpt << " scale " << scale_subjet << endl;
	delete csvm;
	delete numpt;
	delete denpt;
	delete effipt;
      }//possible
      scale_factor *= scale_subjet;
	//}//loop over subjets
	
    }//loop over jets
    //std::cout<<number_not_possible*1.0/bcc->jets->size()<<std::endl;
    //percentagehisto->Fill(number_not_possible*1.0/bcc->jets->size());
    
    /*file_mc->Close();
    
    delete file_mc;*/
    

    
    return scale_factor;
}




