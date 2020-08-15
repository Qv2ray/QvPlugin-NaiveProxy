#include "Serializer.hpp"

#include <QUrlQuery>

const QString NaiveProxyOutboundHandler::SerializeOutbound(const QString &, const QString &alias, const QString &,
                                                           const QJsonObject &object) const
{
    QUrl url;
    if (const auto protocol = object["protocol"].toString(); protocol != "https" && protocol != "quic")
        url.setScheme("naive+https");
    else
        url.setScheme("naive+" + protocol);

    if (const auto username = object["username"].toString(); !username.isEmpty())
        url.setUserName(username);
    if (const auto password = object["password"].toString(); !password.isEmpty())
        url.setPassword(password);

    url.setHost(object["host"].toString());

    if (const auto port = object["port"].toInt(443); port <= 0 || port >= 65536)
        url.setPort(443);
    else
        url.setPort(port);

    QUrlQuery query;
    query.setQueryItems({ { "padding", object["padding"].toBool() ? "true" : "false" } });
    url.setQuery(query);

    url.setFragment(alias);

    return url.toString();
}

const QPair<QString, QJsonObject> NaiveProxyOutboundHandler::DeserializeOutbound(const QString &link, QString *alias,
                                                                                 QString *errorMessage) const
{
    QUrl url(link);
    if (!url.isValid())
    {
        *errorMessage = url.errorString();
        return {};
    }

    const auto description = url.fragment();
    if (!description.isEmpty())
    {
        *alias = description;
    }
    else
    {
        *alias = QString("[%1]-%2:%3").arg(url.scheme()).arg(url.host()).arg(url.port());
    }
    const QStringList trueList = { "1", "true", "yes", "y", "on" };
    const auto usePadding = trueList.contains(QUrlQuery{ url }.queryItemValue("padding").toLower());
    return { "naive", QJsonObject{ { "protocol", url.scheme() },
                                   { "host", url.host() },
                                   { "port", url.port(443) },
                                   { "username", url.userName() },
                                   { "password", url.password() },
                                   { "padding", usePadding } } };
}

const Qv2rayPlugin::OutboundInfoObject NaiveProxyOutboundHandler::GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const
{
    return { //
             { Qv2rayPlugin::INFO_PROTOCOL, protocol },
             { Qv2rayPlugin::INFO_SERVER, outbound["host"].toString() },
             { Qv2rayPlugin::INFO_PORT, outbound["port"].toInt() }
    };
}
