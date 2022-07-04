import FWCore.ParameterSet.Config as cms

# AlCaReco for track based calibration using MinBias events
OutALCARECOSiStripCalMinBiasAAG_noDrop = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOSiStripCalMinBiasAAG')
    ),
    outputCommands = cms.untracked.vstring( 
        'keep *_ALCARECOSiStripCalMinBiasAAG_*_*', 
        'keep *_siStripClusters_*_*', 
        'keep *_siPixelClusters_*_*',
        'keep DetIdedmEDCollection_siStripDigis_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep LumiScalerss_scalersRawToDigi_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_TriggerResults_*_*')
)

# in Run3, SCAL digis replaced by onlineMetaDataDigis
import copy
_run3_common_removedCommands = OutALCARECOSiStripCalMinBiasAAG_noDrop.outputCommands.copy()
_run3_common_removedCommands.remove('keep LumiScalerss_scalersRawToDigi_*_*')
_run3_common_removedCommands.remove('keep DcsStatuss_scalersRawToDigi_*_*')

_run3_common_extraCommands = ['keep DCSRecord_onlineMetaDataDigis_*_*',
                              'keep OnlineLuminosityRecord_onlineMetaDataDigis_*_*']

from Configuration.Eras.Modifier_run3_common_cff import run3_common
run3_common.toModify(OutALCARECOSiStripCalMinBiasAAG_noDrop, outputCommands = _run3_common_removedCommands + _run3_common_extraCommands)

OutALCARECOSiStripCalMinBiasAAG=OutALCARECOSiStripCalMinBiasAAG_noDrop.clone()
OutALCARECOSiStripCalMinBiasAAG.outputCommands.insert(0,"drop *")
