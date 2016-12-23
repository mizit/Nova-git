#include <network.h>

MySocket::MySocket()
{
    pt_type = 0;
}

void net_send_gd_answer(QTcpSocket* socket, char answer)
{
    QDataStream net_data(socket);
    char data[2];
    data[0] = NET_GOOD_DAY;
    data[1] = answer;
    net_data.writeRawData(data, 2);
}
