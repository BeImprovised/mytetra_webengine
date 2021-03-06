

#if QT_VERSION == 0x050600
#include <wobjectimpl.h>
#endif

#include "libraries/flat_control.h"
#include <QAbstractScrollArea>
#include <QAbstractTextDocumentLayout>
#include <QAction>
#include <QDebug>
#include <QMouseEvent>
#include <QPageSetupDialog>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QStatusBar>
#include <QTextDocument>
#include <QTextFormat>
#include <QTextFrame>
#include <QToolBar>

#include "print_preview.h"
#include "view_preview.h"

extern const char *program_title;

static inline int inches_to_pixels(float inches, QPaintDevice *device) {
	return qRound(inches * device->logicalDpiY());
}

static inline qreal mm_to_inches(double mm) {
	return mm * 0.039370147;
}

#if QT_VERSION == 0x050600
W_OBJECT_IMPL(PrintPreview)
#endif

PrintPreview::PrintPreview(const QTextDocument *document, QWidget *parent)
    : QDialog(parent)
    , printer(QPrinter::HighResolution) {
	setWindowTitle(tr(std::string(std::string(program_title) + " - Print Preview").c_str()));

	printer.setFullPage(true);
	doc = document->clone();

	view = new PreviewView(doc);

	doc->setUseDesignMetrics(true);
	doc->documentLayout()->setPaintDevice(view->viewport());

	// add a nice 2 cm margin
	const qreal margin = inches_to_pixels(mm_to_inches(20), this);
	QTextFrameFormat fmt = doc->rootFrame()->frameFormat();
	fmt.setMargin(margin);
	doc->rootFrame()->setFrameFormat(fmt);

	setup();

	QFont f(doc->defaultFont());
	f.setPointSize(10);
	doc->setDefaultFont(f);

	// Кнопки на панели инструментов
	FlatToolButton *button_print = new FlatToolButton("", this);
	button_print->setText(tr("&Print..."));
	button_print->setShortcut(Qt::CTRL + Qt::Key_P);
	button_print->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(button_print, &FlatToolButton::clicked, this, &PrintPreview::print);

	FlatToolButton *button_page_setup = new FlatToolButton("", this);
	button_page_setup->setText(tr("Page Setup..."));
	button_page_setup->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(button_page_setup, &FlatToolButton::clicked, this, &PrintPreview::page_setup);

	FlatToolButton *button_zoom_in = new FlatToolButton("", this);
	button_zoom_in->setText(tr("Zoom In"));
	button_zoom_in->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(button_zoom_in, &FlatToolButton::clicked, view, &PreviewView::zoom_in);

	FlatToolButton *button_zoom_out = new FlatToolButton("", this);
	button_zoom_out->setText(tr("Zoom Out"));
	button_zoom_out->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(button_zoom_out, &FlatToolButton::clicked, view, &PreviewView::zoom_out);

	FlatToolButton *button_close = new FlatToolButton("", this);
	button_close->setText(tr("&Close"));
	button_close->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(button_close, &FlatToolButton::clicked, this, &PrintPreview::close);

	// Панель инструментов
	QHBoxLayout *toolsbox = new QHBoxLayout();
	toolsbox->addWidget(button_print);
	toolsbox->addWidget(button_page_setup);
	toolsbox->addWidget(button_zoom_in);
	toolsbox->addWidget(button_zoom_out);
	toolsbox->addWidget(button_close);
	toolsbox->addStretch();

	// Сборка содержимого окна
	centralLayout = new QVBoxLayout();
	centralLayout->addLayout(toolsbox);
	centralLayout->addWidget(view);
	centralLayout->setSpacing(1);
	centralLayout->setContentsMargins(0, 0, 0,
	                                  0);  // setContentsMargins(1, 1, 1, 1);

	setLayout(centralLayout);
	resize(800, 600);
}

void PrintPreview::setup() {
	QSizeF page = printer.pageRect().size();
	page.setWidth(page.width() * view->logicalDpiX() / printer.logicalDpiX());
	page.setHeight(page.height() * view->logicalDpiY() / printer.logicalDpiY());

	// add a nice 2 cm margin
	const qreal margin = inches_to_pixels(mm_to_inches(20), this);
	QTextFrameFormat fmt = doc->rootFrame()->frameFormat();
	fmt.setMargin(margin);
	doc->rootFrame()->setFrameFormat(fmt);

	doc->setPageSize(page);
}

PrintPreview::~PrintPreview() {
	delete doc;
}

void PrintPreview::print() {
	QPrintDialog *dlg = new QPrintDialog(&printer, this);
	if (dlg->exec() == QDialog::Accepted)
		doc->print(&printer);
	delete dlg;
}

void PrintPreview::page_setup() {
	QPageSetupDialog dlg(&printer, this);
	if (dlg.exec() == QDialog::Accepted) {
		setup();
		view->updateLayout();
	}
}

// #include "PrintPreview.moc"
