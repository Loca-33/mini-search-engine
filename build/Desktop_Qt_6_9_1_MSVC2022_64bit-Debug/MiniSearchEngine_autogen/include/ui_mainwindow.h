/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *directoryLineEdit;
    QPushButton *selectDirectoryButton;
    QLabel *label;
    QTextEdit *queryTextEdit;
    QPushButton *searchButton;
    QLabel *label_2;
    QTextEdit *resultTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        directoryLineEdit = new QLineEdit(centralwidget);
        directoryLineEdit->setObjectName("directoryLineEdit");
        directoryLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(directoryLineEdit);

        selectDirectoryButton = new QPushButton(centralwidget);
        selectDirectoryButton->setObjectName("selectDirectoryButton");

        horizontalLayout->addWidget(selectDirectoryButton);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        queryTextEdit = new QTextEdit(centralwidget);
        queryTextEdit->setObjectName("queryTextEdit");

        verticalLayout->addWidget(queryTextEdit);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");

        verticalLayout->addWidget(searchButton);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        resultTextEdit = new QTextEdit(centralwidget);
        resultTextEdit->setObjectName("resultTextEdit");
        resultTextEdit->setReadOnly(true);

        verticalLayout->addWidget(resultTextEdit);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\277\267\344\275\240\346\220\234\347\264\242\345\274\225\346\223\216", nullptr));
        selectDirectoryButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\350\276\223\345\205\245(\347\254\254\344\270\200\350\241\214\344\270\272\346\237\245\350\257\242\346\225\260\347\233\256\357\274\214\345\220\216\351\235\242\346\257\217\350\241\214\344\270\200\344\270\252\346\237\245\350\257\242):", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\347\273\223\346\236\234:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
