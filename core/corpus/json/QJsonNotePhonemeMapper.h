/* QJsonNotePhonemeMapper.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONNOTEPHONEMEMAPPER_H
#define QJSONNOTEPHONEMEMAPPER_H

#include <QJsonValue>
#include <QSharedPointer>

namespace stand
{
class NotePhonemeMappingItem;
class NotePhonemeMapper;

QJsonValue operator <<(QJsonValue &left, const NotePhonemeMappingItem &right);
QSharedPointer<NotePhonemeMappingItem> operator >>(const QJsonValue &left, QSharedPointer<NotePhonemeMappingItem> &right);

QJsonValue operator <<(QJsonValue &left, const NotePhonemeMapper &right);
QSharedPointer<NotePhonemeMapper> operator >>(const QJsonValue &left, QSharedPointer<NotePhonemeMapper> &right);

}

#endif // QJSONNOTEPHONEMEMAPPER_H
