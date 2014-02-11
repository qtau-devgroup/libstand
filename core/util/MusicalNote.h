/* MusicalNote.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef MUSICALNOTE_H
#define MUSICALNOTE_H

#include <QString>

namespace stand
{

/**
 * @brief MusicalNote namespace contains a utility function for musical notes.
 * @author Hal@shurabaP
 */
namespace MusicalNote
{
const static double DefaultA4Frequency = 440.0;
const static double DefaultA4Note = 69.0;

/**
 * @brief noteFromFrequency calculates a note number of the given frequency.
 * @param frequency
 * @param A4Frequency is a frequency of A4 note.
 * @return a note number for frequency.
 */
double noteFromFrequency(double frequency, double A4Frequency = DefaultA4Frequency);

/**
 * @brief frequencyFromNote calculates a frequency of the given note number.
 * @param note is a note number.
 * @param A4Frequency is a frequency of A4 note.
 * @return frequency for a note number.
 */
double frequencyFromNote(double note, double A4Frequency = DefaultA4Frequency);

/**
 * @brief noteNumber returns note number from note name, such as `C4`, `B2`, `A#5`
 * @note Sharp is available but flat is not.
 * @param name is a note name.
 * @return note number.
 */
int noteNumber(const QString &name);

/**
 * @brief noteName returns note name from note number.
 * @note note number should be between 0 to 127.
 * @param noteNumber
 * @return note name.
 */
const QString &noteName(int noteNumber);

}

}

#endif // MUSICALNOTE_H
