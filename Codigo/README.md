# Código dos dispositivos embarcados

## Firmware

[telemetria_firebase.ino](telemetria_firebase/telemetria_firebase.ino), com configurações privadas removidas e correção do comentário inicial.

### Configuração local

1. Instalar o suporte à placa ESP32 no ambiente Arduino compatível.
2. Instalar bibliotecas compatíveis com os includes `mcp_can.h` e `FirebaseClient.h`. Registrar as versões usadas pelo grupo.
3. Copiar `telemetria_firebase/secrets.example.h` para `telemetria_firebase/secrets.h` e preencher apenas localmente.
4. Selecionar placa e porta correspondentes ao ESP32 e compilar.
5. Conferir oscilador, velocidade CAN, ligações e alimentação antes da execução.

A versão recebida referencia `SSL_CLIENT` e `set_ssl_client_insecure_and_buffer`, mas não inclui suas definições. Confirmar no ambiente original se são fornecidas por um arquivo auxiliar ou configuração da biblioteca e documentar esse requisito. Não foi comprovada compilação desta versão.

## Configuração CAN

- Controlador: MCP2515.
- Taxa: 50 kbit/s.
- Oscilador: 8 MHz.
- CS: GPIO 5.
- INT: GPIO 4.
- Modo: normal.

## Segurança e limites

`secrets.h` é ignorado por uma regra local em [telemetria_firebase/.gitignore](telemetria_firebase/.gitignore). Não versionar o original com valores reais. A chamada de TLS insecure permanece como na versão recebida; não representa validação do certificado.

Consulte [arquitetura e segurança](../Documentacao/07-Arquitetura-e-Seguranca.md) e [campos](../Documentacao/08-Telemetria-CAN-Firebase.md).
