/********************************************************************************
** Form generated from reading UI file 'userinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QAction *actionNew_Game;
    QAction *actionPower_Off;
    QAction *actionDocumentation;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *widget;
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
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuHelp;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QStringLiteral("UserInterface"));
        UserInterface->resize(756, 482);
        actionNew_Game = new QAction(UserInterface);
        actionNew_Game->setObjectName(QStringLiteral("actionNew_Game"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/menuimgs/images/NewGame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Game->setIcon(icon);
        actionPower_Off = new QAction(UserInterface);
        actionPower_Off->setObjectName(QStringLiteral("actionPower_Off"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/menuimgs/images/PowerOff.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPower_Off->setIcon(icon1);
        actionDocumentation = new QAction(UserInterface);
        actionDocumentation->setObjectName(QStringLiteral("actionDocumentation"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menuimgs/images/Help.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDocumentation->setIcon(icon2);
        centralwidget = new QWidget(UserInterface);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(510, 300, 97, 50));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(320, 320, 89, 25));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(510, 20, 171, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(510, 80, 151, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(510, 60, 121, 17));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(300, 70, 131, 41));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(300, 130, 131, 131));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_8 = new QPushButton(widget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 0, 0, 1, 1);

        pushButton_10 = new QPushButton(widget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 0, 1, 1, 1);

        pushButton_9 = new QPushButton(widget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 0, 2, 1, 1);

        pushButton_11 = new QPushButton(widget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout->addWidget(pushButton_11, 1, 0, 1, 1);

        pushButton_12 = new QPushButton(widget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        gridLayout->addWidget(pushButton_12, 1, 1, 1, 1);

        pushButton_13 = new QPushButton(widget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        gridLayout->addWidget(pushButton_13, 1, 2, 1, 1);

        pushButton_14 = new QPushButton(widget);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        gridLayout->addWidget(pushButton_14, 2, 0, 1, 1);

        pushButton_15 = new QPushButton(widget);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));

        gridLayout->addWidget(pushButton_15, 2, 1, 1, 1);

        pushButton_16 = new QPushButton(widget);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));

        gridLayout->addWidget(pushButton_16, 2, 2, 1, 1);

        UserInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserInterface);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 756, 22));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        UserInterface->setMenuBar(menubar);
        toolBar = new QToolBar(UserInterface);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        UserInterface->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(UserInterface);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UserInterface->setStatusBar(statusBar);

        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuMenu->addAction(actionNew_Game);
        menuMenu->addAction(actionPower_Off);
        menuHelp->addAction(actionDocumentation);
        toolBar->addAction(actionNew_Game);
        toolBar->addAction(actionPower_Off);
        toolBar->addSeparator();
        toolBar->addAction(actionDocumentation);

        retranslateUi(UserInterface);

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QMainWindow *UserInterface)
    {
        UserInterface->setWindowTitle(QApplication::translate("UserInterface", "UserInterface", Q_NULLPTR));
        actionNew_Game->setText(QApplication::translate("UserInterface", "New Game ", Q_NULLPTR));
        actionPower_Off->setText(QApplication::translate("UserInterface", "Power Off", Q_NULLPTR));
        actionDocumentation->setText(QApplication::translate("UserInterface", "Documentation", Q_NULLPTR));
        label->setText(QApplication::translate("UserInterface", "Move Time: ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("UserInterface", "End Turn", Q_NULLPTR));
        label_2->setText(QApplication::translate("UserInterface", "Difficulty: Easy/Hard", Q_NULLPTR));
        label_3->setText(QApplication::translate("UserInterface", "Wins: R | P | D", Q_NULLPTR));
        label_4->setText(QApplication::translate("UserInterface", "Match No: X/3", Q_NULLPTR));
        label_5->setText(QApplication::translate("UserInterface", "Robot/Player Turn", Q_NULLPTR));
        pushButton_8->setText(QString());
        pushButton_10->setText(QString());
        pushButton_9->setText(QString());
        pushButton_11->setText(QString());
        pushButton_12->setText(QString());
        pushButton_13->setText(QString());
        pushButton_14->setText(QString());
        pushButton_15->setText(QString());
        pushButton_16->setText(QString());
        menuMenu->setTitle(QApplication::translate("UserInterface", "Menu", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("UserInterface", "Help", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("UserInterface", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
