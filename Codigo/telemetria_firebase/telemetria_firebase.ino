// ============================================================
// MONITORAMENTO VEICULAR CAN + FIREBASE
// ============================================================

#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <WiFi.h>
#include <SPI.h>
#include <mcp_can.h>
#include <FirebaseClient.h>
#include <time.h>
#include "secrets.h"

// ============================================================
// CONFIGURAÇÕES DO WI-FI
// ============================================================


// ============================================================
// CONFIGURAÇÕES DO FIREBASE
// ============================================================


// ============================================================
// CONFIGURAÇÕES DO MCP2515
// ============================================================

#define CAN0_INT 4
const int SPI_CS_PIN = 5;

MCP_CAN CAN0(SPI_CS_PIN);

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

// ============================================================
// CONFIGURAÇÃO DO FIREBASE
// ============================================================

SSL_CLIENT ssl_client;

using AsyncClient = AsyncClientClass;

AsyncClient aClient(ssl_client);

UserAuth user_auth(
  API_KEY,
  USER_EMAIL,
  USER_PASSWORD,
  3000
);

FirebaseApp app;
RealtimeDatabase Database;

AsyncResult databaseResult;

// ============================================================
// VARIÁVEIS DE TELEMETRIA - DRIVETRAIN
// ============================================================

uint16_t rpm = 0;

String statusFuncionamento = "desligado";

uint8_t tempArref_c = 0;

uint16_t velocidade_kmh = 0;

bool arCondicionado = false;

bool freio = false;

// ============================================================
// VARIÁVEIS DE TELEMETRIA - PAINEL NQS
// ============================================================

bool ignicao = false;

uint8_t combustivel_pct = 0;

unsigned long ultimoHeartbeat3C3 = 0;

// ============================================================
// TEMPORIZADORES E CONTROLE DE ESTADO
// ============================================================

unsigned long ultimoPacoteRPM = 0;

unsigned long tempoZeroDetectado = 0;

unsigned long tempoPartidaInicio = 0;

bool emPartida = false;

// ============================================================
// TEMPORIZADORES
// ============================================================

unsigned long lastPrint = 0;

unsigned long ultimoEnvioFirebase = 0;

// Envia uma amostra ao Firebase a cada 1 segundo
const unsigned long INTERVALO_FIREBASE = 1000;

// ============================================================
// PROTÓTIPOS
// ============================================================

void processData(AsyncResult &aResult);

String obterTimestamp();

void enviarFirebase();

void conectarWiFi();

void inicializarHorario();

// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  while (!Serial);

  Serial.println();
  Serial.println("========================================");
  Serial.println(" MONITORAMENTO VEICULAR CAN");
  Serial.println(" ESP32 + MCP2515 + Firebase");
  Serial.println("========================================");
  Serial.println();

  // ----------------------------------------------------------
  // Inicializa MCP2515
  // ----------------------------------------------------------

  if (CAN0.begin(MCP_ANY, CAN_50KBPS, MCP_8MHZ) == CAN_OK) {

    Serial.println("OK: MCP2515 Conectado!");

  } else {

    Serial.println("ERRO: Falha ao inicializar MCP2515!");

    while (1);
  }

  CAN0.setMode(MCP_NORMAL);

  pinMode(CAN0_INT, INPUT);

  // ----------------------------------------------------------
  // Conecta Wi-Fi
  // ----------------------------------------------------------

  conectarWiFi();

  // ----------------------------------------------------------
  // Configura horário via NTP
  // ----------------------------------------------------------

  inicializarHorario();

  // ----------------------------------------------------------
  // Inicializa Firebase
  // ----------------------------------------------------------

  Serial.println();
  Serial.println("Inicializando Firebase...");

  set_ssl_client_insecure_and_buffer(ssl_client);

  initializeApp(
    aClient,
    app,
    getAuth(user_auth),
    processData,
    "authTask"
  );

  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);

  Serial.println("Firebase configurado!");

  Serial.println();
  Serial.println("Sistema pronto.");
  Serial.println();
}

// ============================================================
// LOOP
// ============================================================

