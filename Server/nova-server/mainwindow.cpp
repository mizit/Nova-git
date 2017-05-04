#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    idgen = new CIdGen();
    devour_time = 10000;

    log_model = new QStandardItemModel();
    ui->log->setModel(log_model);

    server = new MyServer();
    connect(server, SIGNAL(newConnection()), this, SLOT(newUser()));
    server->listen(QHostAddress::Any, 63258);  

    //table_model = new QAbstractTableModel;
    table_model = new MyTableModel();
    ui->tableView->setModel(table_model);

    connect(ui->buttonUsrCrt, SIGNAL(clicked()), this, SLOT(UserCreate()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pbtn()));
    connect(ui->btn_save, SIGNAL(clicked()), this, SLOT(DataSave()));
    connect(ui->btn_delItem, SIGNAL(clicked()), this, SLOT(ItemDel()));
    connect(ui->btn_hp, SIGNAL(clicked()), this, SLOT(HpRestore()));
    connect(ui->btn_oxygen, SIGNAL(clicked()), this, SLOT(OxyRestore()));
    connect(ui->btn_send_msg, SIGNAL(clicked()), this, SLOT(SendMessage()));

    hyper_mind = new CHyperMind();
    connect(ui->btn_mine, SIGNAL(clicked()), hyper_mind, SLOT(MinerCreate()));
    connect(ui->btn_carryall, SIGNAL(clicked()), hyper_mind, SLOT(CarryallCreate()));
    connect(ui->btn_anomaly, SIGNAL(clicked()), hyper_mind, SLOT(AnomalyCreate()));
    connect(ui->btn_finder, SIGNAL(clicked()), hyper_mind, SLOT(FinderCreate()));
    connect(ui->btn_bot_back, SIGNAL(clicked()), hyper_mind, SLOT(ComAddBack()));
    connect(ui->btn_bot_go, SIGNAL(clicked()), hyper_mind, SLOT(ComAddGo()));
    connect(ui->btn_bot_drop, SIGNAL(clicked()), hyper_mind, SLOT(ComAddDrop()));
    connect(ui->btn_bot_attack, SIGNAL(clicked()), hyper_mind, SLOT(ComAddAttack()));
    hyper_mind->my_bots = ui->lview_bots;
    for (int i = 0; i < SHIPS.size(); i++)
    {
        hyper_mind->ship_list[i] = SHIPS[i];
    }
    hyper_mind->space_list = &space_items;
    hyper_mind->comx = ui->edit_com_x;
    hyper_mind->comy = ui->edit_com_y;
    hyper_mind->items_view = ui->lview_items2;

    hyper_mind->setActive(1);


    int num = 0;
    QVariant buf;

    QSettings settIrl("save/irl.ini", QSettings::IniFormat);
    settIrl.beginGroup("general");
    int item_num = settIrl.value("num").toInt();
    settIrl.endGroup();
    for (int i = 0; i < item_num; i++)
    {
        settIrl.beginGroup(QString("item%1").arg(i));
        CItem* tmp_item;
        QString type = settIrl.value("type").toString();
        tmp_item = idgen->createItem(type, (quint64) settIrl.value("id").toFloat());
        tmp_item->owner = IRL;
        tmp_item->pos.setX(settIrl.value("x").toFloat());
        tmp_item->pos.setY(settIrl.value("y").toFloat());
        tmp_item->hp = settIrl.value("hp").toFloat();
        tmp_item->power = settIrl.value("x").toFloat();
        tmp_item->image_angle = settIrl.value("image_angle").toFloat();
        settIrl.endGroup();
        irl_items.append(tmp_item);
    }


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
        ui->cbox_ship_text->addItem(ship->login);
        QSettings settPos(QString("save/%1/position.ini").arg(ship->login), QSettings::IniFormat);
        ship->shell->pos->pos->setX(settPos.value("x").toInt());
        ship->shell->pos->pos->setY(settPos.value("y").toInt());
        ship->shell->pos->direction = settPos.value("direction").toInt();
        ship->shell->pos->image_angle = settPos.value("image_angle").toInt();
        ship->shell->pos->rot_speed = settPos.value("rot_speed").toInt();
        ship->shell->pos->speed = settPos.value("speed").toInt();
        ship->shell->loadgrid();

        QSettings settBon(QString("save/%1/bonuses.ini").arg(ship->login), QSettings::IniFormat);
        for (int i = 0; i < NUM_ATR; i++)
        {
            ship->attribute[i].bonus = settBon.value(ship->attribute[i].name).toInt();
        }

        QSettings settInv(QString("save/%1/inventory.ini").arg(ship->login), QSettings::IniFormat);
        settInv.beginGroup("General");
        int item_num = settInv.value("num").toInt();
        ship->attribute[BN_HP].base = settInv.value("hp", ship->attribute[BN_MAX_HP].Calculation()).toInt();
        ship->attribute[BN_OXYGEN].base = settInv.value("oxygen", ship->attribute[BN_MAX_OXYGEN].Calculation()).toInt();
        ship->attribute[BN_MAX_OXYGEN].base = 50;
        settInv.endGroup();
        for (int j = 0; j < item_num; j++)
        {
            settInv.beginGroup(QString("item%1").arg(j));
            CItem* tmp_item;
            QString type = settInv.value("type").toString();
            tmp_item = idgen->createItem(type, (quint64) settInv.value("id").toFloat());
            tmp_item->owner = ship->login;
            tmp_item->pos.setX(settInv.value("x").toFloat());
            tmp_item->pos.setY(settInv.value("y").toFloat());
            tmp_item->hp = settInv.value("hp").toFloat();
            tmp_item->power = settInv.value("x").toFloat();
            tmp_item->image_angle = settInv.value("image_angle").toFloat();
            settInv.endGroup();
            ship->item_list.append(tmp_item);
        }
    }
    ui->combo_userpos->addItem(SPACE);

    QSettings settAstr("data/asteroids.ini", QSettings::IniFormat);
    settAstr.beginGroup("General");
    item_num = settAstr.value("num").toFloat();
    settAstr.endGroup();
    for (int i = 0; i < item_num; i++)
    {
        settAstr.beginGroup(QString("Asteroid%1").arg(i));
        CAsteroid* tmp_astr;
        tmp_astr = new CAsteroid();
        tmp_astr->x = settAstr.value("x", 1).toFloat();
        tmp_astr->y = settAstr.value("y").toFloat();
        tmp_astr->setType(settAstr.value("type").toFloat());
        //tmp_astr->type = settAstr.value("type").toFloat();
        tmp_astr->num = settAstr.value("num").toFloat();
        //LogAddString(QString("X - %1, Y - %2, Type - %3, Num - %4").arg(tmp_astr->x).arg(tmp_astr->y).arg(tmp_astr->type).arg(tmp_astr->num));
        settAstr.endGroup();
        asteroids.append(tmp_astr);
    }

    QSettings settInv("save/space.ini", QSettings::IniFormat);
    settInv.beginGroup("general");
    item_num = settInv.value("num").toInt();
    settInv.endGroup();
    for (int i = 0; i < item_num; i++)
    {
        settInv.beginGroup(QString("item%1").arg(i));
        CItem* tmp_item;
        QString type = settInv.value("type").toString();
        tmp_item = idgen->createItem(type, (quint64) settInv.value("id").toFloat());
        tmp_item->owner = SPACE;
        tmp_item->pos.setX(settInv.value("x").toFloat());
        tmp_item->pos.setY(settInv.value("y").toFloat());
        tmp_item->hp = settInv.value("hp").toFloat();
        tmp_item->power = settInv.value("x").toFloat();
        tmp_item->image_angle = settInv.value("image_angle").toFloat();
        settInv.endGroup();
        if ((tmp_item->type == DEVOURER) || (tmp_item->type == DEVOURER_2))
        {
            DevourerCreate(tmp_item);
        }
        space_items.append(tmp_item);
    } 
    ui->combo_userpos->addItem(IRL);




    connect(ui->combo_userpos, SIGNAL(currentIndexChanged(int)), this, SLOT(UserChange()));
    UserChange();

    timer_update = new QTimer();
    connect(timer_update, SIGNAL(timeout()), this, SLOT(DataUpdate()));
    timer_update->start(500);

    timer_save = new QTimer();
    connect(timer_save, SIGNAL(timeout()), this, SLOT(DataSave()));
    timer_save->start(300000);

    timer_blind_send = new QTimer();
    connect(timer_blind_send, SIGNAL(timeout()), this, SLOT(BlindSend()));
    timer_blind_send->start(10000);

    connect(ui->button_lockpos, SIGNAL(clicked()), this, SLOT(LockPos()));
    connect(ui->button_setpos, SIGNAL(clicked()), this, SLOT(SetPos()));

    ui->lview_items->addItem(TUBE_STRAIGHT);
    ui->lview_items->addItem(TUBE_CORNER);
    ui->lview_items->addItem(TUBE_TEE);
    ui->lview_items->addItem(TUBE_SPLITTER);
    ui->lview_items->addItem(MONEY_CASE);
    ui->lview_items->addItem(GOLD);
    ui->lview_items->addItem(RUBY);
    ui->lview_items->addItem(EMERALD);
    ui->lview_items->addItem(DEVOURER);
    ui->lview_items->addItem(DEVOURER_2);
    ui->lview_items->addItem(POWER_BLOCK);
    ui->lview_items->addItem(POWER_BLOCK_S);
    ui->lview_items->addItem(POWER_BLOCK_T);
    ui->lview_items->addItem(ELEMENT1);
    ui->lview_items->addItem(ELEMENT2);
    ui->lview_items->addItem(ELEMENT3);
    ui->lview_items->addItem(ELEMENT4);
    ui->lview_items->addItem(ELEMENT5);

    ui->lview_items->addItem(LIFE_SYSTEM);
    ui->lview_items->addItem(LIFE_SYSTEM_S);

    ui->lview_items->addItem(NAVIGATION_S);
    ui->lview_items->addItem(NAVIGATION_T);
    ui->lview_items->addItem(NAVIGATION_T_4);
    ui->lview_items->addItem(WEAPON);
    ui->lview_items->addItem(ENGINE_S);
    ui->lview_items->addItem(ENGINE_T);

    connect(ui->button_add_item, SIGNAL(clicked()), this, SLOT(ItemAdd()));
    connect(ui->btn_devour, SIGNAL(clicked()), this, SLOT(SetDevourTime()));

}

