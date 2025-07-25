//
// Created by pedro on 24/07/2025.
//

#include "comunicacao_mqtt.h"
#include "string.h"
#include "stdio.h"
#include "util.h"

static MQTTClient client;

void format(char* address, int port) {
    strcat(address, ":");
    strcat(address, from_int_to_string(port));
}

int mqtt_connect(char* address, int port, const char* clientId) {

    format(address, port);
    MQTTClient_connectOptions connect_options = MQTTClient_connectOptions_initializer;
    int rc;

    MQTTClient_create(&client, address, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    connect_options.keepAliveInterval = 20;
    connect_options.cleansession = 1;

    rc = MQTTClient_connect(client, &connect_options);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("Falha na conexão: %d\n", rc);
        return rc;
    }
    printf("Conexão estabelecida!\n");
    return MQTTCLIENT_SUCCESS;
}

int publish(const char* topic, char* payload) {
    remover_clrf(topic);
    printf("Publicando em '%s': %s\n", topic, payload);
    int rc = MQTTClient_publish(client, topic, strlen(payload), payload, 1, 0, NULL);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("Erro ao publicar: %d\n", rc);
    }
    return rc;
}

void mqtt_disconnect() {
    MQTTClient_disconnect(client, 10000L); // TIMEOUT 10000 ms
    MQTTClient_destroy(&client);
}