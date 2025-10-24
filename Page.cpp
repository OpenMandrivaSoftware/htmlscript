#include "Page.h"
#include <QProcess>

Page::Page(QString defaultDir, QObject *parent):QWebEnginePage(parent),_defaultDir(defaultDir),_script(nullptr) {
	if(!_defaultDir.endsWith('/'))
		_defaultDir.append('/');
}

bool Page::acceptNavigationRequest(QUrl const &url, NavigationType type, bool isMainFrame) {
	if(url.isLocalFile()) {
		open(url.path());
		return false;
	}
	return true;
}

void Page::open(QString file) {
	if(!file.contains("://") && !file.startsWith("/"))
		file=_defaultDir + file;

	if(file.startsWith('/') && (file.endsWith(".sh.htm") || file.endsWith(".sh.html"))) {
		if(_script) {
			_script->terminate();
			delete _script;
		}
		_file = file;
		_script = new QProcess(this);
		connect(_script, &QProcess::finished, this, &Page::scriptFinished);
		_script->setWorkingDirectory(file.section('/', 0, -2));
		_script->start("/bin/bash", QStringList() << "-c" << file, QProcess::ReadOnly);
	} else if(file.endsWith(".run")) {
		QProcess::startDetached("/bin/bash", QStringList() << "-c" << file);
	} else
		QWebEnginePage::load(file);
}

void Page::scriptFinished() {
	QByteArray page=_script->readAllStandardOutput();
	// Workaround for a difference from the old python based version
	page.replace("target=\"hidden\" ", "");
	setHtml(QString::fromLocal8Bit(page), QUrl("file://" + _file));
	_script->deleteLater();
	_script = nullptr;
}
