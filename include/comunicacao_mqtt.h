//
// Created by pedro on 24/07/2025.
//

#ifndef COMUNICACAO_MQTT_H
#define COMUNICACAO_MQTT_H

#include "MQTTClient.h"

int mqtt_connect(char* address, int port, const char* clientId);

int publish(const char* topic, char* payload);

void mqtt_disconnect();
#endif //COMUNICACAO_MQTT_H
