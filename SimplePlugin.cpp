#include "SimplePlugin.hpp"

#include "ui/OutboundEditor.hpp"
#include "ui/SettingsWidget.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

std::unique_ptr<QvPluginKernel> NaiveProxyPlugin::CreateKernel()
{
    return std::make_unique<NaiveProxyKernel>();
}

bool NaiveProxyPlugin::UpdateSettings(const QJsonObject &conf)
{
    settings = conf;
    return true;
}

bool NaiveProxyPlugin::Initialize(const QString &, const QJsonObject &settings)
{
    pluginInstance = this;
    emit PluginLog("Initialize plugin.");
    this->settings = settings;
    this->serializer = std::make_unique<NaiveProxySerializer>();
    this->eventHandler = std::make_unique<NaiveEventHandler>();
    return true;
}

const QJsonObject NaiveProxyPlugin::GetSettngs()
{
    return settings;
}

std::shared_ptr<QvPluginEventHandler> NaiveProxyPlugin::GetEventHandler()
{
    return eventHandler;
}

std::unique_ptr<QWidget> NaiveProxyPlugin::GetSettingsWidget()
{
    return std::make_unique<SettingsWidget>(&settings);
}

std::unique_ptr<QvPluginEditor> NaiveProxyPlugin::GetEditorWidget(UI_TYPE type)
{
    switch (type)
    {
        case UI_TYPE_INBOUND_EDITOR:
        case UI_TYPE_GROUP_EDITOR: break;
        case UI_TYPE_OUTBOUND_EDITOR: return std::make_unique<OutboundEditor>();
    }
    return nullptr;
}

std::shared_ptr<QvPluginSerializer> NaiveProxyPlugin::GetSerializer()
{
    return serializer;
}
