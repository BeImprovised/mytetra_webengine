/*********************************************************************************

    SysTrayIcon.h - Header file for QTM system tray icon
    Copyright (C) 2006-2009 Matthew J Smith

    This file is part of QTM.

    QTM is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 2), as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *******************************************************************************/

#ifndef SYSTRAYICON_H
#define SYSTRAYICON_H

#include <QtGlobal>

// #include "useSTI.h"
// #ifdef USE_SYSTRAYICON
#include "libraries/global_parameters.h"
//#include "libraries/qt_single_application5/qtsingleapplication.h"
#include <QByteArray>
#include <QClipboard>
#include <QDomElement>
#include <QList>
#include <QString>
#include <QStringList>
#include <QSystemTrayIcon>
#ifdef UNITY_LAUNCHER
#include "ui_ListDialogBase.h"
#endif

class QMenu;
class QAction;
class QHttpResponseHeader;
class QuickpostTemplate;
class QListWidgetItem;

class QNetworkAccessManager;
class QNetworkReply;
class sapp_t;
class rs_t;
class HidableTab;
// class ExposedSappRecentFile;

#ifdef Q_OS_MAC
#if QT_VERSION >= 0x050000 // This function is in QMenu in Qt 5.2
void qt_mac_set_dock_menu(QMenu*);
#endif
#endif

class wn_t;
namespace web {
	class Profile;
	template <typename>
	class Docker;
}
class Blogger;
namespace app {
	struct RecentFile;
}
class SysTrayIcon : public STI_SUPERCLASS {
	Q_OBJECT

    public:
	SysTrayIcon(HidableTab* vtab_record, web::Docker<Blogger>* editor_docker, wn_t* main_window, web::Profile* profile, QString style_source, bool noWindow = false, Qt::WindowFlags flags = Qt::Widget, QObject* parent = 0);
	~SysTrayIcon();
	void setDoubleClickFunction(int);
	bool dontStart();
	QStringList templates();
	QStringList templateTitles();
	void quickpostFromDBus(QString&, QString&);

    public slots:
	void configureQuickpostTemplates(QWidget* parent = 0);
	void setCopyTitle(bool);
	void newDoc();
	void openRecentFile();
	void choose(QString fname = QString());
	void chooseRecentFile();
	void quickpost(QClipboard::Mode mode = QClipboard::Clipboard);
	void chooseQuickpostTemplate();
	bool handleArguments();
	void doQuit();
	void saveAll();
	void set_recent_files(const QList<std::shared_ptr<app::RecentFile>>&);

    private slots:
	void iconActivated(QSystemTrayIcon::ActivationReason);
	void quickpostFromTemplate(int, QString, QString t = QString());
	void setNewWindowAtStartup(bool);
	void handleDone(QNetworkReply*);
	void abortQP();
	void openRecentFileFromDialog(QListWidgetItem*);
	void actOnChooseQuickpostTemplate(QListWidgetItem*);

    signals:
	void quickpostTemplateTitlesUpdated(QStringList);
	void quickpostTemplatesUpdated(QStringList);

    private:
	sapp_t* _app;
	// enum _cbtextIsURL { No, Yes, Untested };
	// enum _cbtextIsURL cbtextIsURL;
	bool _copyTitle;
	int activeTemplate;
	QAction* newWindowAtStartup;
	QAction* abortAction;
	QAction* configureTemplates;
#ifndef SUPERMENU
	// QAction *quitAction;
	QAction* _action_tray_quit;
#endif
	QList<QuickpostTemplate*> quickpostTemplateActions;

	QAction* _action_tray_restore;
	QAction* _action_tray_maximize;
	QAction* _action_tray_minimize;

	QMenu* menu;
	QMenu* templateMenu;
	bool _newWindowAtStartup;
	QNetworkAccessManager* netmgr;
	QNetworkReply* currentReply;
	QByteArray responseData;
	QString _cb_text;
	// bool cbtextIsURL;
	int doubleClickFunction;
	bool httpBusy;
	bool templateQPActive;
	bool _dontStart;
	QStringList templateTitleList, templateList;
	QList<int> defaultPublishStatusList;
	QList<bool> copyTitleStatusList;
	QList<QStringList> assocHostLists;
	QList<std::shared_ptr<app::RecentFile>> _recent_files;
	QAction* recentFileActions[10];
	QAction* openRecent;
	QAction* noRecentFilesAction;
	QMenu* recentFilesMenu;
	QByteArray userAgentString;

	//	ts_t *_tree_screen;
	//	web::Docker<web::Browser>* _browser_docker;
	HidableTab* _vtab_record;

	wn_t* _main_window;
	web::Profile* _profile;
	Qt::WindowFlags _flags;
	QString _style_source;

	//	FindScreen *_find_screen;
	web::Docker<Blogger>* _editor_docker;

// QSplitter *_splitter;
// std::shared_ptr<QSettings>  _splitter_config;
// QString _splitter_groupname;
// QString _splitter_sizelist;

#ifndef DONT_USE_DBUS
// QDBusConnection *dbus;
#endif

	void setupQuickpostTemplates();
	void doQP(QString);
	QDomElement templateElement(QDomDocument&, QString&, QString&, int&, bool&, QStringList&);
	void updateRecentFileMenu();
	void setup_main_window_icon_actions();
};

// #endif
#endif
