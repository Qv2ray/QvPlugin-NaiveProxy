#include "Kernel.hpp"

NaiveProxyKernel::NaiveProxyKernel(QObject *parent) : Qv2rayPlugin::QvPluginKernel(parent)
{
}
bool NaiveProxyKernel::StartKernel()
{
    // FIXME: KERNEL EXECUTABLE PATH
    const auto executablePath = "/usr/bin/naiveproxy";
    QStringList arguments;

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
        arguments << QString("--listen=socks://0.0.0.0:%1").arg(socksPort);
    }

    // listen http
    if (this->httpPort)
    {
        arguments << QString("--listen=http://0.0.0.0:%1").arg(httpPort);
    }

    // launch
    // FIXME: Use Another Thread
    this->process->execute(executablePath, arguments);
    return true;
}
void NaiveProxyKernel::SetConnectionSettings(const QMap<KernelSetting, QVariant> &options, const QJsonObject &settings)
{
    this->socksPort = options[KernelSetting::KERNEL_SOCKS_ENABLED].toBool() ? options[KernelSetting::KERNEL_SOCKS_PORT].toInt() : 0;
    this->httpPort = options[KernelSetting::KERNEL_HTTP_ENABLED].toBool() ? options[KernelSetting::KERNEL_HTTP_PORT].toInt() : 0;
    this->host = settings["host"].toString();
    this->port = settings["port"].toInt();
    this->protocol = settings["protocol"].toString();
}
bool NaiveProxyKernel::StopKernel()
{
    this->process->terminate();
    return true;
}
