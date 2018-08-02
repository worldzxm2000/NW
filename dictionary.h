#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <QObject>
#include<QMap>
class Dictionary
{
public:
    Dictionary();
    QString Find(QString key);
protected:
   QMap<QString,QString> map;
};

#endif // DICTIONARY_H
