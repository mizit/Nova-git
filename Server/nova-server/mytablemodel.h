#ifndef MYTABLEMODE_H
#define MYTABLEMODE_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QAbstractTableModel>
#include <ship.h>
#include <QList>

class MyTableModel : public QAbstractTableModel
{
public:
    MyTableModel();
    void StartChange();
    void EndChange();
private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    int row_num;
    int shipSocketNum;
public:
    void add_ship (CShip*);
    QList <CShip*> ship_list;
};

#endif // MYTABLEMODE_H
