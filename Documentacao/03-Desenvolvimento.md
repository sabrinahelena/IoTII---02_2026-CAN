# Desenvolvimento

## Estado atual

A sprint 1 apresentou a proposta. Para a sprint 2, Gabriela enviou firmware de telemetria CAN/Firebase e documentação dos campos. O código implementa leitura, interpretação e envio; ainda é necessário registrar evidências de compilação, execução e gravação. O aplicativo está em desenvolvimento no Android Studio.

## Materiais

O firmware usa ESP32 e MCP2515. A proposta inclui cabo OBD-II, regulador de tensão e conversor de nível lógico. O esquema de ligação completo e os modelos dos demais componentes ainda precisam ser anexados.

## Arquitetura

Veículo (CAN) → MCP2515 → SPI → ESP32 → Wi-Fi/Internet → Firebase Realtime Database → aplicativo Android (integração pendente).

A comunicação CAN está configurada para 50 kbit/s, com oscilador de 8 MHz. CS = GPIO 5; INT = GPIO 4. O MCP2515 opera em modo normal no código; não deve ser descrito como modo listen-only.

## Desenvolvimento do hardware

### Montagem

O esquema elétrico, alimentação, compatibilidade de níveis e registros da montagem ainda devem ser documentados pelo grupo.

### Código

O [firmware](../Codigo/telemetria_firebase/telemetria_firebase.ino) interpreta cinco IDs CAN. Os campos e fórmulas estão em [Telemetria](08-Telemetria-CAN-Firebase.md).

O código acompanha temporizadores para partida, rotação zero, perda de mensagens de RPM e ausência de heartbeat da ignição. A saída serial é programada para aproximadamente 250 ms.

As configurações privadas foram separadas em `secrets.h`, arquivo local não versionado. Foi corrigido o delimitador de comentário da primeira linha do arquivo recebido. A lógica de coleta e a configuração TLS da versão original foram preservadas.

## Armazenamento e acesso aos dados

O firmware usa FirebaseClient, autenticação por e-mail/senha e Firebase Realtime Database. Cada ciclo de envio agenda duas operações:
- `set` em `/telemetria/atual`, substituindo a amostra anterior;
- `push` em `/telemetria/historico`, adicionando uma amostra.

O intervalo é de 1 segundo, condicionado a `app.ready()`. Isso não garante persistência de toda amostra. Os callbacks reportam resultados e erros.

## Desenvolvimento do aplicativo

### Interface

O aplicativo está em desenvolvimento no Android Studio. Sua execução ainda está sendo preparada. Não foram fornecidos código, capturas de tela ou evidências de integração.

### Código

A linguagem, bibliotecas e forma de consulta ao Firebase ainda serão registradas após confirmação do grupo.

## Comunicação entre app e hardware

O ESP32 envia dados ao Firebase por Wi-Fi/Internet. A consulta do banco pelo aplicativo é a integração planejada, ainda pendente. Não há evidência de conexão direta app/ESP32 ou de backend próprio.

## Soluções implementadas e pendências

| Necessidade | Solução presente no código | Pendência |
| --- | --- | --- |
| Interpretar mensagens CAN | Seleção por ID e extração de bytes/bits | Validar significado e escala no veículo |
| Distinguir partida e funcionamento | Estados e temporizadores | Testar transições |
| Tratar ausência de sinais | Timeouts de ignição e RPM | Distinguir falha de comunicação de desligamento real |
| Guardar dados recentes e passados | Estado atual e histórico no Firebase | Comprovar gravação e definir retenção |
| Associar horário às amostras | NTP com UTC-3 | Tratar falta de sincronização |
| Mostrar informações ao motorista | Aplicativo Android em desenvolvimento | Executar e integrar |

As soluções são avanços do projeto; não constituem comprovação de inovação inédita ou de diagnóstico automático de falhas.
