#include "main.h"
#include <QWebEngineView>   //#include <QWebView> //#include <QtWebKitWidgets/QWebView>

//#include <QWebElement>
#include <QWebEnginePage>   //#include <QWebPage>
#include <QtWebEngineWidgets>



//#include <QWebFrame>
#include <QVBoxLayout>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QSslError>
#include <QSslCertificate>
#include <QSslConfiguration>
#include <QMessageBox>
#include <QMap>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QAction>
#include <QApplication>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QUrl>
#include <cassert>
#include <QDockWidget>

#ifdef Q_WS_QWS
#include <QWSServer>
#endif

#include "tabwidget.h"
#include "entrance.h"
#include "entranceinfo.h"
#include "toolbarsearch.h"
#include "views/recordTable/RecordTableScreen.h"
#include "controllers/recordTable/RecordTableController.h"
#include "views/recordTable/RecordTableView.h"
#include "models/recordTable/RecordTableData.h"
#include "models/recordTable/RecordTableModel.h"
#include "libraries/WindowSwitcher.h"
#include "views/browser/webview.h"
#include "libraries/qtSingleApplication5/qtsingleapplication.h"
#include "views/findInBaseScreen/FindScreen.h"
#include <utility>

namespace browser {
    //struct BrowserViewPrivate {
    //    //Q_OBJECT
    //public:
    //    QWebEngineView *view;
    //    QNetworkAccessManager *nam;
    //    QMap<QPair<QString, int>, QByteArray> exceptions;
    //    bool msgShown;
    //    //~BrowserViewPrivate() = default;
    //};

    //    //deprecated
    //    void BrowserManager::loadUrl(const int pos)
    //    {
    //        RecordTableController *recordTableController = globalParameters.getRecordTableScreen()->getRecordTableController();
    //        //int pos = recordTableController->getFirstSelectionPos();
    //        RecordTableModel *recordTableModel = recordTableController->getRecordTableModel();
    //        RecordTableData *recordTableData = recordTableModel->getRecordTableData();
    //        Record *record = recordTableData->getRecord(pos);

    //        //    QUrl _url;
    //        if(record) {
    //            //this->current_record = record;
    //            //_url = record->getField("url");
    //            main_window()->currentTab()->record(record);
    //            //mainWindow()->currentTab()->bind_recordtabcontroller(recordTableController);
    //            loadUrl(record);
    //        }
    //    }

    //Record *BrowserView::findRecord()
    //{
    //    Record *_record = nullptr;
    //    RecordTableController *recordTableController = globalParameters.getRecordTableScreen()->getRecordTableController();
    //    int pos = recordTableController->getFirstSelectionPos();

    //    if(pos != -1) {
    //        //RecordTableView *view = recordTableController->getView();
    //        //view->loadUrl();

    //        RecordTableModel *recordTableModel = recordTableController->getRecordTableModel();
    //        RecordTableData *recordTableData = recordTableModel->getRecordTableData();

    //        Record *record = recordTableData->getRecord(pos);

    //        //if(record->isLite())record->switchToFat();  // no such a value

    //        //QVariant qVariant = recordTableModel->data(pos, Qt::DisplayRole);

    //        //    if(current_record.isLite())current_record.switchToFat();

    //        //    QString dir = globalParameters.getWorkDirectory();
    //        //    QString name = this->d->view->title();

    //        //    if(0 == name.size())name = "default";

    //        //    this->current_record.setNaturalFieldSource("id", url.toString());

    //        //    //this->current_record.setField("name", name);  //
    //        //    this->current_record.setNaturalFieldSource("name", name);
    //        //    //this->current_record.setField("crypt", "0");


    //        //    QString author = "default";
    //        //    QString tags = "default";

    //        //    QString text = this->d->view->page()->mainFrame()->toHtml();

    //        //    if(0 == text.size())text = "<html>no content</html>";

    //        if(record) {
    //            //this->current_record
    //            _record = record;
    //        }

    //        //    this->current_record.setNaturalFieldSource("author", author);
    //        //    this->current_record.setNaturalFieldSource("tags", tags);
    //        //    this->current_record.setText(text);
    //        //    this->current_record.setNaturalFieldSource("url", url.toString());
    //        //    this->current_record.setNaturalFieldSource("dir", dir);

    //    }

    //    return _record;
    //}

