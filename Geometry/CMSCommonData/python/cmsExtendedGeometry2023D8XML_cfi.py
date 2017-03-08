import FWCore.ParameterSet.Config as cms

# This config was generated automatically using generate2023Geometry.py
# If you notice a mistake, please update the generating script, not just this config

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring(
        'Geometry/CMSCommonData/data/materials.xml',
        'Geometry/CMSCommonData/data/rotations.xml',
        'Geometry/CMSCommonData/data/extend/cmsextent.xml',
        'Geometry/CMSCommonData/data/PostLS2/cms.xml',
        'Geometry/CMSCommonData/data/eta3/etaMax.xml',
        'Geometry/CMSCommonData/data/cmsMother.xml',
        'Geometry/CMSCommonData/data/cmsTracker.xml',
        'Geometry/CMSCommonData/data/PhaseII/caloBase.xml',
        'Geometry/CMSCommonData/data/cmsCalo.xml',
        'Geometry/CMSCommonData/data/PhaseII/muonBase.xml',
        'Geometry/CMSCommonData/data/cmsMuon.xml',
        'Geometry/CMSCommonData/data/mgnt.xml',
        'Geometry/CMSCommonData/data/PostLS2/beampipe.xml',
        'Geometry/CMSCommonData/data/PostLS2/cmsBeam.xml',
        'Geometry/CMSCommonData/data/muonMB.xml',
        'Geometry/CMSCommonData/data/muonMagnet.xml',
        'Geometry/CMSCommonData/data/cavern.xml',
        'Geometry/TrackerCommonData/data/PhaseII/trackerParameters.xml',
        'Geometry/TrackerCommonData/data/pixfwdCommon.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/pixfwd.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/pixbar.xml',
        'Geometry/TrackerCommonData/data/trackermaterial.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/tracker.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/pixel.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/trackerbar.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/trackerfwd.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/trackerStructureTopology.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker4026/pixelStructureTopology.xml',
        'Geometry/TrackerSimData/data/PhaseII/TiltedTracker4026/trackersens.xml',
        'Geometry/TrackerSimData/data/PhaseII/TiltedTracker4026/pixelsens.xml',
        'Geometry/TrackerRecoData/data/PhaseII/TiltedTracker4026/trackerRecoMaterial.xml',
        'Geometry/TrackerSimData/data/PhaseII/TiltedTracker4026/trackerProdCuts.xml',
        'Geometry/TrackerSimData/data/PhaseII/TiltedTracker4026/pixelProdCuts.xml',
        'Geometry/TrackerSimData/data/trackerProdCutsBEAM.xml',
        'Geometry/EcalCommonData/data/ectkcable.xml',
        'Geometry/EcalCommonData/data/PhaseII/eregalgo.xml',
        'Geometry/EcalCommonData/data/ebalgo.xml',
        'Geometry/EcalCommonData/data/ebcon.xml',
        'Geometry/EcalCommonData/data/ebrot.xml',
        'Geometry/EcalCommonData/data/eecon.xml',
        'Geometry/EcalCommonData/data/PhaseII/escon.xml',
        'Geometry/EcalCommonData/data/PhaseII/esalgo.xml',
        'Geometry/HcalCommonData/data/hcalrotations.xml',
        'Geometry/HcalCommonData/data/PhaseII/HGCal/hcalalgo.xml',
        'Geometry/HcalCommonData/data/hcalbarrelalgo.xml',
        'Geometry/HcalCommonData/data/PhaseII/HGCal/hcalendcapalgo.xml',
        'Geometry/HcalCommonData/data/hcalouteralgo.xml',
        'Geometry/HcalCommonData/data/hcalforwardalgo.xml',
        'Geometry/HcalCommonData/data/PhaseII/hcalSimNumbering.xml',
        'Geometry/HcalCommonData/data/PhaseII/hcalRecNumberingRebuild.xml',
        'Geometry/HcalCommonData/data/average/hcalforwardmaterial.xml',
        'Geometry/HGCalCommonData/data/v7/hgcal.xml',
        'Geometry/HGCalCommonData/data/v7/hgcalEE.xml',
        'Geometry/HGCalCommonData/data/v7/hgcalHEsil.xml',
        'Geometry/HGCalCommonData/data/v7/hgcalwafer.xml',
        'Geometry/HGCalCommonData/data/v7/hgcalCons.xml',
        'Geometry/MuonCommonData/data/v1/mbCommon.xml',
        'Geometry/MuonCommonData/data/v1/mb1.xml',
        'Geometry/MuonCommonData/data/v1/mb2.xml',
        'Geometry/MuonCommonData/data/v1/mb3.xml',
        'Geometry/MuonCommonData/data/v1/mb4.xml',
        'Geometry/MuonCommonData/data/design/muonYoke.xml',
        'Geometry/MuonCommonData/data/PhaseII/mf.xml',
        'Geometry/MuonCommonData/data/PhaseII/rpcf.xml',
        'Geometry/MuonCommonData/data/PhaseII/gemf.xml',
        'Geometry/MuonCommonData/data/PhaseII/TDR_BaseLine/gem11.xml',
        'Geometry/MuonCommonData/data/PhaseII/TDR_BaseLine/gem21.xml',
        'Geometry/MuonCommonData/data/v2/csc.xml',
        'Geometry/MuonCommonData/data/PhaseII/mfshield.xml',
        'Geometry/MuonCommonData/data/PhaseII/TDR_BaseLine/me0.xml',
        'Geometry/ForwardCommonData/data/forwardshield/2015/v1/forwardshield.xml',
        'Geometry/ForwardCommonData/data/brmrotations.xml',
        'Geometry/ForwardCommonData/data/PostLS2/brm.xml',
        'Geometry/ForwardCommonData/data/zdcmaterials.xml',
        'Geometry/ForwardCommonData/data/lumimaterials.xml',
        'Geometry/ForwardCommonData/data/zdcrotations.xml',
        'Geometry/ForwardCommonData/data/lumirotations.xml',
        'Geometry/ForwardCommonData/data/zdc.xml',
        'Geometry/ForwardCommonData/data/zdclumi.xml',
        'Geometry/ForwardCommonData/data/cmszdc.xml',
        'Geometry/HGCalCommonData/data/fastTimingBarrel.xml',
        'Geometry/HGCalCommonData/data/fastTimingEndcap.xml',
        'Geometry/HGCalCommonData/data/fastTimingElement.xml',
    )+
    cms.vstring(
        'Geometry/MuonCommonData/data/PhaseII/TDR_BaseLine/muonNumbering.xml',
        'Geometry/EcalSimData/data/PhaseII/ecalsens.xml',
        'Geometry/HcalCommonData/data/PhaseII/HGCal/hcalsenspmf.xml',
        'Geometry/HcalSimData/data/hf.xml',
        'Geometry/HcalSimData/data/hfpmt.xml',
        'Geometry/HcalSimData/data/hffibrebundle.xml',
        'Geometry/HcalSimData/data/CaloUtil.xml',
        'Geometry/HGCalSimData/data/hgcsensv6.xml',
        'Geometry/HGCalSimData/data/hgccons.xml',
        'Geometry/HGCalSimData/data/hgcProdCuts.xml',
        'Geometry/MuonSimData/data/PhaseII/ME0EtaPart/muonSens.xml',
        'Geometry/DTGeometryBuilder/data/dtSpecsFilter.xml',
        'Geometry/CSCGeometryBuilder/data/cscSpecsFilter.xml',
        'Geometry/CSCGeometryBuilder/data/cscSpecs.xml',
        'Geometry/RPCGeometryBuilder/data/PhaseII/RPCSpecs.xml',
        'Geometry/GEMGeometryBuilder/data/v7/GEMSpecsFilter.xml',
        'Geometry/GEMGeometryBuilder/data/v7/GEMSpecs.xml',
        'Geometry/ForwardCommonData/data/brmsens.xml',
        'Geometry/ForwardSimData/data/zdcsens.xml',
        'Geometry/HGCalSimData/data/fasttimesens.xml',
        'Geometry/HcalSimData/data/HcalProdCuts.xml',
        'Geometry/EcalSimData/data/EcalProdCuts.xml',
        'Geometry/MuonSimData/data/PhaseII/muonProdCuts.xml',
        'Geometry/ForwardSimData/data/zdcProdCuts.xml',
        'Geometry/ForwardSimData/data/ForwardShieldProdCuts.xml',
        'Geometry/HGCalSimData/data/fasttimeProdCuts.xml',
        'Geometry/CMSCommonData/data/FieldParameters.xml',
    ),
    rootNodeName = cms.string('cms:OCMS')
)
