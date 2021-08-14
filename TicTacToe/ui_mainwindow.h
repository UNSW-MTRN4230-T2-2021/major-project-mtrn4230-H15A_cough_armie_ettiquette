/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionPower_Off;
    QAction *actionDocumentation;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QLabel *scoreLabel;
    QLabel *difficultyLabel;
    QLabel *whoseturnLabel;
    QLabel *matchnoLabel;
    QLabel *timerLabel;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionNew_Game = new QAction(MainWindow);
        actionNew_Game->setObjectName(QStringLiteral("actionNew_Game"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/menuimgs/images/NewGame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Game->setIcon(icon);
        actionPower_Off = new QAction(MainWindow);
        actionPower_Off->setObjectName(QStringLiteral("actionPower_Off"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/menuimgs/images/PowerOff.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPower_Off->setIcon(icon1);
        actionDocumentation = new QAction(MainWindow);
        actionDocumentation->setObjectName(QStringLiteral("actionDocumentation"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menuimgs/images/Help.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDocumentation->setIcon(icon2);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 230, 89, 25));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 80, 158, 131));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_8 = new QPushButton(layoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 0, 0, 1, 1);

        pushButton_10 = new QPushButton(layoutWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 0, 1, 1, 1);

        pushButton_9 = new QPushButton(layoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 0, 2, 1, 1);

        pushButton_11 = new QPushButton(layoutWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout->addWidget(pushButton_11, 1, 0, 1, 1);

        pushButton_12 = new QPushButton(layoutWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        gridLayout->addWidget(pushButton_12, 1, 1, 1, 1);

        pushButton_13 = new QPushButton(layoutWidget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        gridLayout->addWidget(pushButton_13, 1, 2, 1, 1);

        pushButton_14 = new QPushButton(layoutWidget);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        gridLayout->addWidget(pushButton_14, 2, 0, 1, 1);

        pushButton_15 = new QPushButton(layoutWidget);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));

        gridLayout->addWidget(pushButton_15, 2, 1, 1, 1);

        pushButton_16 = new QPushButton(layoutWidget);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));

        gridLayout->addWidget(pushButton_16, 2, 2, 1, 1);

        scoreLabel = new QLabel(centralwidget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setGeometry(QRect(440, 160, 151, 31));
        difficultyLabel = new QLabel(centralwidget);
        difficultyLabel->setObjectName(QStringLiteral("difficultyLabel"));
        difficultyLabel->setGeometry(QRect(440, 100, 171, 31));
        whoseturnLabel = new QLabel(centralwidget);
        whoseturnLabel->setObjectName(QStringLiteral("whoseturnLabel"));
        whoseturnLabel->setGeometry(QRect(230, 20, 131, 41));
        matchnoLabel = new QLabel(centralwidget);
        matchnoLabel->setObjectName(QStringLiteral("matchnoLabel"));
        matchnoLabel->setGeometry(QRect(440, 140, 121, 17));
        timerLabel = new QLabel(centralwidget);
        timerLabel->setObjectName(QStringLiteral("timerLabel"));
        timerLabel->setGeometry(QRect(510, 270, 161, 91));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuMenu->addAction(actionNew_Game);
        menuMenu->addAction(actionPower_Off);
        menuHelp->addAction(actionDocumentation);
        toolBar->addAction(actionNew_Game);
        toolBar->addAction(actionPower_Off);
        toolBar->addSeparator();
        toolBar->addAction(actionDocumentation);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNew_Game->setText(QApplication::translate("MainWindow", "New Game", Q_NULLPTR));
        actionPower_Off->setText(QApplication::translate("MainWindow", "Power Off", Q_NULLPTR));
        actionDocumentation->setText(QApplication::translate("MainWindow", "Documentation", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "End Turn", Q_NULLPTR));
        pushButton_8->setText(QString());
        pushButton_10->setText(QString());
        pushButton_9->setText(QString());
        pushButton_11->setText(QString());
        pushButton_12->setText(QString());
        pushButton_13->setText(QString());
        pushButton_14->setText(QString());
        pushButton_15->setText(QString());
        pushButton_16->setText(QString());
        scoreLabel->setText(QApplication::translate("MainWindow", "Wins: R | P | D", Q_NULLPTR));
        difficultyLabel->setText(QApplication::translate("MainWindow", "Difficulty: Easy/Hard", Q_NULLPTR));
        whoseturnLabel->setText(QApplication::translate("MainWindow", "Robot/Player Turn", Q_NULLPTR));
        matchnoLabel->setText(QApplication::translate("MainWindow", "Match No: X/3", Q_NULLPTR));
        timerLabel->setText(QApplication::translate("MainWindow", "Time Left:", Q_NULLPTR));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
