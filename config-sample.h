/*
 * This is a sample configuration file for the "mqtt_esp8266" light.
 *
 * Change the settings below and save the file as "config.h"
 * You can then upload the code using the Arduino IDE.
 */

// Network mac address
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

// Button pin number, change to actual pin number
#define CONFIG_PIN_BUTTON 2

// MQTT
#define CONFIG_MQTT_HOST "{MQTT-SERVER}"
#define CONFIG_MQTT_PORT 1883 // Usually 1883
#define CONFIG_MQTT_USER "{MQTT-USERNAME}"
#define CONFIG_MQTT_PASS "{MQTT-PASSWORD}"
#define CONFIG_MQTT_CLIENT_ID "DOORBELL" // Must be unique on the MQTT network

#define CONFIG_MQTT_TOPIC_BUTTON "home/doorbell"

// Enables Serial and print statements, comment out to disable
//#define CONFIG_DEBUG

// Uncomment the line with the correct module name
//#define W5100
#define ENC28J60
