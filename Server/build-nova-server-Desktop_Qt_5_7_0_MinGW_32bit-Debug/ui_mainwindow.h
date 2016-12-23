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
        groupBox->setGeometry(QRect(10, 10, 171, 171));
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
        buttonUsrCrt->setGeometry(QRect(70, 130, 75, 23));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        combo_userpos = new QComboBox(tab_3);
        combo_userpos->setObjectName(QStringLiteral("combo_userpos"));
        combo_userpos->setGeometry(QRect(20, 20, 121, 22));
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(180, 40, 281, 191));
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
        tabWidget->addTab(tab_3, QString());
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
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        label_x->setText(QApplication::translate("MainWindow", "x", 0));
        label_y->setText(QApplication::translate("MainWindow", "y", 0));
        label_ia->setText(QApplication::translate("MainWindow", "image_angle", 0));
        label_4->setText(QApplication::translate("MainWindow", "speed", 0));
        lable_rspeed->setText(QApplication::translate("MainWindow", "rot_speed", 0));
        lable_dir->setText(QApplication::translate("MainWindow", "direction", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
