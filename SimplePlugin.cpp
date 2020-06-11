#include "SimplePlugin.hpp"

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
    return std::make_unique<QLabel>("Text!");
}

std::unique_ptr<QvPluginEditor> NaiveProxyPlugin::GetEditorWidget(UI_TYPE type)
{
    switch (type)
    {
        case UI_TYPE_INBOUND_EDITOR:
        case UI_TYPE_OUTBOUND_EDITOR:
        case UI_TYPE_GROUP_EDITOR: break;
    }
    return nullptr;
}

std::shared_ptr<QvPluginSerializer> NaiveProxyPlugin::GetSerializer()
{
    return serializer;
}
