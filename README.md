# 🛰️ Emulador NMEA-GPS

<img src="assets/satellite.gif">

O **Emulador NMEA-GPS** é uma aplicação em C que simula um receptor GPS, gerando sentenças no formato **NMEA 0183** (ex: `$GPGGA`) e enviando-as por diferentes canais de comunicação: **Serial**, **TCP/IP**, **HTTP (Web)** e **MQTT**.

---

## 📌 Funcionalidades

- Geração de sentenças NMEA GPGGA baseadas em posição geográfica real ou aleatória
- Envio das sentenças via:
  - 📟 Porta Serial
  - 🌐 Socket TCP
  - 🌍 Servidor Web embutido
  - ☁️ Broker MQTT
- Interface de menu simples e interativa via terminal
- Modular e extensível para novas formas de comunicação

---

## ⚙️ Requisitos

- [CLion](https://www.jetbrains.com/clion/) ou CMake + GCC/MinGW
- [Eclipse Paho MQTT C](https://github.com/eclipse/paho.mqtt.c) (já incluso no projeto)
- Broker MQTT (como Mosquitto) para testes locais

---

## 🚀 Compilação

### Usando CLion

1. Clone o repositório:
 
```bash
   git clone https://github.com/PedroMagno11/Emulador_NMEA_GPS.git
```

2. Compile com CLion (toolchain MinGW configurada).

### Manual com CMake

```bash
cd Emulador_NMEA_GPS
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

> 💡 Certifique-se de que `libpaho-mqtt3c.dll` esteja presente na pasta de build (`cmake-build-debug`).

---

## 🧪 Execução

Ao rodar o programa, será exibido um menu com as opções:

1. **Porta Serial**
2. **TCP/IP**
3. **Servidor Web**
4. **MQTT**
5. **Sair**

Você poderá definir a posição (aleatória ou manual) e enviar as sentenças para o meio escolhido.

---

## 🌐 Exemplo de uso via MQTT

1. Inicie o Mosquitto:

```bash
mosquitto -v
```

2. Rode o programa, escolha a opção 4, insira o IP do broker e o tópico.

3. Visualize no terminal:

```bash
mosquitto_sub -t "meutopico/#" -v
```

---

## 👨‍💻 Desenvolvedor

| Nome        | Email                                                     | GitHub                                           |
| ----------- | --------------------------------------------------------- | ------------------------------------------------ |
| Pedro Magno | [pedromagnopro@gmail.com](mailto:pedromagnopro@gmail.com) | [@pedromagno11](https://github.com/pedromagno11) |

---

## 🛠️ Contribuindo

Contribuições são bem-vindas! Sinta-se livre para abrir **issues** ou enviar **pull requests**.

1. Fork o projeto
2. Crie uma branch (`git checkout -b minha-feature`)
3. Commit suas alterações (`git commit -am 'Nova feature'`)
4. Push para a branch (`git push origin minha-feature`)
5. Abra um Pull Request

---

## 📜 Licença

Este projeto é distribuído sob a licença MIT. Veja o arquivo `LICENSE` para mais informações.
