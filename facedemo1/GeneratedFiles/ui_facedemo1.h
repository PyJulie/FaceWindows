/********************************************************************************
** Form generated from reading UI file 'facedemo1.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEDEMO1_H
#define UI_FACEDEMO1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_facedemo1Class
{
public:
    QWidget *centralWidget;
    QPushButton *showstuinfo;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_3;
    QGraphicsView *graphicsView_3;
    QFrame *line_3;
    QWidget *tab_2;
    QGraphicsView *graphicsView_2;
    QFrame *line_2;
    QLabel *label_2;
    QWidget *tab_3;
    QGraphicsView *graphicsView_4;
    QFrame *line_4;
    QLabel *label_4;
    QWidget *tab_4;
    QGraphicsView *graphicsView_5;
    QFrame *line_5;
    QLabel *label_5;
    QWidget *tab_5;
    QGraphicsView *graphicsView_6;
    QFrame *line_6;
    QLabel *label_6;
    QPushButton *up_load_image_button;
    QPushButton *pushButton;
    QGraphicsView *base_image_view;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *facedemo1Class)
    {
        if (facedemo1Class->objectName().isEmpty())
            facedemo1Class->setObjectName(QStringLiteral("facedemo1Class"));
        facedemo1Class->resize(1474, 761);
        centralWidget = new QWidget(facedemo1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        showstuinfo = new QPushButton(centralWidget);
        showstuinfo->setObjectName(QStringLiteral("showstuinfo"));
        showstuinfo->setGeometry(QRect(600, 570, 101, 41));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(480, 10, 941, 531));
        tabWidget->setAcceptDrops(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(43, 300, 251, 20));
        label_3->setAlignment(Qt::AlignCenter);
        graphicsView_3 = new QGraphicsView(tab);
        graphicsView_3->setObjectName(QStringLiteral("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(40, 20, 256, 256));
        line_3 = new QFrame(tab);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(330, 0, 20, 511));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        graphicsView_2 = new QGraphicsView(tab_2);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(40, 20, 256, 256));
        line_2 = new QFrame(tab_2);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(330, 0, 20, 511));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(43, 300, 251, 20));
        label_2->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        graphicsView_4 = new QGraphicsView(tab_3);
        graphicsView_4->setObjectName(QStringLiteral("graphicsView_4"));
        graphicsView_4->setGeometry(QRect(40, 20, 256, 256));
        line_4 = new QFrame(tab_3);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(330, 0, 20, 511));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(43, 300, 251, 20));
        label_4->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        graphicsView_5 = new QGraphicsView(tab_4);
        graphicsView_5->setObjectName(QStringLiteral("graphicsView_5"));
        graphicsView_5->setGeometry(QRect(40, 20, 256, 256));
        line_5 = new QFrame(tab_4);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(330, 0, 20, 511));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(43, 300, 251, 20));
        label_5->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        graphicsView_6 = new QGraphicsView(tab_5);
        graphicsView_6->setObjectName(QStringLiteral("graphicsView_6"));
        graphicsView_6->setGeometry(QRect(40, 20, 256, 256));
        line_6 = new QFrame(tab_5);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(330, 0, 20, 511));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(tab_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(43, 300, 251, 20));
        label_6->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_5, QString());
        up_load_image_button = new QPushButton(centralWidget);
        up_load_image_button->setObjectName(QStringLiteral("up_load_image_button"));
        up_load_image_button->setGeometry(QRect(170, 570, 111, 41));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 660, 75, 23));
        base_image_view = new QGraphicsView(centralWidget);
        base_image_view->setObjectName(QStringLiteral("base_image_view"));
        base_image_view->setGeometry(QRect(10, 10, 431, 531));
        facedemo1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(facedemo1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1474, 23));
        facedemo1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(facedemo1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        facedemo1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(facedemo1Class);
        QObject::connect(up_load_image_button, SIGNAL(clicked()), facedemo1Class, SLOT(UpLoadImageButtonClicked()));

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(facedemo1Class);
    } // setupUi

    void retranslateUi(QMainWindow *facedemo1Class)
    {
        facedemo1Class->setWindowTitle(QApplication::translate("facedemo1Class", "facedemo1", 0));
        showstuinfo->setText(QApplication::translate("facedemo1Class", "PushButton", 0));
        label_3->setText(QApplication::translate("facedemo1Class", "No face", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("facedemo1Class", "1", 0));
        label_2->setText(QApplication::translate("facedemo1Class", "No face", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("facedemo1Class", "2", 0));
        label_4->setText(QApplication::translate("facedemo1Class", "No face", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("facedemo1Class", "3", 0));
        label_5->setText(QApplication::translate("facedemo1Class", "No face", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("facedemo1Class", "4", 0));
        label_6->setText(QApplication::translate("facedemo1Class", "No face", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("facedemo1Class", "5", 0));
        up_load_image_button->setText(QApplication::translate("facedemo1Class", "\344\270\212\344\274\240\345\233\276\347\211\207", 0));
        pushButton->setText(QApplication::translate("facedemo1Class", "\345\273\272\347\253\213\346\225\260\346\215\256\345\272\223", 0));
    } // retranslateUi

};

namespace Ui {
    class facedemo1Class: public Ui_facedemo1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEDEMO1_H
