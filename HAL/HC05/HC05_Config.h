/**
 * @file     HC05_Config.h
 * @author   Developer: Naira Mohammed (naira.mohammed.76@gmail.com)
 * @author   Reviewer: Ahmed Ashraf 
 * @brief    Configuration settings for HC05 Bluetooth module.
 * @version   0.2
 * @date      2025-09-03

 * 
 * @copyright Copyright (c) 2025 , Gestell Company 
 */


 
#ifndef _HC05_CONFIG_H_
#define _HC05_CONFIG_H_


/**
 * @def Timeout_Limit
 * @brief Defines the maximum timeout threshold for UART data reception.
 * @details
 * It's used inside the hHC05_ReceiveString() function to prevent the system from hanging
 * if no data is received from HC-05 Bluetooth module within a reasonable time frame. 
 * The value represents a software-based delay counter, not an actual time unit.
 *
 * @note The effective timeout duration depends on the system clock frequency
 *       and the speed of the polling loop.
 */
#define Timeout_Limit  800000

/**
 * @def Buffer_Size
 * @brief Size of the RX ring buffer for HC05 module.
 * @details This defines the maximum number of bytes that can be stored in the RX buffer.
 */
#define Buffer_Size      256
 
#endif /*_HC05_CONFIG_H_*/
