#include "SimplePlugin.hpp"

#include "core/EventHandler.hpp"
#include "core/Kernel.hpp"
#include "core/Serializer.hpp"
#include "ui/UIInterface.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

bool NaiveProxyPlugin::InitializePlugin(const QString &, const QJsonObject &_settings)
{
    this->settings = _settings;
    NaiveProxyPluginInstance = this;
    emit PluginLog("Initializing NaiveProxy plugin.");
    this->outboundHandler = std::make_unique<NaiveProxyOutboundHandler>();
    this->eventHandler = std::make_unique<NaiveEventHandler>();
    this->kernelInterface = std::make_shared<NaiveKernelInterface>();
    this->guiInterface = new NaiveUIInterface();
    return true;
}
