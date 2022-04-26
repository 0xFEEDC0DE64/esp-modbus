/*
 * SPDX-FileCopyrightText: 2016-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_err.h"                // for esp_err_t
#include "esp_modbus_master.h"      // for public interface defines
#include "mbc_tcp_master.h"         // for public interface defines

/**
 * Initialization of Modbus TCP Master controller interface
 */
esp_err_t mbc_master_init_tcp(void** handler, bool start_controller_task)
{
    void* port_handler = NULL;
    esp_err_t error = mbc_tcp_master_create(&port_handler, start_controller_task);

    if ((port_handler != NULL) && (error == ESP_OK)) {
        mbc_master_init_iface(port_handler);
        *handler = port_handler;
    }
    return  error;
}
