#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    idgen = new CIdGen();

    log_model = new QStandardItemModel();
    ui->log->setModel(log_model);

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newUser()));
    server->listen(QHostAddress::Any, 63258);  

    //table_model = new QAbstractTableModel;
    table_model = new MyTableModel();
    ui->tableView->setModel(table_model);

    connect(ui->buttonUsrCrt, SIGNAL(clicked()), this, SLOT(UserCreate()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pbtn()));

    int num = 0;
    QVariant buf;
    QSettings load_shell("data/ships.ini", QSettings::IniFormat);
    load_shell.beginGroup("Base");
    num = load_shell.value("number").toFloat();
    for (int i = 0; i < num; i++)
    {
        ui->cbox_shelltype->addItem(load_shell.value(QString("Ship%1").arg(i)).toString());
    }

    QSettings sett("users.ini", QSettings::IniFormat);
    sett.beginGroup("General");
    num = sett.value("NUM", 0).toInt();
    sett.endGroup();
    for (int i = 0; i < num; i++)
    {
        CShip *ship;
        ship = new CShip();
        sett.beginGroup("General");
        ship->login = sett.value(QString("User%1").arg(i)).toString();
        sett.endGroup();
        sett.beginGroup(ship->login);
        ship->password = sett.value("password").toString();
        ship->shell->name = sett.value("Ship type").toString();
        sett.endGroup();
        table_model->add_ship(ship);
        ui->combo_userpos->addItem(ship->login);
        QSettings settPos(QString("save/%1/position.ini").arg(ship->login), QSettings::IniFormat);
        ship->shell->pos->pos->setX(settPos.value("x").toInt());
        ship->shell->pos->pos->setY(settPos.value("y").toInt());
        ship->shell->pos->direction = settPos.value("direction").toInt();
        ship->shell->pos->image_angle = settPos.value("image_angle").toInt();
        ship->shell->pos->rot_speed = settPos.value("rot_speed").toInt();
        ship->shell->pos->speed = settPos.value("speed").toInt();
        ship->shell->loadgrid();

        QSettings settInv(QString("save/%1/inventory.ini").arg(ship->login), QSettings::IniFormat);
        settInv.beginGroup("General");
        int item_num = settInv.value("num").toInt();
        settInv.endGroup();
        for (int j = 0; j < item_num; j++)
        {
            settInv.beginGroup(QString("item%1").arg(j));
            CItem* tmp_item;
            QString type = settInv.value("type").toString();
            tmp_item = idgen->createItem(type);
            tmp_item->owner = ship->login;
            tmp_item->pos.setX(settInv.value("x").toFloat());
            tmp_item->pos.setY(settInv.value("y").toFloat());
            tmp_item->hp = settInv.value("hp").toFloat();
            tmp_item->power = settInv.value("x").toFloat();
            tmp_item->image_angle = settInv.value("image_angle").toFloat();
            settInv.endGroup();
            ship->item_list.append(tmp_item);
            tmp_item->small_list_position = ship->item_list.size() - 1;

        }
    }

    timer_update = new QTimer();
    connect(timer_update, SIGNAL(timeout()), this, SLOT(DataUpdate()));
    timer_update->start(500);

    timer_save = new QTimer();
    connect(timer_save, SIGNAL(timeout()), this, SLOT(DataSave()));
    timer_save->start(5000);

    connect(ui->button_lockpos, SIGNAL(clicked()), this, SLOT(LockPos()));
    connect(ui->button_setpos, SIGNAL(clicked()), this, SLOT(SetPos()));

    ui->lview_items->addItem(TUBE_STRAIGHT);
    ui->lview_items->addItem(TUBE_CORNER);
    ui->lview_items->addItem(TUBE_TEE);
    ui->lview_items->addItem(TUBE_SPLITTER);

    connect(ui->button_add_item, SIGNAL(clicked()), this, SLOT(ItemAdd()));
}

void MainWindow::ItemAdd()
{
    //quint8 pos = ui->lview_items->currentRow();
    QString type = ui->lview_items->currentItem()->text();
    QString name = ui->combo_userpos->currentText();
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
            CItem *item;
            item = idgen->createItem(type);
            SHIPS[i]->item_list.append(item);
            item->small_list_position = SHIPS[i]->item_list.size() - 1;
            ui->lview_inv->addItem(type + QString(" %1").arg(item->id));
            if (SHIPS[i]->engSocket > 0)
            {
                net_send_item(SClients[SHIPS[i]->engSocket], item);
            }
        }
    }
}