    void Entrance::initSetting(void)
    {
        //    QUrl _url;

        //    if(record)
        //        _url = record->getField("url");

        QUrl url;
        // initialize

        QFileInfo settingsFile;

        // QString sb(QApplication::applicationDirPath());
        // sb.append(QDir::separator());
        // sb.append("browserview.ini");

        QString configFileName = globalparameters.getWorkDirectory() + "/browserview.ini";
        // check to see if we have a settings file where we started from
        // if not fall back to system hard coded path
        QFileInfo file(configFileName.toLatin1()); //file(sb.toLatin1());

        if(file.exists()) {
            qDebug() << "using local settings file";
            settingsFile.setFile(file.filePath());
        } else {
            qDebug() << "using system defined settings file";
            settingsFile.setFile(SETTINGS_FILE);
        }

        QSettings settings(settingsFile.filePath(), QSettings::NativeFormat);

        settings.beginGroup(SETTINGS_SECTION);

        //    if(_url.isEmpty()) {
        url = (settings.value("browser_view").toString());  //QUrl url(settings.value("browser_view").toString());

        //    } else {
        //        url = _url;
        //    }

        //    if(browser->currentTab()) {
        //        RecordTableController *recordtablecontroller = globalParameters.getRecordTableScreen()->getRecordTableController();
        //        //int pos = recordTableController->getFirstSelectionPos();
        //        Record *record = nullptr;

        //        //if(pos != -1) {
        //        RecordTableModel *recordtablemodel = recordtablecontroller->getRecordTableModel();
        //        //RecordTableView *recordtableview = recordtablecontroller->getView();
        //        RecordTableData *recordtabledata = recordtablemodel->getRecordTableData();
        //        record = recordtabledata->getRecordByUrl(url);
        //        //}

        //        if(record)browser->currentTab()->bind_recordtabcontroller(recordtablecontroller);

        //        if((browser->currentTab()->url() != url)) {
        //            this->setUrl(url);
        //        }
        //    }

        qDebug() << "loading url: " << settings.value("main_view").toString();

        if(settings.value("full_screen", false).toBool()) {
            this->showFullScreen();
        }

        if(settings.value("hide_cursor", false).toBool()) {
            this->setCursor(QCursor(Qt::BlankCursor));
#ifdef Q_WS_QWS
            QWSServer::setCursorVisible(false);
#endif
        }

        this->setScrollbars(settings.value("hide_scrollbars", false).toBool());
        this->setCache(settings.value("enable_cache", false).toBool(), settings.value("cache_size_megabytes", 5).toInt());

        settings.endGroup();



        this->show();

        //    RecordTableController *recordTableController = globalParameters.getRecordTableScreen()->getRecordTableController();
        //    int pos = recordTableController->getFirstSelectionPos();

        //    if(pos != -1) {
        //        //RecordTableView *view = recordTableController->getView();
        //        //view->loadUrl();

        //        RecordTableModel *recordTableModel = recordTableController->getRecordTableModel();
        //        RecordTableData *recordTableData = recordTableModel->getRecordTableData();

        //        Record *record = recordTableData->getRecord(pos);

        //        //if(record->isLite())record->switchToFat();  // no such a value

        //        //QVariant qVariant = recordTableModel->data(pos, Qt::DisplayRole);

        //        //    if(current_record.isLite())current_record.switchToFat();

        //        //    QString dir = globalParameters.getWorkDirectory();
        //        //    QString name = this->d->view->title();

        //        //    if(0 == name.size())name = "default";

        //        //    this->current_record.setNaturalFieldSource("id", url.toString());

        //        //    //this->current_record.setField("name", name);  //
        //        //    this->current_record.setNaturalFieldSource("name", name);
        //        //    //this->current_record.setField("crypt", "0");


        //        //    QString author = "default";
        //        //    QString tags = "default";

        //        //    QString text = this->d->view->page()->mainFrame()->toHtml();

        //        //    if(0 == text.size())text = "<html>no content</html>";

        //        if(record) this->current_record = record;

        //        //    this->current_record.setNaturalFieldSource("author", author);
        //        //    this->current_record.setNaturalFieldSource("tags", tags);
        //        //    this->current_record.setText(text);
        //        //    this->current_record.setNaturalFieldSource("url", url.toString());
        //        //    this->current_record.setNaturalFieldSource("dir", dir);

        //    }

        //this->current_record = findRecord();
    }

    //    void BrowserManager::loadUrl(Record *record)
    //    {
    //        QUrl _url = record->getField("url");

    //        if(!_url.isEmpty() && _url.isValid()) {

    //            if(main_window()->currentTab()->url() != _url) {

    //                //if(mainWindow())
    //                //mainWindow()->currentTab()->bind_recordtabcontroller(globalParameters.getRecordTableScreen()->getRecordTableController());
    //                main_window()->currentTab()->record(record);
    //                this->setUrl(_url);
    //            }

    //            this->show();

    //            main_window()->show();
    //            main_window()->currentTab()->show();
    //        }
    //    }

    Entrance *Entrance::prepend(Browser *browser)
    {
        setWidget(browser);
        browser->setParent(this);


        //        adjustSize();
        //        setAutoFillBackground(true);
        //        setFeatures(QDockWidget::NoDockWidgetFeatures);
        //        _browser = browser;
        _mainWindows.prepend(browser);

        return this;
    }

    void Entrance::on_activate_window()
    {

        FindScreen *findscreen = globalparameters.getFindScreen();

        assert(findscreen);
        assert(findscreen->historyhome());

        QObject::disconnect(_home_connection);

        _home_connection = QObject::connect(
                               findscreen->historyhome()
                               , &QAction::triggered
                               , this
        , [this](bool checked = true) {
            Q_UNUSED(checked)
            auto view = activiated_registered().second;

            if(view) {
                WebPage *page = view->page();

                if(page) {
                    Record *record = page->current_record();
                    assert(record);
                    QString home = record->getNaturalFieldSource("home");
                    QUrl homeurl = QUrl(home);

                    if(homeurl.isValid()
                       && homeurl != page->url()
                      ) {
                        record->setNaturalFieldSource("url", home);
                        page->load(record, true);
                    }
                }
            }
        }
                           );

    }

    Browser *Entrance::new_dockedwindow(const QByteArray &state)
    {

        Browser *browser = new Browser(state, _recordtablecontroller, this, _style_source, Qt::MaximizeUsingFullscreenGeometryHint); //, dock_widget

        //        _dockwidget->setWidget(browser);
        //        browser->setParent(_dockwidget);


        //        //        _dockwidget->adjustSize();
        //        //        _dockwidget->setAutoFillBackground(true);
        //        _dockwidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

        //        browser->restore_state(state);
        //        _mainWindows.prepend(browser);

        return browser;     // BrowserView::QDockWidget::BrowserWindow*
    }

    std::pair<Browser *, WebView *> Entrance::new_dockedwindow(QUrl const &url)
    {

        //        DockedWindow *browser =
        new Browser(url
                    , _recordtablecontroller
                    , this
                    , _style_source
                    , Qt::MaximizeUsingFullscreenGeometryHint
                   ); //, dock_widget


        return find(url);   // std::make_pair(browser, find(url).second);     // BrowserView::QDockWidget::BrowserWindow*
    }


