#include "editdialog.h"

#include "ui_editdialog.h"

// Listing 2-8: Editing an item of the list
EditDialog::EditDialog(QWidget* parent) : QDialog(parent), ui(new Ui::EditDialog) { ui->setupUi(this); }

EditDialog::~EditDialog() { delete ui; }

// Listing 2-9: Editing an item of the list
const QString EditDialog::name() const { return ui->nameEdit->text().replace("--", "").trimmed(); }

void EditDialog::setName(const QString& name) { ui->nameEdit->setText(name); }

const QString EditDialog::number() const { return ui->numberEdit->text().replace("--", "").trimmed(); }

void EditDialog::setNumber(const QString& number) { ui->numberEdit->setText(number); }
