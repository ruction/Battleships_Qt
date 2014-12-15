#ifndef SHIP_H
#define SHIP_H

#include <QString>
#include <QSet>


class Ship {
public:
    Ship(quint8 length);
    Ship(quint8 length, QString name);
    quint8 getLength() const;
    QString getName() const;
    QSet<quint16> getPositions() const;
    void setPositions(QSet<quint16> positions);
private:
    quint8 length;              // Ship length
    QString name;               // Ship name
    QSet<quint16> positions;    // List with indexes of the ship position
};

#endif // SHIP_H