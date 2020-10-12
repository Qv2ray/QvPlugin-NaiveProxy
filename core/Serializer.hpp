#pragma once
#include "QvPluginProcessor.hpp"

#include <QObject>

class NaiveProxyOutboundHandler : public Qv2rayPlugin::PluginOutboundHandler
{
  public:
    explicit NaiveProxyOutboundHandler() : Qv2rayPlugin::PluginOutboundHandler(){};
    const QString SerializeOutbound(const QString &protocol,   //
                                    const QString &alias,      //
                                    const QString &groupName,  //
                                    const QJsonObject &object, //
                                    const QJsonObject &) const override;
    const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, //
                                                          QString *alias,      //
                                                          QString *errorMessage) const override;
    const Qv2rayPlugin::OutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override;
    const void SetOutboundInfo(const QString &protocol, const Qv2rayPlugin::OutboundInfoObject &info, QJsonObject &outbound) const override;
    const QList<QString> SupportedProtocols() const override
    {
        return { "naive" };
    }
    const QList<QString> SupportedLinkPrefixes() const override
    {
        return { "naive+https://", "naive+quic://" };
    }
};
