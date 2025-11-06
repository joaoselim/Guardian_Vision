import requests
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from pathlib import Path
from ultralytics import YOLO

# ================= CONFIGURAÇÕES =================
ESP_IP = "http:///10.16.167.104"   # IP do seu ESP32-CAM
EMAIL_REMETENTE = "flangobomb@gmail.com"
EMAIL_SENHA = "sua_senha"  # se Gmail, pode ser App Password
ALERTA_EMAIL = input("Digite o e-mail que receberá o alerta: ")

# ================= FUNÇÕES =================
def acender_led():
    try:
        requests.get(f"{ESP_IP}/led/on", timeout=2)
        print("LED aceso!")
    except:
        print("Erro ao acender o LED.")

def apagar_led():
    try:
        requests.get(f"{ESP_IP}/led/off", timeout=2)
        print("LED apagado!")
    except:
        print("Erro ao apagar o LED.")

def enviar_email():
    try:
        msg = MIMEMultipart()
        msg["From"] = EMAIL_REMETENTE
        msg["To"] = ALERTA_EMAIL
        msg["Subject"] = "⚠️ Alerta de Pessoa Detectada!"
        body = "Uma pessoa foi detectada pela câmera. Alerta acionado!"
        msg.attach(MIMEText(body, "plain"))

        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.starttls()
        server.login(EMAIL_REMETENTE, EMAIL_SENHA)
        server.send_message(msg)
        server.quit()
        print("E-mail enviado com sucesso!")
    except Exception as e:
        print("Erro ao enviar e-mail:", e)

# ================= DETECÇÃO =================
alarme_ativado = False
model = YOLO("yolov5s.pt")  # ou o modelo que você estiver usando
source = "0"  # webcam, pode ser caminho do vídeo ou número da câmera

for result in model.track(source, persist=True):  # track retorna frame a frame
    # Verifica se existe pessoa na detecção (classe 0)
    pessoas = [box for box in result.boxes if int(box.cls) == 0]

    if pessoas and not alarme_ativado:
        alarme_ativado = True
        print("⚠️ Pessoa detectada! Acionando alarme...")
        acender_led()
        enviar_email()

    elif not pessoas and alarme_ativado:
        alarme_ativado = False
        print("Alarme desligado. Apagando LED...")
        apagar_led()
