#pragma once

#include "ui_SettingsWidget.h"

#include <QJsonObject>
class SettingsWidget
    : public QWidget
    , private Ui::SettingsWidget
{
    Q_OBJECT

  public:
    explicit SettingsWidget(QJsonObject *r, QWidget *parent = nullptr);

  protected:
    void changeEvent(QEvent *e);

  private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

  private:
    QJsonObject *root;
};
