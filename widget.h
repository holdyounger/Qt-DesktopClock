#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QLCDNumber>
#include <QLineEdit>
#include <QColor>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void InitUI();

private:


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
