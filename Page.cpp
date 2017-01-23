#include "Page.h"
#include <QProcess>

Page::Page(QString defaultDir, QObject *parent):QWebEnginePage(parent),_defaultDir(defaultDir) {
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
		QProcess p(this);
		p.setWorkingDirectory(file.section('/', 0, -2));
		p.start("/bin/bash", QStringList() << "-c" << file, QProcess::ReadOnly);
		p.waitForFinished(60000);
		QByteArray page=p.readAllStandardOutput();
		// Workaround for a difference from the old python based version
		page.replace("target=\"hidden\" ", "");
		setHtml(QString::fromLocal8Bit(page), QUrl("file://" + file));
	} else if(file.endsWith(".run")) {
		QProcess::startDetached("/bin/bash", QStringList() << "-c" << file);
	} else
		QWebEnginePage::load(file);
}
