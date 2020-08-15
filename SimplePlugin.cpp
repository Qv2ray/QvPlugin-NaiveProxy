#include "SimplePlugin.hpp"

#include "core/EventHandler.hpp"
#include "core/Kernel.hpp"
#include "core/Serializer.hpp"
#include "ui/UIInterface.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

bool NaiveProxyPlugin::InitializePlugin(const QString &, const QJsonObject &settings)
{
    emit PluginLog("Initializing NaiveProxy plugin.");
    this->settings = settings;
    this->outboundHandler = std::make_unique<NaiveProxyOutboundHandler>();
    this->eventHandler = std::make_unique<NaiveEventHandler>();
    this->guiInterface = new NaiveUIInterface();
    return true;
}
