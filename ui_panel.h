/********************************************************************************
** Form generated from reading UI file 'panel.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Panel
{
public:
    QAction *actionDisconnect;
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *north;
    QGroupBox *contentBox;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *contentForm;
    QLabel *textLabel;
    QLineEdit *textMessageField;
    QPushButton *useMatrixButton;
    QGraphicsView *previewWidget;
    QVBoxLayout *animationPanel;
    QGroupBox *slidingBox;
    QFormLayout *formLayout_2;
    QCheckBox *slideCheckBox;
    QLabel *speedLabel;
    QDoubleSpinBox *speedSpinBox;
    QLabel *directionLabel;
    QComboBox *directionBox;
    QGroupBox *blinkingBox;
    QFormLayout *formLayout;
    QCheckBox *blinkCheckBox;
    QLabel *frequencyLabel;
    QDoubleSpinBox *frequencySpinBox;
    QGroupBox *south;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *actionButtons;
    QPushButton *restoreButton;
    QPushButton *applyButton;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuConnection;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Panel)
    {
        if (Panel->objectName().isEmpty())
            Panel->setObjectName(QStringLiteral("Panel"));
        Panel->resize(500, 424);
        actionDisconnect = new QAction(Panel);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionQuit = new QAction(Panel);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(Panel);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        north = new QHBoxLayout();
        north->setSpacing(6);
        north->setObjectName(QStringLiteral("north"));
        contentBox = new QGroupBox(centralWidget);
        contentBox->setObjectName(QStringLiteral("contentBox"));
        verticalLayout_3 = new QVBoxLayout(contentBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        contentForm = new QFormLayout();
        contentForm->setSpacing(6);
        contentForm->setObjectName(QStringLiteral("contentForm"));
        textLabel = new QLabel(contentBox);
        textLabel->setObjectName(QStringLiteral("textLabel"));

        contentForm->setWidget(0, QFormLayout::LabelRole, textLabel);

        textMessageField = new QLineEdit(contentBox);
        textMessageField->setObjectName(QStringLiteral("textMessageField"));

        contentForm->setWidget(0, QFormLayout::FieldRole, textMessageField);


        verticalLayout_3->addLayout(contentForm);

        useMatrixButton = new QPushButton(contentBox);
        useMatrixButton->setObjectName(QStringLiteral("useMatrixButton"));

        verticalLayout_3->addWidget(useMatrixButton);

        previewWidget = new QGraphicsView(contentBox);
        previewWidget->setObjectName(QStringLiteral("previewWidget"));

        verticalLayout_3->addWidget(previewWidget);


        north->addWidget(contentBox);

        animationPanel = new QVBoxLayout();
        animationPanel->setSpacing(6);
        animationPanel->setObjectName(QStringLiteral("animationPanel"));
        slidingBox = new QGroupBox(centralWidget);
        slidingBox->setObjectName(QStringLiteral("slidingBox"));
        formLayout_2 = new QFormLayout(slidingBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        slideCheckBox = new QCheckBox(slidingBox);
        slideCheckBox->setObjectName(QStringLiteral("slideCheckBox"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, slideCheckBox);

        speedLabel = new QLabel(slidingBox);
        speedLabel->setObjectName(QStringLiteral("speedLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, speedLabel);

        speedSpinBox = new QDoubleSpinBox(slidingBox);
        speedSpinBox->setObjectName(QStringLiteral("speedSpinBox"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, speedSpinBox);

        directionLabel = new QLabel(slidingBox);
        directionLabel->setObjectName(QStringLiteral("directionLabel"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, directionLabel);

        directionBox = new QComboBox(slidingBox);
        directionBox->setObjectName(QStringLiteral("directionBox"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, directionBox);


        animationPanel->addWidget(slidingBox);

        blinkingBox = new QGroupBox(centralWidget);
        blinkingBox->setObjectName(QStringLiteral("blinkingBox"));
        formLayout = new QFormLayout(blinkingBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        blinkCheckBox = new QCheckBox(blinkingBox);
        blinkCheckBox->setObjectName(QStringLiteral("blinkCheckBox"));

        formLayout->setWidget(0, QFormLayout::LabelRole, blinkCheckBox);

        frequencyLabel = new QLabel(blinkingBox);
        frequencyLabel->setObjectName(QStringLiteral("frequencyLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, frequencyLabel);

        frequencySpinBox = new QDoubleSpinBox(blinkingBox);
        frequencySpinBox->setObjectName(QStringLiteral("frequencySpinBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, frequencySpinBox);


        animationPanel->addWidget(blinkingBox);


        north->addLayout(animationPanel);


        verticalLayout->addLayout(north);

        south = new QGroupBox(centralWidget);
        south->setObjectName(QStringLiteral("south"));
        verticalLayout_4 = new QVBoxLayout(south);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        actionButtons = new QHBoxLayout();
        actionButtons->setSpacing(6);
        actionButtons->setObjectName(QStringLiteral("actionButtons"));
        restoreButton = new QPushButton(south);
        restoreButton->setObjectName(QStringLiteral("restoreButton"));

        actionButtons->addWidget(restoreButton);

        applyButton = new QPushButton(south);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        actionButtons->addWidget(applyButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        actionButtons->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(actionButtons);

        graphicsView = new QGraphicsView(south);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout_4->addWidget(graphicsView);


        verticalLayout->addWidget(south);

        Panel->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Panel);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 19));
        menuConnection = new QMenu(menuBar);
        menuConnection->setObjectName(QStringLiteral("menuConnection"));
        Panel->setMenuBar(menuBar);
        statusBar = new QStatusBar(Panel);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Panel->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        textLabel->setBuddy(textMessageField);
        speedLabel->setBuddy(speedSpinBox);
        directionLabel->setBuddy(directionBox);
        frequencyLabel->setBuddy(frequencySpinBox);
#endif // QT_NO_SHORTCUT

        menuBar->addAction(menuConnection->menuAction());
        menuConnection->addAction(actionDisconnect);
        menuConnection->addSeparator();
        menuConnection->addAction(actionQuit);

        retranslateUi(Panel);

        QMetaObject::connectSlotsByName(Panel);
    } // setupUi

    void retranslateUi(QMainWindow *Panel)
    {
        Panel->setWindowTitle(QApplication::translate("Panel", "Panel", 0));
        actionDisconnect->setText(QApplication::translate("Panel", "Disconnect", 0));
        actionQuit->setText(QApplication::translate("Panel", "Quit", 0));
        contentBox->setTitle(QApplication::translate("Panel", "Content", 0));
        textLabel->setText(QApplication::translate("Panel", "&Text:", 0));
        textMessageField->setText(QString());
        useMatrixButton->setText(QApplication::translate("Panel", "Use matrix ...", 0));
        slidingBox->setTitle(QApplication::translate("Panel", "Sliding", 0));
        slideCheckBox->setText(QApplication::translate("Panel", "Slide", 0));
        speedLabel->setText(QApplication::translate("Panel", "&Speed (px/sec):", 0));
        directionLabel->setText(QApplication::translate("Panel", "Direction:", 0));
        directionBox->clear();
        directionBox->insertItems(0, QStringList()
         << QApplication::translate("Panel", "Left", 0)
         << QApplication::translate("Panel", "Right", 0)
        );
        blinkingBox->setTitle(QApplication::translate("Panel", "Blinking", 0));
        blinkCheckBox->setText(QApplication::translate("Panel", "Blink", 0));
        frequencyLabel->setText(QApplication::translate("Panel", "&Frequency (Hz):", 0));
        south->setTitle(QApplication::translate("Panel", "Preview", 0));
        restoreButton->setText(QApplication::translate("Panel", "Restore", 0));
        applyButton->setText(QApplication::translate("Panel", "Apply", 0));
        menuConnection->setTitle(QApplication::translate("Panel", "Connection", 0));
    } // retranslateUi

};

namespace Ui {
    class Panel: public Ui_Panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
