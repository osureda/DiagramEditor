/**
 * @file main.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Filters the information from the diagram descriptor and runs the
 *  application with it.
 * @date Monday, July 20, 2026
*/

/**
 * @mainpage
 * This program implements a class structure that serves as a basis for creating a
 * comprehensive diagram editor.
 *
 * At the moment, the application allows drawing some types of database diagrams:
 *  - Entity-relationship diagrams
 *  - Class diagrams
 *  .
 *
 * The class structure has been designed to meet the following requirements:
 *  - Facilitate the extensibility of the editor thanks to a functionality that
 *    allows adding new items and diagram types quickly by writing their properties
 *    to the diagrams descriptor file.
 *  - Guarantee the portability of the application between different operating
 *    systems and execution environments, using the appropriate resources provided
 *    by Qt.
 *  - Establish the bases of certain patterns that will allow the application to be
 *    oriented towards educational use, such as adding comments or saving the
 *    diagram as a JSON file, opening the possibility of an automatic correction
 *    system.
 *  .
 */

#include "jsonfile.h"
#include "mainwindow.h"

#include <cstdlib>
#include <QApplication>
#include <QString>

/// Diagrams descriptor file path.
const QString DIAGRAMS_DESCRIPTOR_FILE = ":/descriptors/diagramsDescriptor.json";

using DiagramEditor::Gui::MainWindow;
using DiagramEditor::Serialization::JsonFile;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JsonFile diagramsDescription(DIAGRAMS_DESCRIPTOR_FILE);
    if (!diagramsDescription.load()) {
        return EXIT_FAILURE;
    }

    MainWindow mainWindow(diagramsDescription.hashForKey("diagramGroups"),
                          diagramsDescription.hashForKey("diagramTypes"),
                          diagramsDescription.hashForKey("diagramItems"));
    mainWindow.showMaximized();

    return a.exec();
}
