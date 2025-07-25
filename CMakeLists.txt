cmake_minimum_required(VERSION 3.29)
project(Emulador_NMEA_GPS C)

set(CMAKE_C_STANDARD 17)

# === Opções configuráveis ===
get_filename_component(PARENT_DIR "${CMAKE_SOURCE_DIR}/.." ABSOLUTE)
set(MQTT_ROOT_DIR "${PARENT_DIR}/libs/paho.mqtt.c")
message(STATUS "MQTT ${MQTT_ROOT_DIR}")
# Diretórios de include
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${MQTT_ROOT_DIR}/src
)

# Diretório da lib compilada
link_directories(${MQTT_ROOT_DIR}/build/src)

# === Lista de fontes ===
set(SOURCES
        src/main.c
        src/domain/gps.c
        src/utils/util.c
        src/front.c
        src/utils/rede_util.c

        src/infraestrutura/comunicacao_tcp.c
        src/infraestrutura/comunicacao_serial.c
        src/infraestrutura/comunicacao_mqtt.c
        src/infraestrutura/web_server.c

        src/modos_comunicacao_service/modo_comunicacao_mqtt.c
        src/modos_comunicacao_service/modo_comunicacao_serial.c
        src/modos_comunicacao_service/modo_comunicacao_tcp.c
        src/modos_comunicacao_service/modo_comunicacao_web.c
)

# === Executável principal ===
add_executable(Emulador_NMEA_GPS ${SOURCES})

# === Linkagem ===
target_link_libraries(Emulador_NMEA_GPS ws2_32 paho-mqtt3c)

# === Executáveis e biblioteca de teste ===
add_executable(teste_gps test/teste_gps.c src/domain/gps.c src/utils/util.c)
add_executable(teste_util test/teste_util.c src/utils/util.c)
add_library(gps STATIC src/domain/gps.c src/utils/util.c)

# === Metadados do Projeto ===
message(STATUS "Emulador NMEA GPS")
set(DESCRIPTION "O Emulador NMEA-GPS emula um receptor GPS. Os dados gerados pelo script são enviados aos clientes no formato NMEA 0183.")
message(STATUS "Descrição: ${DESCRIPTION}")

set(MY_NAME "Pedro Magno")
message(STATUS "Desenvolvido por: ${MY_NAME}")

set(LINK_REPOSITORIO "https://github.com/PedroMagno11/Emulador_NMEA_GPS")
message(STATUS "Repositório: ${LINK_REPOSITORIO}")

message(STATUS "CMake version         : ${CMAKE_VERSION}")
message(STATUS "CMake patch version   : ${CMAKE_PATCH_VERSION}")
message(STATUS "System host name      : ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Project directory      : ${CMAKE_BINARY_DIR}")
