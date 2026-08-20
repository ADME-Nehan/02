#ifndef WIRELESS_AUDIO_SYSTEM_H
#define WIRELESS_AUDIO_SYSTEM_H

#include <Arduino.h>
#include <AudioTools.h>
#include <BluetoothA2DPSource.h>

using namespace audio_tools;

class WirelessAudioSystem {
public:
    explicit WirelessAudioSystem(const String &name);
    void begin();
    void loop();
    bool isConnected() const;

private:
    String deviceName;
    bool btConnected;

    BluetoothA2DPSource a2dpSource;
    I2SStream i2sStream;

    void configureI2S();
};

#endif
