/********************************************************************************
** Form generated from reading UI file 'viewgui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWGUI_H
#define UI_VIEWGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewGui
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *top;
    QWidget *gridLayoutWidget_2;
    QGridLayout *bottom;
    QGroupBox *groupBox;
    QVBoxLayout *menu;
    QPushButton *start;
    QHBoxLayout *choice;
    QGroupBox *level;
    QRadioButton *debutant;
    QRadioButton *normal;
    QGroupBox *mode;
    QRadioButton *placement;
    QRadioButton *file;
    QLabel *background;
    QWidget *gridLayoutWidget_3;
    QGridLayout *battleField;
    QLabel *backgroundbattle;

    void setupUi(QMainWindow *ViewGui)
    {
        if (ViewGui->objectName().isEmpty())
            ViewGui->setObjectName(QString::fromUtf8("ViewGui"));
        ViewGui->resize(930, 753);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ViewGui->sizePolicy().hasHeightForWidth());
        ViewGui->setSizePolicy(sizePolicy);
        ViewGui->setBaseSize(QSize(0, 8000));
        centralwidget = new QWidget(ViewGui);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 931, 91));
        top = new QGridLayout(gridLayoutWidget);
        top->setObjectName(QString::fromUtf8("top"));
        top->setSizeConstraint(QLayout::SetNoConstraint);
        top->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 651, 931, 101));
        bottom = new QGridLayout(gridLayoutWidget_2);
        bottom->setObjectName(QString::fromUtf8("bottom"));
        bottom->setSizeConstraint(QLayout::SetNoConstraint);
        bottom->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(300, 238, 331, 271));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setMouseTracking(false);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid Black;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"background-color : white;\n"
"}"));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        menu = new QVBoxLayout(groupBox);
        menu->setObjectName(QString::fromUtf8("menu"));
        start = new QPushButton(groupBox);
        start->setObjectName(QString::fromUtf8("start"));
        start->setMinimumSize(QSize(0, 100));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(false);
        start->setFont(font1);
        start->setCursor(QCursor(Qt::CrossCursor));
        start->setMouseTracking(true);
        start->setStyleSheet(QString::fromUtf8("QPushButton#start\n"
"    {\n"
"        background-color: red\n"
"    }"));
        start->setAutoExclusive(false);
        start->setAutoDefault(false);

        menu->addWidget(start);

        choice = new QHBoxLayout();
        choice->setObjectName(QString::fromUtf8("choice"));
        level = new QGroupBox(groupBox);
        level->setObjectName(QString::fromUtf8("level"));
        level->setFont(font);
        level->setStyleSheet(QString::fromUtf8(""));
        debutant = new QRadioButton(level);
        debutant->setObjectName(QString::fromUtf8("debutant"));
        debutant->setGeometry(QRect(0, 40, 91, 22));
        debutant->setChecked(true);
        normal = new QRadioButton(level);
        normal->setObjectName(QString::fromUtf8("normal"));
        normal->setGeometry(QRect(0, 80, 91, 22));

        choice->addWidget(level);

        mode = new QGroupBox(groupBox);
        mode->setObjectName(QString::fromUtf8("mode"));
        placement = new QRadioButton(mode);
        placement->setObjectName(QString::fromUtf8("placement"));
        placement->setGeometry(QRect(0, 40, 91, 22));
        placement->setChecked(true);
        file = new QRadioButton(mode);
        file->setObjectName(QString::fromUtf8("file"));
        file->setGeometry(QRect(0, 80, 91, 22));
        file->setAutoFillBackground(false);

        choice->addWidget(mode);


        menu->addLayout(choice);

        background = new QLabel(centralwidget);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(-10, -10, 941, 771));
        background->setMaximumSize(QSize(2000, 2000));
        background->setPixmap(QPixmap(QString::fromUtf8(":/ressources/unknown.png")));
        background->setScaledContents(true);
        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(1, 90, 928, 561));
        battleField = new QGridLayout(gridLayoutWidget_3);
        battleField->setSpacing(0);
        battleField->setObjectName(QString::fromUtf8("battleField"));
        battleField->setSizeConstraint(QLayout::SetDefaultConstraint);
        battleField->setContentsMargins(0, 0, 0, 0);
        backgroundbattle = new QLabel(centralwidget);
        backgroundbattle->setObjectName(QString::fromUtf8("backgroundbattle"));
        backgroundbattle->setGeometry(QRect(0, 90, 931, 561));
        ViewGui->setCentralWidget(centralwidget);
        backgroundbattle->raise();
        background->raise();
        gridLayoutWidget->raise();
        gridLayoutWidget_2->raise();
        gridLayoutWidget_3->raise();
        groupBox->raise();

        retranslateUi(ViewGui);

        QMetaObject::connectSlotsByName(ViewGui);
    } // setupUi

    void retranslateUi(QMainWindow *ViewGui)
    {
        ViewGui->setWindowTitle(QCoreApplication::translate("ViewGui", "ViewGui", nullptr));
        start->setText(QCoreApplication::translate("ViewGui", "START", nullptr));
        level->setTitle(QCoreApplication::translate("ViewGui", "LEVEL", nullptr));
        debutant->setText(QCoreApplication::translate("ViewGui", "DEBUTANT", nullptr));
        normal->setText(QCoreApplication::translate("ViewGui", "NORMAL", nullptr));
        mode->setTitle(QCoreApplication::translate("ViewGui", "MODE", nullptr));
        placement->setText(QCoreApplication::translate("ViewGui", "PLACEMENT", nullptr));
        file->setText(QCoreApplication::translate("ViewGui", "FILE", nullptr));
        background->setText(QString());
        backgroundbattle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ViewGui: public Ui_ViewGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWGUI_H
