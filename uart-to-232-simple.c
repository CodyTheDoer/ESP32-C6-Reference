#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_err.h"
#include <string.h>

// Configuration parameters for the UART
#define UART_PORT_NUM      UART_NUM_1
#define BAUD_RATE          115200
#define TX_PIN             16
#define RX_PIN             17

// Buffer for incoming data and text
#define BUF_SIZE           1024

void app_main(void) {
    // Configure parameters for the UART driver
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_RTC,
    };

    // Install UART driver using the configuration above
    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_set_line_inverse(UART_PORT_NUM, UART_SIGNAL_TXD_INV | UART_SIGNAL_RXD_INV));
    
    // Send data periodically
    const char* test_str = "Hello UART\n";
    while (1) {
        // Write data to UART
        uart_write_bytes(UART_PORT_NUM, test_str, strlen(test_str));

        // Delay for one second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
