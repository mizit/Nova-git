#ifndef CITEM_H
#define CITEM_H

#include <QString>
#include <QPoint>
#include <QList>

//тип - 4 бита
#define IT_TUBE     0x01
#define IT_POWER    0x02
#define IT_NAV      0x03
#define IT_ENGINE   0x04
#define IT_WEAPON   0x05
#define IT_LSYS     0x06
#define IT_ELEM1    0x07
#define IT_ELEM2    0x08
#define IT_ELEM3    0x09
#define IT_ELEM4    0x0A
#define IT_ELEM5    0x0B
#define IT_COMM     0x0C
//размер - 4 бита
//энергия - 1 байт

//Выходы - 4,5 байт
#define LEFT    1
#define UP      2
#define RIGHT   4
#define DOWN    8

#define TUBE_STRAIGHT   "obj_tube_straight"
#define TUBE_CORNER     "obj_tube_corner"
#define TUBE_TEE        "obj_tube_tee"
#define TUBE_SPLITTER   "obj_tube_splitter"
#define MONEY_CASE      "obj_money_case"

#define ITEM_SET    0x01
#define ITEM_GET    0x02
#define ITEM_ADD    0x03
#define ITEM_DROP   0x04
#define ITEM_PICKUP 0x05
#define ITEM_NUM    0x10
#define ITEM_ID     0x20

class CItem
{
public:
    CItem();
public:
    qint64 id;
    QString owner;
    QPoint pos;
    int image_angle;
    QString type;
    int hp;
    int power;
    int big_list_postion;
    int small_list_position;
};

class CIdGen
{
    //Генерируем на основе типа, размера, энергопотребления и выходов
public:
    CIdGen();
    quint64 IdGen(quint8 type, quint8 power);
    quint64 outputs(quint8 x, quint8 y, quint8 out);
    CItem* createItem(QString type, quint8 it = 0);
public:
    QList <CItem*> item_list;
    QList <quint16> free_num;
};

#endif // CITEM_H