void MainWindow::SetDevourTime()
{
    devour_time = ui->edit_devour->text().toInt() * 1000;
}

void MainWindow::BlindSend()
{
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->pilotSocket > 0)
        {
            net_send_asteroid(SClients[SHIPS[i]->pilotSocket], asteroids);
            //net_send_engine(SClients[SHIPS[i]->pilotSocket], SHIPS[i]);
            for (int j = 0; j < SHIPS.size(); j++)
            {
                if (SHIPS[j]->pilotSocket <= 0)
                {
                    net_send_set_position(SClients[SHIPS[i]->pilotSocket], SHIPS[j]);
                }
            }
        }
        if (SHIPS[i]->navSocket > 0)
        {
            net_send_asteroid(SClients[SHIPS[i]->navSocket], asteroids);
            //net_send_navigation(SClients[SHIPS[i]->pilotSocket], SHIPS[i]);
            for (int j = 0; j < SHIPS.size(); j++)
            {
                if (SHIPS[j]->pilotSocket <= 0)
                {
                    net_send_set_position(SClients[SHIPS[i]->navSocket], SHIPS[j]);
                }
            }
        }
    }
}

void MainWindow::SendMessage()
{
    CShip* ship;
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == ui->cbox_ship_text->currentText())
        {
            ship = SHIPS[i];
            if (ship->navSocket > 0)
            {
                net_send_text(SClients[ship->navSocket], ui->textEdit->toPlainText(), TX_SYSTEM, 0, 0);
            }
            ui->textEdit->clear();
        }
    }

}

