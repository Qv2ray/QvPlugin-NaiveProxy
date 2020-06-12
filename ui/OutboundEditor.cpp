#include "OutboundEditor.hpp"

OutboundEditor::OutboundEditor(QWidget *parent) : Qv2rayPlugin::QvPluginEditor(parent)
{
    setupUi(this);
}

void OutboundEditor::SetContent(const QJsonObject &r)
{
    root = r;
    userTxt->setText(root["username"].toString());
    passTxt->setText(root["password"].toString());
    comboBox->setCurrentText(root["protocol"].toString());
}

void OutboundEditor::changeEvent(QEvent *e)
{

    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void OutboundEditor::on_comboBox_currentTextChanged(const QString &arg1)
{
    root["protocol"] = arg1;
}

void OutboundEditor::on_userTxt_textEdited(const QString &arg1)
{
    root["username"] = arg1;
}

void OutboundEditor::on_passTxt_textEdited(const QString &arg1)
{
    root["password"] = arg1;
}
