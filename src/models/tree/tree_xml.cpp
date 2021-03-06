
#if QT_VERSION == 0x050600
#include <wobjectimpl.h>
#endif

#include <QMessageBox>
#include <QObject>
#include <QTextCodec>

#include "libraries/disk_helper.h"
#include "libraries/global_parameters.h"
#include "libraries/trash_monitoring.h"
#include "main.h"
#include "models/record_table/items_flat.h"
#include "tree_xml.h"
#include "views/app_config/app_config_dialog.h"
#include "views/browser/browser.h"
#include "views/main_window/main_window.h"
#include "views/record_table/record_screen.h"

extern TrashMonitoring trashmonitoring;
extern std::shared_ptr<gl_para> gl_paras;

#if QT_VERSION == 0x050600
W_OBJECT_IMPL(XmlTree)
#endif

XmlTree::XmlTree(void)
    : _dom_model(new QDomDocument()) {
	// _dom_model = new QDomDocument();
}

XmlTree::~XmlTree(void) {
	delete _dom_model;
}

bool XmlTree::load(QString _file_path) {
	bool result = false;
	// Загрузка файла дерева разделов
	QFile xmlFile(_file_path);
	// Если файл не может быть открыт
	if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::information(0, tr("Error"), tr("Cannot read file %1:\n%2.").arg(_file_path).arg(xmlFile.errorString()));

		return false;
	}
	// Преобразование xml-документа в Dom представление
	QString errorStr;
	int errorLine;
	int errorColumn;
	if (!_dom_model->setContent(&xmlFile, true, &errorStr, &errorLine, &errorColumn)) {
		QMessageBox::information(0, tr("Error converting to DOM"), tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr));

		//		result = false;
	} else
		result = true;
	xmlFile.close();
	return result;
}

QDomDocument *XmlTree::dom_model(void) {
	return _dom_model;
}