void loop() {

  // ==========================================================
  // Mantém Firebase funcionando
  // ==========================================================

  app.loop();

  // ==========================================================
  // 1. LEITURA DO BARRAMENTO CAN
  // ==========================================================

  if (!digitalRead(CAN0_INT) || CAN0.checkReceive() == CAN_MSGAVAIL) {

    if (CAN0.readMsgBuf(&rxId, &len, rxBuf) == CAN_OK) {

      unsigned long id = rxId & 0x7FF;

      // ======================================================
      // ID 0x281 -> RPM + ESTADO DO AR CONDICIONADO
      // ======================================================

      if (id == 0x281 && len >= 3) {

        ultimoPacoteRPM = millis();

        // ----------------------------------------------------
        // Estado do A/C
        // Byte 2, Bit 7
        // 0x80 = ligado
        // 0x40/0x00 = desligado
        // ----------------------------------------------------

        arCondicionado = ((rxBuf[2] & 0x80) != 0);

        // ----------------------------------------------------
        // RPM - Bytes 4 e 5
        // ----------------------------------------------------

        if (len >= 6) {

          uint16_t rpmLido =
            ((uint16_t)(rxBuf[4] & 0x3F) << 8) |
            rxBuf[5];

          if (rpmLido > 0) {

            // ------------------------------------------------
            // Detecta início da partida
            // ------------------------------------------------

            if (
              rpm == 0 &&
              rpmLido >= 300 &&
              !emPartida
            ) {

              emPartida = true;

              tempoPartidaInicio = millis();

              statusFuncionamento = "partida";
            }

            rpm = rpmLido;

            tempoZeroDetectado = 0;

            // ------------------------------------------------
            // Após 2 segundos considera motor funcionando
            // ------------------------------------------------

            if (emPartida) {

              if (millis() - tempoPartidaInicio > 2000) {

                emPartida = false;

                statusFuncionamento = "em_funcionamento";
              }

            } else {

              statusFuncionamento = "em_funcionamento";
            }

          }

          else {

            if (tempoZeroDetectado == 0) {

              tempoZeroDetectado = millis();
            }

            if (millis() - tempoZeroDetectado > 1200) {

              rpm = 0;

              statusFuncionamento = "desligado";

              emPartida = false;
            }
          }
        }
      }

      // ======================================================
      // ID 0x380 -> TEMPERATURA DE ARREFECIMENTO
      // Byte 3
      // ======================================================

      if (id == 0x380 && len >= 4) {

        tempArref_c = rxBuf[3];
      }

      // ======================================================
      // ID 0x180 -> FREIO + VELOCIDADE
      // ======================================================

      if (id == 0x180 && len >= 3) {

        // ----------------------------------------------------
        // Freio
        // ----------------------------------------------------

        freio = ((rxBuf[0] & 0x80) != 0);

        // ----------------------------------------------------
        // Velocidade
        // ----------------------------------------------------

        uint16_t rawSpeed =
          ((uint16_t)rxBuf[1] << 8) |
          rxBuf[2];

        if (rawSpeed <= 24576) {

          velocidade_kmh = 0;

        } else {

          velocidade_kmh =
            (rawSpeed - 24576) / 16;
        }
      }

      // ======================================================
      // ID 0x6E3 -> NÍVEL DE COMBUSTÍVEL
      // Byte 4
      // ======================================================

      if (id == 0x6E3 && len >= 5) {

        if (rxBuf[4] <= 100) {

          combustivel_pct = rxBuf[4];
        }
      }

      // ======================================================
      // ID 0x3C3 -> ESTADO DA IGNIÇÃO
      // ======================================================

      if (id == 0x3C3 && len >= 1) {

        if (
          rxBuf[0] == 0x20 ||
          rxBuf[0] == 0xA0
        ) {

          ultimoHeartbeat3C3 = millis();

          ignicao = true;
        }
      }
    }
  }

  // ==========================================================
  // 2. TIMEOUT DA IGNIÇÃO (KEY-OFF)
  if (
    ignicao &&
    (millis() - ultimoHeartbeat3C3 > 2500)
  ) {

    ignicao = false;
  }

  // ==========================================================
  // 3. TIMEOUT GLOBAL DE PERDA DA REDE CAN / MOTOR
if (
    !ignicao ||
    (
      millis() - ultimoPacoteRPM > 1500 &&
      ultimoPacoteRPM > 0
    )
  ) {

    rpm = 0;

    velocidade_kmh = 0;

    statusFuncionamento = "desligado";

    emPartida = false;

    arCondicionado = false;

    freio = false;
  }

  // ==========================================================
  // 4. MONITOR SERIAL
  if (millis() - lastPrint > 250) {

    lastPrint = millis();

    Serial.print("{\"painel\":{\"ignicao\":");

    Serial.print(
      ignicao ? "true" : "false"
    );

    Serial.print(",\"combustivel_pct\":");

    Serial.print(combustivel_pct);

    Serial.print("},\"motor\":{\"rpm\":");

    Serial.print(rpm);

    Serial.print(",\"velocidade_kmh\":");

    Serial.print(velocidade_kmh);

    Serial.print(",\"status\":\"");

    Serial.print(statusFuncionamento);

    Serial.print("\",\"tempArref_c\":");

    Serial.print(tempArref_c);

    Serial.print(",\"freio\":");

    Serial.print(
      freio ? "true" : "false"
    );

    Serial.print(",\"arCondicionado\":");

    Serial.print(
      arCondicionado ? "true" : "false"
    );

    Serial.println("}}");
  }

  // ==========================================================
  // 5. ENVIO PARA O FIREBASE
  if (
    millis() - ultimoEnvioFirebase >=
    INTERVALO_FIREBASE
  ) {

    ultimoEnvioFirebase = millis();

    if (app.ready()) {

      enviarFirebase();

    } else {

      Serial.println(
        "Firebase ainda não está pronto."
      );
    }
  }
}

