/*
 * SPDX-FileCopyrightText: 2016-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_err.h"                // for esp_err_t
#include "esp_modbus_slave.h"       // for public slave defines
#include "mbc_tcp_slave.h"          // for public interface defines

/**
 * Initialization of Modbus TCP Slave controller
 */
esp_err_t mbc_slave_init_tcp(mb_slave_interface_t** handler, bool start_controller_task)
{
    void* port_handler = NULL;
    esp_err_t error = mbc_tcp_slave_create(&port_handler, start_controller_task);

    if ((port_handler != NULL) && (error == ESP_OK)) {
        mbc_slave_init_iface((mb_slave_interface_t*)port_handler);
        *handler = port_handler;
    }
    return  error;
}
