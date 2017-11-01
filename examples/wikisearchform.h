#ifndef WIKISEARCHFORM_H
#define WIKISEARCHFORM_H

#include <QWidget>

namespace Ui {
class WikiSearchForm;
}

class WikiSearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit WikiSearchForm(QWidget *parent = 0);
    ~WikiSearchForm();

private:
    Ui::WikiSearchForm *ui;
};

#endif // WIKISEARCHFORM_H
