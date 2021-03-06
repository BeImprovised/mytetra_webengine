
#if QT_VERSION == 0x050600
#include <wobjectimpl.h>
#endif

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "editor_add_table_form.h"

#if QT_VERSION == 0x050600
W_OBJECT_IMPL(EditorAddTableForm)
#endif

EditorAddTableForm::EditorAddTableForm() {
	this->setWindowTitle(tr("Create a new table"));

	labelColumns = new QLabel(tr("Columns: "));
	labelRows = new QLabel(tr("Rows: "));
	labelWidth = new QLabel(tr("Width: "));
	labelPercent = new QLabel(tr("%"));

	spinColumns = new QSpinBox();
	spinColumns->setRange(1, 100);
	spinColumns->setValue(2);

	spinRows = new QSpinBox();
	spinRows->setRange(1, 100);
	spinRows->setValue(2);

	spinWidth = new QSpinBox();
	spinWidth->setRange(1, 100);
	spinWidth->setValue(100);

	// show_border=new QCheckBox(tr("Show border"));

	buttonBox = new QDialogButtonBox(Qt::Horizontal);
	buttonBox->addButton(tr("OK"), QDialogButtonBox::AcceptRole);
	buttonBox->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &EditorAddTableForm::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &EditorAddTableForm::reject);

	QGridLayout *gridLayout = new QGridLayout();

	gridLayout->addWidget(labelColumns, 0, 0);
	gridLayout->addWidget(spinColumns, 0, 1);

	gridLayout->addWidget(labelRows, 1, 0);
	gridLayout->addWidget(spinRows, 1, 1);

	gridLayout->addWidget(labelWidth, 2, 0);
	gridLayout->addWidget(spinWidth, 2, 1);
	gridLayout->addWidget(labelPercent, 2, 3);

	// Максимально растягивается по ширине первый столбец
	gridLayout->setColumnStretch(0, 1);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addLayout(gridLayout);
	mainLayout->addWidget(buttonBox);
}

int EditorAddTableForm::get_columns(void) {
	return spinColumns->value();
}

int EditorAddTableForm::get_rows(void) {
	return spinRows->value();
}

int EditorAddTableForm::get_width(void) {
	return spinWidth->value();
}

/*
   bool EditorAddTableForm::get_show_border(void)
   {
   if(show_border->checkState()==Qt::Unchecked)
   return false;
   else
   return true;
   }
 */
