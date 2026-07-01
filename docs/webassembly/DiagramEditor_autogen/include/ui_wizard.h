/********************************************************************************
** Form generated from reading UI file 'wizard.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIZARD_H
#define UI_WIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_Wizard
{
public:
    QWizardPage *chooseDiagramModelPage;
    QVBoxLayout *chooseDiagramModelPageLayout;
    QLabel *chooseDiagramModelLabel;
    QHBoxLayout *chooseDiagramModelSelectorLayout;

    void setupUi(QWizard *Wizard)
    {
        if (Wizard->objectName().isEmpty())
            Wizard->setObjectName("Wizard");
        Wizard->resize(1006, 817);
        Wizard->setWizardStyle(QWizard::WizardStyle::ClassicStyle);
        Wizard->setOptions(QWizard::WizardOption::HaveNextButtonOnLastPage|QWizard::WizardOption::NoCancelButton);
        Wizard->setSubTitleFormat(Qt::TextFormat::AutoText);
        chooseDiagramModelPage = new QWizardPage();
        chooseDiagramModelPage->setObjectName("chooseDiagramModelPage");
        chooseDiagramModelPageLayout = new QVBoxLayout(chooseDiagramModelPage);
        chooseDiagramModelPageLayout->setObjectName("chooseDiagramModelPageLayout");
        chooseDiagramModelLabel = new QLabel(chooseDiagramModelPage);
        chooseDiagramModelLabel->setObjectName("chooseDiagramModelLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chooseDiagramModelLabel->sizePolicy().hasHeightForWidth());
        chooseDiagramModelLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        chooseDiagramModelLabel->setFont(font);

        chooseDiagramModelPageLayout->addWidget(chooseDiagramModelLabel);

        chooseDiagramModelSelectorLayout = new QHBoxLayout();
        chooseDiagramModelSelectorLayout->setObjectName("chooseDiagramModelSelectorLayout");

        chooseDiagramModelPageLayout->addLayout(chooseDiagramModelSelectorLayout);

        Wizard->addPage(chooseDiagramModelPage);

        retranslateUi(Wizard);

        QMetaObject::connectSlotsByName(Wizard);
    } // setupUi

    void retranslateUi(QWizard *Wizard)
    {
        Wizard->setWindowTitle(QCoreApplication::translate("Wizard", "Wizard", nullptr));
        chooseDiagramModelLabel->setText(QCoreApplication::translate("Wizard", "Choose your diagram model", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wizard: public Ui_Wizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARD_H
