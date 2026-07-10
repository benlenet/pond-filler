#include "hardware_interface.h"

adc_oneshot_unit_handle_t adc_handle;

// private functions
void adc_init(adc_oneshot_unit_handle_t adc_handle);
void uart_init(void);
void gpio_init(void);



void hw_init_sensors(void) {
    adc_init(adc_handle);
    uart_init();
    gpio_init();
}

void hw_set_sensor_power(int state) {
    gpio_set_level(GPIO_WATER_EN, state);
}

void hw_set_indicator_led(int state) {
    gpio_set_level(GPIO_LED, state);
}

int hw_read_water_level(void) {
    int adc_value;
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_PIN, &adc_value));
    return adc_value;
}

void hw_set_solenoid_valve(int state) {
    gpio_set_level(GPIO_GATE, state);
}

void adc_init(adc_oneshot_unit_handle_t adc_handle) {
    // Initialize ADC Oneshot Mode Driver on the ADC Unit
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT    
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    // Configure ADC channel
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH,
        .atten = ADC_ATTEN,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_PIN, &config));
}

void uart_init(void) {
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
        
    };
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_set_pin(UART_PORT_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void gpio_init(void) {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << GPIO_WATER_EN) | (1ULL << GPIO_GATE) | (1ULL << GPIO_LED);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    gpio_set_level(GPIO_GATE,    0);
    gpio_set_level(GPIO_WATER_EN,0);
    gpio_set_level(GPIO_LED,     0);
}
