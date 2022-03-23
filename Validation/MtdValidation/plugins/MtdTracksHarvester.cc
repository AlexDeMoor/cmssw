#include <string>

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DQMServices/Core/interface/DQMEDHarvester.h"
#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/ForwardDetId/interface/ETLDetId.h"

class MtdTracksHarvester : public DQMEDHarvester {
public:
  explicit MtdTracksHarvester(const edm::ParameterSet& iConfig);
  ~MtdTracksHarvester() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

protected:
  void dqmEndJob(DQMStore::IBooker&, DQMStore::IGetter&) override;

private:
  void computeEfficiency1D(MonitorElement* num, MonitorElement* den, MonitorElement* result);

  void incrementME(MonitorElement* base, MonitorElement* toBeAdded);

  const std::string folder_;

  // --- Histograms
  MonitorElement* meBtlEtaEff_;
  MonitorElement* meBtlPhiEff_;
  MonitorElement* meBtlPtEff_;
  MonitorElement* meEtlEtaEff_[2];
  MonitorElement* meEtlPhiEff_[2];
  MonitorElement* meEtlPtEff_[2];
  MonitorElement* meMVAPtSelEff_;
  MonitorElement* meMVAEtaSelEff_;
  MonitorElement* meMVAPtMatchEff_;
  MonitorElement* meMVAEtaMatchEff_;

  MonitorElement* meBarrelTruePi_;
  MonitorElement* meBarrelTrueK_;
  MonitorElement* meBarrelTrueP_;

  MonitorElement* meEndcapTruePi_;
  MonitorElement* meEndcapTrueK_;
  MonitorElement* meEndcapTrueP_;

  MonitorElement* meBarrelAsPi_;
  MonitorElement* meBarrelAsK_;
  MonitorElement* meBarrelAsP_;
  MonitorElement* meBarrelNoPID_;

  MonitorElement* meEndcapAsPi_;
  MonitorElement* meEndcapAsK_;
  MonitorElement* meEndcapAsP_;
  MonitorElement* meEndcapNoPID_;

  MonitorElement* meBarrelPIDPiAsPiEff_;
  MonitorElement* meBarrelPIDPiAsKEff_;
  MonitorElement* meBarrelPIDPiAsPEff_;
  MonitorElement* meBarrelPIDPiNoPIDEff_;

  MonitorElement* meBarrelPIDKAsPiEff_;
  MonitorElement* meBarrelPIDKAsKEff_;
  MonitorElement* meBarrelPIDKAsPEff_;
  MonitorElement* meBarrelPIDKNoPIDEff_;

  MonitorElement* meBarrelPIDPAsPiEff_;
  MonitorElement* meBarrelPIDPAsKEff_;
  MonitorElement* meBarrelPIDPAsPEff_;
  MonitorElement* meBarrelPIDPNoPIDEff_;

  MonitorElement* meEndcapPIDPiAsPiEff_;
  MonitorElement* meEndcapPIDPiAsKEff_;
  MonitorElement* meEndcapPIDPiAsPEff_;
  MonitorElement* meEndcapPIDPiNoPIDEff_;

  MonitorElement* meEndcapPIDKAsPiEff_;
  MonitorElement* meEndcapPIDKAsKEff_;
  MonitorElement* meEndcapPIDKAsPEff_;
  MonitorElement* meEndcapPIDKNoPIDEff_;

  MonitorElement* meEndcapPIDPAsPiEff_;
  MonitorElement* meEndcapPIDPAsKEff_;
  MonitorElement* meEndcapPIDPAsPEff_;
  MonitorElement* meEndcapPIDPNoPIDEff_;

  MonitorElement* meBarrelPiPurity_;
  MonitorElement* meBarrelKPurity_;
  MonitorElement* meBarrelPPurity_;

  MonitorElement* meEndcapPiPurity_;
  MonitorElement* meEndcapKPurity_;
  MonitorElement* meEndcapPPurity_;
};

// ------------ constructor and destructor --------------
MtdTracksHarvester::MtdTracksHarvester(const edm::ParameterSet& iConfig)
    : folder_(iConfig.getParameter<std::string>("folder")) {}

MtdTracksHarvester::~MtdTracksHarvester() {}

// auxiliary method to compute efficiency from the ratio of two 1D MonitorElement
void MtdTracksHarvester::computeEfficiency1D(MonitorElement* num, MonitorElement* den, MonitorElement* result) {
  for (int ibin = 1; ibin <= den->getNbinsX(); ibin++) {
    double eff = num->getBinContent(ibin) / den->getBinContent(ibin);
    double bin_err = sqrt((num->getBinContent(ibin) * (den->getBinContent(ibin) - num->getBinContent(ibin))) /
                          pow(den->getBinContent(ibin), 3));
    if (den->getBinContent(ibin) == 0) {
      eff = 0;
      bin_err = 0;
    }
    result->setBinContent(ibin, eff);
    result->setBinError(ibin, bin_err);
  }
}

