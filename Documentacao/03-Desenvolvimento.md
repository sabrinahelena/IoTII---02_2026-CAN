# Desenvolvimento

## Estado atual do registro

Este documento descreve a arquitetura proposta na sprint 1. A montagem, o firmware, o armazenamento e o aplicativo terão seu desenvolvimento e testes registrados conforme o grupo informar as entregas.

## Arquitetura proposta

**Veículo (rede CAN) → Hardware → Armazenamento dos dados → Monitoramento via aplicativo**

O fluxo mantém a arquitetura apresentada na sprint 1: obter informações do veículo, processá-las no hardware, armazená-las e permitir seu acompanhamento pelo aplicativo.

## Materiais previstos

- Cabo OBD-II.
- Regulador de tensão.
- Módulo CAN.
- Conversor de nível lógico.
- ESP32.

Os modelos, especificações, esquema de ligação e materiais efetivamente utilizados serão documentados após confirmação do grupo.

## Desenvolvimento do hardware

### Montagem

Prevê-se integrar os componentes para comunicação com a rede CAN do veículo. O esquema elétrico e as evidências da montagem ainda devem ser registrados.

### Código

O firmware deverá permitir a captura das mensagens e a obtenção dos parâmetros de interesse: RPM, velocidade, temperatura do líquido de arrefecimento e estado da ignição. A interpretação e a disponibilidade desses parâmetros deverão ser validadas.

## Armazenamento e acesso aos dados

A solução deverá armazenar as informações coletadas e disponibilizá-las para consulta pelo aplicativo. A modelagem do banco, a tecnologia adotada e a interface de acesso serão documentadas conforme forem definidas.

## Desenvolvimento do aplicativo

### Interface

O aplicativo deverá apresentar informações do veículo e permitir o acompanhamento de seu histórico e comportamento por gráficos. As telas e evidências de funcionamento serão incluídas durante o desenvolvimento.

### Código

A tecnologia e a implementação do aplicativo ainda precisam ser registradas. As tarefas incluem desenvolver a interface e integrar a consulta às informações disponibilizadas pelo sistema.

## Comunicação entre aplicativo e hardware

A proposta prevê armazenamento dos dados entre a coleta pelo hardware e a visualização pelo aplicativo. Os protocolos de envio, a interface de consulta e a frequência de atualização permanecem a definir e documentar.

## Registro das próximas entregas

Para cada avanço, registrar:

- O que foi implementado e onde está o código.
- Decisões técnicas e componentes utilizados.
- Como foi testado e quais resultados foram obtidos.
- Evidências, limitações e pendências.