void MainWindow::LockPos()
{
    if (timer_update->isActive())
    {
        timer_update->stop();
        ui->button_lockpos->setText("Разлочить");
    }
    else
    {
        timer_update->start(500);
        ui->button_lockpos->setText("Залочить");
    }
}

void MainWindow::SetPos()
{
    QString name = ui->combo_userpos->currentText();
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
                SHIPS[i]->shell->pos->pos->setX(ui->edit_x->text().toInt());
                SHIPS[i]->shell->pos->pos->setY(ui->edit_y->text().toInt());
                SHIPS[i]->shell->pos->direction = ui->edit_dir->text().toInt();
                SHIPS[i]->shell->pos->image_angle = ui->edit_ia->text().toInt();
                SHIPS[i]->shell->pos->rot_speed = ui->edit_rspeed->text().toInt();
                SHIPS[i]->shell->pos->speed = ui->edit_speed->text().toInt();
                net_send_set_position(SClients[SHIPS[i]->pilotSocket], SHIPS[i]);
        }
    }
}

void MainWindow::DataSave()
{
    for (int i = 0; i < SHIPS.size(); i++)
    {
        QSettings settPos(QString("save/%1/position.ini").arg(SHIPS[i]->login), QSettings::IniFormat);
        settPos.setValue("x", SHIPS[i]->shell->pos->pos->rx());
        settPos.setValue("y", SHIPS[i]->shell->pos->pos->ry());
        settPos.setValue("direction", SHIPS[i]->shell->pos->direction);
        settPos.setValue("image_angle", SHIPS[i]->shell->pos->image_angle);
        settPos.setValue("rot_speed", SHIPS[i]->shell->pos->rot_speed);
        settPos.setValue("speed", SHIPS[i]->shell->pos->speed);

        QSettings settInv(QString("save/%1/inventory.ini").arg(SHIPS[i]->login), QSettings::IniFormat);
        settInv.beginGroup("general");
        settInv.setValue("num", SHIPS[i]->item_list.size());
        settInv.endGroup();
        for (int j = 0; j < SHIPS[i]->item_list.size(); j++)
        {
            settInv.beginGroup(QString("item%1").arg(j));
            settInv.setValue("type", SHIPS[i]->item_list[j]->type);
            settInv.setValue("x", SHIPS[i]->item_list[j]->pos.rx());
            settInv.setValue("y", SHIPS[i]->item_list[j]->pos.ry());
            settInv.setValue("hp", SHIPS[i]->item_list[j]->hp);
            settInv.setValue("power", SHIPS[i]->item_list[j]->power);
            settInv.setValue("image_angle", SHIPS[i]->item_list[j]->image_angle);
            settInv.endGroup();
        }
    }
}

void MainWindow::pbtn()
{
    LogAddString(QString("length - %1").arg(SHIPS[0]->login.length()));
}

void MainWindow::UserCreate()
{
    int num = 0;
    QSettings sett("users.ini", QSettings::IniFormat);
    sett.beginGroup("General");
    num = sett.value("NUM", 0).toInt();
    for (int i = 0; i < num; i++)
    {
        if (ui->editLogin->text() == sett.value(QString("User%1").arg(i)))
        {
            return;
        }
    }
    sett.setValue(QString("User%1").arg(num), ui->editLogin->text());
    num++;
    sett.setValue("NUM", num);
    sett.endGroup();
    sett.beginGroup(ui->editLogin->text());
    sett.setValue("Password", ui->editPass->text());
    sett.setValue("Ship type", ui->cbox_shelltype->currentText());
    sett.endGroup();
    CShip *ship;
    ship = new CShip();
    ship->login = ui->editLogin->text();
    ship->password = ui->editPass->text();
    ship->shell->name = ui->cbox_shelltype->currentText();
    table_model->add_ship(ship);
}

void MainWindow::newUser()
{
    QTcpSocket* loc_soc;
    loc_soc = (QTcpSocket*)(server->nextPendingConnection());
    MySocket* clientSocket;
    clientSocket = new MySocket();
    clientSocket->setSocketDescriptor(loc_soc->socketDescriptor());
    //clientSocket = dynamic_cast<MySocket*>(loc_soc);
    //clientSocket = static_cast<MySocket*>(server->nextPendingConnection());
    clientSocket->log = ui->log;
    clientSocket->log_model = log_model;
    clientSocket->pt_type = 0;
    int idusersocs = clientSocket->socketDescriptor();
    SClients[idusersocs] = clientSocket;
    clientSocket->descriptor = idusersocs;
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(UserDisconnected()));
}

