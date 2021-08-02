#include "listdialog.h"

#include "editdialog.h"
#include "ui_listdialog.h"

// Listing 2-3: Constructor of the ListDialog class
ListDialog::ListDialog(QWidget* parent) : QDialog(parent), ui(new Ui::ListDialog)
{
    ui->setupUi(this);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editItem()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
}

ListDialog::~ListDialog() { delete ui; }

// Listing 2-4: Adding a new item to the list
void ListDialog::addItem()
{
    EditDialog dlg(this);

    if (dlg.exec() == DialogCode::Accepted)
        ui->list->addItem(dlg.name() + " -- " + dlg.number());
}

// Listing 2-5: Deleting an item of the list
void ListDialog::deleteItem() { delete ui->list->currentItem(); }

// Listing 2-6: Editing an item of the list
void ListDialog::editItem()
{
    if (!ui->list->currentItem())
        return;

    QStringList parts = ui->list->currentItem()->text().split("--");

    EditDialog dlg(this);
    dlg.setName(parts[0].trimmed());
    dlg.setNumber(parts[1].trimmed());

    if (dlg.exec() == DialogCode::Accepted)
        ui->list->currentItem()->setText(dlg.name() + " -- " + dlg.number());
}
