/*
 * SPDX-FileCopyrightText: 2016-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ESP_MB_SLAVE_INTERFACE_H
#define _ESP_MB_SLAVE_INTERFACE_H

// Public interface header for slave
#include <stdint.h>                 // for standard int types definition
#include <stddef.h>                 // for NULL and std defines
#include "freertos/FreeRTOS.h"      // for task creation and queues access
#include "freertos/event_groups.h"  // for event groups
#include "esp_modbus_common.h"      // for common types
#include "mb.h"
#include "mbc_slave.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MB_SLAVE_CHECK(a, err_code, format, ...) MB_RETURN_ON_FALSE(a, err_code, TAG, format __VA_OPT__(,) __VA_ARGS__)

#define MB_SLAVE_ASSERT(con) do { \
        if (!(con)) { ESP_LOGE(TAG, "assert errno:%d, errno_str: !(%s)", errno, strerror(errno)); assert(0 && #con); } \
    } while (0)

/**
 * @brief Initialize Modbus Slave controller and stack for TCP port
 *
 * @param[out] handler handler(pointer) to master data structure
 * @return
 *     - ESP_OK                 Success
 *     - ESP_ERR_NO_MEM         Parameter error
 *     - ESP_ERR_NOT_SUPPORTED  Port type not supported
 *     - ESP_ERR_INVALID_STATE  Initialization failure
 */
esp_err_t mbc_slave_init_tcp(mb_slave_interface_t** handler, bool start_controller_task);

/**
 * @brief Initialize Modbus Slave controller and stack for Serial port
 *
 * @param[out] handler handler(pointer) to master data structure
 * @param[in] port_type the type of port
 * @return
 *     - ESP_OK                 Success
 *     - ESP_ERR_NO_MEM         Parameter error
 *     - ESP_ERR_NOT_SUPPORTED  Port type not supported
 *     - ESP_ERR_INVALID_STATE  Initialization failure
 */
esp_err_t mbc_slave_init(mb_port_type_t port_type, mb_slave_interface_t **handler, bool start_controller_task);

/**
 * @brief Initialize Modbus Slave controller interface handle
 *
 * @param[in] handler - pointer to slave interface data structure
 */
void mbc_slave_init_iface(mb_slave_interface_t* handler);

/**
 * @brief Destroy Modbus controller and stack
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_ERR_INVALID_STATE Parameter error
 */
esp_err_t mbc_slave_destroy(void);

/**
 * @brief Start Modbus communication stack
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_ERR_INVALID_ARG Modbus stack start error
 */
esp_err_t mbc_slave_start(void);

/**
 * @brief Set Modbus communication parameters for the controller
 *
 * @param comm_info Communication parameters structure.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Incorrect parameter data
 */
esp_err_t mbc_slave_setup(void* comm_info);

/**
 * @brief Wait for specific event on parameter change.
 *
 * @param group Group event bit mask to wait for change
 *
 * @return
 *     - mb_event_group_t event bits triggered
 */
mb_event_group_t mbc_slave_check_event(mb_event_group_t group);

/**
 * @brief Get parameter information
 *
 * @param[out] reg_info parameter info structure
 * @param timeout Timeout in milliseconds to read information from
 *                parameter queue
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_TIMEOUT Can not get data from parameter queue
 *                       or queue overflow
 */
esp_err_t mbc_slave_get_param_info(mb_param_info_t* reg_info, uint32_t timeout);

/**
 * @brief Set Modbus area descriptor
 *
 * @param descr_data Modbus registers area descriptor structure
 *
 * @return
 *     - ESP_OK: The appropriate descriptor is set
 *     - ESP_ERR_INVALID_ARG: The argument is incorrect
 */
esp_err_t mbc_slave_set_descriptor(mb_register_area_descriptor_t descr_data);

// Callback function for reading of MB Discrete Input Registers
eMBErrorCode mbc_reg_discrete_slave_cb(UCHAR* reg_buffer, USHORT address, USHORT n_discrete);
// Callback function for reading of MB Coils Registers
eMBErrorCode mbc_reg_coils_slave_cb(UCHAR* reg_buffer, USHORT address, USHORT n_coils, eMBRegisterMode mode);
// Callback function for reading of MB Holding Registers
// Executed by stack when request to read/write holding registers is received
eMBErrorCode mbc_reg_holding_slave_cb(UCHAR * reg_buffer, USHORT address, USHORT n_regs, eMBRegisterMode mode);
// Callback function for reading of MB Input Registers
eMBErrorCode mbc_reg_input_slave_cb(UCHAR * reg_buffer, USHORT address, USHORT n_regs);
#ifdef __cplusplus
}
#endif

#endif
