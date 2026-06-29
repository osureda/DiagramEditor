/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionManual;
    QAction *actionSettings;
    QAction *exportJSONFile;
    QAction *importJSONFile;
    QWidget *centralWidget;
    QHBoxLayout *centralLayout;
    QTabWidget *itemSelectorWidget;
    QVBoxLayout *diagramEditorLayout;
    QFrame *editingToolsFrame;
    QHBoxLayout *editingToolsLayout;
    QToolButton *addItemToolButton;
    QToolButton *selectionToolButton;
    QToolButton *addResizerToolButton;
    QToolButton *removeResizerToolButton;
    QSpacerItem *editingToolsSpacer;
    QToolButton *removeItemsToolButton;
    QGraphicsView *diagramView;
    QTabWidget *propertiesPanel;
    QWidget *specificationsTab;
    QVBoxLayout *specificationsTabLayout;
    QScrollArea *specificationsScrollArea;
    QWidget *specificationsContainerWidget;
    QVBoxLayout *specificationsContainerLayout;
    QPushButton *saveSpecificationsButton;
    QWidget *jsonTab;
    QVBoxLayout *jsonTabLayout;
    QHBoxLayout *jsonClipboardActionsLayout;
    QPushButton *copyJsonButton;
    QPushButton *pasteJsonButton;
    QScrollArea *jsonScrollArea;
    QWidget *jsonContainerWidget;
    QVBoxLayout *jsonContainerLayout;
    QTextEdit *jsonTextEdit;
    QHBoxLayout *jsonFileActionsLayout;
    QPushButton *loadJsonButton;
    QPushButton *saveJsonButton;
    QButtonGroup *editionModesButtonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1200, 800);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setDocumentMode(false);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionManual = new QAction(MainWindow);
        actionManual->setObjectName("actionManual");
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName("actionSettings");
        exportJSONFile = new QAction(MainWindow);
        exportJSONFile->setObjectName("exportJSONFile");
        importJSONFile = new QAction(MainWindow);
        importJSONFile->setObjectName("importJSONFile");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralLayout = new QHBoxLayout(centralWidget);
        centralLayout->setObjectName("centralLayout");
        itemSelectorWidget = new QTabWidget(centralWidget);
        itemSelectorWidget->setObjectName("itemSelectorWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(itemSelectorWidget->sizePolicy().hasHeightForWidth());
        itemSelectorWidget->setSizePolicy(sizePolicy);
        itemSelectorWidget->setMinimumSize(QSize(204, 0));
        itemSelectorWidget->setTabBarAutoHide(true);

        centralLayout->addWidget(itemSelectorWidget);

        diagramEditorLayout = new QVBoxLayout();
        diagramEditorLayout->setObjectName("diagramEditorLayout");
        editingToolsFrame = new QFrame(centralWidget);
        editingToolsFrame->setObjectName("editingToolsFrame");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(editingToolsFrame->sizePolicy().hasHeightForWidth());
        editingToolsFrame->setSizePolicy(sizePolicy1);
        editingToolsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        editingToolsFrame->setFrameShadow(QFrame::Shadow::Raised);
        editingToolsLayout = new QHBoxLayout(editingToolsFrame);
        editingToolsLayout->setObjectName("editingToolsLayout");
        addItemToolButton = new QToolButton(editingToolsFrame);
        editionModesButtonGroup = new QButtonGroup(MainWindow);
        editionModesButtonGroup->setObjectName("editionModesButtonGroup");
        editionModesButtonGroup->addButton(addItemToolButton);
        addItemToolButton->setObjectName("addItemToolButton");
        addItemToolButton->setMinimumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/plusObject.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addItemToolButton->setIcon(icon);
        addItemToolButton->setCheckable(true);
        addItemToolButton->setChecked(true);

        editingToolsLayout->addWidget(addItemToolButton);

        selectionToolButton = new QToolButton(editingToolsFrame);
        editionModesButtonGroup->addButton(selectionToolButton);
        selectionToolButton->setObjectName("selectionToolButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(selectionToolButton->sizePolicy().hasHeightForWidth());
        selectionToolButton->setSizePolicy(sizePolicy2);
        selectionToolButton->setMinimumSize(QSize(30, 30));
        selectionToolButton->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/mouseArrow.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        selectionToolButton->setIcon(icon1);
        selectionToolButton->setIconSize(QSize(20, 20));
        selectionToolButton->setCheckable(true);

        editingToolsLayout->addWidget(selectionToolButton);

        addResizerToolButton = new QToolButton(editingToolsFrame);
        editionModesButtonGroup->addButton(addResizerToolButton);
        addResizerToolButton->setObjectName("addResizerToolButton");
        addResizerToolButton->setMinimumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/linedSquare.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addResizerToolButton->setIcon(icon2);
        addResizerToolButton->setCheckable(true);

        editingToolsLayout->addWidget(addResizerToolButton);

        removeResizerToolButton = new QToolButton(editingToolsFrame);
        editionModesButtonGroup->addButton(removeResizerToolButton);
        removeResizerToolButton->setObjectName("removeResizerToolButton");
        removeResizerToolButton->setMinimumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/shortLine.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        removeResizerToolButton->setIcon(icon3);
        removeResizerToolButton->setCheckable(true);

        editingToolsLayout->addWidget(removeResizerToolButton);

        editingToolsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        editingToolsLayout->addItem(editingToolsSpacer);

        removeItemsToolButton = new QToolButton(editingToolsFrame);
        removeItemsToolButton->setObjectName("removeItemsToolButton");
        sizePolicy2.setHeightForWidth(removeItemsToolButton->sizePolicy().hasHeightForWidth());
        removeItemsToolButton->setSizePolicy(sizePolicy2);
        removeItemsToolButton->setMinimumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/bin.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        removeItemsToolButton->setIcon(icon4);

        editingToolsLayout->addWidget(removeItemsToolButton);


        diagramEditorLayout->addWidget(editingToolsFrame);

        diagramView = new QGraphicsView(centralWidget);
        diagramView->setObjectName("diagramView");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(diagramView->sizePolicy().hasHeightForWidth());
        diagramView->setSizePolicy(sizePolicy3);

        diagramEditorLayout->addWidget(diagramView);


        centralLayout->addLayout(diagramEditorLayout);

        propertiesPanel = new QTabWidget(centralWidget);
        propertiesPanel->setObjectName("propertiesPanel");
        sizePolicy.setHeightForWidth(propertiesPanel->sizePolicy().hasHeightForWidth());
        propertiesPanel->setSizePolicy(sizePolicy);
        propertiesPanel->setMinimumSize(QSize(350, 0));
        specificationsTab = new QWidget();
        specificationsTab->setObjectName("specificationsTab");
        sizePolicy3.setHeightForWidth(specificationsTab->sizePolicy().hasHeightForWidth());
        specificationsTab->setSizePolicy(sizePolicy3);
        specificationsTabLayout = new QVBoxLayout(specificationsTab);
        specificationsTabLayout->setObjectName("specificationsTabLayout");
        specificationsScrollArea = new QScrollArea(specificationsTab);
        specificationsScrollArea->setObjectName("specificationsScrollArea");
        specificationsScrollArea->setWidgetResizable(true);
        specificationsContainerWidget = new QWidget();
        specificationsContainerWidget->setObjectName("specificationsContainerWidget");
        specificationsContainerWidget->setGeometry(QRect(0, 0, 322, 681));
        sizePolicy3.setHeightForWidth(specificationsContainerWidget->sizePolicy().hasHeightForWidth());
        specificationsContainerWidget->setSizePolicy(sizePolicy3);
        specificationsContainerLayout = new QVBoxLayout(specificationsContainerWidget);
        specificationsContainerLayout->setObjectName("specificationsContainerLayout");
        specificationsScrollArea->setWidget(specificationsContainerWidget);

        specificationsTabLayout->addWidget(specificationsScrollArea);

        saveSpecificationsButton = new QPushButton(specificationsTab);
        saveSpecificationsButton->setObjectName("saveSpecificationsButton");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(saveSpecificationsButton->sizePolicy().hasHeightForWidth());
        saveSpecificationsButton->setSizePolicy(sizePolicy4);

        specificationsTabLayout->addWidget(saveSpecificationsButton);

        propertiesPanel->addTab(specificationsTab, QString());
        jsonTab = new QWidget();
        jsonTab->setObjectName("jsonTab");
        sizePolicy3.setHeightForWidth(jsonTab->sizePolicy().hasHeightForWidth());
        jsonTab->setSizePolicy(sizePolicy3);
        jsonTabLayout = new QVBoxLayout(jsonTab);
        jsonTabLayout->setObjectName("jsonTabLayout");
        jsonClipboardActionsLayout = new QHBoxLayout();
        jsonClipboardActionsLayout->setObjectName("jsonClipboardActionsLayout");
        copyJsonButton = new QPushButton(jsonTab);
        copyJsonButton->setObjectName("copyJsonButton");

        jsonClipboardActionsLayout->addWidget(copyJsonButton);

        pasteJsonButton = new QPushButton(jsonTab);
        pasteJsonButton->setObjectName("pasteJsonButton");

        jsonClipboardActionsLayout->addWidget(pasteJsonButton);


        jsonTabLayout->addLayout(jsonClipboardActionsLayout);

        jsonScrollArea = new QScrollArea(jsonTab);
        jsonScrollArea->setObjectName("jsonScrollArea");
        jsonScrollArea->setWidgetResizable(true);
        jsonContainerWidget = new QWidget();
        jsonContainerWidget->setObjectName("jsonContainerWidget");
        jsonContainerWidget->setGeometry(QRect(0, 0, 322, 641));
        jsonContainerLayout = new QVBoxLayout(jsonContainerWidget);
        jsonContainerLayout->setObjectName("jsonContainerLayout");
        jsonTextEdit = new QTextEdit(jsonContainerWidget);
        jsonTextEdit->setObjectName("jsonTextEdit");

        jsonContainerLayout->addWidget(jsonTextEdit);

        jsonScrollArea->setWidget(jsonContainerWidget);

        jsonTabLayout->addWidget(jsonScrollArea);

        jsonFileActionsLayout = new QHBoxLayout();
        jsonFileActionsLayout->setObjectName("jsonFileActionsLayout");
        loadJsonButton = new QPushButton(jsonTab);
        loadJsonButton->setObjectName("loadJsonButton");

        jsonFileActionsLayout->addWidget(loadJsonButton);

        saveJsonButton = new QPushButton(jsonTab);
        saveJsonButton->setObjectName("saveJsonButton");

        jsonFileActionsLayout->addWidget(saveJsonButton);


        jsonTabLayout->addLayout(jsonFileActionsLayout);

        propertiesPanel->addTab(jsonTab, QString());

        centralLayout->addWidget(propertiesPanel);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        itemSelectorWidget->setCurrentIndex(-1);
        propertiesPanel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionManual->setText(QCoreApplication::translate("MainWindow", "Manual", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        exportJSONFile->setText(QCoreApplication::translate("MainWindow", "JSON FIle", nullptr));
        importJSONFile->setText(QCoreApplication::translate("MainWindow", "JSON File", nullptr));
        addItemToolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        selectionToolButton->setText(QString());
        addResizerToolButton->setText(QString());
        removeResizerToolButton->setText(QCoreApplication::translate("MainWindow", "- Resizer", nullptr));
        removeItemsToolButton->setText(QString());
        saveSpecificationsButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        propertiesPanel->setTabText(propertiesPanel->indexOf(specificationsTab), QCoreApplication::translate("MainWindow", "Specifications", nullptr));
        copyJsonButton->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        pasteJsonButton->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        loadJsonButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        saveJsonButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        propertiesPanel->setTabText(propertiesPanel->indexOf(jsonTab), QCoreApplication::translate("MainWindow", "JSON File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