// auxiliary method to add 1D MonitorElement toBeAdded to a base ME
void MtdTracksHarvester::incrementME(MonitorElement* base, MonitorElement* toBeAdded) {
  for (int ibin = 1; ibin <= base->getNbinsX(); ibin++) {
    double newC = base->getBinContent(ibin) + toBeAdded->getBinContent(ibin);
    double newE = std::sqrt(newC);
    base->setBinContent(ibin, newC);
    base->setBinError(ibin, newE);
  }
}

// ------------ endjob tasks ----------------------------
void MtdTracksHarvester::dqmEndJob(DQMStore::IBooker& ibook, DQMStore::IGetter& igetter) {
  // --- Get the monitoring histograms
  MonitorElement* meBTLTrackEffEtaTot = igetter.get(folder_ + "TrackBTLEffEtaTot");
  MonitorElement* meBTLTrackEffPhiTot = igetter.get(folder_ + "TrackBTLEffPhiTot");
  MonitorElement* meBTLTrackEffPtTot = igetter.get(folder_ + "TrackBTLEffPtTot");
  MonitorElement* meBTLTrackEffEtaMtd = igetter.get(folder_ + "TrackBTLEffEtaMtd");
  MonitorElement* meBTLTrackEffPhiMtd = igetter.get(folder_ + "TrackBTLEffPhiMtd");
  MonitorElement* meBTLTrackEffPtMtd = igetter.get(folder_ + "TrackBTLEffPtMtd");
  MonitorElement* meETLTrackEffEtaTotZneg = igetter.get(folder_ + "TrackETLEffEtaTotZneg");
  MonitorElement* meETLTrackEffPhiTotZneg = igetter.get(folder_ + "TrackETLEffPhiTotZneg");
  MonitorElement* meETLTrackEffPtTotZneg = igetter.get(folder_ + "TrackETLEffPtTotZneg");
  MonitorElement* meETLTrackEffEtaMtdZneg = igetter.get(folder_ + "TrackETLEffEtaMtdZneg");
  MonitorElement* meETLTrackEffPhiMtdZneg = igetter.get(folder_ + "TrackETLEffPhiMtdZneg");
  MonitorElement* meETLTrackEffPtMtdZneg = igetter.get(folder_ + "TrackETLEffPtMtdZneg");
  MonitorElement* meETLTrackEffEtaTotZpos = igetter.get(folder_ + "TrackETLEffEtaTotZpos");
  MonitorElement* meETLTrackEffPhiTotZpos = igetter.get(folder_ + "TrackETLEffPhiTotZpos");
  MonitorElement* meETLTrackEffPtTotZpos = igetter.get(folder_ + "TrackETLEffPtTotZpos");
  MonitorElement* meETLTrackEffEtaMtdZpos = igetter.get(folder_ + "TrackETLEffEtaMtdZpos");
  MonitorElement* meETLTrackEffPhiMtdZpos = igetter.get(folder_ + "TrackETLEffPhiMtdZpos");
  MonitorElement* meETLTrackEffPtMtdZpos = igetter.get(folder_ + "TrackETLEffPtMtdZpos");
  MonitorElement* meMVATrackEffPtTot = igetter.get(folder_ + "MVAEffPtTot");
  MonitorElement* meMVATrackMatchedEffPtTot = igetter.get(folder_ + "MVAMatchedEffPtTot");
  MonitorElement* meMVATrackMatchedEffPtMtd = igetter.get(folder_ + "MVAMatchedEffPtMtd");
  MonitorElement* meMVATrackEffEtaTot = igetter.get(folder_ + "MVAEffEtaTot");
  MonitorElement* meMVATrackMatchedEffEtaTot = igetter.get(folder_ + "MVAMatchedEffEtaTot");
  MonitorElement* meMVATrackMatchedEffEtaMtd = igetter.get(folder_ + "MVAMatchedEffEtaMtd");

  if (!meBTLTrackEffEtaTot || !meBTLTrackEffPhiTot || !meBTLTrackEffPtTot || !meBTLTrackEffEtaMtd ||
      !meBTLTrackEffPhiMtd || !meBTLTrackEffPtMtd || !meETLTrackEffEtaTotZneg || !meETLTrackEffPhiTotZneg ||
      !meETLTrackEffPtTotZneg || !meETLTrackEffEtaMtdZneg || !meETLTrackEffPhiMtdZneg || !meETLTrackEffPtMtdZneg ||
      !meETLTrackEffEtaTotZpos || !meETLTrackEffPhiTotZpos || !meETLTrackEffPtTotZpos || !meETLTrackEffEtaMtdZpos ||
      !meETLTrackEffPhiMtdZpos || !meETLTrackEffPtMtdZpos || !meMVATrackEffPtTot || !meMVATrackMatchedEffPtTot ||
      !meMVATrackMatchedEffPtMtd || !meMVATrackEffEtaTot || !meMVATrackMatchedEffEtaTot ||
      !meMVATrackMatchedEffEtaMtd) {
    edm::LogError("MtdTracksHarvester") << "Monitoring histograms not found!" << std::endl;
    return;
  }

  // --- Book  histograms
  ibook.cd(folder_);
  meBtlEtaEff_ = ibook.book1D("BtlEtaEff",
                              " Track Efficiency VS Eta;#eta;Efficiency",
                              meBTLTrackEffEtaTot->getNbinsX(),
                              meBTLTrackEffEtaTot->getTH1()->GetXaxis()->GetXmin(),
                              meBTLTrackEffEtaTot->getTH1()->GetXaxis()->GetXmax());
  meBtlEtaEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBTLTrackEffEtaMtd, meBTLTrackEffEtaTot, meBtlEtaEff_);

  meBtlPhiEff_ = ibook.book1D("BtlPhiEff",
                              "Track Efficiency VS Phi;#phi [rad];Efficiency",
                              meBTLTrackEffPhiTot->getNbinsX(),
                              meBTLTrackEffPhiTot->getTH1()->GetXaxis()->GetXmin(),
                              meBTLTrackEffPhiTot->getTH1()->GetXaxis()->GetXmax());
  meBtlPhiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBTLTrackEffPhiMtd, meBTLTrackEffPhiTot, meBtlPhiEff_);

  meBtlPtEff_ = ibook.book1D("BtlPtEff",
                             "Track Efficiency VS Pt;Pt [GeV];Efficiency",
                             meBTLTrackEffPtTot->getNbinsX(),
                             meBTLTrackEffPtTot->getTH1()->GetXaxis()->GetXmin(),
                             meBTLTrackEffPtTot->getTH1()->GetXaxis()->GetXmax());
  meBtlPtEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBTLTrackEffPtMtd, meBTLTrackEffPtTot, meBtlPtEff_);

  meEtlEtaEff_[0] = ibook.book1D("EtlEtaEffZneg",
                                 " Track Efficiency VS Eta (-Z);#eta;Efficiency",
                                 meETLTrackEffEtaTotZneg->getNbinsX(),
                                 meETLTrackEffEtaTotZneg->getTH1()->GetXaxis()->GetXmin(),
                                 meETLTrackEffEtaTotZneg->getTH1()->GetXaxis()->GetXmax());
  meEtlEtaEff_[0]->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meETLTrackEffEtaMtdZneg, meETLTrackEffEtaTotZneg, meEtlEtaEff_[0]);

  meEtlPhiEff_[0] = ibook.book1D("EtlPhiEffZneg",
                                 "Track Efficiency VS Phi (-Z);#phi [rad];Efficiency",
                                 meETLTrackEffPhiTotZneg->getNbinsX(),
                                 meETLTrackEffPhiTotZneg->getTH1()->GetXaxis()->GetXmin(),
                                 meETLTrackEffPhiTotZneg->getTH1()->GetXaxis()->GetXmax());
  meEtlPhiEff_[0]->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meETLTrackEffPhiMtdZneg, meETLTrackEffPhiTotZneg, meEtlPhiEff_[0]);

  meEtlPtEff_[0] = ibook.book1D("EtlPtEffZneg",
                                "Track Efficiency VS Pt (-Z);Pt [GeV];Efficiency",
                                meETLTrackEffPtTotZneg->getNbinsX(),
                                meETLTrackEffPtTotZneg->getTH1()->GetXaxis()->GetXmin(),
                                meETLTrackEffPtTotZneg->getTH1()->GetXaxis()->GetXmax());
  meEtlPtEff_[0]->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meETLTrackEffPtMtdZneg, meETLTrackEffPtTotZneg, meEtlPtEff_[0]);

  meEtlEtaEff_[1] = ibook.book1D("EtlEtaEffZpos",
                                 " Track Efficiency VS Eta (+Z);#eta;Efficiency",
                                 meETLTrackEffEtaTotZpos->getNbinsX(),
                                 meETLTrackEffEtaTotZpos->getTH1()->GetXaxis()->GetXmin(),
                                 meETLTrackEffEtaTotZpos->getTH1()->GetXaxis()->GetXmax());
  meEtlEtaEff_[1]->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meETLTrackEffEtaMtdZpos, meETLTrackEffEtaTotZpos, meEtlEtaEff_[1]);

  meEtlPhiEff_[1] = ibook.book1D("EtlPhiEffZpos",
                                 "Track Efficiency VS Phi (+Z);#phi [rad];Efficiency",
                                 meETLTrackEffPhiTotZpos->getNbinsX(),
                                 meETLTrackEffPhiTotZpos->getTH1()->GetXaxis()->GetXmin(),
                                 meETLTrackEffPhiTotZpos->getTH1()->GetXaxis()->GetXmax());
  meEtlPhiEff_[1]->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meETLTrackEffPhiMtdZpos, meETLTrackEffPhiTotZpos, meEtlPhiEff_[1]);

  meEtlPtEff_[1] = ibook.book1D("EtlPtEffZpos",
                                "Track Efficiency VS Pt (+Z);Pt [GeV];Efficiency",
                                meETLTrackEffPtTotZpos->getNbinsX(),
                                meETLTrackEffPtTotZpos->getTH1()->GetXaxis()->GetXmin(),
                                meETLTrackEffPtTotZpos->getTH1()->GetXaxis()->GetXmax());
  meEtlPtEff_[1]->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meETLTrackEffPtMtdZpos, meETLTrackEffPtTotZpos, meEtlPtEff_[1]);

  meMVAPtSelEff_ = ibook.book1D("MVAPtSelEff",
                                "Track selected efficiency VS Pt;Pt [GeV];Efficiency",
                                meMVATrackEffPtTot->getNbinsX(),
                                meMVATrackEffPtTot->getTH1()->GetXaxis()->GetXmin(),
                                meMVATrackEffPtTot->getTH1()->GetXaxis()->GetXmax());
  meMVAPtSelEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meMVATrackMatchedEffPtTot, meMVATrackEffPtTot, meMVAPtSelEff_);

  meMVAEtaSelEff_ = ibook.book1D("MVAEtaSelEff",
                                 "Track selected efficiency VS Eta;Eta;Efficiency",
                                 meMVATrackEffEtaTot->getNbinsX(),
                                 meMVATrackEffEtaTot->getTH1()->GetXaxis()->GetXmin(),
                                 meMVATrackEffEtaTot->getTH1()->GetXaxis()->GetXmax());
  meMVAEtaSelEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meMVATrackMatchedEffEtaTot, meMVATrackEffEtaTot, meMVAEtaSelEff_);

  meMVAPtMatchEff_ = ibook.book1D("MVAPtMatchEff",
                                  "Track matched to GEN efficiency VS Pt;Pt [GeV];Efficiency",
                                  meMVATrackMatchedEffPtTot->getNbinsX(),
                                  meMVATrackMatchedEffPtTot->getTH1()->GetXaxis()->GetXmin(),
                                  meMVATrackMatchedEffPtTot->getTH1()->GetXaxis()->GetXmax());
  meMVAPtMatchEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meMVATrackMatchedEffPtMtd, meMVATrackMatchedEffPtTot, meMVAPtMatchEff_);

  meMVAEtaMatchEff_ = ibook.book1D("MVAEtaMatchEff",
                                   "Track matched to GEN efficiency VS Eta;Eta;Efficiency",
                                   meMVATrackMatchedEffEtaTot->getNbinsX(),
                                   meMVATrackMatchedEffEtaTot->getTH1()->GetXaxis()->GetXmin(),
                                   meMVATrackMatchedEffEtaTot->getTH1()->GetXaxis()->GetXmax());
  meMVAEtaMatchEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meMVATrackMatchedEffEtaMtd, meMVATrackMatchedEffEtaTot, meMVAEtaMatchEff_);

  meBtlPhiEff_->getTH1()->SetMinimum(0.);
  meBtlPtEff_->getTH1()->SetMinimum(0.);
  for (int i = 0; i < 2; i++) {
    meEtlEtaEff_[i]->getTH1()->SetMinimum(0.);
    meEtlPhiEff_[i]->getTH1()->SetMinimum(0.);
    meEtlPtEff_[i]->getTH1()->SetMinimum(0.);
  }
  meMVAPtSelEff_->getTH1()->SetMinimum(0.);
  meMVAEtaSelEff_->getTH1()->SetMinimum(0.);
  meMVAPtMatchEff_->getTH1()->SetMinimum(0.);
  meMVAEtaMatchEff_->getTH1()->SetMinimum(0.);

  MonitorElement* meBarrelPIDp = igetter.get(folder_ + "BarrelPIDp");
  MonitorElement* meEndcapPIDp = igetter.get(folder_ + "EndcapPIDp");

  MonitorElement* meBarrelTruePiNoPID = igetter.get(folder_ + "BarrelTruePiNoPID");
  MonitorElement* meBarrelTrueKNoPID = igetter.get(folder_ + "BarrelTrueKNoPID");
  MonitorElement* meBarrelTruePNoPID = igetter.get(folder_ + "BarrelTruePNoPID");
  MonitorElement* meEndcapTruePiNoPID = igetter.get(folder_ + "EndcapTruePiNoPID");
  MonitorElement* meEndcapTrueKNoPID = igetter.get(folder_ + "EndcapTrueKNoPID");
  MonitorElement* meEndcapTruePNoPID = igetter.get(folder_ + "EndcapTruePNoPID");

  MonitorElement* meBarrelTruePiAsPi = igetter.get(folder_ + "BarrelTruePiAsPi");
  MonitorElement* meBarrelTrueKAsPi = igetter.get(folder_ + "BarrelTrueKAsPi");
  MonitorElement* meBarrelTruePAsPi = igetter.get(folder_ + "BarrelTruePAsPi");
  MonitorElement* meEndcapTruePiAsPi = igetter.get(folder_ + "EndcapTruePiAsPi");
  MonitorElement* meEndcapTrueKAsPi = igetter.get(folder_ + "EndcapTrueKAsPi");
  MonitorElement* meEndcapTruePAsPi = igetter.get(folder_ + "EndcapTruePAsPi");

  MonitorElement* meBarrelTruePiAsK = igetter.get(folder_ + "BarrelTruePiAsK");
  MonitorElement* meBarrelTrueKAsK = igetter.get(folder_ + "BarrelTrueKAsK");
  MonitorElement* meBarrelTruePAsK = igetter.get(folder_ + "BarrelTruePAsK");
  MonitorElement* meEndcapTruePiAsK = igetter.get(folder_ + "EndcapTruePiAsK");
  MonitorElement* meEndcapTrueKAsK = igetter.get(folder_ + "EndcapTrueKAsK");
  MonitorElement* meEndcapTruePAsK = igetter.get(folder_ + "EndcapTruePAsK");

  MonitorElement* meBarrelTruePiAsP = igetter.get(folder_ + "BarrelTruePiAsP");
  MonitorElement* meBarrelTrueKAsP = igetter.get(folder_ + "BarrelTrueKAsP");
  MonitorElement* meBarrelTruePAsP = igetter.get(folder_ + "BarrelTruePAsP");
  MonitorElement* meEndcapTruePiAsP = igetter.get(folder_ + "EndcapTruePiAsP");
  MonitorElement* meEndcapTrueKAsP = igetter.get(folder_ + "EndcapTrueKAsP");
  MonitorElement* meEndcapTruePAsP = igetter.get(folder_ + "EndcapTruePAsP");

  if (!meBarrelPIDp || !meEndcapPIDp || !meBarrelTruePiNoPID || !meBarrelTrueKNoPID || !meBarrelTruePNoPID ||
      !meEndcapTruePiNoPID || !meEndcapTrueKNoPID || !meEndcapTruePNoPID || !meBarrelTruePiAsPi || !meBarrelTrueKAsPi ||
      !meBarrelTruePAsPi || !meEndcapTruePiAsPi || !meEndcapTrueKAsPi || !meEndcapTruePAsPi || !meBarrelTruePiAsK ||
      !meBarrelTrueKAsK || !meBarrelTruePAsK || !meEndcapTruePiAsK || !meEndcapTrueKAsK || !meEndcapTruePAsK ||
      !meBarrelTruePiAsP || !meBarrelTrueKAsP || !meBarrelTruePAsP || !meEndcapTruePiAsP || !meEndcapTrueKAsP ||
      !meEndcapTruePAsP) {
    edm::LogWarning("Primary4DVertexHarvester") << "PID Monitoring histograms not found!" << std::endl;
    return;
  }

  meBarrelTruePi_ = ibook.book1D("BarrelTruePi",
                                 "Barrel True Pi P;P [GeV]",
                                 meBarrelPIDp->getNbinsX(),
                                 meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                 meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelTruePi_, meBarrelTruePiAsPi);
  incrementME(meBarrelTruePi_, meBarrelTruePiAsK);
  incrementME(meBarrelTruePi_, meBarrelTruePiAsP);
  incrementME(meBarrelTruePi_, meBarrelTruePiNoPID);

  meEndcapTruePi_ = ibook.book1D("EndcapTruePi",
                                 "Endcap True Pi P;P [GeV]",
                                 meBarrelPIDp->getNbinsX(),
                                 meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                 meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapTruePi_, meEndcapTruePiAsPi);
  incrementME(meEndcapTruePi_, meEndcapTruePiAsK);
  incrementME(meEndcapTruePi_, meEndcapTruePiAsP);
  incrementME(meEndcapTruePi_, meEndcapTruePiNoPID);

  meBarrelTrueK_ = ibook.book1D("BarrelTrueK",
                                "Barrel True K P;P [GeV]",
                                meBarrelPIDp->getNbinsX(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelTrueK_, meBarrelTrueKAsPi);
  incrementME(meBarrelTrueK_, meBarrelTrueKAsK);
  incrementME(meBarrelTrueK_, meBarrelTrueKAsP);
  incrementME(meBarrelTrueK_, meBarrelTrueKNoPID);

  meEndcapTrueK_ = ibook.book1D("EndcapTrueK",
                                "Endcap True K P;P [GeV]",
                                meBarrelPIDp->getNbinsX(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapTrueK_, meEndcapTrueKAsPi);
  incrementME(meEndcapTrueK_, meEndcapTrueKAsK);
  incrementME(meEndcapTrueK_, meEndcapTrueKAsP);
  incrementME(meEndcapTrueK_, meEndcapTrueKNoPID);

  meBarrelTrueP_ = ibook.book1D("BarrelTrueP",
                                "Barrel True P P;P [GeV]",
                                meBarrelPIDp->getNbinsX(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelTrueP_, meBarrelTruePAsPi);
  incrementME(meBarrelTrueP_, meBarrelTruePAsK);
  incrementME(meBarrelTrueP_, meBarrelTruePAsP);
  incrementME(meBarrelTrueP_, meBarrelTruePNoPID);

  meEndcapTrueP_ = ibook.book1D("EndcapTrueP",
                                "Endcap True P P;P [GeV]",
                                meBarrelPIDp->getNbinsX(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapTrueP_, meEndcapTruePAsPi);
  incrementME(meEndcapTrueP_, meEndcapTruePAsK);
  incrementME(meEndcapTrueP_, meEndcapTruePAsP);
  incrementME(meEndcapTrueP_, meEndcapTruePNoPID);

  meBarrelPIDPiAsPiEff_ = ibook.book1D("BarrelPIDPiAsPiEff",
                                       "Barrel True pi as pi id. fraction VS P;P [GeV]",
                                       meBarrelPIDp->getNbinsX(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPiAsPiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePiAsPi, meBarrelTruePi_, meBarrelPIDPiAsPiEff_);

  meBarrelPIDPiAsKEff_ = ibook.book1D("BarrelPIDPiAsKEff",
                                      "Barrel True pi as k id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPiAsKEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePiAsK, meBarrelTruePi_, meBarrelPIDPiAsKEff_);

  meBarrelPIDPiAsPEff_ = ibook.book1D("BarrelPIDPiAsPEff",
                                      "Barrel True pi as p id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPiAsPEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePiAsP, meBarrelTruePi_, meBarrelPIDPiAsPEff_);

  meBarrelPIDPiNoPIDEff_ = ibook.book1D("BarrelPIDPiNoPIDEff",
                                        "Barrel True pi no PID id. fraction VS P;P [GeV]",
                                        meBarrelPIDp->getNbinsX(),
                                        meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                        meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPiNoPIDEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePiNoPID, meBarrelTruePi_, meBarrelPIDPiNoPIDEff_);

  meBarrelPIDKAsPiEff_ = ibook.book1D("BarrelPIDKAsPiEff",
                                      "Barrel True k as pi id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDKAsPiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTrueKAsPi, meBarrelTrueK_, meBarrelPIDKAsPiEff_);

  meBarrelPIDKAsKEff_ = ibook.book1D("BarrelPIDKAsKEff",
                                     "Barrel True k as k id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDKAsKEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTrueKAsK, meBarrelTrueK_, meBarrelPIDKAsKEff_);

  meBarrelPIDKAsPEff_ = ibook.book1D("BarrelPIDKAsPEff",
                                     "Barrel True k as p id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDKAsPEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTrueKAsP, meBarrelTrueK_, meBarrelPIDKAsPEff_);

  meBarrelPIDKNoPIDEff_ = ibook.book1D("BarrelPIDKNoPIDEff",
                                       "Barrel True k no PID id. fraction VS P;P [GeV]",
                                       meBarrelPIDp->getNbinsX(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDKNoPIDEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTrueKNoPID, meBarrelTrueK_, meBarrelPIDKNoPIDEff_);

  meBarrelPIDPAsPiEff_ = ibook.book1D("BarrelPIDPAsPiEff",
                                      "Barrel True p as pi id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPAsPiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePAsPi, meBarrelTrueP_, meBarrelPIDPAsPiEff_);

  meBarrelPIDPAsKEff_ = ibook.book1D("BarrelPIDPAsKEff",
                                     "Barrel True p as k id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPAsKEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePAsK, meBarrelTrueP_, meBarrelPIDPAsKEff_);

  meBarrelPIDPAsPEff_ = ibook.book1D("BarrelPIDPAsPEff",
                                     "Barrel True p as p id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPAsPEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePAsP, meBarrelTrueP_, meBarrelPIDPAsPEff_);

  meBarrelPIDPNoPIDEff_ = ibook.book1D("BarrelPIDPNoPIDEff",
                                       "Barrel True p no PID id. fraction VS P;P [GeV]",
                                       meBarrelPIDp->getNbinsX(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPIDPNoPIDEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePNoPID, meBarrelTrueP_, meBarrelPIDPNoPIDEff_);

  meEndcapPIDPiAsPiEff_ = ibook.book1D("EndcapPIDPiAsPiEff",
                                       "Endcap True pi as pi id. fraction VS P;P [GeV]",
                                       meBarrelPIDp->getNbinsX(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPiAsPiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePiAsPi, meEndcapTruePi_, meEndcapPIDPiAsPiEff_);

  meEndcapPIDPiAsKEff_ = ibook.book1D("EndcapPIDPiAsKEff",
                                      "Endcap True pi as k id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPiAsKEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePiAsK, meEndcapTruePi_, meEndcapPIDPiAsKEff_);

  meEndcapPIDPiAsPEff_ = ibook.book1D("EndcapPIDPiAsPEff",
                                      "Endcap True pi as p id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPiAsPEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePiAsP, meEndcapTruePi_, meEndcapPIDPiAsPEff_);

  meEndcapPIDPiNoPIDEff_ = ibook.book1D("EndcapPIDPiNoPIDEff",
                                        "Endcap True pi no PID id. fraction VS P;P [GeV]",
                                        meBarrelPIDp->getNbinsX(),
                                        meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                        meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPiNoPIDEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePiNoPID, meEndcapTruePi_, meEndcapPIDPiNoPIDEff_);

  meEndcapPIDKAsPiEff_ = ibook.book1D("EndcapPIDKAsPiEff",
                                      "Endcap True k as pi id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDKAsPiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTrueKAsPi, meEndcapTrueK_, meEndcapPIDKAsPiEff_);

  meEndcapPIDKAsKEff_ = ibook.book1D("EndcapPIDKAsKEff",
                                     "Endcap True k as k id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDKAsKEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTrueKAsK, meEndcapTrueK_, meEndcapPIDKAsKEff_);

  meEndcapPIDKAsPEff_ = ibook.book1D("EndcapPIDKAsPEff",
                                     "Endcap True k as p id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDKAsPEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTrueKAsP, meEndcapTrueK_, meEndcapPIDKAsPEff_);

  meEndcapPIDKNoPIDEff_ = ibook.book1D("EndcapPIDKNoPIDEff",
                                       "Endcap True k no PID id. fraction VS P;P [GeV]",
                                       meBarrelPIDp->getNbinsX(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDKNoPIDEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTrueKNoPID, meEndcapTrueK_, meEndcapPIDKNoPIDEff_);

  meEndcapPIDPAsPiEff_ = ibook.book1D("EndcapPIDPAsPiEff",
                                      "Endcap True p as pi id. fraction VS P;P [GeV]",
                                      meBarrelPIDp->getNbinsX(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                      meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPAsPiEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePAsPi, meEndcapTrueP_, meEndcapPIDPAsPiEff_);

  meEndcapPIDPAsKEff_ = ibook.book1D("EndcapPIDPAsKEff",
                                     "Endcap True p as k id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPAsKEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePAsK, meEndcapTrueP_, meEndcapPIDPAsKEff_);

  meEndcapPIDPAsPEff_ = ibook.book1D("EndcapPIDPAsPEff",
                                     "Endcap True p as p id. fraction VS P;P [GeV]",
                                     meBarrelPIDp->getNbinsX(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                     meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPAsPEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePAsP, meEndcapTrueP_, meEndcapPIDPAsPEff_);

  meEndcapPIDPNoPIDEff_ = ibook.book1D("EndcapPIDPNoPIDEff",
                                       "Endcap True p no PID id. fraction VS P;P [GeV]",
                                       meBarrelPIDp->getNbinsX(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                       meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPIDPNoPIDEff_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePNoPID, meEndcapTrueP_, meEndcapPIDPNoPIDEff_);

  meBarrelAsPi_ = ibook.book1D("BarrelAsPi",
                               "Barrel Identified Pi P;P [GeV]",
                               meBarrelPIDp->getNbinsX(),
                               meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                               meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelAsPi_, meBarrelTruePiAsPi);
  incrementME(meBarrelAsPi_, meBarrelTrueKAsPi);
  incrementME(meBarrelAsPi_, meBarrelTruePAsPi);

  meEndcapAsPi_ = ibook.book1D("EndcapAsPi",
                               "Endcap Identified Pi P;P [GeV]",
                               meBarrelPIDp->getNbinsX(),
                               meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                               meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapAsPi_, meEndcapTruePiAsPi);
  incrementME(meEndcapAsPi_, meEndcapTrueKAsPi);
  incrementME(meEndcapAsPi_, meEndcapTruePAsPi);

  meBarrelAsK_ = ibook.book1D("BarrelAsK",
                              "Barrel Identified K P;P [GeV]",
                              meBarrelPIDp->getNbinsX(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelAsK_, meBarrelTruePiAsK);
  incrementME(meBarrelAsK_, meBarrelTrueKAsK);
  incrementME(meBarrelAsK_, meBarrelTruePAsK);

  meEndcapAsK_ = ibook.book1D("EndcapAsK",
                              "Endcap Identified K P;P [GeV]",
                              meBarrelPIDp->getNbinsX(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapAsK_, meEndcapTruePiAsK);
  incrementME(meEndcapAsK_, meEndcapTrueKAsK);
  incrementME(meEndcapAsK_, meEndcapTruePAsK);

  meBarrelAsP_ = ibook.book1D("BarrelAsP",
                              "Barrel Identified P P;P [GeV]",
                              meBarrelPIDp->getNbinsX(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelAsP_, meBarrelTruePiAsP);
  incrementME(meBarrelAsP_, meBarrelTrueKAsP);
  incrementME(meBarrelAsP_, meBarrelTruePAsP);

  meEndcapAsP_ = ibook.book1D("EndcapAsP",
                              "Endcap Identified P P;P [GeV]",
                              meBarrelPIDp->getNbinsX(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                              meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapAsP_, meEndcapTruePiAsP);
  incrementME(meEndcapAsP_, meEndcapTrueKAsP);
  incrementME(meEndcapAsP_, meEndcapTruePAsP);

  meBarrelNoPID_ = ibook.book1D("BarrelNoPID",
                                "Barrel NoPID P;P [GeV]",
                                meBarrelPIDp->getNbinsX(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meBarrelNoPID_, meBarrelTruePiNoPID);
  incrementME(meBarrelNoPID_, meBarrelTrueKNoPID);
  incrementME(meBarrelNoPID_, meBarrelTruePNoPID);

  meEndcapNoPID_ = ibook.book1D("EndcapNoPID",
                                "Endcap NoPID P;P [GeV]",
                                meBarrelPIDp->getNbinsX(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  incrementME(meEndcapNoPID_, meEndcapTruePiNoPID);
  incrementME(meEndcapNoPID_, meEndcapTrueKNoPID);
  incrementME(meEndcapNoPID_, meEndcapTruePNoPID);

  meBarrelPiPurity_ = ibook.book1D("BarrelPiPurity",
                                   "Barrel pi id. fraction true pi VS P;P [GeV]",
                                   meBarrelPIDp->getNbinsX(),
                                   meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                   meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPiPurity_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePiAsPi, meBarrelAsPi_, meBarrelPiPurity_);

  meBarrelKPurity_ = ibook.book1D("BarrelKPurity",
                                  "Barrel k id. fraction true k VS P;P [GeV]",
                                  meBarrelPIDp->getNbinsX(),
                                  meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                  meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelKPurity_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTrueKAsK, meBarrelAsK_, meBarrelKPurity_);

  meBarrelPPurity_ = ibook.book1D("BarrelPPurity",
                                  "Barrel p id. fraction true p VS P;P [GeV]",
                                  meBarrelPIDp->getNbinsX(),
                                  meBarrelPIDp->getTH1()->GetXaxis()->GetXmin(),
                                  meBarrelPIDp->getTH1()->GetXaxis()->GetXmax());
  meBarrelPPurity_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meBarrelTruePAsP, meBarrelAsP_, meBarrelPPurity_);

  meEndcapPiPurity_ = ibook.book1D("EndcapPiPurity",
                                   "Endcap pi id. fraction true pi VS P;P [GeV]",
                                   meEndcapPIDp->getNbinsX(),
                                   meEndcapPIDp->getTH1()->GetXaxis()->GetXmin(),
                                   meEndcapPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPiPurity_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePiAsPi, meEndcapAsPi_, meEndcapPiPurity_);

  meEndcapKPurity_ = ibook.book1D("EndcapKPurity",
                                  "Endcap k id. fraction true k VS P;P [GeV]",
                                  meEndcapPIDp->getNbinsX(),
                                  meEndcapPIDp->getTH1()->GetXaxis()->GetXmin(),
                                  meEndcapPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapKPurity_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTrueKAsK, meEndcapAsK_, meEndcapKPurity_);

  meEndcapPPurity_ = ibook.book1D("EndcapPPurity",
                                  "Endcap p id. fraction true p VS P;P [GeV]",
                                  meEndcapPIDp->getNbinsX(),
                                  meEndcapPIDp->getTH1()->GetXaxis()->GetXmin(),
                                  meEndcapPIDp->getTH1()->GetXaxis()->GetXmax());
  meEndcapPPurity_->getTH1()->SetMinimum(0.);
  computeEfficiency1D(meEndcapTruePAsP, meEndcapAsP_, meEndcapPPurity_);
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ----------
void MtdTracksHarvester::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;

  desc.add<std::string>("folder", "MTD/Tracks/");

  descriptions.add("MtdTracksPostProcessor", desc);
}

DEFINE_FWK_MODULE(MtdTracksHarvester);
