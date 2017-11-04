/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton2;
    QLineEdit *mPageEdit;
    QLabel *label;
    QLineEdit *mWikiEdit;
    QLabel *label_3;
    QPlainTextEdit *plainTextEdit;
    QGridLayout *gridLayout_2;
    QLineEdit *mLoginEdit;
    QLabel *label_2;
    QLabel *mMdpLabel;
    QLineEdit *mMdpEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton1;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 376);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton2 = new QPushButton(centralWidget);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        pushButton2->setEnabled(false);

        gridLayout->addWidget(pushButton2, 1, 3, 1, 1);

        mPageEdit = new QLineEdit(centralWidget);
        mPageEdit->setObjectName(QStringLiteral("mPageEdit"));

        gridLayout->addWidget(mPageEdit, 1, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        mWikiEdit = new QLineEdit(centralWidget);
        mWikiEdit->setObjectName(QStringLiteral("mWikiEdit"));

        gridLayout->addWidget(mWikiEdit, 0, 1, 1, 3);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mLoginEdit = new QLineEdit(centralWidget);
        mLoginEdit->setObjectName(QStringLiteral("mLoginEdit"));

        gridLayout_2->addWidget(mLoginEdit, 0, 3, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        mMdpLabel = new QLabel(centralWidget);
        mMdpLabel->setObjectName(QStringLiteral("mMdpLabel"));

        gridLayout_2->addWidget(mMdpLabel, 1, 1, 1, 1);

        mMdpEdit = new QLineEdit(centralWidget);
        mMdpEdit->setObjectName(QStringLiteral("mMdpEdit"));
        mMdpEdit->setAcceptDrops(true);
        mMdpEdit->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(mMdpEdit, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 4, 1, 1);

        pushButton1 = new QPushButton(centralWidget);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        pushButton1->setEnabled(false);

        gridLayout_2->addWidget(pushButton1, 1, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        pushButton2->setText(QApplication::translate("MainWindow", "Load page", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Page : ", Q_NULLPTR));
        mWikiEdit->setText(QApplication::translate("MainWindow", "https://test.wikipedia.org/w/api.php", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Wiki :", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Username:", Q_NULLPTR));
        mMdpLabel->setText(QApplication::translate("MainWindow", "Password:", Q_NULLPTR));
        pushButton1->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
