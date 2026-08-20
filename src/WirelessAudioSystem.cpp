#include "WirelessAudioSystem.h"
#include "BoardConfig.h"

WirelessAudioSystem::WirelessAudioSystem(const String &name)
    : deviceName(name), btConnected(false) {}

void WirelessAudioSystem::begin() {
    Serial.println("[WirelessAudioSystem] Initializing Bluetooth A2DP Source...");
    if (!CalmNestPicoBoard::LEGACY_I2S_PROFILE_VALIDATED) {
        Serial.println("[WirelessAudioSystem] WARNING: legacy I2S input conflicts with the V1.7 UART pin map. Hardware audio validation is required.");
    }

    // 1. Configure I2S RX (audio input from ESP32-S3 main MCU)
    configureI2S();

    // 2. Basic Bluetooth A2DP configuration
    a2dpSource.set_local_name(deviceName.c_str());  // Custom broadcast name
    a2dpSource.set_auto_reconnect(true);            // Reconnect automatically

    // 3. Set I2S stream as data source for A2DP
    a2dpSource.set_data_source(i2sStream);

    // 4. Optional event logging
    a2dpSource.set_discovery_mode_callback([](esp_bt_gap_discovery_state_t state) {
        if (state == ESP_BT_GAP_DISCOVERY_STARTED)
            Serial.println("[WirelessAudioSystem] Bluetooth discovery started...");
        else if (state == ESP_BT_GAP_DISCOVERY_STOPPED)
            Serial.println("[WirelessAudioSystem] Bluetooth discovery stopped.");
    });

    a2dpSource.set_avrc_passthru_command_callback([](uint8_t key, bool released) {
        Serial.printf("[WirelessAudioSystem] AVRCP key: %u (%s)\n",
                      key, released ? "released" : "pressed");
    });

    // 5. Start Bluetooth A2DP streaming
    a2dpSource.start(deviceName.c_str());
    btConnected = a2dpSource.is_connected();

    Serial.println("[WirelessAudioSystem] A2DP Source started (open pairing, SBC 44.1 kHz stereo).");
}

void WirelessAudioSystem::configureI2S() {
    auto config = i2sStream.defaultConfig(RX_MODE);
    config.sample_rate = CalmNestPicoBoard::SAMPLE_RATE;
    config.bits_per_sample = CalmNestPicoBoard::BITS_PER_SAMPLE;
    config.channels = CalmNestPicoBoard::CHANNELS;
    config.pin_ws = CalmNestPicoBoard::LEGACY_I2S_LRCLK;
    config.pin_bck = CalmNestPicoBoard::LEGACY_I2S_BCLK;
    config.pin_data = CalmNestPicoBoard::LEGACY_I2S_DATA_IN;
    config.i2s_format = I2S_STD_FORMAT;

    i2sStream.begin(config);
    Serial.println("[WirelessAudioSystem] I2S RX configured (44.1 kHz stereo).");
}

void WirelessAudioSystem::loop() {
    const bool connectedNow = a2dpSource.is_connected();
    if (connectedNow != btConnected) {
        Serial.println(connectedNow
                           ? "[WirelessAudioSystem] Bluetooth connected."
                           : "[WirelessAudioSystem] Bluetooth disconnected. Auto reconnect remains active.");
        btConnected = connectedNow;
    }
}

bool WirelessAudioSystem::isConnected() const {
    return btConnected;
}
