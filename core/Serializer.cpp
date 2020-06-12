#include "Serializer.hpp"

const QString NaiveProxySerializer::SerializeOutbound(const QString &protocol, const QString &alias, const QString &,
                                                      const QJsonObject &object) const
{
    QUrlQuery q;
    q.setQueryItems({ { "padding", object["padding"].toBool() ? "true" : "false" } });
    QUrl url;
    url.setScheme(protocol + "+" + object["protocol"].toString());
    url.setUserName(object["username"].toString());
    url.setPassword(object["password"].toString());
    url.setHost(object["host"].toString());
    url.setPort(object["port"].toInt());
    url.setQuery(q);
    url.setFragment(alias);
    return url.toString();
}

const QPair<QString, QJsonObject> NaiveProxySerializer::DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const
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
    return { "naive", //
             QJsonObject{
                 { "protocol", url.scheme() },
                 { "host", url.host() },
                 { "port", url.port() },
                 { "username", url.userName() },
                 { "password", url.password() },
                 { "password", trueList.contains(QUrlQuery{ url }.queryItemValue("padding").toLower()) } //
             } };
}

const Qv2rayPlugin::QvPluginOutboundInfoObject NaiveProxySerializer::GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const
{
    return { outbound["host"].toString(), protocol, outbound["port"].toInt() };
}
