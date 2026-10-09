# Sprint 2

**Situação:** em preparação para a apresentação de 09/10/2026.  
**Aplicativo:** em desenvolvimento no Android Studio.

## Critérios de avaliação

| Critério | Pontos | Conteúdo preparado |
| --- | --- | --- |
| Arquitetura de rede/comunicação e segurança | 5 | CAN, SPI, Wi-Fi, Firebase, autenticação, configuração privada e limitações TLS |
| Inovações apresentadas e soluções encontradas | 5 | Evolução da proposta para firmware, novos sinais, estados/timeouts, histórico e NTP |
| Acompanhamento do projeto | 5 | Histórico Git, documentação por sprint e tarefas com critérios; issues/quadro ainda pendentes |

## Avanços em relação à sprint 1

- Identificação do MCP2515 e configuração CAN/SPI no firmware.
- Implementação de interpretação de RPM, velocidade, temperatura, ignição, combustível e freio.
- Classificação do estado do motor e tratamento por temporizadores.
- Implementação de envio por Wi-Fi ao Firebase Realtime Database.
- Separação entre estado atual e histórico.
- Uso de NTP para data/hora.
- Documentação técnica dos campos recebida do grupo.
- Aplicativo em desenvolvimento no Android Studio.

Os avanços acima são identificados no código e na documentação. Testes de execução e integração dependem de evidências do grupo.

## Arquitetura e segurança

Veículo CAN → MCP2515 → SPI → ESP32 → Wi-Fi/Internet → Firebase → aplicativo Android (integração pendente).

Autenticação por e-mail/senha presente. Configurações privadas retiradas do código público. A validação de certificado TLS está desativada na versão recebida e as regras do banco ainda não foram fornecidas. Esses controles não devem ser apresentados como concluídos.

## Soluções encontradas

| Problema | Solução no código |
| --- | --- |
| Mensagens brutas de diferentes sinais | Decodificação por IDs e bytes |
| Distinguir partida/funcionamento | Máquina de estados com temporizadores |
| Ausência de heartbeat/mensagens RPM | Timeouts |
| Consultar última leitura e acompanhar evolução | Estado atual e histórico separados |
| Relacionar amostras ao tempo | Sincronização NTP |

## Acompanhamento

A documentação da sprint 1 já consta no repositório. Os modelos de tarefas foram atualizados para refletir Firebase e Android Studio. Issues e quadro ainda precisam ser cadastrados; não há evidência de acompanhamento via cards nesta consulta.

## Material

- [Documentação técnica do grupo](../../Documentacao/Anexos/documentacao_telemetria_veicular_can_firebase.pdf)
- [Arquitetura e segurança](../../Documentacao/07-Arquitetura-e-Seguranca.md)
- [Telemetria](../../Documentacao/08-Telemetria-CAN-Firebase.md)
- [Firmware](../../Codigo/README.md)
- [Testes e limitações](../../Documentacao/04-Testes.md)
- [Tarefas e acompanhamento](../../Documentacao/09-Acompanhamento.md)

Os slides finais e as evidências de demonstração ainda serão anexados pelo grupo.
