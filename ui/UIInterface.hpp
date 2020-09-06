#pragma once

#include "interface/QvGUIPluginInterface.hpp"
#include "ui/OutboundEditor.hpp"
#include "ui/SettingsWidget.hpp"

using namespace Qv2rayPlugin;

class NaiveUIInterface : public Qv2rayPlugin::PluginGUIInterface
{
    QIcon Icon() const override
    {
        return QIcon(":/assets/naive.png");
    }
    virtual std::unique_ptr<QvPluginSettingsWidget> createSettingsWidgets() const override
    {
        return std::make_unique<SettingsWidget>();
    }
    virtual QList<typed_plugin_editor> createInboundEditors() const override
    {
        return {};
    }
    virtual QList<typed_plugin_editor> createOutboundEditors() const override
    {
        return { MakeEditorInfoPair<OutboundEditor>("naive", "NaiveProxy") };
    }
    virtual std::unique_ptr<QvPluginMainWindowWidget> createMainWindowWidget() const override
    {
        return nullptr;
    }
    virtual QList<PluginGuiComponentType> GetComponents() const override
    {
        return { GUI_COMPONENT_SETTINGS, GUI_COMPONENT_OUTBOUND_EDITOR };
    }
};
