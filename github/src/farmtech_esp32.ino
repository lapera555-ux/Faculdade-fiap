#include <DHT.h>

#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Botões que simulam Nitrogênio, Fósforo e Potássio
#define BTN_N 12
#define BTN_P 13
#define BTN_K 14

// LDR simulando pH do solo
#define LDR_PIN 34

// Relé simulando a bomba d'água
#define RELE_PIN 26

// Controle opcional de chuva via Serial:
// Digite C no Serial Monitor para "com chuva"
// Digite S no Serial Monitor para "sem chuva"
bool chuvaPrevista = false;

float mapPhFromLdr(int valorLdr) {
  return (valorLdr / 4095.0f) * 14.0f;
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("Sistema FarmTech iniciado.");

  pinMode(BTN_N, INPUT_PULLUP);
  pinMode(BTN_P, INPUT_PULLUP);
  pinMode(BTN_K, INPUT_PULLUP);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);

  dht.begin();
}

void processaSerial() {
  while (Serial.available() > 0) {
    char c = toupper(Serial.read());
    if (c == 'C') {
      chuvaPrevista = true;
      Serial.println("Previsao atual: COM CHUVA");
    } else if (c == 'S') {
      chuvaPrevista = false;
      Serial.println("Previsao atual: SEM CHUVA");
    }
  }
}

void loop() {
  processaSerial();

  float umidade = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  float ph = mapPhFromLdr(ldrValue);

  bool N = !digitalRead(BTN_N);
  bool P = !digitalRead(BTN_P);
  bool K = !digitalRead(BTN_K);

  int nutrientesAtivos = (int)N + (int)P + (int)K;

  // Cultura de referência: tomate
  // Regras escolhidas pelo grupo:
  // 1) Umidade abaixo de 60%
  // 2) pH entre 5.5 e 7.0
  // 3) Pelo menos 2 nutrientes ativos
  // 4) Sem previsão de chuva
  bool umidadeBaixa = !isnan(umidade) && umidade < 60.0;
  bool phAdequado = ph >= 5.5 && ph <= 7.0;
  bool nutrientesOk = nutrientesAtivos >= 2;
  bool deveIrrigar = umidadeBaixa && phAdequado && nutrientesOk && !chuvaPrevista;

  digitalWrite(RELE_PIN, deveIrrigar ? HIGH : LOW);

  Serial.println("====================================");
  Serial.print("Umidade do solo simulada (DHT22): ");
  if (isnan(umidade)) Serial.println("ERRO");
  else {
    Serial.print(umidade, 1);
    Serial.println("%");
  }

  Serial.print("LDR bruto: ");
  Serial.println(ldrValue);

  Serial.print("pH simulado: ");
  Serial.println(ph, 2);

  Serial.print("N ativo: ");
  Serial.println(N ? "SIM" : "NAO");

  Serial.print("P ativo: ");
  Serial.println(P ? "SIM" : "NAO");

  Serial.print("K ativo: ");
  Serial.println(K ? "SIM" : "NAO");

  Serial.print("Nutrientes ativos: ");
  Serial.println(nutrientesAtivos);

  Serial.print("Previsao de chuva: ");
  Serial.println(chuvaPrevista ? "SIM" : "NAO");

  Serial.print("Bomba / rele: ");
  Serial.println(deveIrrigar ? "LIGADO" : "DESLIGADO");

  Serial.println("Para testar chuva no Serial Monitor:");
  Serial.println("Digite S = sem chuva | C = com chuva");
  Serial.println();

  delay(2000);
}
