#include "cbot.h"

CBot::CBot()
{
    timer = new CBotTimer();
    timer->owner = this;
    update_timer = new CBotTimer;
    update_timer->owner = this;
    active = 0;
    ready_to_send = 1;
    net_id = 0;
    connect(update_timer, SIGNAL(timeout()), this, SLOT(Update()));
    setActive(1);
}

void CBot::setActive(qint8 a)
{
    active = a;
    if (active)
    {
        update_timer->start(time_update);
    }
    else
    {
        update_timer->stop();
        timer->stop();
    }
}

void CBot::Update()
{
    ExecuteCommand();
    ready_to_send = 1;
}

CBot::~CBot()
{

}

void CBot::ExecuteCommand()
{
    if (commands_list.size() > 0)
    {
        CBotCommand* com;
        com = commands_list[0];
        switch (com->type)
        {
        case BC_RETURN:
            direction = point_direction(x, y, boss->x, boss->y);
            speed = min(max_speed, point_distance(x, y, boss->x, boss->y));
            x += cos(direction) * speed;
            y += sin(direction) * speed;
            if (point_distance(x, y, boss->x, boss->y) < 1000)
            {
                commands_list.removeFirst();
                //setActive(0);
                delete com;
            }
            break;
        case BC_GO:
            direction =  point_direction(x, y, com->x, com->y);
            speed = min(max_speed, point_distance(x, y, com->x, com->y));
            x += cos(direction) * speed;
            y += sin(direction) * speed;
            if (point_distance(x, y, com->x, com->y) < 1000)
            {
                commands_list.removeFirst();
                //setActive(0);
                delete com;
            }
            break;
        case BC_ATTACK:
            direction =  point_direction(x, y, com->goal->shell->pos->pos->rx(), com->goal->shell->pos->pos->ry());
            speed = min(max_speed, point_distance(x, y, com->goal->shell->pos->pos->rx(), com->goal->shell->pos->pos->ry()));
            x += cos(direction) * speed;
            y += sin(direction) * speed;
            if (point_distance(x, y, com->goal->shell->pos->pos->rx(), com->goal->shell->pos->pos->ry()) < 1000)
            {
                commands_list.clear();
                active = -1;
                CBotCommand *new_com;
                new_com = new CBotCommand();
                new_com->GoToBoss();
                commands_list.append(new_com);
                delete com;
            }
            break;
        }
    }
    else
    {
        speed = 0;
    }
}

CBotCommand::CBotCommand()
{

}

void CBotCommand::GoToBoss()
{
    type = BC_RETURN;
    x = owner->boss->x;
    y = owner->boss->y;
    //direction = atan((y - owner->y) / (x - owner->x));
}

void CBotCommand::GoToCoordinate(qint64 l_x, qint64 l_y)
{
    type = BC_GO;
    x = l_x;
    y = l_y;
}
void CBotCommand::Drop(CBot* bot)
{
    type = BC_DROP;
    bot_to_drop = bot;
}

void CBotCommand::Drop(CItem* item)
{
    type = BC_DROP;
    item_to_drop = item;
}

void CBotCommand::GoToShip(CShip* goal)
{
    type = BC_ATTACK;
    x = goal->shell->pos->pos->rx();
    y = goal->shell->pos->pos->ry();
}



CMiner::CMiner()
{
    time_update = 10000;
    hp = 50;
    max_speed = 0;
    name = "obj_miner";
}

CCarryall::CCarryall()
{
    time_update = 500;
    hp = 20;
    max_speed = 150;
    name = "obj_carryall";
}

CAnomaly::CAnomaly()
{
    time_update = 10000;
    hp = 100;
    max_speed = 0;
    name = "obj_anomaly";
}

CFinder::CFinder()
{
    time_update = 100;
    hp = 30;
    max_speed = 90;
    name = "obj_finder";
}

CHyperMind::CHyperMind()
{
    for (int i = 1; i < 1000; i++)
    {
        id_list.append(i);
    }
    time_update = 10000;
    hp = 100000;
    hp_add = 0;
    name = "obj_hyper_mind";
    x = 165000;
    y = 105000;
    bots.append(this);
}

void CHyperMind::BotCreate(qint32 type, qint8 act)
{
    CBot *bot;
    switch(type)
    {
    case MINER:
        bot = new CMiner();
        break;
    case CARRYALL:
        bot = new CCarryall();
        break;
    case ANOMALY:
        bot = new CAnomaly();
        break;
    case FINDER:
        bot = new CFinder();
        break;
    default:
        bot = new CBot();
    }
    bot->boss = this;
    bot->active = act;
    bot->x = x;
    bot->y = y;
    bot->net_id = id_list.first();
    id_list.removeFirst();
    bots.append(bot);
    if (type == CARRYALL)
    {
        carryalls.append(static_cast <CCarryall*> (bot));
    }
    if (bot->active)
    {
        bot->update_timer->start(bot->time_update);
    }
    ChangeData();
}

void CHyperMind::MinerCreate()
{
    BotCreate (MINER, 1);
}

void CHyperMind::CarryallCreate()
{
    BotCreate (CARRYALL, 1);
}

void CHyperMind::AnomalyCreate()
{
    BotCreate (ANOMALY, 1);
}

void CHyperMind::FinderCreate()
{
    BotCreate (FINDER, 1);
}

void CHyperMind::BotDead()
{

}

void CHyperMind::ComAddBack()
{
    if (my_bots->currentRow() > -1)
    {
        CBot *bot;
        bot = bots[my_bots->currentRow()];
        CBotCommand* com;
        com = new CBotCommand;
        com->owner = bot;
        com->GoToBoss();
        bot->commands_list.append(com);
    }
}

void CHyperMind::ComAddGo()
{
    if (my_bots->currentRow() > -1)
    {
        CBot *bot;
        bot = bots[my_bots->currentRow()];
        CBotCommand* com;
        com = new CBotCommand;
        com->owner = bot;
        com->GoToCoordinate(comx->text().toInt(), comy->text().toInt());
        bot->commands_list.append(com);
    }
}

void CHyperMind::ComAddDrop()
{
    CBot *bot;
    bot = bots[my_bots->currentRow()];
    CBotCommand* com;
    com = new CBotCommand;
    com->owner = bot;
    if (items_view->currentRow() > -1)
    {
        com->Drop(bot->item_list[items_view->currentRow()]);
    }
    bot->commands_list.append(com);
}

void CHyperMind::ComAddAttack()
{

}


void CHyperMind::ChangeData()
{
    my_bots->clear();
    for (int i = 0; i < bots.size(); i++)
    {
        my_bots->addItem(bots[i]->name);
    }
}


CBotTimer::CBotTimer()
{

}

