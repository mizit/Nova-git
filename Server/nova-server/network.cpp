#include <network.h>

MyServer::MyServer()
{

}

void MyServer::incomingConnection(qintptr des)
{
    MySocket *soc;
    soc = new MySocket;
    soc->setSocketDescriptor(des);
    addPendingConnection(soc);
}


MySocket::MySocket()
{
    pt_type = 0;
    descriptor = 0;
}

qint64 MySocket::MyWrite(char* data, quint64 maxSize)
{
    data[0] = (maxSize & 0xFF);
    data[1] = (maxSize & 0xFF00) << 8;
    return write(data, maxSize + 2);
}

void MySocket::LogAddString(QString str)
{
    QStandardItem *item;
    item = new QStandardItem();
    item->setText(str);
    log_model->appendRow(item);
    log->scrollToBottom();
}

//WORK WITH RAW DATA
QString GetString(char *str, int pos)
{
    QString ans = QString("");
    while (str[pos] != 0)
    {
        ans += QString("%1").arg(str[pos]);
        pos++;
    }
    return ans;
}

qint32 GetInt32(unsigned char *str, int pos)
{
    qint32 ans = 0;
    ans = (str[pos + 3] << 24) + (str[pos + 2] << 16) + (str[pos + 1] << 8) + str[pos];
    return ans;
}

qint64 GetInt64(unsigned char *str, int pos)
{
    qint64 ans = 0;
    ans = ((qint64)str[pos + 7] << 56) + ((qint64)str[pos + 6] << 48) +
            ((qint64)str[pos + 5] << 40) + ((qint64)str[pos + 4] << 32) +
            (str[pos + 3] << 24) + (str[pos + 2] << 16) + (str[pos + 1] << 8) + str[pos];
    return ans;
}

qint32 SetToRawData(unsigned char *str, int pos, qint32 data)
{
    str[pos] = data & 0xFF;
    str[pos + 1] = (data & 0xFF00) >> 8;
    str[pos + 2] = (data & 0xFF0000) >> 16;
    str[pos + 3] = (data & 0xFF000000) >> 24;
    return pos + 4;
}

qint32 SetToRawData(unsigned char *str, int pos, qint64 data)
{
    for (int i = 0; i < 8; i++)
    {
        str[pos + i] = (data & (0xFF << (i * 8))) >> (i * 8);
    }
    return pos + 8;
}

qint32 SetToRawData(unsigned char *str, int pos, QString data)
{
    int i = 0;
    for (i = 0; i < data.length(); i++)
    {
        str[pos + i] = data.at(i).toLatin1();
    }
    str[pos + i] = 0;
    return pos + i + 1;
}

QString RawDataToString(char* data, int len)
{
    QString str;
    str = QString("NET << ");
    for (int i = 0; i < len; i++)
    {
        str += QString("0x%1 ").arg(int(data[i]), 2, 16, QChar('0'));
    }
    return str;
}


//SEND MESSAGES
void net_send_gd_answer(MySocket* socket, char answer)
{
    QDataStream net_data(socket);
    char data[4];
    data[2] = NET_GOOD_DAY;
    data[3] = answer;
    socket->MyWrite(data, 2);
}

void net_send_set_position(MySocket* socket, CShip* ship)
{
    QDataStream net_data(socket);
    int len = 6 * 4 + ship->login.length() + 4;
    unsigned char data[256];
    //data = new unsigned char[len];
    data[2] = NET_POSITION;
    int runner = 3;
    runner = SetToRawData(data, runner, ship->login);
    runner = SetToRawData(data, runner, ship->shell->pos->pos->rx());
    runner = SetToRawData(data, runner, ship->shell->pos->pos->ry());
    runner = SetToRawData(data, runner, ship->shell->pos->image_angle);
    runner = SetToRawData(data, runner, ship->shell->pos->speed);
    runner = SetToRawData(data, runner, ship->shell->pos->rot_speed);
    runner = SetToRawData(data, runner, ship->shell->pos->direction);
    runner = SetToRawData(data, runner, ship->shell->name);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_mark(MySocket* socket, qint32 x, qint32 y)
{
    QDataStream net_data(socket);
    unsigned char data[11];
    data[2] = NET_MARK;
    int runner = 3;
    runner = SetToRawData(data, runner, x);
    runner = SetToRawData(data, runner, y);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_item(MySocket* socket, CItem* item, qint32 com)
{
    QDataStream net_data(socket);
    unsigned char data[255];
    //data = new unsigned char[len];
    data[2] = NET_ITEM;
    int runner = 3;
    runner = SetToRawData(data, runner, com);
    runner = SetToRawData(data, runner, item->type);
    runner = SetToRawData(data, runner, item->id);
    runner = SetToRawData(data, runner, item->pos.rx());
    runner = SetToRawData(data, runner, item->pos.ry());
    runner = SetToRawData(data, runner, item->image_angle);
    runner = SetToRawData(data, runner, item->hp);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    //socket->LogAddString(item->type);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_shell(MySocket* socket, CShell* shell)
{
    QDataStream net_data(socket);
    int len = 4 * GRID_SIZE * GRID_SIZE;
    unsigned char *data;
    data = new unsigned char[len];
    data[2] = NET_SHELL;
    int runner = 3;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            runner = SetToRawData(data, runner, shell->grid[i][j].permissions);
        }
    }
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_engine(MySocket* socket, CShip* ship)
{
    QDataStream net_data(socket);
    unsigned char data[255];
    data[2] = NET_SHIP_DATA;
    int runner = 3;
    runner = SetToRawData(data, runner, ship->main_drive);
    runner = SetToRawData(data, runner, ship->man_drive);
    runner = SetToRawData(data, runner, ship->back_drive);
    runner = SetToRawData(data, runner, ship->mass);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_navigation(MySocket* socket, CShip* ship)
{
    QDataStream net_data(socket);
    unsigned char data[255];
    data[2] = NET_SHIP_DATA;
    int runner = 3;
    runner = SetToRawData(data, runner, ship->radar_range);
    runner = SetToRawData(data, runner, ship->radio_range);
    runner = SetToRawData(data, runner, ship->system_level);
    runner = SetToRawData(data, runner, ship->main_drive);
    runner = SetToRawData(data, runner, ship->man_drive);
    runner = SetToRawData(data, runner, ship->back_drive);
    runner = SetToRawData(data, runner, ship->mass);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_text(MySocket* socket, QString str, qint32 flags, qint32 chn, qint32 distance)
{
    QDataStream net_data(socket);
    unsigned char data[512];
    data[2] = NET_TEXT;
    int runner = 3;
    runner = SetToRawData(data, runner, chn);
    runner = SetToRawData(data, runner, flags);
    runner = SetToRawData(data, runner, str);
    runner = SetToRawData(data, runner, distance);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->MyWrite((char*)data, runner - 2);
}

void net_send_dock(MySocket* socket, CShip* ship1, CShip* ship2, qint32 flags)
{
    QDataStream net_data(socket);
    unsigned char data[512];
    data[2] = NET_DOCK;
    int runner = 3;
    runner = SetToRawData(data, runner, ship1->login);
    runner = SetToRawData(data, runner, ship2->login);
    runner = SetToRawData(data, runner, flags);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->MyWrite((char*)data, runner - 2);
}
