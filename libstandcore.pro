#-------------------------------------------------
# http://github.com/qtau-devgroup/libstand
#-------------------------------------------------
QT -= gui

CONFIG += console
CONFIG -= app_bundle
TARGET = $$qtLibraryTarget(stand)

TEMPLATE = lib

LIBS += -lsndfile

HEADERS += \
    core/utau/UtauPhoneme.h \
    core/utau/UtauOtoHash.h \
    core/util/MusicalNote.h \
    core/synthesis/FrameRenderer.h \
    core/synthesis/FrameSynthesizer.h \
    core/synthesis/Synthesis.h \
    core/util/ResourceRepository.h \
    core/corpus/Phoneme.h \
    core/dsp/Decimator.h \
    core/dsp/DioF0Estimator.h \
    core/dsp/F0Estimator.h \
    core/dsp/FftSg.h \
    core/dsp/MinimumPhase.h \
    core/dsp/PlatinumResidualCalculator.h \
    core/dsp/StarSpectrumEstimator.h \
    core/dsp/SynchronousSpectrumEstimator.h \
    core/dsp/WindowFunctions.h \
    core/dsp/helpers/DioHelper.h \
    core/dsp/Signal.h \
    core/synthesis/world/WorldFrame.h \
    core/synthesis/world/WorldFrameRepository.h \
    core/synthesis/world/WorldWaveform.h \
    core/synthesis/world/WorldWaveformRepository.h \
    core/synthesis/world/WorldFrameSynthesizer.h \
    core/synthesis/FrameProvider.h \
    core/synthesis/world/WorldWaveformFactory.h \
    core/dsp/BlockingEstimator.h \
    core/synthesis/world/WorldFrameProvider.h \
    core/synthesis/world/WorldSynthesizer.h \
    core/dsp/Contour.h \
    core/dsp/ContourSerializer.h \
    core/dsp/PlatinumPeakEstimator.h \
    core/dsp/helpers/DoDelete.h \
    core/synthesis/world/WorldKeyListFrameProvider.h \
    core/synthesis/world/WorldFrameAnalyzer.h \
    core/util/SoundfileDevice.h \
    core/utau/UtauCharacterInfo.h \
    core/utau/UtauPrefixMap.h \
    core/dsp/WaveFileSignalFactory.h \
    core/corpus/PhonemeKey.h \
    core/utau/UtauVoicebank.h \
    core/corpus/PhonemeSelector.h \
    core/corpus/WaveformFrameInfo.h \
    core/corpus/WaveformFrameInfoList.h \
    core/corpus/PhonemeRepository.h \
    core/corpus/NotePhonemeMapper.h \
    core/corpus/WaveformCorpusBuilder.h \
    core/corpus/WaveformCorpus.h \
    core/corpus/CorpusMeta.h \
    core/corpus/UtauPhonemeConverter.h \
    core/util/JsonSerializer.h \
    core/corpus/json/QJsonCorpusMeta.h \
    core/corpus/json/QJsonPhoneme.h \
    core/corpus/json/QJsonPhonemeRepository.h \
    core/corpus/json/QJsonWaveformCorpus.h \
    core/corpus/json/QJsonNotePhonemeMapper.h \
    core/corpus/UtauCharacterInfoConverter.h \
    core/corpus/UtauWaveformCorpusBuilder.h

SOURCES += \
    core/utau/UtauPhoneme.cpp \
    core/utau/UtauOtoHash.cpp \
    core/util/MusicalNote.cpp \
    core/synthesis/FrameRenderer.cpp \
    core/synthesis/FrameSynthesizer.cpp \
    core/synthesis/Synthesis.cpp \
    core/util/ResourceRepository.cpp \
    core/corpus/Phoneme.cpp \
    core/dsp/Decimator.cpp \
    core/dsp/DioF0Estimator.cpp \
    core/dsp/F0Estimator.cpp \
    core/dsp/FftSg.cpp \
    core/dsp/MinimumPhase.cpp \
    core/dsp/PlatinumResidualCalculator.cpp \
    core/dsp/StarSpectrumEstimator.cpp \
    core/dsp/SynchronousSpectrumEstimator.cpp \
    core/dsp/WindowFunctions.cpp \
    core/dsp/Signal.cpp \
    core/synthesis/world/WorldFrame.cpp \
    core/synthesis/world/WorldFrameRepository.cpp \
    core/synthesis/world/WorldWaveform.cpp \
    core/synthesis/world/WorldWaveformRepository.cpp \
    core/synthesis/world/WorldFrameSynthesizer.cpp \
    core/synthesis/FrameProvider.cpp \
    core/synthesis/world/WorldWaveformFactory.cpp \
    core/dsp/BlockingEstimator.cpp \
    core/synthesis/world/WorldFrameProvider.cpp \
    core/synthesis/world/WorldSynthesizer.cpp \
    core/dsp/Contour.cpp \
    core/dsp/ContourSerializer.cpp \
    core/dsp/PlatinumPeakEstimator.cpp \
    core/synthesis/world/WorldKeyListFrameProvider.cpp \
    core/synthesis/world/WorldFrameAnalyzer.cpp \
    core/util/SoundfileDevice.cpp \
    core/utau/UtauCharacterInfo.cpp \
    core/utau/UtauPrefixMap.cpp \
    core/dsp/WaveFileSignalFactory.cpp \
    core/corpus/PhonemeKey.cpp \
    core/utau/UtauVoicebank.cpp \
    core/corpus/PhonemeSelector.cpp \
    core/corpus/WaveformFrameInfo.cpp \
    core/corpus/WaveformFrameInfoList.cpp \
    core/corpus/PhonemeRepository.cpp \
    core/corpus/NotePhonemeMapper.cpp \
    core/corpus/WaveformCorpusBuilder.cpp \
    core/corpus/WaveformCorpus.cpp \
    core/corpus/CorpusMeta.cpp \
    core/corpus/UtauPhonemeConverter.cpp \
    core/util/JsonSerializer.cpp \
    core/corpus/json/QJsonCorpusMeta.cpp \
    core/corpus/json/QJsonPhoneme.cpp \
    core/corpus/json/QJsonPhonemeRepository.cpp \
    core/corpus/json/QJsonWaveformCorpus.cpp \
    core/corpus/json/QJsonNotePhonemeMapper.cpp \
    core/corpus/UtauCharacterInfoConverter.cpp \
    core/corpus/UtauWaveformCorpusBuilder.cpp

INCLUDEPATH += \
    core

QMAKE_CXXFLAGS += -Wall -std=c++11

#--------------------------------------------
CONFIG(debug, debug|release) {
    COMPILEDIR = $${OUT_PWD}/../../../debug
} else {
    COMPILEDIR = $${OUT_PWD}/../../../release
}

DESTDIR         = $${COMPILEDIR}/libstand/
OBJECTS_DIR     = $${COMPILEDIR}/libstand/.obj
MOC_DIR         = $${COMPILEDIR}/libstand/.moc
RCC_DIR         = $${COMPILEDIR}/libstand/.rcc
UI_DIR          = $${COMPILEDIR}/libstand/.ui
#--------------------------------------------

