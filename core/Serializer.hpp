#pragma once
#include "QvPluginProcessor.hpp"

#include <QObject>

class NaiveProxySerializer : public Qv2rayPlugin::QvPluginSerializer
{
    Q_OBJECT
  public:
    explicit NaiveProxySerializer(QObject *parent = nullptr) : QvPluginSerializer(parent){};
    const QString SerializeOutbound(const QString &protocol,  //
                                    const QString &alias,     //
                                    const QString &groupName, //
                                    const QJsonObject &object) const override;
    const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, //
                                                          QString *alias,      //
                                                          QString *errorMessage) const override;
    const Qv2rayPlugin::QvPluginOutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override;
    const QList<QString> ShareLinkPrefixes() const override
    {
        return { "naive+https://", "naive+quic://" };
    }
    const QList<QString> OutboundProtocols() const override
    {
        return { "naive+https", "naive+quic" };
    }
};
