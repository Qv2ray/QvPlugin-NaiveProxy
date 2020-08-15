#pragma once

#include "interface/QvGUIPluginInterface.hpp"
#include "interface/QvPluginProcessor.hpp"
#include "ui_OutboundEditor.h"

class OutboundEditor
    : public Qv2rayPlugin::QvPluginEditor
    , private Ui::OutboundEditor
{
    Q_OBJECT

  public:
    explicit OutboundEditor(QWidget *parent = nullptr);
    void SetHostInfo(const QString &address, int port)
    {
        root["host"] = address;
        root["port"] = port;
    }
    QPair<QString, int> GetHostInfo() const
    {
        return { root["host"].toString(), root["port"].toInt() };
    }
    //
    void SetContent(const QJsonObject &);
    const QJsonObject GetContent() const
    {
        return root;
    }

  protected:
    void changeEvent(QEvent *e);

  private slots:
    void on_comboProtocol_currentTextChanged(const QString &arg1);
    void on_textUsername_textEdited(const QString &arg1);
    void on_textPassword_textEdited(const QString &arg1);
    void on_checkPadding_stateChanged(int arg1);

  private:
    QJsonObject root;
};