void MainWindow::DataUpdate()
{
    QString name = ui->combo_userpos->currentText();
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
            ui->edit_x->setText(QString("%1").arg(SHIPS[i]->shell->pos->pos->rx()));
            ui->edit_y->setText(QString("%1").arg(SHIPS[i]->shell->pos->pos->ry()));
            ui->edit_ia->setText(QString("%1").arg(SHIPS[i]->shell->pos->image_angle));
            ui->edit_dir->setText(QString("%1").arg(SHIPS[i]->shell->pos->direction));
            ui->edit_speed->setText(QString("%1").arg(SHIPS[i]->shell->pos->speed));
            ui->edit_rspeed->setText(QString("%1").arg(SHIPS[i]->shell->pos->rot_speed));

            ui->lview_inv->clear();
            for (int j = 0; j < SHIPS[i]->item_list.size(); j++)
            {
                ui->lview_inv->addItem(SHIPS[i]->item_list[j]->type + QString(" %1").arg(SHIPS[i]->item_list[j]->id));
            }
        }
    }
}

void MainWindow::UserDisconnected()
{
    MySocket* clientSocket = (MySocket*)sender();
    if (clientSocket->pt_type != 0)
    {
        LogAddString(QString("User disconnected - %1").arg(clientSocket->parentShip->login));
        table_model->StartChange();
        *clientSocket->parentShip->sockets[clientSocket->pt_type] = -1;
        table_model->EndChange();
    }
    SClients.remove(clientSocket->descriptor);
    clientSocket->close();
    //clientSocket->deleteLater();
}

