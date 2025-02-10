#include "parser.h"

QVariant Parser::jsonValue(const QJsonObject &json, const QString &path)
{
    QList <QString> list = path.split('.');
    QJsonObject object = json;

    for (int i = 0; i < list.count(); i++)
    {
        QString key = list.at(i);
        int index = -1;

        if (key.endsWith(']'))
        {
            int position = key.indexOf('[');
            index = key.mid(position + 1, key.length() - position - 2).toInt();
            key = key.mid(0, position);
        }

        if (!object.contains(key))
            break;

        if (i < list.length() - 1)
        {
            object = index < 0 ? object.value(key).toObject() : object.value(key).toArray().at(index).toObject();
            continue;
        }

        return index < 0 ? object.value(key).toVariant() : object.value(key).toArray().at(index).toVariant();
    }

    return QVariant();
}

QVariant Parser::stringValue(const QString &string)
{
    bool check;
    double value = string.toDouble(&check);

    if (check)
        return value;

    if (string != "true" && string != "false")
        return string;

    return string == "true" ? true : false;
}
