/********************************************************************************
** Form generated from reading UI file 'docwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCWINDOW_H
#define UI_DOCWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_docWindow
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *textEdit;

    void setupUi(QDialog *docWindow)
    {
        if (docWindow->objectName().isEmpty())
            docWindow->setObjectName(QStringLiteral("docWindow"));
        docWindow->resize(906, 526);
        buttonBox = new QDialogButtonBox(docWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(550, 480, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textEdit = new QTextEdit(docWindow);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 911, 471));

        retranslateUi(docWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), docWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), docWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(docWindow);
    } // setupUi

    void retranslateUi(QDialog *docWindow)
    {
        docWindow->setWindowTitle(QApplication::translate("docWindow", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class docWindow: public Ui_docWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCWINDOW_H
