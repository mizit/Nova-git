#include "citem.h"

CItem::CItem()
{
    id = 0;
    owner = "space";
    pos.setX(0);
    pos.setY(0);
    image_angle = 0;
    type = "noone";
    hp = 100;
    power = 100;
}

CIdGen::CIdGen()
{
    for (quint16 i = 0; i < 4096; i++)
    {
        free_num.append(i);
    }
}

quint64 CIdGen::outputs(quint8 x, quint8 y, quint8 out)
{
    return ((out << y) << x * 3);
}

quint64 CIdGen::IdGen(quint8 type, quint8 power)
{
    if (type > 0x0F)
    {
        return 0;
    }
    quint16 num = free_num[0];
    free_num.removeFirst();
    return ((quint64)type << 60) + ((quint64)power << 48) + num;
}

CItem* CIdGen::createItem(QString type, quint8 it)
{
    CItem* item;
    item = new CItem();
    item->id = IdGen(it, 0);
    item->type = type;
    item_list.append(item);
    return item;
}

CItem* CIdGen::createItem(QString type, quint64 id)
{
    CItem* item;
    item = new CItem();
    item->id = id;
    item->type = type;
    item_list.append(item);
    bool test = false;
    for (int i = 0; i < free_num.size(); i++)
    {
        if (free_num[i] == id)
        {
            free_num.removeAt(i);
            test = true;
            break;
        }
    }
    if (!test)
    {
        item->id = IdGen(0, 0);
    }
    return item;
}
