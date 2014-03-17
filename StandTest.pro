include(StandCore.pro)

QT += testlib core
QT -= gui

CONFIG += console
CONFIG += test

LIBS += -lgmock

TEMPLATE = app

HEADERS += \
    test/AutoTest.h \
    test/utau/UtauOtoHashTest.h \
    test/util/MusicalNoteTest.h \
    test/dsp/DecimatorTest.h \
    test/dsp/DioF0EstimatorTest.h \
    test/dsp/FftTest.h \
    test/dsp/MinimumPhaseTest.h \
    test/dsp/PlatinumResidualCalculatorTest.h \
    test/dsp/StarSpectrumEstimatorTest.h \
    test/dsp/world/common.h \
    test/dsp/world/constant_numbers.h \
    test/dsp/world/dio.h \
    test/dsp/world/fft.h \
    test/dsp/world/matlabfunctions.h \
    test/dsp/world/platinum.h \
    test/dsp/world/star.h \
    test/dsp/world/synthesis_ap.h \
    test/dsp/world/tandem_ap.h \
    test/dsp/world/world_synthesis.h \
    test/dsp/helpers/WorldDecimator.h \
    test/synthesis/SimpleRendererTest.h \
    test/synthesis/world/WorldFrameProviderTest.h \
    test/synthesis/world/WorldFrameRepositoryTest.h \
    test/synthesis/world/WorldFrameAnalyzerTest.h \
    test/synthesis/world/WorldFrameSynthesizerTest.h \
    test/synthesis/world/WorldWaveformFactoryTest.h \
    test/utau/UtauCharacterInfoTest.h \
    test/utau/UtauPrefixMapTest.h \
    test/corpus/WaveformFrameInfoRepositoryTest.h \
    test/helper/MockResourceRepository.h \
    test/corpus/UtauPhonemeConverterTest.h \
    test/helper/MockResourceFactory.h \
    test/corpus/PhonemeSelectorTest.h \
    test/corpus/WaveformCorpusTest.h

SOURCES += \
    test/main.cpp \
    test/AutoTest.cpp \
    test/dsp/world/common.cpp \
    test/dsp/world/dio.cpp \
    test/dsp/world/fft.cpp \
    test/dsp/world/matlabfunctions.cpp \
    test/dsp/world/platinum.cpp \
    test/dsp/world/star.cpp \
    test/dsp/world/synthesis_ap.cpp \
    test/dsp/world/tandem_ap.cpp \
    test/dsp/world/world_synthesis.cpp \
    test/dsp/helpers/WorldDecimator.cpp

INCLUDEPATH += \
    core \
    test

QMAKE_CXXFLAGS += -Wall -std=c++11