    std::pair<Browser *, WebView *> Entrance::new_dockedwindow(Record *const record)
    {

        //        DockedWindow *browser =
        new Browser(record
                    , _recordtablecontroller
                    , this
                    , _style_source
                    , Qt::MaximizeUsingFullscreenGeometryHint
                   ); //, dock_widget


        return find(record);   // std::make_pair(browser, find(url).second);     // BrowserView::QDockWidget::BrowserWindow*
    }


    WebView *Entrance::new_view(QUrl const &url)
    {
        //BrowserView *browser_view = globalParameters.getBrowserView();
        //BrowserWindow *browser = nullptr;

        //if(browser_view) {
        //        browser = browser_view->getBrowserWindow();     //
        //auto dock_widget = new QDockWidget(this, Qt::MaximizeUsingFullscreenGeometryHint);
        //dock_widget->setParent(this);

        //        DockedWindow *browser =
        new Browser(url
                    , _recordtablecontroller
                    , this
                    , _style_source
                    , Qt::MaximizeUsingFullscreenGeometryHint
                   ); //, dock_widget

        //        _dockwidget->setWidget(browser);
        //        browser->setParent(_dockwidget);

        //        //    QVBoxLayout *layout = new QVBoxLayout(this);
        //        //    //QDockWidget *dock_widget = new QDockWidget(this, Qt::MaximizeUsingFullscreenGeometryHint);
        //        //    //when change dock_widget to member variable, you need rebuild the project! else the behavior will be weird.
        //        //    layout->setMargin(0);

        //        //        _dockwidget->adjustSize();
        //        //        _dockwidget->setAutoFillBackground(true);
        //        _dockwidget->setFeatures(QDockWidget::NoDockWidgetFeatures);   // AllDockWidgetFeatures

        //        //Qt::MaximizeUsingFullscreenGeometryHint

        //        //        if(!browser) {
        //        //            browser = new BrowserWindow(browser_view);  //incomplete
        //        //        }
        //        _mainWindows.prepend(browser);
        //        //browser->show();
        //        //}

        //        //this->exec();
        //        assert(record->binded_only_page());
        //        assert(record->binded_only_page()->view());

        return find(url).second;   // std::make_pair(browser, find(url).second);     // BrowserView::QDockWidget::BrowserWindow*
    }

    //    WebView *Entrance::new_dockedwindow(Record *const record)
    //    {
    //        //BrowserView *browser_view = globalParameters.getBrowserView();
    //        //BrowserWindow *browser = nullptr;

    //        //if(browser_view) {
    //        //        browser = browser_view->getBrowserWindow();     //
    //        //auto dock_widget = new QDockWidget(this, Qt::MaximizeUsingFullscreenGeometryHint);
    //        //dock_widget->setParent(this);
    //        DockedWindow *browser = new DockedWindow(record->getNaturalFieldSource("url")
    //                                                 , _recordtablecontroller
    //                                                 , this
    //                                                 , _style_source
    //                                                 , Qt::MaximizeUsingFullscreenGeometryHint
    //                                                ); //, dock_widget

    //        //        _dockwidget->setWidget(browser);
    //        //        browser->setParent(_dockwidget);

    //        //        //    QVBoxLayout *layout = new QVBoxLayout(this);
    //        //        //    //QDockWidget *dock_widget = new QDockWidget(this, Qt::MaximizeUsingFullscreenGeometryHint);
    //        //        //    //when change dock_widget to member variable, you need rebuild the project! else the behavior will be weird.
    //        //        //    layout->setMargin(0);

    //        //        //        _dockwidget->adjustSize();
    //        //        //        _dockwidget->setAutoFillBackground(true);
    //        //        _dockwidget->setFeatures(QDockWidget::NoDockWidgetFeatures);   // AllDockWidgetFeatures

    //        //        //Qt::MaximizeUsingFullscreenGeometryHint

    //        //        //        if(!browser) {
    //        //        //            browser = new BrowserWindow(browser_view);  //incomplete
    //        //        //        }
    //        //        _mainWindows.prepend(browser);
    //        //        //browser->show();
    //        //        //}

    //        //        //this->exec();
    //        assert(record->binded_only_page());
    //        assert(record->binded_only_page()->view());
    //        return record->binded_only_page()->view();  // std::make_pair(browser, record->binded_only_page()->view());     // BrowserView::QDockWidget::BrowserWindow*
    //    }


    //    DockWidget::DockWidget(QWidget *parent, DockedWindow *browser, Qt::WindowFlags flags)
    //        : QDockWidget(parent, flags)
    //    {
    //        this->setWidget(browser);
    //        browser->setParent(this);

    //        //    QVBoxLayout *layout = new QVBoxLayout(this);
    //        //    //QDockWidget *dock_widget = new QDockWidget(this, Qt::MaximizeUsingFullscreenGeometryHint);
    //        //    //when change dock_widget to member variable, you need rebuild the project! else the behavior will be weird.
    //        //    layout->setMargin(0);

    //        //        adjustSize();
    //        //        setAutoFillBackground(true);
    //        setFeatures(QDockWidget::NoDockWidgetFeatures);   // AllDockWidgetFeatures

    //        //Qt::MaximizeUsingFullscreenGeometryHint

    //        qobject_cast<Entrance *>(parent)->window_list().prepend(browser);
    //    }

