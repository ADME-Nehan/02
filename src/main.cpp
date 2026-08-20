#include <Arduino.h>
#include "WirelessAudioSystem.h"
#include "BoardConfig.h"

WirelessAudioSystem wirelessAudio(CalmNestPicoBoard::BLUETOOTH_NAME);

void setup() {
    Serial.begin(CalmNestPicoBoard::SERIAL_BAUD);
    delay(500);

    Serial.println("\n=== CalmNest PICO-D4 Audio Subsystem Boot ===");

    // Initialize the Wireless Audio subsystem
    wirelessAudio.begin();

    Serial.println("[System] Initialization Complete. Waiting for I2S stream...");
}

void loop() {
    // Keep Bluetooth active and handle reconnects if needed
    wirelessAudio.loop();

    // Optionally add a small delay to yield background tasks
    delay(50);
}