void MainWindow::slotReadClient()
{
    MySocket* clientSocket = (MySocket*)sender();
    char data[38];
    char tmp_len[2];
    int len;
    QDataStream net_data(clientSocket);
    net_data.readRawData(tmp_len, 2);
    len = (tmp_len[1] << 8) + tmp_len[0];
    //data = new char[len];
    net_data.readRawData(data, len);
    //LogAddString(RawDataToString(data, len));
    switch (data[0])
    {
        case NET_GOOD_DAY:
        {
            int member_type = data[1];
            QString login = GetString(data, 2);
            QString password = GetString(data, 3 + login.length());
            bool test = 0;
            for (int i = 0; i < SHIPS.size(); i++)
            {
                if (SHIPS[i]->login == login)
                {
                    test = 1;
                    if (SHIPS[i]->password == password)
                    {
                        int idusersoc = SClients.key(clientSocket, -1);
                        if (idusersoc >= 0)
                        {
                            if (*(SHIPS[i]->sockets[member_type]) == -1)
                            {
                                table_model->StartChange();
                                *(SHIPS[i]->sockets[member_type]) = idusersoc;
                                table_model->EndChange();
                                LogAddString(QString("User connected - %1").arg(SHIPS[i]->login));
                                clientSocket->parentShip = SHIPS[i];
                                clientSocket->pt_type = member_type;
                                net_send_gd_answer(clientSocket, YES);
                            }
                            else
                            {
                                net_send_gd_answer(clientSocket, BUSY);
                            }
                        }
                        else
                        {
                            net_send_gd_answer(clientSocket, ERROR);
                        }
                    }
                    else
                    {
                        LogAddString(SHIPS[i]->password);
                        LogAddString(password);
                        net_send_gd_answer(clientSocket, NO);
                    }
                    break;
                }
                //net_send_gd_answer(clientSocket, ERROR);
            }
            if (!test)
            {
                net_send_gd_answer(clientSocket, NO);
            }
            break;
        }
        case NET_POSITION:
        {
            qint32 x = GetInt32((unsigned char*)data, 1);
            qint32 y = GetInt32((unsigned char*)data, 5);
            qint32 image_angle = GetInt32((unsigned char*)data, 9);
            qint32 speed = GetInt32((unsigned char*)data, 13);
            qint32 rot_speed = GetInt32((unsigned char*)data, 17);
            qint32 direction = GetInt32((unsigned char*)data, 21);
            clientSocket->parentShip->shell->pos->pos->setX(x);
            clientSocket->parentShip->shell->pos->pos->setY(y);
            clientSocket->parentShip->shell->pos->image_angle = image_angle;
            clientSocket->parentShip->shell->pos->speed = speed;
            clientSocket->parentShip->shell->pos->rot_speed = rot_speed;
            clientSocket->parentShip->shell->pos->direction = direction;
            for (int i = 0; i < SHIPS.size(); i++)
            {
                if ((SHIPS[i] != clientSocket->parentShip) && (SHIPS[i]->pilotSocket > 0))
                {
                    net_send_set_position(SClients[SHIPS[i]->pilotSocket], clientSocket->parentShip);
                }
                if (SHIPS[i]->navSocket > 0)
                {
                    net_send_set_position(SClients[SHIPS[i]->navSocket], clientSocket->parentShip);
                }
            }
            break;
        }
        case NET_FIRST_LOAD:
        {
            for (int i = 0; i < SHIPS.size(); i++)
            {
                net_send_set_position(clientSocket, SHIPS[i]);
            }
            break;
        }
        case NET_IM_OUT:
        {
            table_model->StartChange();
            *clientSocket->parentShip->sockets[clientSocket->pt_type] = -1;
            table_model->EndChange();
            int idusersocs = clientSocket->socketDescriptor();
            SClients.remove(idusersocs);
            delete clientSocket;
            break;
        }
        case NET_MARK:
        {
            qint32 x = GetInt32((unsigned char*)data, 1);
            qint32 y = GetInt32((unsigned char*)data, 5);
            if (clientSocket->parentShip->pilotSocket > 0)
            {
                net_send_mark(SClients[clientSocket->parentShip->pilotSocket], x, y);
            }
            break;
        }
        case NET_ITEM:
        {
            char def_com = data[1];
            CItem *tmp_item = 0;
            if ((def_com & 0x0F) == ITEM_SET)
            {
                if ((def_com & 0xF0) == ITEM_ID)
                {
                    qint64 tmp_id = GetInt64((unsigned char*)data, 2);
                    for (int i = 0; i < idgen->item_list.size(); i++)
                    {
                        if (idgen->item_list[i]->id == tmp_id)
                        {
                            tmp_item = idgen->item_list[i];
                        }
                    }
                }
                if ((def_com & 0xF0) == ITEM_NUM)
                {
                    qint64 num = GetInt64((unsigned char*)data, 2);
                    if ((num > 0) && (num < clientSocket->parentShip->item_list.size()))
                    {
                        tmp_item = clientSocket->parentShip->item_list[num];
                    }
                }
                if (tmp_item)
                {
                    tmp_item->type = GetString(data, 10);
                    tmp_item->pos.setX(GetInt32((unsigned char*)data, 11 + tmp_item->type.length()));
                    tmp_item->pos.setY(GetInt32((unsigned char*)data, 15 + tmp_item->type.length()));
                    tmp_item->image_angle = GetInt32((unsigned char*)data, 19 + tmp_item->type.length());
                    tmp_item->hp = GetInt32((unsigned char*)data, 23 + tmp_item->type.length());
                }
            }
            if ((def_com & 0x0F) == ITEM_GET)
            {
                if ((def_com & 0xF0) == ITEM_ID)
                {
                    qint64 tmp_id = GetInt64((unsigned char*)data, 2);
                    for (int i = 0; i < idgen->item_list.size(); i++)
                    {
                        if (idgen->item_list[i]->id == tmp_id)
                        {
                            tmp_item = idgen->item_list[i];
                        }
                    }
                }
                if ((def_com & 0xF0) == ITEM_NUM)
                {
                    qint64 num = GetInt64((unsigned char*)data, 2);
                    if ((num > -1) && (num < clientSocket->parentShip->item_list.size()))
                    {
                        tmp_item = clientSocket->parentShip->item_list[num];
                    }
                }
                if (tmp_item == 0)
                {
                    tmp_item = new CItem();
                    net_send_item(clientSocket, tmp_item);
                    delete tmp_item;
                }
                else
                {
                    net_send_item(clientSocket, tmp_item);
                }

            }
            break;
        }
        case NET_SHELL:
        {
            QString goal = GetString(data, 1);
            for (int i = 0; i < SHIPS.size(); i++)
            {
                if (SHIPS[i]->login == goal)
                {
                    net_send_shell(clientSocket, SHIPS[i]->shell);
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    foreach(int i,SClients.keys())
    {
        SClients[i]->close();
        SClients.remove(i);
    }
    server->close();

    delete ui;
}


void MainWindow::LogAddString(QString str)
{
    QStandardItem *item;
    item = new QStandardItem();
    item->setText(str);
    log_model->appendRow(item);
    ui->log->scrollToBottom();
}