// ============================================================
// CONEXÃO WI-FI
void conectarWiFi() {

  Serial.print("Conectando ao Wi-Fi");

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(300);
  }

  Serial.println();

  Serial.println("Wi-Fi conectado!");

  Serial.print("IP: ");

  Serial.println(WiFi.localIP());
}

// ============================================================
// CONFIGURAÇÃO DO HORÁRIO
void inicializarHorario() {

  Serial.println();
  Serial.println(
    "Sincronizando horário via NTP..."
  );

  // Brasil / Brasília = UTC-3
  configTime(
    -3 * 3600,
    0,
    "pool.ntp.org",
    "time.nist.gov"
  );

  struct tm timeinfo;

  int tentativas = 0;

  while (
    !getLocalTime(&timeinfo) &&
    tentativas < 20
  ) {

    Serial.print(".");

    delay(500);

    tentativas++;
  }

  Serial.println();

  if (tentativas < 20) {

    Serial.println(
      "Horário sincronizado!"
    );

    Serial.print(
      "Data/hora: "
    );

    Serial.println(
      obterTimestamp()
    );

  } else {

    Serial.println(
      "AVISO: Não foi possível sincronizar o horário."
    );
  }
}

// ============================================================
// OBTÉM TIMESTAMP FORMATADO
String obterTimestamp() {

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {

    return "00/00/0000 00:00:00";
  }

  char timestamp[25];

  strftime(
    timestamp,
    sizeof(timestamp),
    "%d/%m/%Y %H:%M:%S",
    &timeinfo
  );

  return String(timestamp);
}

// ============================================================
// ENVIA TELEMETRIA PARA O FIREBASE
void enviarFirebase() {

  // ----------------------------------------------------------
  // Obtém horário atual
  String timestamp = obterTimestamp();

  // ----------------------------------------------------------
  // Monta JSON
  String json = "{";

  json += "\"timestamp\":\"";
  json += timestamp;
  json += "\",";

  // ==========================================================
  // PAINEL
  json += "\"painel\":{";

  json += "\"ignicao\":";
  json += (
    ignicao ? "true" : "false"
  );

  json += ",";

  json += "\"combustivel_pct\":";
  json += String(combustivel_pct);

  json += "},";

  // ==========================================================
  // MOTOR
json += "\"motor\":{";

  json += "\"rpm\":";
  json += String(rpm);

  json += ",";

  json += "\"velocidade_kmh\":";
  json += String(velocidade_kmh);

  json += ",";

  json += "\"status\":\"";
  json += statusFuncionamento;
  json += "\"";

  json += ",";

  json += "\"tempArref_c\":";
  json += String(tempArref_c);

  json += ",";

  json += "\"freio\":";
  json += (
    freio ? "true" : "false"
  );

  json += ",";

  json += "\"arCondicionado\":";
  json += (
    arCondicionado ? "true" : "false"
  );

  json += "}";

  json += "}";

  
  // Converte para objeto Firebase
  object_t dados(json);


  // 1. Atualiza estado atual
  Database.set<object_t>(
    aClient,
    "/telemetria/atual",
    dados,
    processData,
    "setAtual"
  );


  // 2. Adiciona nova amostra ao histórico
  Database.push<object_t>(
    aClient,
    "/telemetria/historico",
    dados,
    processData,
    "pushHistorico"
  );

  // ----------------------------------------------------------
  // Mostra no Serial
 
  Serial.println();
  Serial.println(
    "Firebase -> telemetria enviada"
  );

  Serial.print(
    "Timestamp: "
  );

  Serial.println(timestamp);
}

// ============================================================
// PROCESSAMENTO DAS RESPOSTAS DO FIREBASE
void processData(AsyncResult &aResult) {

  if (!aResult.isResult()) {

    return;
  }

  // ----------------------------------------------------------
  // Eventos
 if (aResult.isEvent()) {

    Firebase.printf(
      "Firebase Event: %s | %s | code: %d\n",
      aResult.uid().c_str(),
      aResult.eventLog().message().c_str(),
      aResult.eventLog().code()
    );
  }

  // ----------------------------------------------------------
  // Debug
  if (aResult.isDebug()) {

    Firebase.printf(
      "Firebase Debug: %s | %s\n",
      aResult.uid().c_str(),
      aResult.debug().c_str()
    );
  }

  // ----------------------------------------------------------
  // Erros
   if (aResult.isError()) {

    Firebase.printf(
      "Firebase ERRO: %s | %s | code: %d\n",
      aResult.uid().c_str(),
      aResult.error().message().c_str(),
      aResult.error().code()
    );
  }

  // ----------------------------------------------------------
  // Resultado
  if (aResult.available()) {

    Firebase.printf(
      "Firebase OK: %s\n",
      aResult.uid().c_str()
    );

    Firebase.printf(
      "Payload: %s\n",
      aResult.c_str()
    );
  }
}