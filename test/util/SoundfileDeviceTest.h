/* SoundfileDeviceTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef SOUNDFILEDEVICETEST_H
#define SOUNDFILEDEVICETEST_H

#include <QTest>
#include <QBuffer>
#include "util/SoundfileDevice.h"

#include "AutoTest.h"

namespace stand
{

class SoundfileDeviceTest : public QObject
{
    Q_OBJECT
private slots:
    void write_and_read_properly_in()
    {
        int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

        QList<Signal> signalList;
        Signal signal(22050);
        for(int i = 0; i < signal.size(); i++)
        {
            signal[i] = (i % 256) / 512.0;
        }
        signalList.append(signal);
        signalList.append(signal);

        QSharedPointer<QBuffer> buffer = QSharedPointer<QBuffer>(new QBuffer());

        QCOMPARE(SoundfileDevice().write(signalList, format, buffer), true);

        auto actual = (SoundfileDevice().read(buffer));
        QCOMPARE(actual, signalList);
        for(int i = 0; i < actual.size(); i++)
        {
            QCOMPARE(actual[i].samplingFrequency(), signalList[i].samplingFrequency());
        }
    }
};

}

DECLARE_TEST(stand::SoundfileDeviceTest)

#endif // SOUNDFILEDEVICETEST_H