    Entrance::Entrance(RecordTableController *recordtablecontroller, const QString &style_source, QWidget *parent, Qt::WindowFlags flags)
        : QDockWidget(parent, flags)  //, _application(application)
        , _mainWindows(QList<QPointer<Browser> >())
        , _recordtablecontroller(recordtablecontroller)
        , _style_source(style_source)
        , _hidetitlebar(new QWidget(this, Qt::FramelessWindowHint | Qt::CustomizeWindowHint
                                    //| Qt::SplashScreen
                                   ))
          //    , _dockwidget(new DockWidget(
          //                      this
          //                      , _mainWindows[0].data()
          //                      ,  flags  //Qt::Widget   //Qt::WindowMaximizeButtonHint //Qt::MaximizeUsingFullscreenGeometryHint
          //                  )
          //                 )
          //        , _browser(new DockedWindow(register_record(QUrl(DockedWindow::_defaulthome))
          //                                    , recordtablecontroller
          //                                    , this, style_source, flags    //Qt::Widget   //Qt::WindowMaximizeButtonHint  // Qt::MaximizeUsingFullscreenGeometryHint
          //                                   ))
    {

        //        invoke_ptr = &Entrance::active_url;

        //_mainWindows.prepend(browser);

        //d->view = new QWebEngineView(this);
        //d->view->page()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
        //d->view->page()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

        //    browser->setWebAttribute(QWebEngineSettings::JavascriptEnabled, true);
        //    browser->setWebAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);

        //browser->msgShown = false;

        //    QVBoxLayout *layout = new QVBoxLayout(this);
        //    QDockWidget *dock_widget = new QDockWidget(this, Qt::MaximizeUsingFullscreenGeometryHint);
        //    when change dock_widget to member variable, you need rebuild the project! else the behavior will be weird.
        //    layout->setMargin(0);


        //        _dockwidget->setWidget(_mainWindows[0].data());
        //        //    //    layout->addWidget(browser);
        //        //    //    browser->setLayout(layout);
        //        _mainWindows[0]->setParent(_dockwidget);

        setWindowFlags( //Qt::Window |
            Qt::FramelessWindowHint
            //|Qt::Popup
            | Qt::CustomizeWindowHint
            //| Qt::SplashScreen  // http://www.qtforum.org/article/20174/how-to-create-borderless-windows-with-no-title-bar.html?s=86e2c5a6509f28a482adbb7d9f3654bb2058a301#post75829
        );

        setAutoFillBackground(true);
        adjustSize();
        setFeatures(QDockWidget::NoDockWidgetFeatures
                    | QDockWidget::DockWidgetVerticalTitleBar
                    //| Qt::DockWidgetArea::NoDockWidgetArea
                    //| Qt::MaximizeUsingFullscreenGeometryHint
                   ); // AllDockWidgetFeatures
        //this->titleBarWidget()->hide();

        QWidget *titleBar = titleBarWidget();

        //        QVBoxLayout *main = new QVBoxLayout;
        //        //main -> addLayout(0);
        //        //main -> addLayout(0);
        //        main->setGeometry(QRect());
        //        main->setSizeConstraint(QLayout::SetMinimumSize);
        //        //setWindowTitle(tr("Find"));
        //        //setLayout(main);

        //        _hidetitlebar->setMinimumWidth(0);
        //        _hidetitlebar->setMaximumWidth(0);
        //        _hidetitlebar->setMinimumHeight(0);
        //        _hidetitlebar->setMaximumHeight(
        //            0
        //            // parent->height() // for QDockWidget::DockWidgetVerticalTitleBar
        //        );
        //        _hidetitlebar->setMinimumSize(QSize(0, 0));
        //        _hidetitlebar->resize(QSize(0, 0));

        //_hidetitlebar->setLayout(main);

        setTitleBarWidget(_hidetitlebar);
        //_hidetitlebar->hide();
        _hidetitlebar->setVisible(false);

        delete titleBar;

        setupActions();

        setupUI();
        assembly();

        initSetting();

        setupSignals();

        //        new_mainwindow(register_record(QUrl(DockedWindow::_defaulthome)));  // main_window() will never fail

        //d->nam = d->view->page()->networkAccessManager();

        //connect(d->nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(finished(QNetworkReply *)));

        //connect(d->nam, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)), this, SLOT(sslErrors(QNetworkReply *, const QList<QSslError> &)));

        //    browser->show();
    }

    Entrance::~Entrance()
    {
        if(_hidetitlebar)delete _hidetitlebar;

        for(int i = 0; i < _mainWindows.size(); ++i) {
            Browser *window = _mainWindows.at(i);
            delete window;
        }

        //if(isselfcreated())delete current_record;   // no, do not apply memory by this class for record, from the original source
        if(_actionFreeze)delete _actionFreeze;

        //        if(_dockwidget)delete _dockwidget;

        //    if(browser)delete browser;  // I can't destroy?
    }


    void Entrance::setupActions()
    {
        _actionFreeze = new QAction(tr("Pin / freeze browser view"), this);
        _actionFreeze->setStatusTip(tr("Pin / freeze browser view"));
        _actionFreeze->setIcon(QIcon(":/resource/pic/pentalpha.svg"));
    }

    void Entrance::setupUI(void)
    {

    }

    //void BrowserView::setupDynamicSignals(void)
    //{

    //    //    //Connect a signal to a pointer to qobject member function
    //    //    template <typename Func1, typename Func2>
    //    //    static inline QMetaObject::Connection connect(
    //    //        const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
    //    //        const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot,
    //    //        Qt::ConnectionType type = Qt::AutoConnection);

    //    static QMetaObject::Connection _connection_loadfinished;    // for disconnect
    //    static QMetaObject::Connection _connection_openlinkinnewtab;

    //    if(_connection_loadfinished.operator void *QMetaObject::Connection:: * () != nullptr) {
    //        QObject::disconnect(_connection_loadfinished);
    //    }

