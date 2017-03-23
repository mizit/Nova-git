/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListView *log;
    QTableView *tableView;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QLineEdit *editLogin;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *editPass;
    QPushButton *buttonUsrCrt;
    QComboBox *cbox_shelltype;
    QLabel *label_3;
    QWidget *tab_3;
    QComboBox *combo_userpos;
    QGroupBox *groupBox_2;
    QLabel *label_x;
    QLabel *label_y;
    QLabel *label_ia;
    QLabel *label_4;
    QLabel *lable_rspeed;
    QLabel *lable_dir;
    QLineEdit *edit_x;
    QLineEdit *edit_y;
    QLineEdit *edit_speed;
    QLineEdit *edit_ia;
    QLineEdit *edit_rspeed;
    QLineEdit *edit_dir;
    QPushButton *button_lockpos;
    QPushButton *button_setpos;
    QGroupBox *groupBox_3;
    QPushButton *button_add_item;
    QListWidget *lview_items;
    QListWidget *lview_inv;
    QPushButton *btn_delItem;
    QGroupBox *groupBox_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *edit_air_output;
    QLineEdit *edit_air_bank;
    QLineEdit *edit_safely;
    QLineEdit *edit_radio_range;
    QLineEdit *edit_system_level;
    QLineEdit *edit_radar_range;
    QLineEdit *edit_man_drive;
    QLineEdit *edit_back_drive;
    QLineEdit *edit_main_drive;
    QLineEdit *edit_weapon_num;
    QLineEdit *edit_mass;
    QPushButton *pushButton;
    QPushButton *btn_save;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1184, 647);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1161, 591));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        log = new QListView(tab);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(620, 10, 531, 531));
        tableView = new QTableView(tab);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 551, 531));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 171, 241));
        editLogin = new QLineEdit(groupBox);
        editLogin->setObjectName(QStringLiteral("editLogin"));
        editLogin->setGeometry(QRect(30, 40, 113, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 47, 13));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 70, 47, 13));
        editPass = new QLineEdit(groupBox);
        editPass->setObjectName(QStringLiteral("editPass"));
        editPass->setGeometry(QRect(30, 90, 113, 20));
        buttonUsrCrt = new QPushButton(groupBox);
        buttonUsrCrt->setObjectName(QStringLiteral("buttonUsrCrt"));
        buttonUsrCrt->setGeometry(QRect(60, 200, 75, 23));
        cbox_shelltype = new QComboBox(groupBox);
        cbox_shelltype->setObjectName(QStringLiteral("cbox_shelltype"));
        cbox_shelltype->setGeometry(QRect(30, 150, 111, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 130, 47, 13));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        combo_userpos = new QComboBox(tab_3);
        combo_userpos->setObjectName(QStringLiteral("combo_userpos"));
        combo_userpos->setGeometry(QRect(20, 20, 121, 22));
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(170, 20, 281, 201));
        label_x = new QLabel(groupBox_2);
        label_x->setObjectName(QStringLiteral("label_x"));
        label_x->setGeometry(QRect(20, 20, 47, 13));
        label_x->setToolTipDuration(-1);
        label_y = new QLabel(groupBox_2);
        label_y->setObjectName(QStringLiteral("label_y"));
        label_y->setGeometry(QRect(20, 70, 47, 13));
        label_ia = new QLabel(groupBox_2);
        label_ia->setObjectName(QStringLiteral("label_ia"));
        label_ia->setGeometry(QRect(150, 20, 61, 16));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 120, 47, 13));
        lable_rspeed = new QLabel(groupBox_2);
        lable_rspeed->setObjectName(QStringLiteral("lable_rspeed"));
        lable_rspeed->setGeometry(QRect(150, 70, 61, 16));
        lable_dir = new QLabel(groupBox_2);
        lable_dir->setObjectName(QStringLiteral("lable_dir"));
        lable_dir->setGeometry(QRect(150, 120, 47, 13));
        edit_x = new QLineEdit(groupBox_2);
        edit_x->setObjectName(QStringLiteral("edit_x"));
        edit_x->setGeometry(QRect(20, 40, 113, 20));
        edit_y = new QLineEdit(groupBox_2);
        edit_y->setObjectName(QStringLiteral("edit_y"));
        edit_y->setGeometry(QRect(20, 90, 113, 20));
        edit_speed = new QLineEdit(groupBox_2);
        edit_speed->setObjectName(QStringLiteral("edit_speed"));
        edit_speed->setGeometry(QRect(20, 140, 113, 20));
        edit_ia = new QLineEdit(groupBox_2);
        edit_ia->setObjectName(QStringLiteral("edit_ia"));
        edit_ia->setGeometry(QRect(150, 40, 113, 20));
        edit_rspeed = new QLineEdit(groupBox_2);
        edit_rspeed->setObjectName(QStringLiteral("edit_rspeed"));
        edit_rspeed->setGeometry(QRect(150, 90, 113, 20));
        edit_dir = new QLineEdit(groupBox_2);
        edit_dir->setObjectName(QStringLiteral("edit_dir"));
        edit_dir->setGeometry(QRect(150, 140, 113, 20));
        button_lockpos = new QPushButton(groupBox_2);
        button_lockpos->setObjectName(QStringLiteral("button_lockpos"));
        button_lockpos->setGeometry(QRect(20, 170, 75, 23));
        button_setpos = new QPushButton(groupBox_2);
        button_setpos->setObjectName(QStringLiteral("button_setpos"));
        button_setpos->setGeometry(QRect(150, 170, 75, 23));
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(470, 20, 531, 491));
        button_add_item = new QPushButton(groupBox_3);
        button_add_item->setObjectName(QStringLiteral("button_add_item"));
        button_add_item->setGeometry(QRect(320, 450, 75, 23));
        lview_items = new QListWidget(groupBox_3);
        lview_items->setObjectName(QStringLiteral("lview_items"));
        lview_items->setGeometry(QRect(280, 20, 231, 421));
        lview_inv = new QListWidget(groupBox_3);
        lview_inv->setObjectName(QStringLiteral("lview_inv"));
        lview_inv->setGeometry(QRect(10, 20, 256, 451));
        btn_delItem = new QPushButton(groupBox_3);
        btn_delItem->setObjectName(QStringLiteral("btn_delItem"));
        btn_delItem->setGeometry(QRect(410, 450, 75, 23));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(130, 240, 321, 311));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 61, 16));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(110, 20, 47, 13));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(210, 20, 47, 13));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(210, 80, 71, 16));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 80, 71, 16));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(110, 80, 61, 16));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(210, 140, 61, 16));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 140, 61, 16));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(110, 140, 61, 16));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 200, 47, 13));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(110, 200, 71, 16));
        edit_air_output = new QLineEdit(groupBox_4);
        edit_air_output->setObjectName(QStringLiteral("edit_air_output"));
        edit_air_output->setGeometry(QRect(10, 50, 71, 20));
        edit_air_bank = new QLineEdit(groupBox_4);
        edit_air_bank->setObjectName(QStringLiteral("edit_air_bank"));
        edit_air_bank->setGeometry(QRect(110, 50, 71, 20));
        edit_safely = new QLineEdit(groupBox_4);
        edit_safely->setObjectName(QStringLiteral("edit_safely"));
        edit_safely->setGeometry(QRect(210, 50, 71, 20));
        edit_radio_range = new QLineEdit(groupBox_4);
        edit_radio_range->setObjectName(QStringLiteral("edit_radio_range"));
        edit_radio_range->setGeometry(QRect(110, 110, 71, 20));
        edit_system_level = new QLineEdit(groupBox_4);
        edit_system_level->setObjectName(QStringLiteral("edit_system_level"));
        edit_system_level->setGeometry(QRect(210, 110, 71, 20));
        edit_radar_range = new QLineEdit(groupBox_4);
        edit_radar_range->setObjectName(QStringLiteral("edit_radar_range"));
        edit_radar_range->setGeometry(QRect(10, 110, 71, 20));
        edit_man_drive = new QLineEdit(groupBox_4);
        edit_man_drive->setObjectName(QStringLiteral("edit_man_drive"));
        edit_man_drive->setGeometry(QRect(110, 170, 71, 20));
        edit_back_drive = new QLineEdit(groupBox_4);
        edit_back_drive->setObjectName(QStringLiteral("edit_back_drive"));
        edit_back_drive->setGeometry(QRect(210, 170, 71, 20));
        edit_main_drive = new QLineEdit(groupBox_4);
        edit_main_drive->setObjectName(QStringLiteral("edit_main_drive"));
        edit_main_drive->setGeometry(QRect(10, 170, 71, 20));
        edit_weapon_num = new QLineEdit(groupBox_4);
        edit_weapon_num->setObjectName(QStringLiteral("edit_weapon_num"));
        edit_weapon_num->setGeometry(QRect(110, 230, 71, 20));
        edit_mass = new QLineEdit(groupBox_4);
        edit_mass->setObjectName(QStringLiteral("edit_mass"));
        edit_mass->setGeometry(QRect(10, 230, 71, 20));
        tabWidget->addTab(tab_3, QString());
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1090, 0, 75, 23));
        btn_save = new QPushButton(centralWidget);
        btn_save->setObjectName(QStringLiteral("btn_save"));
        btn_save->setGeometry(QRect(1000, 0, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1184, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\320\236\320\261\321\211\320\265\320\265", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "User creating", 0));
        label->setText(QApplication::translate("MainWindow", "Login", 0));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0));
        buttonUsrCrt->setText(QApplication::translate("MainWindow", "Create", 0));
        label_3->setText(QApplication::translate("MainWindow", "Shell type", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        label_x->setText(QApplication::translate("MainWindow", "x", 0));
        label_y->setText(QApplication::translate("MainWindow", "y", 0));
        label_ia->setText(QApplication::translate("MainWindow", "image_angle", 0));
        label_4->setText(QApplication::translate("MainWindow", "speed", 0));
        lable_rspeed->setText(QApplication::translate("MainWindow", "rot_speed", 0));
        lable_dir->setText(QApplication::translate("MainWindow", "direction", 0));
        button_lockpos->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\273\320\276\321\207\320\270\321\202\321\214", 0));
        button_setpos->setText(QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Inventory", 0));
        button_add_item->setText(QApplication::translate("MainWindow", "Add Item", 0));
        btn_delItem->setText(QApplication::translate("MainWindow", "Del Item", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Status", 0));
        label_5->setText(QApplication::translate("MainWindow", "air_output", 0));
        label_6->setText(QApplication::translate("MainWindow", "air_bank", 0));
        label_7->setText(QApplication::translate("MainWindow", "safely", 0));
        label_8->setText(QApplication::translate("MainWindow", "system_level", 0));
        label_9->setText(QApplication::translate("MainWindow", "radar_range", 0));
        label_10->setText(QApplication::translate("MainWindow", "radio_range", 0));
        label_11->setText(QApplication::translate("MainWindow", "back_drive", 0));
        label_12->setText(QApplication::translate("MainWindow", "main_drive", 0));
        label_13->setText(QApplication::translate("MainWindow", "man_drive", 0));
        label_15->setText(QApplication::translate("MainWindow", "mass", 0));
        label_16->setText(QApplication::translate("MainWindow", "weapon_num", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        btn_save->setText(QApplication::translate("MainWindow", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
