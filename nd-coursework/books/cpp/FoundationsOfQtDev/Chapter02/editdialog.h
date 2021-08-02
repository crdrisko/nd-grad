#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui
{
    class EditDialog;
}


// Listing 2-7: Editing dialog class
class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget* parent = nullptr);
    ~EditDialog();

    const QString name() const;
    void setName(const QString&);

    const QString number() const;
    void setNumber(const QString&);

private:
    Ui::EditDialog* ui;
};

#endif   // EDITDIALOG_H
