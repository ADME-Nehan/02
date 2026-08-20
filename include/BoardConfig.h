#ifndef CALMNEST_PICO_BOARD_CONFIG_H
#define CALMNEST_PICO_BOARD_CONFIG_H

namespace CalmNestPicoBoard {

// Released V1.7 physical links
constexpr int UART_TX_TO_S3 = 19;
constexpr int UART_RX_FROM_S3 = 25;
constexpr unsigned long BOARD_UART_BAUD = 3000000UL;

constexpr int NFC_SDA = 32;
constexpr int NFC_SCL = 33;

// Legacy wireless audio firmware expected a local I2S input on 25, 26, 27.
// GPIO25 is used by the released V1.7 UART link, therefore this legacy I2S
// profile must not be treated as validated for the assembled V1.7 board.
constexpr int LEGACY_I2S_LRCLK = 25;
constexpr int LEGACY_I2S_BCLK = 26;
constexpr int LEGACY_I2S_DATA_IN = 27;
constexpr bool LEGACY_I2S_PROFILE_VALIDATED = false;

constexpr int SAMPLE_RATE = 44100;
constexpr int BITS_PER_SAMPLE = 16;
constexpr int CHANNELS = 2;
constexpr unsigned long SERIAL_BAUD = 115200;
constexpr const char *BLUETOOTH_NAME = "CalmNest Beta";

}  // namespace CalmNestPicoBoard

#endif
