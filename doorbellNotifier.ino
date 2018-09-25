#ifdef ENC28J60
#include <UIPEthernet.h>
#else
#include <Ethernet.h>
#endif
#include "PubSubClient.h"

// https://github.com/depuits/AButt
#include <AButt.h>

#include "config.h"

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);
AButt button(CONFIG_PIN_BUTTON, true);

void holdStart() {
    mqttClient.publish(CONFIG_MQTT_TOPIC_BUTTON, "1", true);
}
void holdEnd() {
    mqttClient.publish(CONFIG_MQTT_TOPIC_BUTTON, "0", true);
}

void setup() 
{
    pinMode(CONFIG_PIN_BUTTON, INPUT_PULLUP);

    button.onHold(holdStart, holdEnd);
    button.setHoldDelay(500); // set the hold delay low so it's called quickly

	// setup serial communication
#ifdef CONFIG_DEBUG
	Serial.begin(9600);
#endif
	// setup ethernet communication using DHCP
	if(Ethernet.begin(mac) == 0) 
	{
#ifdef CONFIG_DEBUG
		Serial.println("Ethernet configuration using DHCP failed");
#endif
		while(true);
	}

	// setup mqtt client
	mqttClient.setServer(CONFIG_MQTT_HOST, CONFIG_MQTT_PORT);
}

void reconnect() 
{
	// Loop until we're reconnected
	while (!mqttClient.connected()) 
	{
#ifdef CONFIG_DEBUG
		Serial.print("Attempting MQTT connection...");
#endif
		// Attempt to connect
		if (mqttClient.connect(CONFIG_MQTT_CLIENT_ID, CONFIG_MQTT_USER, CONFIG_MQTT_PASS)) 
		{
#ifdef CONFIG_DEBUG
			Serial.println("connected");
#endif
		}
		else 
		{
#ifdef CONFIG_DEBUG
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
#endif
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void loop() 
{
	if (!mqttClient.connected()) 
	{
		reconnect();
	}

	mqttClient.loop();

    button.update();
}