    //    if(_connection_openlinkinnewtab.operator void *QMetaObject::Connection:: * () != nullptr) {
    //        QObject::disconnect(_connection_openlinkinnewtab);
    //    }

    //    //…
    //    //    _connection = QObject::connect(…);
    //    //…
    //    //    QObject::disconnect(_connection);
    //    if(browser->currentTab() != nullptr) {
    //        _connection_loadfinished =  //QWebView::
    //            connect
    //            //                   <
    //            //                   void (QWebView::*)(bool)
    //            //                   , void (RecordTableController::*)(void)
    //            //                   >
    //            (
    //                browser->currentTab()
    //                //, &BrowserView::urlChanged//, &QWebView::urlChanged  //
    //                , &WebView::loadFinished
    //                , this//globalParameters.getRecordTableScreen()->getRecordTableController()
    //                //, &BrowserView::onUrlChanged//&RecordTableController::autoAddNewAfterContext
    //                , &BrowserView::onLoadFinished//
    //            );

    //        //    _connection = connect(this
    //        //                          , &BrowserView::loadChanged
    //        //                          , globalParameters.getRecordTableScreen()->getRecordTableController()
    //        //                          , &RecordTableController::autoAddNewAfterContext);

    //        //void (BrowserView::*lU)(const QUrl &) = &BrowserView::loadUrl;
    //        _connection_openlinkinnewtab = connect
    //                                       //                  <
    //                                       //                  void (QWebEngineView::*)(const QUrl &)
    //                                       //                  , void (BrowserView::*)(const QUrl &)
    //                                       //                  >
    //                                       (browser->currentTab()
    //                                        , &WebView::openLinkInNewTab
    //                                        , this
    //                                        //, &BrowserView::loadUrl //
    //                                        , &BrowserView::openLinkInNewTab
    //                                       );
    //    }
    //}

    void Entrance::active_url(const QUrl &url)
    {
        //        Record *r =
        auto ara = boost::make_shared<Entrance::ActiveRecordBinder>(this);
        request_record(
            url
            , std::make_shared<sd::_interface<sd::meta_info<boost::shared_ptr<void>>, browser::WebView *, Record *const>>(
                ""
                , &Entrance::ActiveRecordBinder::generator
                , ara
            )
            , std::make_shared<sd::_interface<sd::meta_info<boost::shared_ptr<void>>, void>>(
                ""
                , &Entrance::ActiveRecordBinder::activator
                , ara
            )
        );
        //        r->active_immediately(true);
        //        return active_record(r);
    }

    void Entrance::setupSignals(void)
    {
        auto _toolbarsearch = globalparameters.getFindScreen()->toolbarsearch();
        connect(_toolbarsearch, &ToolbarSearch::search, this, &Entrance::active_url);
        connect(this->_actionFreeze, SIGNAL(triggered()), globalparameters.getWindowSwitcher(), SLOT(findInBaseClick()));

    }

    void Entrance::assembly(void)
    {

    }

    //    void BrowserManager::setUrl(const QUrl &_url)
    //    {
    //        //if(browser)
    //        main_window()->loadPage(_url.toString());
    //    }

    void Entrance::setScrollbars(bool hide)
    {
        if(!hide) {
            //d->view->page()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAsNeeded);
            //d->view->page()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAsNeeded);
        }
    }

    void Entrance::setCache(bool cache, int cacheSize)
    {
        if(cache) {
            QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
            QString location = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
            diskCache->setCacheDirectory(location);
            diskCache->setMaximumCacheSize(cacheSize * 1024 * 1024); //in MB's
            //d->nam->setCache(diskCache);
            //        browser->setCache(diskCache);
            qDebug() << QString("Cache location: %1").arg(location);
            qDebug() << QString("Cache maximum size: %1MB").arg(cacheSize);
        }
    }

    //    //deprecated
    //    void BrowserManager::onLoadFinished(bool finished)
    //    {
    //        if(finished) {

    //            //        //QWebFrame *frame = d->view->page()->mainFrame();
    //            //        //QWebElement dom_title(frame->findFirstElement("title"));
    //            //        QString title = mainWindow()->currentTab()->title();   //dom_title.evaluateJavaScript("this.text").toString();

    //            //        RecordTableController *recordTableController = globalParameters.getRecordTableScreen()->getRecordTableController();

    //            //        //RecordTableData *recordTableData = recordTableController->getRecordTableModel()->getRecordTableData();

    //            //        int pos = recordTableController->getFirstSelectionPos();
    //            //        Record *_record = recordTableController->getRecordTableModel()->getRecordTableData()->getRecord(pos);

    //            //        if(_record)_record->setNaturalFieldSource("name", title);

    //            main_window()->currentTab()->synchronize_title_to_record();
    //        }
    //    }

    //    // deprecated, move to class WebView
    //    void BrowserManager::openLinkInNewTab()
    //    {
    //        //QString url(QString(""));
    //        QUrl _url = main_window()->currentTab()->url();

    //        RecordTableController *recordTableController = globalParameters.getRecordTableScreen()->getRecordTableController();

    //        RecordTableData *recordTableData = recordTableController->getRecordTableModel()->getRecordTableData();

    //        if(!recordTableData->isRecordExists(_url)) {

    //            int pos = recordTableController->getFirstSelectionPos();
    //            Record *previous_record = recordTableController->getRecordTableModel()->getRecordTableData()->getRecord(pos);

    //            if(previous_record) {
    //                Record record;

    //                if(record.isLite())record.switchToFat();

