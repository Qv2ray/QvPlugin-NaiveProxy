#include "SettingsWidget.hpp"

#include <QFileDialog>

#ifndef DEFAULT_KERNEL_PATH
    #ifdef Q_OS_LINUX
        #define DEFAULT_KERNEL_PATH "/bin/naiveproxy"
    #elif defined(Q_OS_MAC) || defined(Q_OS_WIN)
        #define DEFAULT_KERNEL_PATH (QApplication::applicationDirPath() + "naiveproxy.exe")
    #endif
#endif
SettingsWidget::SettingsWidget(QJsonObject *r, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    root = r;
    if (!root->contains("kernelPath"))
    {
        root->insert("kernelPath", DEFAULT_KERNEL_PATH);
    }
    lineEdit->setText(root->value("kernelPath").toString());
}

void SettingsWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void SettingsWidget::on_pushButton_clicked()
{
    const auto core = QFileDialog::getOpenFileName(this, tr("Open NaiveProxy Kernel"), QDir::currentPath());

    if (!core.isEmpty())
    {
        lineEdit->setText(core);
        on_lineEdit_textEdited(core);
    }
}

void SettingsWidget::on_lineEdit_textEdited(const QString &arg1)
{
    root->insert("kernelPath", arg1);
}
