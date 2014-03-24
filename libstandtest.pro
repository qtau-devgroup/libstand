#-------------------------------------------------
# http://github.com/qtau-devgroup/libstand
#-------------------------------------------------
include(libstandcore.pro)

QT += testlib core
QT -= gui

CONFIG += console
CONFIG += test

LIBS += \
    -lgmock \
    -lgtest

TARGET   = $$qtLibraryTarget(standtest)

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
    test/helper/MockResourceRepository.h \
    test/corpus/UtauPhonemeConverterTest.h \
    test/helper/MockResourceFactory.h \
    test/corpus/PhonemeSelectorTest.h \
    test/corpus/WaveformCorpusTest.h \
    test/corpus/json/QJsonCorpusMetaTest.h \
    test/corpus/json/QJsonPhonemeTest.h \
    test/corpus/json/QJsonPhonemeRepositoryTest.h \
    test/corpus/json/QJsonNotePhonemeMapperTest.h \
    test/util/SoundfileDeviceTest.h

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

#--------------------------------------------
CONFIG(debug, debug|release) {
    COMPILEDIR = $${OUT_PWD}/../../../debug
} else {
    COMPILEDIR = $${OUT_PWD}/../../../release
}

DESTDIR         = $${COMPILEDIR}/libstand/.tests
OBJECTS_DIR     = $${COMPILEDIR}/libstand/.obj
MOC_DIR         = $${COMPILEDIR}/libstand/.moc
RCC_DIR         = $${COMPILEDIR}/libstand/.rcc
UI_DIR          = $${COMPILEDIR}/libstand/.ui
#--------------------------------------------