void MainWindow::HpRestore()
{
    QString name = ui->combo_userpos->currentText();
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
            SHIPS[i]->attribute[BN_HP].base =  SHIPS[i]->attribute[BN_MAX_HP].Calculation();
        }
    }
}

void MainWindow::OxyRestore()
{
    QString name = ui->combo_userpos->currentText();
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
            SHIPS[i]->attribute[BN_OXYGEN].base =  SHIPS[i]->attribute[BN_MAX_OXYGEN].Calculation();
        }
    }
}

void MainWindow::UserChange()
{
    QString name = ui->combo_userpos->currentText();
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
            SHIPS[i]->attribute[BN_AIR_OUTPUT].setOutput(ui->edit_air_output);
            SHIPS[i]->attribute[BN_AIR_BANK].setOutput(ui->edit_air_bank);
            SHIPS[i]->attribute[BN_SAFELY].setOutput(ui->edit_safely);
            SHIPS[i]->attribute[BN_RADAR_RANGE].setOutput(ui->edit_radar_range);
            SHIPS[i]->attribute[BN_RADIO_RANGE].setOutput(ui->edit_radio_range);
            SHIPS[i]->attribute[BN_SYSTEM_LEVEL].setOutput(ui->edit_system_level);
            SHIPS[i]->attribute[BN_MAIN_DRIVE].setOutput(ui->edit_main_drive);
            SHIPS[i]->attribute[BN_MAN_DRIVE].setOutput(ui->edit_man_drive);
            SHIPS[i]->attribute[BN_BACK_DRIVE].setOutput(ui->edit_back_drive);
            SHIPS[i]->attribute[BN_MASS].setOutput(ui->edit_mass);
            SHIPS[i]->attribute[BN_MAX_HP].setOutput(ui->edit_hp_max);
            SHIPS[i]->attribute[BN_MAX_OXYGEN].setOutput(ui->edit_oxygen_max);
            SHIPS[i]->attribute[BN_HP].setOutput(ui->edit_hp);
            SHIPS[i]->attribute[BN_OXYGEN].setOutput(ui->edit_oxygen);
            SHIPS[i]->attribute[BN_WEAPON_STR].setOutput(ui->edit_weapon_str);
            SHIPS[i]->attribute[BN_WEAPON_RANGE].setOutput(ui->edit_weapon_range);
            SHIPS[i]->attribute[BN_WEAPON_RAPID].setOutput(ui->edit_weapon_rapid);


            SHIPS[i]->attribute[BN_AIR_OUTPUT].setInput(ui->edit_air_output_2);
            SHIPS[i]->attribute[BN_AIR_BANK].setInput(ui->edit_air_bank_2);
            SHIPS[i]->attribute[BN_SAFELY].setInput(ui->edit_safely_2);
            SHIPS[i]->attribute[BN_RADAR_RANGE].setInput(ui->edit_radar_range_2);
            SHIPS[i]->attribute[BN_RADIO_RANGE].setInput(ui->edit_radio_range_2);
            SHIPS[i]->attribute[BN_SYSTEM_LEVEL].setInput(ui->edit_system_level_2);
            SHIPS[i]->attribute[BN_MAIN_DRIVE].setInput(ui->edit_main_drive_2);
            SHIPS[i]->attribute[BN_MAN_DRIVE].setInput(ui->edit_man_drive_2);
            SHIPS[i]->attribute[BN_BACK_DRIVE].setInput(ui->edit_back_drive_2);
            SHIPS[i]->attribute[BN_MASS].setInput(ui->edit_mass_2);
            SHIPS[i]->attribute[BN_MAX_HP].setInput(ui->edit_hp_max_2);
            SHIPS[i]->attribute[BN_MAX_OXYGEN].setInput(ui->edit_air_bank);
            SHIPS[i]->attribute[BN_HP].setInput(ui->edit_hp_2);
            SHIPS[i]->attribute[BN_OXYGEN].setInput(ui->edit_oxygen_2);
            SHIPS[i]->attribute[BN_WEAPON_STR].setInput(ui->edit_weapon_str_2);
            SHIPS[i]->attribute[BN_WEAPON_RANGE].setInput(ui->edit_weapon_range_2);
            SHIPS[i]->attribute[BN_WEAPON_RAPID].setInput(ui->edit_weapon_rapid_2);

            for (int j = 0; j < NUM_ATR; j++)
            {
                SHIPS[i]->attribute[j].input_bonus->setText(QString("%1").arg(SHIPS[i]->attribute[j].bonus));
            }
        }
        else
        {
            for (int j = 0; j < NUM_ATR; j++)
            {
                SHIPS[i]->attribute[j].ClearEdit();
            }
        }
    }
}

void MainWindow::ItemDel()
{
    QString name = ui->combo_userpos->currentText();
    int num;
    num = ui->lview_inv->currentRow();
    if (num >= 0)
    {
        for (int i = 0; i < SHIPS.size(); i++)
        {
            if (SHIPS[i]->login == name)
            {
                if (SHIPS[i]->engSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->engSocket], SHIPS[i]->item_list[num], ITEM_DEL|ITEM_ID);
                }
                deleteItem(SHIPS[i]->item_list[num]);
            }
        }
        if (name == SPACE)
        {
            for (int i = 0; i < SHIPS.size(); i++)
            {
                if (SHIPS[i]->pilotSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->pilotSocket], space_items[num], ITEM_DEL|ITEM_ID);
                }
                if (SHIPS[i]->navSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->navSocket], space_items[num], ITEM_DEL|ITEM_ID);
                }
                if (SHIPS[i]->engSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->engSocket], space_items[num], ITEM_DEL|ITEM_ID);
                }
            }
            deleteItem(space_items[num]);
        }
        if (name == IRL)
        {
            deleteItem(irl_items[num]);
        }
    }
    DataUpdate();
}

