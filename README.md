# 🛡️ Guardian Vision

**Guardian Vision** é um sistema de **alarme inteligente** capaz de **distinguir seres humanos de outros objetos**, utilizando visão computacional com **YOLOv5** e integração com um **ESP32**.  
O objetivo é oferecer uma solução prática e eficiente para **monitoramento de segurança residencial ou industrial**.

---

## 🚀 Funcionalidades

- Detecção inteligente de pessoas utilizando **YOLOv5**.  
- Acionamento automático do **alarme via ESP32** quando um humano é identificado.  
- Interface web simples para monitoramento e controle remoto.  
- Operação em rede local com IP fixo (internet estática).

---

## 🧠 Arquitetura do Projeto

[🎥 Câmera] → [🐍 alarme_inteligente.py] → [🔍 Detecção YOLOv5] → [📡 Comunicação Serial] → [🔌 ESP32] → [🚨 Alertas]

---

## 🧩 Requisitos

Antes de começar, você precisará ter instalado:

- [Python 3.8+](https://www.python.org/downloads/)
- [Git](https://git-scm.com/downloads)
- Uma **placa ESP32**
- Conexão de internet **estática** (sem troca de IP)

Além disso, será necessário clonar o repositório oficial do **YOLOv5**:
bash
git clone https://github.com/ultralytics/yolov5.git
\`\`\`

---

## ⚙️ Instalação e Configuração

### 1️⃣ Clonar o repositório do Guardian Vision

\`\`\`bash
git clone https://github.com/joaoselim/Guardian_Vision.git
cd Guardian_Vision
\`\`\`

### 2️⃣ Integrar com o YOLOv5

Mova o arquivo `alarme_inteligente.py` para dentro da pasta do YOLOv5:
\`\`\`bash
mv alarme_inteligente.py ./yolov5/
\`\`\`

---

## 🔌 Configuração do ESP32

1. Abra o arquivo `alarme_esp32.ino` na **Arduino IDE**.  
2. Conecte seu **ESP32** via USB.  
3. Faça o upload do código para a placa.  
4. Após o upload, abra o **Monitor Serial** e copie o **IP exibido** — ele será usado para acessar a interface web do sistema.

> ⚠️ Certifique-se de que o IP é **estático**, pois mudanças podem causar falha na comunicação entre o Python e o ESP32.

---

## 🖥️ Executando o Sistema

1. Com o ESP32 configurado e conectado à rede, acesse o IP no navegador para abrir a interface HTML.  
2. No seu PC, dentro da pasta do YOLOv5, execute o seguinte comando:

\`\`\`bash
python alarme_inteligente.py
\`\`\`

3. O sistema iniciará a detecção. Sempre que um **humano for identificado**, o **alarme será acionado automaticamente**.

---

## 🧪 Testes

- Cadastre um e-mail no HTML
- Aponte a câmera para diferentes objetos e pessoas.  
- Observe no console o log de detecção e o acionamento do alarme.  
- Verifique o feedback de e-mail realizado pelo esp-32.

---

## 🛠️ Tecnologias Utilizadas

- **Python 3**
- **YOLOv5** (Visão Computacional)
- **ESP32** (Microcontrolador)
- **HTML** (Interface Web)
- **Arduino IDE**

---

## 🤝 Contribuições

Sinta-se à vontade para contribuir!  
- Abra uma *issue* para relatar bugs ou sugerir melhorias.  
- Faça um *fork* e envie um *pull request* com suas alterações.

---


## 👨‍💻 Autores

**Igor Mavigno**
**João Selim**
**Lara Siecola**
**Pedro Henrique**

> Projeto desenvolvido como parte de um sistema de segurança baseado em IA.  
📧 Contatos:
> [igor@mavigno.com]
> [ph.oliveira@gec.inatel.br]
> [lara.siecola@gec.inatel.br]
> [joao.amback@ges.inatel.br]

