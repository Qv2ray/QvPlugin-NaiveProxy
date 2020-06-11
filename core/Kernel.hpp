#pragma once
#include "QvPluginProcessor.hpp"

class NaiveProxyKernel : public Qv2rayPlugin::QvPluginKernel
{
  public:
    explicit NaiveProxyKernel(QObject *parent = nullptr);
    bool StartKernel() override;
    bool StopKernel() override;
    void SetConnectionSettings(const QMap<KernelSetting, QVariant> &options, const QJsonObject &settings) override;

  private:
    QString protocol;
    QString host;
    QString username;
    QString password;
    QString listenIp;
    int port;
    std::unique_ptr<QProcess> process;

  private:
    bool isStarted = false;
    int socksPort = 0;
    int httpPort = 0;
};
