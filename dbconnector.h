#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>

class DBConnector : public QObject
{
    Q_OBJECT
public:
    explicit DBConnector(QObject *parent = nullptr);

signals:

};

#endif // DBCONNECTOR_H
