#include "Kernel.hpp"

NaiveProxyKernel::NaiveProxyKernel(QObject *parent) : Qv2rayPlugin::QvPluginKernel(parent)
{
    connect(process.get(), &QProcess::readyRead, [this]() { emit this->OnKernelLogAvailable(process->readAll()); });
    connect(process.get(), &QProcess::stateChanged, [this]() {
        if (this->isStarted)
        {
            this->isStarted = false;
            emit OnKernelCrashed(tr("Naiveproxy kernel crashed"));
            StopKernel();
        }
    });
}
bool NaiveProxyKernel::StartKernel()
{
    // FIXME: KERNEL EXECUTABLE PATH
    const auto executablePath = "/usr/bin/naiveproxy";
    QStringList arguments;

    // log
    {
        arguments << "--log";
    }

    // proxy
    {
        QUrl url;
        url.setScheme(protocol.replace("naive+", ""));
        url.setUserName(username);
        url.setPassword(password);
        url.setHost(host);
        url.setPort(port);
        arguments << QString("--proxy=%1").arg(url.url());
    }

    // listen socks
    if (this->socksPort)
    {
        arguments << QString("--listen=socks://%1:%2").arg(listenIp).arg(socksPort);
    }

    // listen http
    if (this->httpPort)
    {
        arguments << QString("--listen=http://%1:%2").arg(listenIp).arg(httpPort);
    }

    // launch
    // FIXME: Use Another Thread
    this->process->execute(executablePath, arguments);
    isStarted = true;
    return true;
}
void NaiveProxyKernel::SetConnectionSettings(const QMap<KernelSetting, QVariant> &options, const QJsonObject &settings)
{
    this->listenIp = options[KernelSetting::KERNEL_LISTEN_ADDRESS].toString();
    this->socksPort = options[KernelSetting::KERNEL_SOCKS_ENABLED].toBool() ? options[KernelSetting::KERNEL_SOCKS_PORT].toInt() : 0;
    this->httpPort = options[KernelSetting::KERNEL_HTTP_ENABLED].toBool() ? options[KernelSetting::KERNEL_HTTP_PORT].toInt() : 0;
    this->host = settings["host"].toString();
    this->port = settings["port"].toInt();
    this->protocol = settings["protocol"].toString();
}
bool NaiveProxyKernel::StopKernel()
{
    this->process->terminate();
    this->process->waitForFinished();
    return true;
}
