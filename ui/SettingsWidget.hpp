#pragma once
#include <QJsonObject>
#include <QtGlobal>

#ifndef DEFAULT_KERNEL_PATH
    #ifdef Q_OS_WIN
        #define DEFAULT_KERNEL_PATH (QApplication::applicationDirPath() + "naiveproxy.exe")
    #elif defined(Q_OS_MAC)
        #define DEFAULT_KERNEL_PATH (QApplication::applicationDirPath() + "naiveproxy")
    #else
        #define DEFAULT_KERNEL_PATH "/bin/naiveproxy"
    #endif
#endif

#include "interface/QvGUIPluginInterface.hpp"
#include "ui_SettingsWidget.h"

class SettingsWidget
    : public Qv2rayPlugin::QvPluginSettingsWidget
    , private Ui::SettingsWidget
{
    Q_OBJECT

  public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    void SetSettings(const QJsonObject &settings) override
    {
        root = settings;
        if (!root.contains("kernelPath"))
        {
            root.insert("kernelPath", DEFAULT_KERNEL_PATH);
        }
        textKernelPath->setText(root.value("kernelPath").toString());
    }
    QJsonObject GetSettings() override
    {
        return root;
    }

  protected:
    void changeEvent(QEvent *e);

  private slots:
    void on_textKernelPath_textEdited(const QString &arg1);
    void on_buttonBrowseKernel_clicked();
    void on_buttonTestKernel_clicked();

  private:
    QJsonObject root;
};
