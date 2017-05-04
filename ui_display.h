/********************************************************************************
** Form generated from reading UI file 'display.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Display
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTreeView *fileExplorer;
    QPushButton *stabVideoButton;

    void setupUi(QWidget *Display)
    {
        if (Display->objectName().isEmpty())
            Display->setObjectName(QStringLiteral("Display"));
        Display->resize(1200, 722);
        Display->setMaximumSize(QSize(1200, 722));
        horizontalLayout = new QHBoxLayout(Display);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        fileExplorer = new QTreeView(Display);
        fileExplorer->setObjectName(QStringLiteral("fileExplorer"));
        fileExplorer->setMinimumSize(QSize(300, 0));
        fileExplorer->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        fileExplorer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fileExplorer->setAutoScroll(true);
        fileExplorer->setRootIsDecorated(false);

        verticalLayout->addWidget(fileExplorer);

        stabVideoButton = new QPushButton(Display);
        stabVideoButton->setObjectName(QStringLiteral("stabVideoButton"));
        stabVideoButton->setMinimumSize(QSize(200, 0));
        QFont font;
        font.setPointSize(7);
        stabVideoButton->setFont(font);

        verticalLayout->addWidget(stabVideoButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Display);

        QMetaObject::connectSlotsByName(Display);
    } // setupUi

    void retranslateUi(QWidget *Display)
    {
        Display->setWindowTitle(QApplication::translate("Display", "Display", Q_NULLPTR));
        stabVideoButton->setText(QApplication::translate("Display", "Stabilize Video", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Display: public Ui_Display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_H
