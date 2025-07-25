cmake_minimum_required(VERSION 3.29)
project(Emulador_NMEA_GPS C)

set(CMAKE_C_STANDARD 17)

include_directories(include)

# Diretórios da biblioteca MQTT
include_directories(include "C:/AmbienteDeDesenvolvimento/C_Projects/libs/paho.mqtt.c/src")
link_directories("C:/AmbienteDeDesenvolvimento/C_Projects/libs/paho.mqtt.c/build/src")

add_executable(Emulador_NMEA_GPS src/main.c
        src/domain/gps.c
        src/utils/util.c
        include/comunicacao_tcp.h
        src/infraestrutura/comunicacao_tcp.c
        include/front.h
        src/front.c
        include/web_server.h
        src/infraestrutura/web_server.c
        include/rede_util.h
        src/utils/rede_util.c
        include/comunicacao_serial.h
        src/infraestrutura/comunicacao_serial.c
        include/comunicacao_mqtt.h
        src/infraestrutura/comunicacao_mqtt.c
        src/modos_comunicacao_service/modo_comunicacao_mqtt.c
        src/modos_comunicacao_service/modo_comunicacao_serial.c
        src/modos_comunicacao_service/modo_comunicacao_tcp.c
        src/modos_comunicacao_service/modo_comunicacao_web.c
        include/modo_comunicacao_mqtt.h
        include/modo_comunicacao_web.h
        include/modo_comunicacao_tcp.h
        include/modo_comunicacao_serial.h
)

#
# Emulador NMEA GPS
# O Emulador NMEA-GPS emula um receptor GPS. Os dados gerados pelo script
# são enviados aos clientes no formato NMEA 0183.
#
# Desenvolvido por Pedro Magno <pedromagnopro@gmail.com>
# Github: www.github.com/pedromagno11
#

message("Emulador NMEA GPS")
set(DESCRIPTION "O Emulador NMEA-GPS emula um receptor GPS. Os dados gerados pelo script são enviados aos clientes no formato NMEA 0183.")
message("Descrição do sistema: ${DESCRIPTION}")
message("")

set(MY_NAME "Pedro Magno")
message("Desenvolvido por: ${MY_NAME}")

set(LINK_REPOSITORIO "https://github.com/PedroMagno11/Emulador_NMEA_GPS")
message("Link do repositório do projeto: ${LINK_REPOSITORIO}")
message("")

message("CMake command         : ${CMAKE_COMMAND}")
message("CMake version         : ${CMAKE_VERSION}")
message("CMake patch version   : ${CMAKE_PATCH_VERSION}")
message("System host name     : ${CMAKE_HOST_SYSTEM_NAME}")
message("Project directory     : ${CMAKE_BINARY_DIR}")
message("")
add_executable(teste_gps test/teste_gps.c src/domain/gps.c
        include/util.h
        src/utils/util.c
)
add_library(gps include/gps.h
        src/domain/gps.c
        include/util.h
        src/utils/util.c
)
add_executable(teste_util test/teste_util.c
        include/util.h
        src/utils/util.c
)

# Linka as bibliotecas: socket + MQTT
target_link_libraries(Emulador_NMEA_GPS ws2_32 paho-mqtt3c)