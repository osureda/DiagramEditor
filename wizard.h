/**
 * @file wizard.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of Wizard class.
 * @date Monday, July 20, 2026
 */
#ifndef WIZARD_H
#define WIZARD_H

#include "diagramtype.h"

#include <QObject>
#include <QVariant>
#include <QWizard>

QT_BEGIN_NAMESPACE
class QWidget;

namespace Ui {
class Wizard;
}
QT_END_NAMESPACE

namespace DiagramEditor::Gui {

class ScrollableDataButtonsSelector;

/**
 * @class Wizard
 * @brief The initialization wizard to select the diagram configuration.
 */
class Wizard : public QWizard
{
    Q_OBJECT

public:
    /// The number of columns of the diagram type group selector.
    static const int DIAGRAM_GROUPS_GRID_SIZE = 2;

    /// The number of columns of the diagram type selector.
    static const int DIAGRAM_TYPES_GRID_SIZE = 1;

    /// The size of the diagram type group icons.
    static const int DIAGRAM_GROUP_ICON_SIZE = 200;

    /// The size of the diagram type icons.
    static const int DIAGRAM_TYPE_ICON_SIZE = 75;

    /**
     * @struct Configuration
     * @brief The data of a selected configuration.
     */
    struct Configuration {
        DiagramType::DiagramItemsIds diagramItems; ///< Diagram items associated to the selected diagram type
    };

    /**
     * @param diagramGroups The data of the diagram type groups to choose.
     * @param diagramTypes The data of the diagram types to choose.
     * @param parent The container of the wizard.
     * @pre True.
     * @post The wizard is contained by parent and has the diagram type groups
     *       loaded from diagramGroups and the diagram types loaded from
     *       diagramTypes to choose.
     */
    Wizard(const QVariantHash &diagramGroups, const QVariantHash &diagramTypes, QWidget *parent = nullptr);

    /**
     * @pre True.
     * @post The wizard has been destroyed.
     */
    ~Wizard() override;

    /**
     * @return The data of the selected configuration.
     * @pre True.
     * @post The data of the selected configuration has been returned.
     */
    Configuration selectedConfiguration() const;

private slots:
    /**
     * @param selectedGroupData The data of the selected diagram type group.
     * @pre True.
     * @post The selected diagram type group has changed to the one loaded from
     *       selectedGroupData.
     */
    void selectedGroupChanged(const QVariantHash &selectedGroupData);

private:
    Ui::Wizard *ui; ///< Wizard's user interface

    QVariantHash allDiagramTypes; ///< The data of the diagram types to choose
    ScrollableDataButtonsSelector *diagramTypesSelector; ///< The diagram types selector
};

}

#endif // WIZARD_H
