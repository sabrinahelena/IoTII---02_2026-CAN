# Monitoramento Veicular utilizando Rede CAN

**Disciplina:** IoT II  
**Semestre:** 2º semestre de 2026  
**Campus/unidade, curso e orientador:** a confirmar.

## Integrantes

- Gabriela Almeida
- Victoria Barbosa
- Sabrina Ferreira

## Resumo

O projeto propõe acompanhar o funcionamento diário do veículo por meio da coleta de informações da rede CAN, armazenamento e visualização em aplicativo. Na sprint 2, o firmware recebido utiliza ESP32 e MCP2515 e implementa leitura e interpretação de mensagens, conexão Wi-Fi e envio ao Firebase Realtime Database.

Os sinais contemplados são RPM, velocidade, temperatura do líquido de arrefecimento, ignição, combustível, freio e estado do motor. O ar-condicionado também está no código, mas permanece não testado. O aplicativo está em desenvolvimento no Android Studio; sua execução e integração ainda estão pendentes.

## Arquitetura de rede e comunicação

**Veículo (CAN) → MCP2515 (SPI) → ESP32 → Wi-Fi/Internet → Firebase Realtime Database → aplicativo Android (integração pendente)**

A arquitetura mantém o fluxo apresentado na sprint 1. O firmware está configurado para CAN a 50 kbit/s, oscilador do MCP2515 de 8 MHz, CS no GPIO 5 e INT no GPIO 4. Esses parâmetros devem corresponder ao hardware e veículo utilizados.

O estado atual é atualizado em `/telemetria/atual`; novas amostras são adicionadas a `/telemetria/historico`. O envio é programado para cada segundo quando o Firebase está pronto. A data/hora é obtida por NTP em UTC-3.

## Situação do projeto

| Etapa | Situação |
| --- | --- |
| Sprint 1 | Apresentada: problema, proposta e arquitetura |
| Sprint 2 | Em preparação: firmware CAN/Firebase e documentação técnica recebidos; app em desenvolvimento |
| Sprint 3 | Registro futuro |

A existência de código não comprova execução ou aprovação de testes. Evidências do hardware, gravações no Firebase e integração do app serão registradas em [Testes](Documentacao/04-Testes.md).

## Segurança

As configurações privadas ficam em um arquivo local `secrets.h`, excluído do versionamento. O repositório oferece apenas `secrets.example.h` com valores fictícios.

O firmware utiliza autenticação Firebase por e-mail/senha. A versão recebida chama `set_ssl_client_insecure_and_buffer`, desativando a validação do certificado TLS: essa limitação permanece no código e deve ser corrigida e testada. As regras de autorização do banco não foram fornecidas. Consulte [Arquitetura e segurança](Documentacao/07-Arquitetura-e-Seguranca.md).

## Objetivos

- Coletar e interpretar parâmetros da rede CAN.
- Armazenar estado atual e histórico.
- Disponibilizar dados para consulta pelo aplicativo.
- Apresentar o comportamento do veículo ao motorista.

## Organização do repositório

| Área | Conteúdo |
| --- | --- |
| [Código do equipamento](Codigo/README.md) | Firmware ESP32 e configuração local |
| [BackEnd](Back/README.md) | Acesso aos dados via Firebase |
| [FrontEnd](Front/README.md) | Área preservada do template |
| [Aplicativo](App/README.md) | App em desenvolvimento no Android Studio |
| [Banco de dados](DB/README.md) | Estrutura e exemplos de telemetria |
| [Manual de utilização](Manual/manual%20de%20utilização.md) | Área preservada para instruções de uso |

## Apresentações

- [Sprint 1](Apresentacao/Sprint%201/README.md)
- [Sprint 2](Apresentacao/Sprint%202/README.md)
- [Sprint 3](Apresentacao/Sprint%203/README.md)
- [Vídeos e fotos](Apresentacao/Videos_fotos/README.md)

## Documentação

- [Introdução e proposta](Documentacao/01-Introducão.md)
- [Metodologias ágeis](Documentacao/02-Metodologias%20Ágeis.md)
- [Desenvolvimento](Documentacao/03-Desenvolvimento.md)
- [Testes](Documentacao/04-Testes.md)
- [Conclusão](Documentacao/05-Conclusão.md)
- [Referências](Documentacao/06-Referências.md)
- [Arquitetura e segurança](Documentacao/07-Arquitetura-e-Seguranca.md)
- [Campos de telemetria](Documentacao/08-Telemetria-CAN-Firebase.md)
- [Documentação técnica enviada pelo grupo](Documentacao/Anexos/documentacao_telemetria_veicular_can_firebase.pdf)

## Acompanhamento

O histórico de commits já registra a documentação da proposta e da sprint 1. As [issues](https://github.com/sabrinahelena/IoTII---02_2026-CAN/issues) ainda precisam ser cadastradas; os modelos estão em [Tarefas](Documentacao/09-Acompanhamento.md). O quadro GitHub Projects permanece a configurar.
