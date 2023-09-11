#include <QApplication>
#include <QWebEngineView>
#include <QCommandLineParser>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIcon>
#include "Page.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	app.setApplicationVersion("1.0.1");

	QCommandLineParser cl;
	cl.setApplicationDescription(QCoreApplication::translate("main", "HTML Script Runner"));
	cl.addHelpOption();
	cl.addVersionOption();
	cl.addPositionalArgument("startpage", QCoreApplication::translate("main", "Start page"));
	QCommandLineOption size("s", QCoreApplication::translate("size", "Initial size"), "size", "870x520");
	QCommandLineOption icon("i", QCoreApplication::translate("icon", "Application icon"), "icon", "/usr/share/icons/openmandriva.svg");
	QCommandLineOption c("c", QCoreApplication::translate("main", "Ignored, for compatibility with old version"));
	QCommandLineOption title("t", QCoreApplication::translate("main", "Application title"), "title", "HTML Script Runner");
	cl.addOptions(QList<QCommandLineOption>() << size << icon << c << title);
	cl.process(app);

	QString t=cl.value(title);
	if(!t.isEmpty())
		// We allow overriding the application name because that's the
		// window title -- and we want OM Welcome to have a different
		// title than Control Center and whatever else may use
		// htmlscript in the future
		app.setApplicationName(t);

	unsigned int w, h;
	QString s=cl.value(size);
	if(s.contains('x')) {
		w=s.section('x', 0, 0).toUInt();
		h=s.section('x', 1, 1).toUInt();
	}

	QString arg = cl.positionalArguments().empty() ? QDir::currentPath() : cl.positionalArguments().at(0), dir, startpage;

	QFileInfo fi(arg);
	if(fi.isDir()) {
		dir = arg;
		if(QFile::exists(dir + "/index.sh.html"))
			startpage = dir + "/index.sh.html";
		else
			startpage = dir + "/index.sh.htm";
	} else {
		dir = fi.absolutePath();
		startpage = fi.fileName();
	}

	QWebEngineView *l=new QWebEngineView(static_cast<QWidget*>(nullptr));
	l->setWindowIcon(QIcon(cl.value(icon)));
	Page *p=new Page(dir, l);
	l->setPage(p);
	p->open(startpage);
	l->resize(w, h);
	l->show();
	app.exec();
	delete l;
}
