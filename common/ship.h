#ifndef SHIP_H
#define SHIP_H

#include <QObject>
#include <QSet>


class Ship : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint8 length READ getLength() NOTIFY lengthChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QSet<quint16> positions READ getPositions WRITE setPositions NOTIFY positionsChanged)
public:
    Ship(QObject* parent = 0);
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
signals:
    void lengthChanged();
    void nameChanged();
    void positionsChanged();
};

#endif // SHIP_H
