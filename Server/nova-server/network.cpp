#include <network.h>

MySocket::MySocket()
{
    pt_type = 0;
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

qint32 SetToRawData(unsigned char *str, int pos, qint32 data)
{
    str[pos] = data & 0xFF;
    str[pos + 1] = (data & 0xFF00) >> 8;
    str[pos + 2] = (data & 0xFF0000) >> 16;
    str[pos + 3] = (data & 0xFF000000) >> 24;
    return pos + 4;
}

qint32 SetToRawData(unsigned char *str, int pos, QString data)
{
    int i = 0;
    for (i = 0; i < data.length(); i++)
    {
        str[pos + i] = data.at(i).toLatin1();
    }
    str[pos + i + 1] = 0;
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
    char data[2];
    data[2] = NET_GOOD_DAY;
    data[3] = answer;
    //net_data.writeRawData(data, 2);
    socket->MyWrite(data, 2);
}

void net_send_set_position(MySocket* socket, CShip* ship)
{
    QDataStream net_data(socket);
    //socket->flush();
    //while (socket->bytesToWrite() > 0);
    int len = 6 * 4 + ship->login.length() + 4;
    unsigned char *data;
    data = new unsigned char[len];
    data[2] = NET_POSITION;
    int runner = 3;
    runner = SetToRawData(data, runner, ship->login);
    runner = SetToRawData(data, runner, ship->shell->pos->pos->rx());
    runner = SetToRawData(data, runner, ship->shell->pos->pos->ry());
    runner = SetToRawData(data, runner, ship->shell->pos->image_angle);
    runner = SetToRawData(data, runner, ship->shell->pos->speed);
    runner = SetToRawData(data, runner, ship->shell->pos->rot_speed);
    runner = SetToRawData(data, runner, ship->shell->pos->direction);
    data[0] = (unsigned char)(runner & 0xFF);
    data[1] = (unsigned char)((runner & 0xFF00) << 8);
    socket->LogAddString(RawDataToString((char*)data, runner));
    socket->MyWrite((char*)data, runner - 2);
    //net_data.writeRawData((char*)data, runner);
}