    //                //QString title = d->view->title(); // not ready yet
    //                record.setNaturalFieldSource("id",   previous_record->getNaturalFieldSource("id"));
    //                record.setNaturalFieldSource("name",   previous_record->getNaturalFieldSource("name"));
    //                record.setNaturalFieldSource("author", previous_record->getNaturalFieldSource("author"));
    //                record.setNaturalFieldSource("url",    _url.toString());    // only changed
    //                record.setNaturalFieldSource("tags",   previous_record->getNaturalFieldSource("tags"));

    //                recordTableController->addNew(ADD_NEW_RECORD_AFTER, record);   //recordTableController->autoAddNewAfterContext();
    //            }
    //        }

    //        //    Record *previous_record = recordTableController->getRecordTableModel()->getRecordTableData()->getRecord(pos);
    //        //    //if(current_record)
    //        //    url = previous_record->getNaturalFieldSource("url");

    //        //    std::string url_compare_stored = _url.toString().toStdString();
    //        //    std::string url_compare_get = url.toStdString();
    //        //    std::string compare = getDifference(url_compare_stored, url_compare_get);
    //        //    //QUrl qurl(url);

    //        //    //if(qurl != _url) {
    //        //    if(compare.size() != 0 && compare != "/") { // really changed!

    //        //        //if(this->current_record->getNaturalFieldSource("url") != _url.toString()) {



    //        //        //this->current_record = new Record();    // should from framework

    //        //        Record record;

    //        //        if(record.isLite())record.switchToFat();

    //        //        record.setNaturalFieldSource("id",   previous_record->getNaturalFieldSource("id"));
    //        //        record.setNaturalFieldSource("name",   previous_record->getNaturalFieldSource("name"));
    //        //        record.setNaturalFieldSource("author", previous_record->getNaturalFieldSource("author"));
    //        //        record.setNaturalFieldSource("url",    _url.toString());    // only changed
    //        //        record.setNaturalFieldSource("tags",   previous_record->getNaturalFieldSource("tags"));

    //        //        //record.setText(browser_view->getText());
    //        //        if(!recordTableData->isRecordExists(_url)) {
    //        //            //this->current_record->setNaturalFieldSource("url", _url.toString());
    //        //            recordTableController->addNew(ADD_NEW_RECORD_AFTER, record);   //recordTableController->autoAddNewAfterContext();

    //        //            //loadUrl(_url);

    //        //            //this->current_record = findRecord();
    //        //            //assert(this->current_record->getNaturalFieldSource("url") == _url.toString());
    //        //        }

    //        //    }
    //    }


    void Entrance::finished(QNetworkReply *reply)
    {
        if(reply->error() != QNetworkReply::NoError) {
            qDebug() <<  QString("Network Error: %1").arg(reply->errorString());
        }

        if(reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool() == true) {
            QVariant contentVar = reply->header(QNetworkRequest::ContentTypeHeader);
            qDebug() <<  QString("Cache Used: %1").arg(contentVar.toString());
        }

        //    QUrl url = reply->url();
        //    QString _url = current_record->getNaturalFieldSource("url");
        //    std::string url_compare_stored = _url.toStdString();
        //    std::string url_compare_get = url.toString().toStdString();
        //    std::string compare = "";

        //    if(url_compare_stored.size() >= url_compare_get.size()) {
        //        url_compare_stored.erase(url_compare_get.begin(), url_compare_get.end());
        //        compare = url_compare_stored;
        //    } else {
        //        url_compare_get.erase(url_compare_stored.begin(), url_compare_stored.end());
        //        compare = url_compare_get;
        //    }

        //    std::string::size_type pos;

        //    while((pos = compare.find_first_of(" ")) != compare.npos)compare.erase(pos, 1);

        //    if(compare == "" || compare == "/") {
        //        //if(this->current_record->getNaturalFieldSource("url") != url.toString()) {
        //        this->current_record->setNaturalFieldSource("url", url.toString());
        //        this->loadChanged();
        //    }

    }

    void Entrance::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
    {
        foreach(const QSslError &error, errors) {
            qDebug() << QString("SSL Error: %1").arg(error.errorString());
        }

        reply->ignoreSslErrors(errors);
    }


    void Entrance::clean()
    {
        if(_mainWindows.count() > 0) {
            // cleanup any deleted main windows first
            for(int i = _mainWindows.count() - 1; i >= 0; --i) {
                if(_mainWindows.at(i).isNull()) {
                    _mainWindows.removeAt(i);
                }
            }
        }
    }

    std::pair<Browser *, WebView *> Entrance::activiated_registered()
    {
        clean();
        std::pair<Browser *, WebView *> dp = std::make_pair(nullptr, nullptr);


        //        if(_mainWindows.isEmpty()) {
        //            dp = new_dockedwindow(
        //                     QUrl(DockedWindow::_defaulthome)
        //                 );
        //        } else { //

        if(!_mainWindows.isEmpty()) {
            for(auto &i : _mainWindows) {
                if(i->isVisible() || i->isActiveWindow()) {
                    assert(i.data());
                    dp.first = i.data();
                    dp.second = i->tabWidget()->currentWebView();
                    break;
                }
            }
        }

        //        assert(dp.first);
        return //qobject_cast<DockedWindow *>(widget()); //
            dp;   //_mainWindows[0];
    }

    //    WebView *Entrance::active_record_alternative(Record *const record) {return active_record(record).second;}

