#pragma once
#include "QvPluginProcessor.hpp"

class NaiveEventHandler : public Qv2rayPlugin::QvPluginEventHandler
{
  public:
    NaiveEventHandler(QObject *parent = nullptr);
};