void MainWindow::ComplexDeleteItem(CItem* item)
{
    QString name = item->owner;
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == name)
        {
            if (SHIPS[i]->engSocket > 0)
            {

                net_send_item(SClients[SHIPS[i]->engSocket], item, ITEM_DEL|ITEM_ID);
            }
            deleteItem(item);
        }
    }
    if (name == SPACE)
    {
        for (int i = 0; i < SHIPS.size(); i++)
        {
            if (SHIPS[i]->pilotSocket > 0)
            {
                net_send_item(SClients[SHIPS[i]->pilotSocket], item, ITEM_DEL|ITEM_ID);
            }
            if (SHIPS[i]->navSocket > 0)
            {
                net_send_item(SClients[SHIPS[i]->navSocket], item, ITEM_DEL|ITEM_ID);
            }
            if (SHIPS[i]->engSocket > 0)
            {
                net_send_item(SClients[SHIPS[i]->engSocket], item, ITEM_DEL|ITEM_ID);
            }
        }
        deleteItem(item);
    }
    if (name == IRL)
    {
        deleteItem(item);
    }
    DataUpdate();
}

void MainWindow::ItemAdd()
{
    //quint8 pos = ui->lview_items->currentRow();
    if (ui->lview_items->currentRow() >= 0)
    {
        QString type = ui->lview_items->currentItem()->text();
        QString name = ui->combo_userpos->currentText();
        for (int i = 0; i < SHIPS.size(); i++)
        {
            if (SHIPS[i]->login == name)
            {
                CItem *item;
                item = idgen->createItem(type);
                SHIPS[i]->item_list.append(item);
                item->owner = SHIPS[i]->login;
                ui->lview_inv->addItem(type + QString(" %1").arg(item->id));
                if (SHIPS[i]->engSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->engSocket], item, ITEM_SET | ITEM_ID);
                }
            }
        }
        if (name == SPACE)
        {
            CItem *item;
            item = idgen->createItem(type);
            if ((item->type == DEVOURER) || (item->type == DEVOURER_2))
            {
                DevourerCreate(item);
            }
            space_items.append(item);
            item->owner = SPACE;
            ui->lview_inv->addItem(type + QString(" %1").arg(item->id));
            for (int i = 0; i < SHIPS.size(); i++)
            {
                if (SHIPS[i]->pilotSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->pilotSocket], item, ITEM_SET | ITEM_ID);
                }
                if (SHIPS[i]->navSocket > 0)
                {
                    net_send_item(SClients[SHIPS[i]->navSocket], item, ITEM_SET | ITEM_ID);
                }
            }
        }
        if (name == IRL)
        {
            CItem *item;
            item = idgen->createItem(type);
            irl_items.append(item);
            item->owner = IRL;
            ui->lview_inv->addItem(type + QString(" %1").arg(item->id));
        }
    }
}

void MainWindow::deleteItem(CItem* item)
{
    idgen->free_num.append(item->id);
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->login == item->owner)
        {
            SHIPS[i]->item_list.removeOne(item);
        }
    }
    if (item->owner == SPACE)
    {
        space_items.removeOne(item);
    }
    if (item->owner == IRL)
    {
        irl_items.removeOne(item);
    }
    delete item;
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
                for (int j = 0; j < SHIPS.size(); j++)
                {
                    if (SHIPS[j]->pilotSocket > 0)
                    {
                        net_send_set_position(SClients[SHIPS[j]->pilotSocket], SHIPS[i]);
                    }
                    if (SHIPS[j]->navSocket > 0)
                    {
                        net_send_set_position(SClients[SHIPS[j]->navSocket], SHIPS[i]);
                    }
                }
        }
    }
}

