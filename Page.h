#ifndef _PAGE_H_
#define _PAGE_H_ 1
#include <QWebEnginePage>
#include <QProcess>

class Page:public QWebEnginePage {
	Q_OBJECT
public:
	Page(QString defaultDir, QObject *parent=0);
	void open(QString file);
protected:
	bool acceptNavigationRequest(QUrl const &url, NavigationType type, bool isMainFrame) override;
protected slots:
	void scriptFinished();
protected:
	QString	_defaultDir;
	QProcess *_script;
	QString _file;
};
#endif
