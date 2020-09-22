#pragma once

#include "QvPluginInterface.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class NaiveProxyPlugin
    : public QObject
    , public Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{ "NaiveProxy Plugin",     //
                                 "Qv2ray Workgroup",      //
                                 "qvplugin_naiveproxy",   //
                                 "NaiveProxy Plugin.",    //
                                 "v3.0.0",                //
                                 "Qv2ray/QvPlugin-Naive", //
                                 {
                                     COMPONENT_GUI,             //
                                     COMPONENT_KERNEL,          //
                                     COMPONENT_OUTBOUND_HANDLER //
                                 },
                                 UPDATE_GITHUB_RELEASE };
    }
    bool InitializePlugin(const QString &, const QJsonObject &) override;

  signals:
    void PluginLog(const QString &) const override;
    void PluginErrorMessageBox(const QString &, const QString &) const override;
};

DECLARE_PLUGIN_INSTANCE(NaiveProxyPlugin);
