/**
 * @file specificationsform.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of SpecificationsForm class.
 * @date Monday, July 20, 2026
 */
#ifndef SPECIFICATIONSFORM_H
#define SPECIFICATIONSFORM_H

#include <QList>
#include <QObject>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

/**
 * @class SpecificationsForm
 * @brief A form for editing diagram item specifications that can contain many
 *        diagram component specification forms.
 */
class SpecificationsForm : public QWidget
{
    Q_OBJECT

    public:
        /**
         * @pre True.
         * @post The form is empty.
         */
        SpecificationsForm();

        /**
         * @param form The specifications form to add.
         * @pre True.
         * @post The given specifications form has been added.
         */
        void appendForm(const SpecificationsForm *form);

        /**
         * @param fieldName The name of the field to add.
         * @param fieldWidget The values widget of the field to add.
         * @pre True.
         * @post A form field named fieldName and with the values widget
         *       fieldWidget has been added to the last form.
         */
        void appendField(const QString &fieldName, QWidget *fieldWidget);

        /**
         * @return The number of forms that contains the form.
         * @pre True.
         * @post The number of forms that contains the form has been returned.
         */
        int formCount() const;

        /**
         * @return The number of fields that contains the form.
         * @pre True.
         * @post The number of fields that contains the form has been returned.
         */
        int fieldCount() const;

        /**
         * @return The values widget of the field with the name in the form at the
         *         index.
         * @param formIndex The index of the form of the field we want to obtain
         * @param fieldName The name of the field we want to obtain.
         * @pre True.
         * @post The values widget of the field named fieldName in the form at index
         *       formIndex has been returned.
         */
        QWidget *fieldResults(int formIndex, const QString &fieldName) const;

    private:
        /**
         * @struct FormField
         * @brief The data of a specifications form field.
         */
        struct FormField {
            QString name;
            QWidget *widget;
        };

        /**
         * @invariant formLayout.count() == formFields.size()
         * @invariant formStartIndices is sorted ascending
         * @invariant formStartIndices[0..formStartIndices.size()] < formFields.size()
         */
        QVBoxLayout *formLayout; ///< The layout of the form

        QList<int> formStartIndices; ///< The indices of the first fields of each form
        QList<FormField> formFields; ///< The fields of the form

        /**
         * @return An entire field widget with the field name and values widget.
         * @param fieldName The name of the field whose widget we want to obtain.
         * @param fieldWidget The values widget of the field whose widget we want
         *        to obtain.
         * @pre True.
         * @post An entire field widget named fieldName and with the values widget
         *       fieldWidget has been returned.
         */
        QWidget *field(const QString &fieldName, QWidget *fieldWidget) const;
};

#endif // SPECIFICATIONSFORM_H
