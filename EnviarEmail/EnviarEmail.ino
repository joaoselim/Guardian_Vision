#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP_Mail_Client.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

// ------------------ Wi-Fi ------------------
const char* ssid = "igor's Galaxy S20 FE 5G";
const char* password = "undd2674";

// ------------------ VARIÁVEIS ------------------
bool pessoaDetectada = false;
int enviarEmailFlag = 0;
String userEmail = "";
#define LED_PIN 4
// ------------------ SERVIDOR ------------------
AsyncWebServer server(80);

// ------------------ SMTP ------------------
SMTPSession smtp;
const char* smtpHost = "smtp.gmail.com";
const int smtpPort = 465;
const char* emailRemetente = "guardianvisionfetin@gmail.com";
const char* senhaEmail = "eosz znji liqg jzcv"; // senha de app do Gmail

// ------------------ ENVIO DE E-MAIL ------------------
void enviarEmail(String destino) {
  SMTP_Message message;
  message.sender.name = "Alerta";
  message.sender.email = emailRemetente;
  message.subject = "Alarme acionado!";
  message.addRecipient("Usuário", destino.c_str());
  message.text.content = "Uma pessoa foi detectada pelo sistema de segurança.\n Seu alarme foi acionado, para desligá-lo acesse o site ou o aplicativo.";
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  smtp.debug(1);

  ESP_Mail_Session session;
  session.server.host_name = smtpHost;
  session.server.port = smtpPort;
  session.login.email = emailRemetente;
  session.login.password = senhaEmail;
  session.login.user_domain = "";

  if (!smtp.connect(&session)) {
    Serial.println("Erro de conexão SMTP");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Erro ao enviar email");
  } else {
    Serial.println("Email enviado com sucesso!");
  }
}

// ------------------ SETUP ------------------
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("\nESP32 iniciado...");

  // Iniciar SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Falha ao montar SPIFFS");
    return;
  } else {
    Serial.println("SPIFFS iniciado");
  }

  // Conectar ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado com sucesso!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Servir arquivos estáticos do SPIFFS
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Endpoint para receber JSON do frontend
  server.on("/api/subscribe-alert", HTTP_POST,
    [](AsyncWebServerRequest *request){}, 
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      String body;
      for (size_t i = 0; i < len; i++) {
        body += (char)data[i];
      }
      Serial.println("JSON recebido: " + body);

      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, body);

      if (error) {
        Serial.println("Falha ao parsear JSON");
        request->send(400, "application/json", "{\"message\":\"Erro ao ler JSON\"}");
        return;
      }

      // Extrair o campo "email"
      userEmail = doc["email"].as<String>();
      Serial.println("E-mail salvo: " + userEmail);

      
//      pessoaDetectada = !pessoaDetectada;
      Serial.println("Pessoa detectada: " + String(pessoaDetectada));
      

      // Resposta para o navegador
      request->send(200, "application/json", "{\"message\":\"E-mail cadastrado com sucesso!\"}");
    }
  );

  // Endpoint para status (JSON)
  // ver se é esse caminho que vai usar mesmo 
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request){
    DynamicJsonDocument doc(128);
    doc["detectado"] = pessoaDetectada;
    String resposta;
    serializeJson(doc, resposta);
    request->send(200, "application/json", resposta);
  });

  // Endpoints para controlar LED 
  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ligado via /ligar");
    request->send(200, "text/plain", "LED ligado");
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED desligado via /desligar");
    request->send(200, "text/plain", "LED desligado");
  });
  
  // Iniciar servidor
  server.begin();
  Serial.println("Servidor iniciado!");
}

// ------------------ LOOP ------------------
void loop() {   
    if (digitalRead(LED_PIN) == HIGH) {
      pessoaDetectada = true;
    } 
    else if(digitalRead(LED_PIN) == LOW){
      pessoaDetectada = false;
      enviarEmailFlag = 0;
    }

  if (pessoaDetectada && userEmail != "") {
    // Para garantir que será enviado apenas um email por vez
    if (enviarEmailFlag == 0) {
      enviarEmailFlag++;
      enviarEmail(userEmail);
    }
  }
}
