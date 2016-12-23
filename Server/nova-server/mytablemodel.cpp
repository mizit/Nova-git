#include "mytablemodel.h"


MyTableModel::MyTableModel()
{
    row_num = 0;
    shipSocketNum = 4;
}

int MyTableModel::rowCount(const QModelIndex &parent) const
{
    return (ship_list.size() * shipSocketNum);
}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if ((role == Qt::DisplayRole) && (ship_list.size() > 0))
    {
        //QString unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
        // строкой выше мы формируем ответ. QString::number преобразует число в текст
        QString answer = QString("");
        CShip *ship = ship_list[(int)(index.row() / shipSocketNum)];
        switch ((index.row() % shipSocketNum))
        {
        case 0:
            if (index.column() == 0)
            {
                answer = ship->login;
            }
            if (index.column() == 1)
            {
                answer = QString("Pilot");
            }
            if (index.column() == 2)
            {
                if (ship->pilotSocket >= 0)
                {
                    answer = QString("Connect");
                }
                else
                {
                    answer = QString("Disconnect");
                }
            }
            break;
        case 1:
            if (index.column() == 1)
            {
                answer = QString("Navigation");
            }
            if (index.column() == 2)
            {
                if (ship->navSocket >= 0)
                {
                    answer = QString("Connect");
                }
                else
                {
                    answer = QString("Disconnect");
                }
            }
            break;
        case 2:
            if (index.column() == 1)
            {
                answer = QString("Engineer");
            }
            if (index.column() == 2)
            {
                if (ship->engSocket >= 0)
                {
                    answer = QString("Connect");
                }
                else
                {
                    answer = QString("Disconnect");
                }
            }
            break;
        case 3:
            if (index.column() == 1)
            {
                answer = QString("Gunner");
            }
            if (index.column() == 2)
            {
                if (ship->batSocket >= 0)
                {
                    answer = QString("Connect");
                }
                else
                {
                    answer = QString("Disconnect");
                }
            }
            break;
        }
        return QVariant(answer);

    }
    return QVariant();
}

void MyTableModel::add_ship(CShip* ship)
{
    beginResetModel();
    ship_list << ship;
    row_num += shipSocketNum;
    endResetModel();
}


void MyTableModel::StartChange()
{
    beginResetModel();
}

void MyTableModel::EndChange()
{
    endResetModel();
}