    // prepare active chain but not load them
    std::pair<Browser *, WebView *> Entrance::equip_registered(Record *const record)
    {
        assert(record);
        clean();
        //DockedWindow *w = nullptr;
        std::pair<Browser *, WebView *> dp = std::make_pair(nullptr, nullptr);

        if(record) {
            //            assert(!record->generator()); // maybe Entrance::ActiveRecordBinder registered
            assert(QUrl(record->getNaturalFieldSource("url")).isValid());

            if(// !record->generator() && // maybe Entrance::ActiveRecordBinder registered
                    QUrl(record->getNaturalFieldSource("url")).isValid()) {
                //        QUrl url = QUrl(record->getNaturalFieldSource("url"));



                if(_mainWindows.isEmpty()) {

                    //            Record *r = record ? record : request_record(QUrl(DockedWindow::_defaulthome));
                    //            r->active_immediately(true);

                    dp = new_dockedwindow(
                             record // record ? QUrl(record->getNaturalFieldSource("url")).isValid() ? QUrl(record->getNaturalFieldSource("url")) : QUrl(DockedWindow::_defaulthome) : QUrl(DockedWindow::_defaulthome)
                         );
                } else {
                    auto generator = [](boost::shared_ptr<WebPage::ActiveRecordBinder> ar) {
                        return std::make_shared<sd::_interface<sd::meta_info<boost::shared_ptr<void>>, browser::WebView *, Record *const>> (
                                   ""
                                   , &WebPage::ActiveRecordBinder::generator
                                   , ar
                               );
                    };
                    auto activator = [](boost::shared_ptr<WebPage::ActiveRecordBinder> ar) {
                        return std::make_shared<sd::_interface<sd::meta_info<boost::shared_ptr<void>>, void>> (
                                   ""
                                   , &WebPage::ActiveRecordBinder::activator
                                   , ar
                               );
                    };

                    //                    if(record && QUrl(record->getNaturalFieldSource("url")).isValid()) {
                    //            if(record)record->active_immediately(true);

                    for(auto &i : _mainWindows) {

                        dp.second = i->tabWidget()->find(record->getNaturalFieldSource("url"));

                        if(dp.second != nullptr) {
                            //setWidget(i.data());
                            dp.first = i.data();

                            //                    if(!i->isVisible() || !i->isActiveWindow()) {
                            //                        i->raise();
                            //                        i->activateWindow();
                            //                    }

                            break;
                        } else if(i->isVisible() || i->isActiveWindow()) {
                            assert(i.data());
                            dp.first = i.data();
                            //                    break;
                        }
                    }

                    assert(dp.first);

                    if(dp.second == nullptr && dp.first) {
                        //            dp = invoke_page(record); //->tabWidget()->find_view(record);    // create_view(record, main_window(record));
                        dp.second = dp.first->invoke_page(record);
                    }

                    //            if(!dp.first->isActiveWindow() || !dp.first->isVisible()) {
                    //                dp.first->raise();
                    //                dp.first->activateWindow();
                    //            }

                    //            dp.first->tabWidget()->setCurrentWidget(dp.second);
                    //            dp.second->show();

                    // registered record, but have no generator:
                    boost::shared_ptr<WebPage::ActiveRecordBinder> ar = boost::make_shared<WebPage::ActiveRecordBinder>(dp.second->page(), true);
                    record->generator(
                        generator(ar)
                    );

                    record->activator(
                        activator(ar)
                    );

                    //                    }

                    //            else {    // record == nullptr and !_mainWindows.isEmpty()
                    //                // just for get a activiated view
                    //                for(auto &i : _mainWindows) {
                    //                    if(i->isActiveWindow()) {
                    //                        dp.first = i.data();
                    //                        dp.second = i->tabWidget()->currentWebView();
                    //                    }
                    //                }

                    //                //                boost::shared_ptr<WebPage::ActiveRecordBinder> ar = boost::make_shared<WebPage::ActiveRecordBinder>(dp.second->page(), true);
                    //                //                request_record(
                    //                //                    QUrl(DockedWindow::_defaulthome)
                    //                //                    , generator(ar)
                    //                //                    , activator(ar)
                    //                //                );
                    //            }
                }

                assert(dp.first);
                assert(dp.second);
                setWidget(dp.first);
            }
        }

        return dp;  // qobject_cast<DockedWindow *>(widget()); //
        // _mainWindows[0];
    }

    //    std::pair<DockedWindow *, WebView *> Entrance::invoke_page(Record *const record)
    //    {
    //        clean();

    //        std::pair<DockedWindow *, WebView *> dp = std::make_pair(nullptr, nullptr);

    //        if(_mainWindows.isEmpty()) {
    //            dp = new_dockedwindow(record);
    //        } else {
    //            for(auto &i : _mainWindows) {
    //                dp.second = i->tabWidget()->find(record->getNaturalFieldSource("url"));

    //                if(dp.second != nullptr) {
    //                    dp.first = i.data();

    //                    if(!i->isVisible()) {
    //                        i->raise();
    //                        i->activateWindow();
    //                    }

    //                    break;
    //                } else if(i->isVisible()) {
    //                    dp.first = i.data();
    //                }
    //            }

    //            if(dp.first == nullptr) {
    //                dp.first = _mainWindows[0].data();
    //            }

    //            assert(dp.first);
    //        }


    //        const DockedWindow *w = dp.first;
    //        TabWidget *const tab = w->tabWidget();

    //        if(dp.second == nullptr && w != nullptr) {

    //            // Record *blank_url = check_register_record(QUrl(DockedWindow::_defaulthome));

    //            //            if(blank.isLite())blank.switchToFat();
    //            //            blank.setNaturalFieldSource("url", DockedWindow::_defaulthome);

    //            WebView *blankview = nullptr;
    //            blankview = tab->find(QUrl(DockedWindow::_defaulthome));
    //            //PageView *no_pin = nullptr;
    //            dp.second = w->tabWidget()->find_nopin();
    //            // assert(dp.first);

