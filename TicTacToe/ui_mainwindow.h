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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionPower_Off;
    QAction *actionDocumentation;
    QWidget *centralwidget;
    QLabel *whoseTurnLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *difficultyLabel;
    QLabel *timerLabel;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *matchnoLabel;
    QLabel *scoreLabel;
    QPushButton *pBEndTurn;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QPushButton *pBR1C1;
    QPushButton *pBR1C2;
    QPushButton *pBR1C3;
    QPushButton *pBR2C1;
    QPushButton *pBR2C2;
    QPushButton *pBR2C3;
    QPushButton *pBR3C1;
    QPushButton *pBR3C2;
    QPushButton *pBR3C3;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(722, 456);
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
        whoseTurnLabel = new QLabel(centralwidget);
        whoseTurnLabel->setObjectName(QStringLiteral("whoseTurnLabel"));
        whoseTurnLabel->setGeometry(QRect(170, 20, 351, 71));
        QFont font;
        font.setPointSize(30);
        whoseTurnLabel->setFont(font);
        whoseTurnLabel->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(480, 130, 231, 72));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        difficultyLabel = new QLabel(layoutWidget);
        difficultyLabel->setObjectName(QStringLiteral("difficultyLabel"));
        QFont font1;
        font1.setPointSize(20);
        difficultyLabel->setFont(font1);

        verticalLayout->addWidget(difficultyLabel);

        timerLabel = new QLabel(layoutWidget);
        timerLabel->setObjectName(QStringLiteral("timerLabel"));
        timerLabel->setFont(font1);

        verticalLayout->addWidget(timerLabel);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 132, 261, 72));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        matchnoLabel = new QLabel(layoutWidget1);
        matchnoLabel->setObjectName(QStringLiteral("matchnoLabel"));
        matchnoLabel->setFont(font1);

        verticalLayout_2->addWidget(matchnoLabel);

        scoreLabel = new QLabel(layoutWidget1);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setFont(font1);

        verticalLayout_2->addWidget(scoreLabel);

        pBEndTurn = new QPushButton(centralwidget);
        pBEndTurn->setObjectName(QStringLiteral("pBEndTurn"));
        pBEndTurn->setGeometry(QRect(290, 260, 117, 40));
        pBEndTurn->setFont(font1);
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(272, 112, 158, 131));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pBR1C1 = new QPushButton(layoutWidget2);
        pBR1C1->setObjectName(QStringLiteral("pBR1C1"));

        gridLayout->addWidget(pBR1C1, 0, 0, 1, 1);

        pBR1C2 = new QPushButton(layoutWidget2);
        pBR1C2->setObjectName(QStringLiteral("pBR1C2"));

        gridLayout->addWidget(pBR1C2, 0, 1, 1, 1);

        pBR1C3 = new QPushButton(layoutWidget2);
        pBR1C3->setObjectName(QStringLiteral("pBR1C3"));

        gridLayout->addWidget(pBR1C3, 0, 2, 1, 1);

        pBR2C1 = new QPushButton(layoutWidget2);
        pBR2C1->setObjectName(QStringLiteral("pBR2C1"));

        gridLayout->addWidget(pBR2C1, 1, 0, 1, 1);

        pBR2C2 = new QPushButton(layoutWidget2);
        pBR2C2->setObjectName(QStringLiteral("pBR2C2"));

        gridLayout->addWidget(pBR2C2, 1, 1, 1, 1);

        pBR2C3 = new QPushButton(layoutWidget2);
        pBR2C3->setObjectName(QStringLiteral("pBR2C3"));

        gridLayout->addWidget(pBR2C3, 1, 2, 1, 1);

        pBR3C1 = new QPushButton(layoutWidget2);
        pBR3C1->setObjectName(QStringLiteral("pBR3C1"));

        gridLayout->addWidget(pBR3C1, 2, 0, 1, 1);

        pBR3C2 = new QPushButton(layoutWidget2);
        pBR3C2->setObjectName(QStringLiteral("pBR3C2"));

        gridLayout->addWidget(pBR3C2, 2, 1, 1, 1);

        pBR3C3 = new QPushButton(layoutWidget2);
        pBR3C3->setObjectName(QStringLiteral("pBR3C3"));

        gridLayout->addWidget(pBR3C3, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 722, 22));
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
        whoseTurnLabel->setText(QApplication::translate("MainWindow", "--", Q_NULLPTR));
        difficultyLabel->setText(QApplication::translate("MainWindow", "Difficulty: --", Q_NULLPTR));
        timerLabel->setText(QApplication::translate("MainWindow", "Time Left:", Q_NULLPTR));
        matchnoLabel->setText(QApplication::translate("MainWindow", "Match No: --", Q_NULLPTR));
        scoreLabel->setText(QApplication::translate("MainWindow", "Wins: --", Q_NULLPTR));
        pBEndTurn->setText(QApplication::translate("MainWindow", "End Turn", Q_NULLPTR));
        pBR1C1->setText(QString());
        pBR1C2->setText(QString());
        pBR1C3->setText(QString());
        pBR2C1->setText(QString());
        pBR2C2->setText(QString());
        pBR2C3->setText(QString());
        pBR3C1->setText(QString());
        pBR3C2->setText(QString());
        pBR3C3->setText(QString());
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
