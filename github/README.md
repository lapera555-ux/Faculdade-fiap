# 🌱 FarmTech Solutions - Fase 2

## Descrição
Este projeto simula um sistema de irrigação inteligente no Wokwi usando ESP32.

### Sensores e atuadores simulados
- **DHT22** → umidade do solo simulada
- **LDR** → pH do solo simulado
- **3 botões** → nutrientes N, P e K
- **Relé azul** → bomba d'água

## Cultura adotada
Tomate

## Lógica de irrigação
A bomba liga somente quando:
- a umidade está **abaixo de 60%**
- o pH simulado está entre **5.5 e 7.0**
- pelo menos **2 dos 3 nutrientes** estão ativos
- **não** há previsão de chuva

## Teste extra pelo Serial Monitor
- Digite **S** para simular **sem chuva**
- Digite **C** para simular **com chuva**

## Estrutura do repositório
- `src/farmtech_esp32.ino` → código do ESP32
- `wokwi/diagram.json` → circuito do Wokwi
- `wokwi/libraries.txt` → bibliotecas do projeto
- `images/` → coloque aqui os prints do circuito e da execução

## Como rodar no Wokwi
1. Crie um novo projeto ESP32.
2. Substitua o conteúdo do `sketch.ino` pelo conteúdo de `src/farmtech_esp32.ino`.
3. Substitua o conteúdo do `diagram.json` pelo conteúdo de `wokwi/diagram.json`.
4. Crie ou substitua o `libraries.txt` com o conteúdo de `wokwi/libraries.txt`.
5. Clique em **Start Simulation**.
6. Abra o **Serial Monitor** em **115200 baud**.

## Imagens
Adicione nesta pasta:
- `images/circuito.png`
- `images/simulacao.png`
- `images/serial-monitor.png`

## Vídeo
Cole aqui o link do YouTube sem listagem.

## Entrega
Na FIAP, envie:
- link do GitHub
- link do vídeo no YouTube