void MainWindow::DataSave()
{

    for (int i = 0; i < SHIPS.size(); i++)
    {
        QFile file(QString("save/%1/position.ini").arg(SHIPS[i]->login));
        file.remove();
        QSettings settPos(QString("save/%1/position.ini").arg(SHIPS[i]->login), QSettings::IniFormat);
        settPos.setValue("x", SHIPS[i]->shell->pos->pos->rx());
        settPos.setValue("y", SHIPS[i]->shell->pos->pos->ry());
        settPos.setValue("direction", SHIPS[i]->shell->pos->direction);
        settPos.setValue("image_angle", SHIPS[i]->shell->pos->image_angle);
        settPos.setValue("rot_speed", SHIPS[i]->shell->pos->rot_speed);
        settPos.setValue("speed", SHIPS[i]->shell->pos->speed);

        QSettings settBon(QString("save/%1/bonuses.ini").arg(SHIPS[i]->login), QSettings::IniFormat);
        for (int j = 0; j < NUM_ATR; j++)
        {
            settBon.setValue(SHIPS[i]->attribute[j].name, SHIPS[i]->attribute[j].bonus);
        }

        file.setFileName(QString("save/%1/inventory.ini").arg(SHIPS[i]->login));
        file.remove();
        QSettings settInv(QString("save/%1/inventory.ini").arg(SHIPS[i]->login), QSettings::IniFormat);
        settInv.beginGroup("general");
        settInv.setValue("num", SHIPS[i]->item_list.size());
        settInv.setValue("hp", SHIPS[i]->attribute[BN_HP].base);
        settInv.setValue("oxygen", SHIPS[i]->attribute[BN_OXYGEN].base);
        settInv.endGroup();
        for (int j = 0; j < SHIPS[i]->item_list.size(); j++)
        {
            settInv.beginGroup(QString("item%1").arg(j));
            settInv.setValue("type", SHIPS[i]->item_list[j]->type);
            settInv.setValue("id", SHIPS[i]->item_list[j]->id);
            settInv.setValue("x", SHIPS[i]->item_list[j]->pos.rx());
            settInv.setValue("y", SHIPS[i]->item_list[j]->pos.ry());
            settInv.setValue("hp", SHIPS[i]->item_list[j]->hp);
            settInv.setValue("power", SHIPS[i]->item_list[j]->power);
            settInv.setValue("image_angle", SHIPS[i]->item_list[j]->image_angle);
            settInv.endGroup();
        }
    }

    QFile file("save/space.ini");
    file.remove();
    QSettings settInv("save/space.ini", QSettings::IniFormat);
    settInv.beginGroup("general");
    settInv.setValue("num", space_items.size());
    settInv.endGroup();
    for (int i = 0; i < space_items.size(); i++)
    {
        settInv.beginGroup(QString("item%1").arg(i));
        settInv.setValue("type", space_items[i]->type);
        settInv.setValue("id", space_items[i]->id);
        settInv.setValue("x", space_items[i]->pos.rx());
        settInv.setValue("y", space_items[i]->pos.ry());
        settInv.setValue("hp", space_items[i]->hp);
        settInv.setValue("power", space_items[i]->power);
        settInv.setValue("image_angle", space_items[i]->image_angle);
        settInv.endGroup();
    }

    QFile fileIrl("save/irl.ini");
    fileIrl.remove();
    QSettings settIrl("save/irl.ini", QSettings::IniFormat);
    settIrl.beginGroup("general");
    settIrl.setValue("num", irl_items.size());
    settIrl.endGroup();
    for (int i = 0; i < irl_items.size(); i++)
    {
        settIrl.beginGroup(QString("item%1").arg(i));
        settIrl.setValue("id", irl_items[i]->id);
        settIrl.setValue("type", irl_items[i]->type);
        settIrl.setValue("x", irl_items[i]->pos.rx());
        settIrl.setValue("y", irl_items[i]->pos.ry());
        settIrl.setValue("hp", irl_items[i]->hp);
        settIrl.setValue("power", irl_items[i]->power);
        settIrl.setValue("image_angle", irl_items[i]->image_angle);
        settIrl.endGroup();
    }

    QFile fileAstr("data/asteroids.ini");
    fileAstr.remove();
    QSettings settAstr("data/asteroids.ini", QSettings::IniFormat);
    settAstr.beginGroup("general");
    settAstr.setValue("num", asteroids.size());
    settAstr.endGroup();
    for (int i = 0; i < asteroids.size(); i++)
    {
        settAstr.beginGroup(QString("Asteroid%1").arg(i));
        settAstr.setValue("x", asteroids[i]->x);
        settAstr.setValue("y", asteroids[i]->y);
        settAstr.setValue("type", asteroids[i]->code);
        settAstr.setValue("num", asteroids[i]->num);
        settAstr.endGroup();
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
    //QTcpSocket* loc_soc;
    //loc_soc = (QTcpSocket*)(server->nextPendingConnection());
    MySocket* clientSocket;
    clientSocket = (MySocket*)(server->nextPendingConnection());
    //clientSocket = new MySocket();
    //clientSocket->setSocketDescriptor(loc_soc->socketDescriptor());
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
            for (int j = 0; j < NUM_ATR; j++)
            {
                SHIPS[i]->attribute[j].Calculation();
            }

        }
    }
    if (name == SPACE)
    {
        ui->lview_inv->clear();
        for (int j = 0; j < space_items.size(); j++)
        {
            ui->lview_inv->addItem(space_items[j]->type + QString(" %1").arg(space_items[j]->id));
        }
    }
    if (name == IRL)
    {
        ui->lview_inv->clear();
        for (int j = 0; j < irl_items.size(); j++)
        {
            ui->lview_inv->addItem(irl_items[j]->type + QString(" %1").arg(irl_items[j]->id));
        }
    }
    for (int i = 0; i < hyper_mind->bots.size(); i++)
    {
        CBot* bot;
        bot = hyper_mind->bots[i];
        if (bot->commands_list.size() > 0)
        {
            if (bot->commands_list[0]->type == BC_DROP)
            {
                if (bot->item_list.size() > 0)
                {
                    CItem* item;
                    item = bot->item_list[0];
                    item->pos.setX(bot->x);
                    item->pos.setY(bot->y);
                    item->owner = SPACE;
                    space_items.append(item);
                    bot->item_list.removeFirst();
                    for (int j = 0; j < SHIPS.size(); j++)
                    {
                        if (SHIPS[j]->pilotSocket > 0)
                        {
                            net_send_item(SClients[SHIPS[j]->pilotSocket], item, ITEM_ID|ITEM_SET);
                        }
                        if (SHIPS[j]->navSocket > 0)
                        {
                            net_send_item(SClients[SHIPS[j]->navSocket], item, ITEM_ID|ITEM_SET);
                        }
                    }
                }
                if (bot->cargo_bots.size() > 0)
                {
                    CBot* c_bot;
                    c_bot = bot->cargo_bots[0];
                    c_bot->x = bot->x;
                    c_bot->y = bot->y;
                    c_bot->setActive(1);
                    for (int j = 0; j < SHIPS.size(); j++)
                    {
                        if (SHIPS[j]->pilotSocket > 0)
                        {
                            net_send_bot(SClients[SHIPS[j]->pilotSocket], c_bot);
                        }
                        if (SHIPS[j]->navSocket > 0)
                        {
                            net_send_bot(SClients[SHIPS[j]->navSocket], c_bot);
                        }
                    }
                }
            }
        }
        if (bot->ready_to_send)
        {
            bot->ready_to_send = 0;
            for (int j = 0; j < SHIPS.size(); j++)
            {
                if (SHIPS[j]->pilotSocket > 0)
                {
                    net_send_bot(SClients[SHIPS[j]->pilotSocket], bot);
                }
                if (SHIPS[j]->navSocket > 0)
                {
                    net_send_bot(SClients[SHIPS[j]->navSocket], bot);
                }
            }
        }
    }
    if (ui->lview_bots->currentRow() > -1)
    {
        CBot* bot = hyper_mind->bots[ui->lview_bots->currentRow()];
        ui->lview_orders->clear();
        for (int i = 0; i < bot->commands_list.size(); i++)
        {
            ui->lview_orders->addItem(QString("%1").arg(bot->commands_list[i]->type));
        }
        ui->edit_bot_x->setText(QString("%1").arg(bot->x));
        ui->edit_bot_y->setText(QString("%1").arg(bot->y));
        if (bot->commands_list.size() > 0)
        {
            ui->edit_bot_speed->setText(QString("%1").arg(point_distance(bot->x, bot->y, bot->commands_list[0]->x, bot->commands_list[0]->y)));
        }
        ui->edit_bot_active->setText(QString("%1").arg(bot->direction));
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
    char data[1024];
    char tmp_len[2];
    int len;
    QDataStream net_data(clientSocket);
    while (net_data.readRawData(tmp_len, 2) > 0)
    {
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
                    if (clientSocket->parentShip->engSocket == clientSocket->descriptor)
                    {
                        qint64 num = GetInt64((unsigned char*)data, 2);
                        if ((num > -1) && (num < clientSocket->parentShip->item_list.size()))
                        {
                            tmp_item = clientSocket->parentShip->item_list[num];
                        }
                    }
                    if ((clientSocket->parentShip->pilotSocket == clientSocket->descriptor) ||
                        (clientSocket->parentShip->navSocket == clientSocket->descriptor))
                    {
                        qint64 num = GetInt64((unsigned char*)data, 2);
                        if ((num > -1) && (num < space_items.size()))
                        {
                            tmp_item = space_items[num];
                        }
                    }
                }
                if ((def_com & 0x0F) == ITEM_SET)
                {
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
                    if (tmp_item == 0)
                    {
                        tmp_item = new CItem();
                        net_send_item(clientSocket, tmp_item, ITEM_SET | ITEM_ID);
                        delete tmp_item;
                    }
                    else
                    {
                        if (tmp_item->owner == IRL)
                        {
                            irl_items.removeAt(irl_items.indexOf(tmp_item));
                            clientSocket->parentShip->item_list.append(tmp_item);
                            tmp_item->owner = clientSocket->parentShip->login;
                            net_send_item(clientSocket, tmp_item, ITEM_SET | ITEM_ID);
                        }
                        if (tmp_item->owner == SPACE)
                        {
                            if ((clientSocket->parentShip->pilotSocket == clientSocket->descriptor) ||
                                (clientSocket->parentShip->navSocket == clientSocket->descriptor))
                            {
                                net_send_item(clientSocket, tmp_item, ITEM_SET | ITEM_ID);
                            }
                        }
                        if (tmp_item->owner == clientSocket->parentShip->login)
                        {
                            net_send_item(clientSocket, tmp_item, ITEM_SET | ITEM_ID);
                        }
                    }

                }
                if ((def_com &0x0F) == ITEM_DROP)
                {
                    if (clientSocket->parentShip->engSocket == clientSocket->descriptor)
                    {
                        if (tmp_item)
                        {
                            if (tmp_item->owner == clientSocket->parentShip->login)
                            {
                                tmp_item->type = GetString(data, 10);
                                tmp_item->pos.setX(clientSocket->parentShip->shell->pos->pos->rx());
                                tmp_item->pos.setY(clientSocket->parentShip->shell->pos->pos->ry());
                                tmp_item->image_angle = GetInt32((unsigned char*)data, 19 + tmp_item->type.length());
                                tmp_item->hp = GetInt32((unsigned char*)data, 23 + tmp_item->type.length());
                                tmp_item->owner = SPACE;
                                for (int i = 0; i < clientSocket->parentShip->item_list.size(); i++)
                                {
                                    if (clientSocket->parentShip->item_list[i]->id == tmp_item->id)
                                    {
                                        clientSocket->parentShip->item_list.removeAt(i);
                                        break;
                                    }
                                }
                                if ((tmp_item->type == DEVOURER) || (tmp_item->type == DEVOURER_2))
                                {
                                    DevourerCreate(tmp_item);
                                }
                                space_items.append(tmp_item);
                                for (int i = 0; i < SHIPS.size(); i++)
                                {
                                    if (SHIPS[i]->pilotSocket > 0)
                                    {
                                        net_send_item(SClients[SHIPS[i]->pilotSocket], tmp_item, ITEM_DROP | ITEM_ID);
                                    }
                                    if (SHIPS[i]->navSocket > 0)
                                    {
                                        net_send_item(SClients[SHIPS[i]->navSocket], tmp_item, ITEM_DROP | ITEM_ID);
                                    }
                                }
                            }
                        }
                    }
                    if (clientSocket->parentShip->pilotSocket == clientSocket->descriptor)
                    {
                        if (clientSocket->parentShip->engSocket > 0)
                        {
                            net_send_item(SClients[clientSocket->parentShip->engSocket], tmp_item, ITEM_DROP | ITEM_ID);
                        }
                    }
                }
                if ((def_com &0x0F) == ITEM_PICKUP)
                {
                    if (clientSocket->parentShip->engSocket == clientSocket->descriptor)
                    {
                        if (tmp_item)
                        {
                            if (tmp_item->owner == SPACE)
                            {
                                tmp_item->type = GetString(data, 10);
                                tmp_item->pos.setX(0);
                                tmp_item->pos.setY(0);
                                tmp_item->image_angle = GetInt32((unsigned char*)data, 19 + tmp_item->type.length());
                                tmp_item->hp = GetInt32((unsigned char*)data, 23 + tmp_item->type.length());
                                tmp_item->owner = clientSocket->parentShip->login;
                                for (int i = 0; i < space_items.size(); i++)
                                {
                                    if (space_items[i]->id == tmp_item->id)
                                    {
                                        space_items.removeAt(i);
                                        break;
                                    }
                                }
                                clientSocket->parentShip->item_list.append(tmp_item);
                                for (int i = 0; i < SHIPS.size(); i++)
                                {
                                    if (SHIPS[i]->pilotSocket > 0)
                                    {
                                        net_send_item(SClients[SHIPS[i]->pilotSocket], tmp_item, ITEM_PICKUP | ITEM_ID);
                                    }
                                    if (SHIPS[i]->navSocket > 0)
                                    {
                                        net_send_item(SClients[SHIPS[i]->navSocket], tmp_item, ITEM_PICKUP | ITEM_ID);
                                    }
                                }
                            }
                        }
                    }
                    if (clientSocket->parentShip->pilotSocket == clientSocket->descriptor)
                    {
                        if (clientSocket->parentShip->engSocket > 0)
                        {
                            net_send_item(SClients[clientSocket->parentShip->engSocket], tmp_item, ITEM_PICKUP | ITEM_ID);
                        }
                    }
                }
                if ((def_com &0x0F) == ITEM_DEL)
                {
                    deleteItem(tmp_item);
                }
                if ((def_com &0x0F) == ITEM_ADD)
                {
                    tmp_item = new CItem();
                    tmp_item->type = GetString(data, 10);
                    tmp_item->id = idgen->IdGen(0, 0);
                    tmp_item->pos.setX(GetInt32((unsigned char*)data, 11 + tmp_item->type.length()));
                    tmp_item->pos.setY(GetInt32((unsigned char*)data, 15 + tmp_item->type.length()));
                    tmp_item->image_angle = GetInt32((unsigned char*)data, 19 + tmp_item->type.length());
                    tmp_item->hp = GetInt32((unsigned char*)data, 23 + tmp_item->type.length());

                }
                break;
            }
            case NET_SHIP_DATA:
            {
                for (int i = 0; i < 13; i++)
                {
                    clientSocket->parentShip->attribute[i].base = GetInt32((unsigned char*)data, 1 + i * 4);
                }
                clientSocket->parentShip->attribute[BN_MAX_HP].base = GetInt32((unsigned char*)data, 1 + 13 * 4);
                if (clientSocket->parentShip->pilotSocket > 0)
                {
                    net_send_engine(SClients[clientSocket->parentShip->pilotSocket], clientSocket->parentShip);
                }
                if (clientSocket->parentShip->navSocket > 0)
                {
                    net_send_navigation(SClients[clientSocket->parentShip->navSocket], clientSocket->parentShip);
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
                break;
            }
            case NET_TEXT:
            {
                qint32 chn = GetInt32((unsigned char *)data, 1);
                QString text = GetString(data, 5);
                LogAddString(QString("[%1]:%2").arg(clientSocket->parentShip->login).arg(text));
                for (int i = 0; i < SHIPS.size(); i++)
                {
                    if (SHIPS[i]->navSocket > 0)
                    {
                        net_send_text(SClients[SHIPS[i]->navSocket], text, TX_MESSAGE, chn,
                                point_distance(clientSocket->parentShip->shell->pos->pos, SHIPS[i]->shell->pos->pos));
                    }
                }
                break;
            }
            case NET_DOCK:
            {
                qint32 flags = GetInt32((unsigned char *)data, 1);
                QString login_ship = GetString(data, 5);
                for (int i = 0; i < SHIPS.size(); i++)
                {
                    if (SHIPS[i]->login == login_ship)
                    {
                        if (SHIPS[i]->pilotSocket > 0)
                        {
                            net_send_dock(SClients[SHIPS[i]->pilotSocket], clientSocket->parentShip, SHIPS[i], flags);
                        }
                        if (SHIPS[i]->navSocket > 0)
                        {
                            net_send_dock(SClients[SHIPS[i]->navSocket], clientSocket->parentShip, SHIPS[i], flags);
                        }
                        if (clientSocket->parentShip->navSocket > 0)
                        {
                            net_send_dock(SClients[clientSocket->parentShip->navSocket], clientSocket->parentShip, SHIPS[i], flags);
                        }
                        if (SHIPS[i]->engSocket > 0)
                        {
                            net_send_dock(SClients[SHIPS[i]->engSocket], clientSocket->parentShip, SHIPS[i], flags);
                        }
                        if (clientSocket->parentShip->engSocket > 0)
                        {
                            net_send_dock(SClients[clientSocket->parentShip->engSocket], clientSocket->parentShip, SHIPS[i], flags);
                        }
                    }
                }
                break;
            }
            case NET_SUPPLIES:
            {
                qint32 flags = GetInt32((unsigned char *)data, 1);
                qint32 number = GetInt32((unsigned char *)data, 5);
                if (flags == SP_HP_ADD)
                {
                    clientSocket->parentShip->attribute[BN_HP].base += number;
                    if (clientSocket->parentShip->attribute[BN_HP].base > clientSocket->parentShip->attribute[BN_MAX_HP].Calculation())
                    {
                        clientSocket->parentShip->attribute[BN_HP].base = clientSocket->parentShip->attribute[BN_MAX_HP].Calculation();
                    }
                }
                if (flags == SP_HP_SUB)
                {
                    clientSocket->parentShip->attribute[BN_HP].base -= number;
                    if (clientSocket->parentShip->attribute[BN_HP].base < 0)
                    {
                        clientSocket->parentShip->attribute[BN_HP].base = 0;
                    }
                    if (clientSocket->parentShip->engSocket > 0)
                    {
                        net_send_damage(SClients[clientSocket->parentShip->engSocket], number);
                    }
                }
                if (flags == SP_OXYGEN_ADD)
                {
                    clientSocket->parentShip->attribute[BN_OXYGEN].base += number;
                    if (clientSocket->parentShip->attribute[BN_OXYGEN].base > clientSocket->parentShip->attribute[BN_MAX_OXYGEN].Calculation())
                    {
                        clientSocket->parentShip->attribute[BN_OXYGEN].base = clientSocket->parentShip->attribute[BN_MAX_OXYGEN].Calculation();
                    }
                }
                if (flags == SP_OXYGEN_SUB)
                {
                    clientSocket->parentShip->attribute[BN_OXYGEN].base -= number;
                    if (clientSocket->parentShip->attribute[BN_OXYGEN].base < 0)
                    {
                        clientSocket->parentShip->attribute[BN_OXYGEN].base = 0;
                    }
                }
                break;
            }
            case NET_SHOT:
            {
                SShot shot;
                shot.x = GetInt32((unsigned char *)data, 1);
                shot.y = GetInt32((unsigned char *)data, 5);
                shot.speed = GetInt32((unsigned char *)data, 9);
                shot.direction = GetInt32((unsigned char *)data, 13);
                shot.damage = GetInt32((unsigned char *)data, 17);
                shot.ttl = GetInt32((unsigned char *)data, 21);
                for (int i = 0; i < SHIPS.size(); i++)
                {
                    if (SHIPS[i] != clientSocket->parentShip)
                    {
                        if (SHIPS[i]->pilotSocket > 0)
                        {
                            net_send_shot(SClients[SHIPS[i]->pilotSocket], shot);
                        }
                        if (SHIPS[i]->navSocket > 0)
                        {
                            net_send_shot(SClients[SHIPS[i]->navSocket], shot);
                        }
                    }
                }
                break;
            }
            case NET_TRADE:
            {
                qint64 id = GetInt64((unsigned char *)data, 1);
                QString goal = GetString((char *)data, 9);
                CItem *item;
                for (int i = 0; i < idgen->item_list.size(); i++)
                {
                    if (idgen->item_list[i]->id == id)
                    {
                        item = idgen->item_list[i];
                    }
                }
                if (goal == "IRL")
                {
                    clientSocket->parentShip->item_list.removeAt(clientSocket->parentShip->item_list.indexOf(item));
                    irl_items.append(item);
                }
                else
                {
                    for (int i = 0; i < SHIPS.size(); i++)
                    {
                        if (SHIPS[i]->login == goal)
                        {
                            clientSocket->parentShip->item_list.removeAt(clientSocket->parentShip->item_list.indexOf(item));
                            SHIPS[i]->item_list.append(item);
                            if (SHIPS[i]->engSocket > 0)
                            {
                                net_send_item(SClients[SHIPS[i]->engSocket], item, ITEM_ID|ITEM_SET);
                            }
                        }
                    }
                }
                break;
            }
            case NET_ASTEROID:
            {
                qint32 x = GetInt32((unsigned char *)data, 1);
                if (x == 0x7FFFFFFF)
                {
                    net_send_asteroid(clientSocket, asteroids);
                    break;
                }
                qint32 y = GetInt32((unsigned char *)data, 5);
                qint32 type = GetInt32((unsigned char *)data, 9);
                qint32 num = GetInt32((unsigned char *)data, 13);
                for (int i = 0; i < asteroids.size(); i++)
                {
                    if ((asteroids[i]->x == x) && (asteroids[i]->y == y))
                    {
                        asteroids[i]->type = type;
                        asteroids[i]->num = num;
                        for (int j = 0; j < SHIPS.size(); j++)
                        {
                            if (SHIPS[j]->pilotSocket > 0)
                            {
                                net_send_asteroid(SClients[SHIPS[j]->pilotSocket], asteroids[i]);
                            }
                            if (SHIPS[j]->navSocket > 0)
                            {
                                net_send_asteroid(SClients[SHIPS[j]->navSocket], asteroids[i]);
                            }
                        }
                    }
                }
                break;
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

CDevourer* MainWindow::DevourerCreate(CItem* base)
{
    CDevourer* dev;
    dev = new CDevourer();
    connect(dev->timer, SIGNAL(timeout()), this, SLOT(DevourerTimeout()));
    dev->base = base;
    dev->nearest_asteroid = dev->FindNearestAsteroid(asteroids);
    if (dev->CanDig())
    {
        dev->timer->start(devour_time);
    }
    else
    {
        delete dev;
    }
    return dev;
}

void MainWindow::DevourerTimeout()
{
    CDevourer* dev;
    dev = ((CDevourerTimer*)sender())->owner;
    if (dev->nearest_asteroid->num > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            SpaceItemCreate(dev->base->pos.rx() + rand() % 200 - 100, dev->base->pos.ry() + rand() % 200 - 100, dev->nearest_asteroid->type);
        }
    }
    dev->nearest_asteroid->num = 0;
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->pilotSocket > 0)
        {
            net_send_asteroid(SClients[SHIPS[i]->pilotSocket], dev->nearest_asteroid);
        }
        if (SHIPS[i]->navSocket > 0)
        {
            net_send_asteroid(SClients[SHIPS[i]->navSocket], dev->nearest_asteroid);
        }
    }
    ComplexDeleteItem(dev->base);
    delete dev;
}


CItem* MainWindow::SpaceItemCreate(qint32 x, qint32 y, QString type)
{
    CItem* item;
    item = idgen->createItem(type);
    item->pos.setX(x);
    item->pos.setY(y);
    item->owner = SPACE;
    space_items.append(item);
    for (int i = 0; i < SHIPS.size(); i++)
    {
        if (SHIPS[i]->pilotSocket > 0)
        {
            net_send_item(SClients[SHIPS[i]->pilotSocket], item, ITEM_SET|ITEM_ID);
        }
        if (SHIPS[i]->navSocket > 0)
        {
            net_send_item(SClients[SHIPS[i]->navSocket], item, ITEM_SET|ITEM_ID);
        }
    }
    return item;
}
