
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <MediaWiki/Edit>
#include <MediaWiki/MediaWiki>
#include <MediaWiki/Login>
#include <MediaWiki/QueryInfo>
#include <MediaWiki/QueryRevision>

namespace Ui
{
    class MainWindow;
}

using namespace mediawiki;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget* const parent = 0);
    ~MainWindow();


private slots:

    void on_plainTextEdit_textChanged();
    void on_mPageEdit_textChanged(const QString &arg1);
    void on_mWikiEdit_textChanged(const QString &arg1);
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();

//    void loginHandle(KJob* mlogin);
//    void revisionHandle(const QList<Revision>& revisions);
//    void editError(KJob* job);
//    void revisionError(KJob* job);

private:

    Ui::MainWindow* ui;
    MediaWiki*      mediawiki;


};

#endif // MAINWINDOW_H
