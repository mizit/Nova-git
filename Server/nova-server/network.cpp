#include <network.h>

MySocket::MySocket()
{
    pt_type = 0;
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
    return pos + i;
}



//SEND MESSAGES
void net_send_gd_answer(QTcpSocket* socket, char answer)
{
    QDataStream net_data(socket);
    char data[2];
    data[0] = NET_GOOD_DAY;
    data[1] = answer;
    //net_data.writeRawData(data, 2);
    socket->write(data, 2);
    socket->flush();
    while (socket->bytesToWrite() > 0);
    socket->waitForBytesWritten(1000);
}

void net_send_set_position(QTcpSocket* socket, CShip* ship)
{
    QDataStream net_data(socket);
    //socket->flush();
    //while (socket->bytesToWrite() > 0);
    int len = 6 * 4 + ship->login.length() + 1;
    unsigned char *data;
    data = new unsigned char[len];
    data[0] = NET_POSITION;
    int runner = 1;
    runner = SetToRawData(data, runner, ship->login);
    runner = SetToRawData(data, runner, ship->shell->pos->pos->rx());
    runner = SetToRawData(data, runner, ship->shell->pos->pos->ry());
    runner = SetToRawData(data, runner, ship->shell->pos->image_angle);
    runner = SetToRawData(data, runner, ship->shell->pos->speed);
    runner = SetToRawData(data, runner, ship->shell->pos->rot_speed);
    runner = SetToRawData(data, runner, ship->shell->pos->direction);
    socket->write((char*)data, runner);
    //net_data.writeRawData((char*)data, runner);
}
