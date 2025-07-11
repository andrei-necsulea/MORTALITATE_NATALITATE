#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

namespace Ui {

    class MainWindow {
    public:
        QWidget* centralwidget;
        QVBoxLayout* verticalLayout;
        QLabel* titleLabel;
        QFormLayout* formLayout;
        QLabel* labelCountry;
        QComboBox* countryCombo;
        QLabel* labelExtraDeath;
        QLineEdit* extraDeathRateEdit;
        QLabel* labelDuration;
        QLineEdit* durationEdit;
        QLabel* labelBirth1;
        QLineEdit* birthRate1Edit;
        QLabel* labelBirth2;
        QLineEdit* birthRate2Edit;
        QLabel* labelCapacity;
        QLineEdit* capacityEdit;
        QHBoxLayout* buttonLayout;
        QPushButton* detailsBtn;
        QPushButton* crisisBtn;
        QPushButton* scenarioBtn;
        QPushButton* generalBtn;
        QMenuBar* menubar;
        QStatusBar* statusbar;

        void setupUi(QMainWindow* MainWindow) {
            if (MainWindow->objectName().isEmpty())
                MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
            MainWindow->resize(800, 600);
            centralwidget = new QWidget(MainWindow);
            centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
            verticalLayout = new QVBoxLayout(centralwidget);
            verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
            titleLabel = new QLabel(centralwidget);
            titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
            titleLabel->setAlignment(Qt::AlignCenter);
            verticalLayout->addWidget(titleLabel);

            formLayout = new QFormLayout();
            formLayout->setObjectName(QString::fromUtf8("formLayout"));
            labelCountry = new QLabel(centralwidget);
            labelCountry->setObjectName(QString::fromUtf8("labelCountry"));
            formLayout->setWidget(0, QFormLayout::LabelRole, labelCountry);
            countryCombo = new QComboBox(centralwidget);
            countryCombo->setObjectName(QString::fromUtf8("countryCombo"));
            formLayout->setWidget(0, QFormLayout::FieldRole, countryCombo);
            labelExtraDeath = new QLabel(centralwidget);
            labelExtraDeath->setObjectName(QString::fromUtf8("labelExtraDeath"));
            formLayout->setWidget(1, QFormLayout::LabelRole, labelExtraDeath);
            extraDeathRateEdit = new QLineEdit(centralwidget);
            extraDeathRateEdit->setObjectName(QString::fromUtf8("extraDeathRateEdit"));
            formLayout->setWidget(1, QFormLayout::FieldRole, extraDeathRateEdit);
            labelDuration = new QLabel(centralwidget);
            labelDuration->setObjectName(QString::fromUtf8("labelDuration"));
            formLayout->setWidget(2, QFormLayout::LabelRole, labelDuration);
            durationEdit = new QLineEdit(centralwidget);
            durationEdit->setObjectName(QString::fromUtf8("durationEdit"));
            formLayout->setWidget(2, QFormLayout::FieldRole, durationEdit);
            labelBirth1 = new QLabel(centralwidget);
            labelBirth1->setObjectName(QString::fromUtf8("labelBirth1"));
            formLayout->setWidget(3, QFormLayout::LabelRole, labelBirth1);
            birthRate1Edit = new QLineEdit(centralwidget);
            birthRate1Edit->setObjectName(QString::fromUtf8("birthRate1Edit"));
            formLayout->setWidget(3, QFormLayout::FieldRole, birthRate1Edit);
            labelBirth2 = new QLabel(centralwidget);
            labelBirth2->setObjectName(QString::fromUtf8("labelBirth2"));
            formLayout->setWidget(4, QFormLayout::LabelRole, labelBirth2);
            birthRate2Edit = new QLineEdit(centralwidget);
            birthRate2Edit->setObjectName(QString::fromUtf8("birthRate2Edit"));
            formLayout->setWidget(4, QFormLayout::FieldRole, birthRate2Edit);
            labelCapacity = new QLabel(centralwidget);
            labelCapacity->setObjectName(QString::fromUtf8("labelCapacity"));
            formLayout->setWidget(5, QFormLayout::LabelRole, labelCapacity);
            capacityEdit = new QLineEdit(centralwidget);
            capacityEdit->setObjectName(QString::fromUtf8("capacityEdit"));
            formLayout->setWidget(5, QFormLayout::FieldRole, capacityEdit);
            verticalLayout->addLayout(formLayout);

            buttonLayout = new QHBoxLayout();
            buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
            detailsBtn = new QPushButton(centralwidget);
            detailsBtn->setObjectName(QString::fromUtf8("detailsBtn"));
            buttonLayout->addWidget(detailsBtn);
            crisisBtn = new QPushButton(centralwidget);
            crisisBtn->setObjectName(QString::fromUtf8("crisisBtn"));
            buttonLayout->addWidget(crisisBtn);
            scenarioBtn = new QPushButton(centralwidget);
            scenarioBtn->setObjectName(QString::fromUtf8("scenarioBtn"));
            buttonLayout->addWidget(scenarioBtn);
            generalBtn = new QPushButton(centralwidget);
            generalBtn->setObjectName(QString::fromUtf8("generalBtn"));
            buttonLayout->addWidget(generalBtn);
            verticalLayout->addLayout(buttonLayout);

            MainWindow->setCentralWidget(centralwidget);
            menubar = new QMenuBar(MainWindow);
            menubar->setObjectName(QString::fromUtf8("menubar"));
            MainWindow->setMenuBar(menubar);
            statusbar = new QStatusBar(MainWindow);
            statusbar->setObjectName(QString::fromUtf8("statusbar"));
            MainWindow->setStatusBar(statusbar);

            retranslateUi(MainWindow);
            QMetaObject::connectSlotsByName(MainWindow);
        }

        void retranslateUi(QMainWindow* MainWindow) {
            MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Modele de natalitate si mortalitate", nullptr));
            titleLabel->setText(QCoreApplication::translate("MainWindow", "<b>Selectați țara și completați datele:</b>", nullptr));
            labelCountry->setText(QCoreApplication::translate("MainWindow", "Țară:", nullptr));
            labelExtraDeath->setText(QCoreApplication::translate("MainWindow", "Creștere temporară mortalitate:", nullptr));
            labelDuration->setText(QCoreApplication::translate("MainWindow", "Durata simulare (ani):", nullptr));
            labelBirth1->setText(QCoreApplication::translate("MainWindow", "Rata natalitate 1:", nullptr));
            labelBirth2->setText(QCoreApplication::translate("MainWindow", "Rata natalitate 2:", nullptr));
            labelCapacity->setText(QCoreApplication::translate("MainWindow", "Capacitate suport mediu:", nullptr));
            detailsBtn->setText(QCoreApplication::translate("MainWindow", "Detalii țară", nullptr));
            crisisBtn->setText(QCoreApplication::translate("MainWindow", "Simulare criză globală", nullptr));
            scenarioBtn->setText(QCoreApplication::translate("MainWindow", "Analiză scenarii evoluție", nullptr));
            generalBtn->setText(QCoreApplication::translate("MainWindow", "Raport general", nullptr));
        }
    };

} // namespace Ui

#endif // UI_MAINWINDOW_H
