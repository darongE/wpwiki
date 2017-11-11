#ifndef WIKIFORM_H
#define WIKIFORM_H

#include <QMainWindow>
#include <QMessageBox>

#include <MediaWiki/Edit>
#include <MediaWiki/MediaWiki>


namespace Ui {
class WikiForm;
}

using namespace mediawiki;

class WikiForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit WikiForm(QWidget *parent = 0);
    ~WikiForm();



private Q_SLOTS:


    // show on basic data
    // claims, imageinfo, parse, query, wikidata

    void on_TextEdit_BasicInfo_textChanged();

    // show raw data
    void on_TextEdit_General_textChanged();

    // url
    void on_Edit_Url_textChanged(const QString &arg1);
    void on_Edit_Page_textChanged(const QString &arg1);
    void on_btn_load_clicked();

private:
    Ui::WikiForm *ui;
    MediaWiki*   mediawiki;


};

#endif // WIKIFORM_H







