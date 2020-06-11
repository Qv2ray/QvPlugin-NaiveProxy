#pragma once
#include "QvPluginProcessor.hpp"

class SimpleEventHandler : public Qv2rayPlugin::QvPluginEventHandler
{
  public:
    SimpleEventHandler(QObject *parent = nullptr);
};