    //            if(blankview != nullptr) {
    //                dp.second = blankview;
    //                blankview->page()->load(record);
    //            } else if(dp.second != nullptr) {   // no_pin
    //                if(dp.second->page()->url().toString() != record->getNaturalFieldSource("url"))dp.second->page()->load(record);
    //            } else {
    //                dp.second = tab->newTab(record);  // , false
    //                // auto load
    //            }

    //            //            tab->setCurrentWidget(dp.second);   // tab->setCurrentIndex(tab->webViewIndex(dp.second));
    //            //            dp.second->show();
    //        }

    //        //        tab->setCurrentWidget(dp.second);
    //        //        dp.second->show();
    //        assert(dp.first);
    //        assert(dp.second);
    //        return dp;  //_mainWindows[0];
    //    }

    //    QList<DockedWindow *> Entrance::window_raw_list()
    //    {
    //        clean();
    //        QList<DockedWindow *> list;

    //        for(int i = 0; i < _mainWindows.count(); ++i)
    //            list.append(_mainWindows.at(i));

    //        return list;
    //    }

    QList<QPointer<Browser> > &Entrance::window_list()
    {
        clean();
        //        QList<DockedWindow *> list;

        //        for(int i = 0; i < _mainWindows.count(); ++i)
        //            list.append(_mainWindows.at(i));

        return _mainWindows;    // list;
    }

#if defined(Q_OS_OSX)
    void BrowserView::lastWindowClosed()
    {
        clean();
        BrowserWindow *mw = new BrowserWindow(this);
        mw->slotHome();
        _mainWindows.prepend(mw);
    }
#endif


    void Entrance::openUrl(const QUrl &url)
    {
        active_url(url); // active_record()->loadPage(url.toString());
    }


    std::pair<Browser *, WebView *> Entrance::find(Record *const record)
    {
        std::pair<Browser *, WebView *> dp{nullptr, nullptr};

        //        if(_mainWindows.isEmpty())dp.first = activebrowser();

        //        if(!_mainWindows.isEmpty()) {
        //new_dockedwindow(record);
        for(auto &i : _mainWindows) {
            dp.second = i->tabWidget()->find(record->getNaturalFieldSource("url"));

            if(dp.second != nullptr) {
                //setWidget(i.data());
                dp.first = i.data();
                break;
            } else if(i->isVisible() || i->isActiveWindow()) {
                dp.first = i.data();
            }
        }

        //        }

        //        if(dp.first == nullptr)dp.first = _mainWindows[0].data();

        //        if(!dp.first->isActiveWindow()) {
        //            dp.first->raise();
        //            dp.first->activateWindow();
        //        }
        assert(dp.first);
        return dp;
    }

    std::pair<Browser *, WebView *> Entrance::find(QUrl url)
    {
        std::pair<Browser *, WebView *> dp{nullptr, nullptr};

        //        if(_mainWindows.isEmpty())dp.first = activebrowser();

        //        if(!_mainWindows.isEmpty()) {
        //new_dockedwindow(record);
        for(auto &i : _mainWindows) {
            dp.second = i->tabWidget()->find(url);

            if(dp.second != nullptr) {
                //setWidget(i.data());
                dp.first = i.data();
                break;
            } else if(i->isVisible() || i->isActiveWindow()) {
                dp.first = i.data();
            }
        }

        //        }

        //        if(dp.first == nullptr)dp.first = _mainWindows[0].data();

        //        if(!dp.first->isActiveWindow()) {
        //            dp.first->raise();
        //            dp.first->activateWindow();
        //        }
        assert(dp.first);
        return dp;
    }

    //    BrowserView *BrowserManager::create_view(Record *record, BrowserWindow *window)
    //    {
    //        BrowserView *bv = nullptr;
    //        bv = window->tabWidget()->newTabFull(record, _recordtablecontroller, true);
    //        return bv;
    //    }

    bool Entrance::restore_state(const QByteArray &state)
    {
        if(window_list().count() == 0) {
            new_dockedwindow(QUrl(browser::Browser::_defaulthome));
        }

        return activiated_registered().first->restore_state(state);
    }

    //    std::pair<DockedWindow *, WebView *> Entrance::active_record(Record *const record)
    //    {


    //        std::pair<DockedWindow *, WebView *> dp;
    //        //        DockedWindow *w = nullptr;
    //        //        PageView *bv = nullptr;
    //        dp = active_record(record);   // assert(record->page() == nullptr);  // maybe come from other tree branches

    //        assert(dp.first);
    //        assert(dp.second);

    //        //        if(dp.second == nullptr && dp.first) {
    //        //            //            dp = invoke_page(record); //->tabWidget()->find_view(record);    // create_view(record, main_window(record));
    //        //            dp.second = dp.first->invoke_page(record);
    //        //        }

    //        //        assert(dp.second);

    //        setWidget(dp.first);

    //        //        if(!dp.first->isActiveWindow()) {
    //        //            dp.first->raise();
    //        //            dp.first->activateWindow();
    //        //        }

    //        //        // should this after loadfinished()? a global knoeledge based strategy needed?
    //        //        dp.first->tabWidget()->setCurrentWidget(dp.second);
    //        //        dp.second->show();


    //        //        bv->window()->raise();
    //        //        dp.second->switch_show();

    //        return dp;
    //    }


    //    void BrowserManager::runScriptOnOpenViews(const QString &source)
    //    {
    //        for(auto &w : main_windows()) {
    //            w->runScriptOnOpenViews(source);

    //            //            for(int i = 0; i < w->tabWidget()->count(); ++i) {
    //            //                auto browserview = w->tabWidget()->webView(i);

    //            //                if(browserview != nullptr)
    //            //                    browserview->page()->runJavaScript(source);
    //            //            }
    //        }
    //    }


}


