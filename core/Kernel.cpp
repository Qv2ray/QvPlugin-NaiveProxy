#include "Kernel.hpp"

#include "SimplePlugin.hpp"
#include "interface/QvPluginInterface.hpp"

#include <QFile>

NaiveProxyKernel::NaiveProxyKernel() : Qv2rayPlugin::PluginKernel()
{
    process.setProcessChannelMode(QProcess::MergedChannels);
    connect(&process, &QProcess::readyRead, [this]() { emit this->OnKernelLogAvailable(process.readAll()); });
    connect(&process, &QProcess::stateChanged, [this]() {
        if (this->isStarted && process.state() == QProcess::ProcessState::NotRunning)
        {
            this->isStarted = false;
            StopKernel();
            emit OnKernelCrashed(tr("NaiveProxy kernel crashed with code %1").arg(process.exitCode()));
        }
    });
}

bool NaiveProxyKernel::StartKernel()
{
    const auto executablePath = pluginInstance->GetSettngs()["kernelPath"].toString();
    if (!QFile::exists(executablePath))
    {
        pluginInstance->PluginErrorMessageBox(tr("Naive!"),
                                              tr("We cannot find your NaiveProxy kernel. Please configure it in the plugin settings."));
        return false;
    }

    QStringList arguments{ "--log" };

    // proxy
    {
        QUrl url;
        url.setScheme(protocol.replace("naive+", ""));
        if (!username.isEmpty() || !password.isEmpty())
        {
            url.setUserName(username);
            url.setPassword(password);
        }
        url.setHost(host);
        url.setPort(port);
        arguments << QString("--proxy=%1").arg(url.url());
    }

    if (this->padding)
    {
        arguments << "--padding";
    }

    // listen socks
    if (this->socksPort)
    {
        arguments << QString("--listen=socks://%1:%2").arg(listenIp).arg(socksPort);
    }

    // listen http
    if (this->httpPort)
    {
        httpProxy.httpListen(QHostAddress(listenIp), httpPort, socksPort);
    }

    // launch
    this->process.start(executablePath, arguments);
    isStarted = true;
    return true;
}

void NaiveProxyKernel::SetConnectionSettings(const QMap<Qv2rayPlugin::KernelOptionFlags, QVariant> &options, const QJsonObject &settings)
{
    this->listenIp = options[KERNEL_LISTEN_ADDRESS].toString();
    this->socksPort = options[KERNEL_SOCKS_ENABLED].toBool() ? options[KERNEL_SOCKS_PORT].toInt() : 0;
    this->httpPort = options[KERNEL_HTTP_ENABLED].toBool() ? options[KERNEL_HTTP_PORT].toInt() : 0;
    this->host = settings["host"].toString();
    this->port = settings["port"].toInt(443);
    this->username = settings["username"].toString();
    this->password = settings["password"].toString();
    this->protocol = settings["protocol"].toString();
    this->padding = settings["padding"].toBool();

    if (this->protocol != "https" && this->protocol != "quic")
    {
        emit OnKernelLogAvailable(QString("warning: outbound protocol %1 is falled back to https"));
        this->protocol = "https";
    }

    if (this->port <= 0 || this->port >= 65536)
    {
        emit OnKernelLogAvailable(QString("warning: outbound port %1 is falled back to 443"));
        this->port = 443;
    }
}

bool NaiveProxyKernel::StopKernel()
{
    if (this->httpPort)
    {
        httpProxy.close();
    }
    isStarted = false;
    this->process.close();
    this->process.waitForFinished();
    return true;
}
