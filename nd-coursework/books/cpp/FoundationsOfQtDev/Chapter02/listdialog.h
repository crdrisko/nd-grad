#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>

namespace Ui
{
    class ListDialog;
}

// Listing 2-2: The header file for the ListDialog class
class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget* parent = nullptr);
    ~ListDialog();

private slots:
    void addItem();
    void editItem();
    void deleteItem();

private:
    Ui::ListDialog* ui;
};

#endif   // LISTDIALOG_H
