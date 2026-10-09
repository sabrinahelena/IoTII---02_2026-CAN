# Introdução

## Contexto e problema

O projeto Monitoramento Veicular utilizando Rede CAN foi proposto na disciplina IoT II. A manutenção tradicional pode depender de luzes no painel ou de sinais perceptíveis ao motorista, fazendo com que alterações no funcionamento do veículo sejam identificadas apenas quando já se tornaram relevantes.

A falta de acompanhamento contínuo e de acesso ao histórico dificulta observar a evolução dos parâmetros e perceber pequenas mudanças no comportamento do carro.

## Proposta

Desenvolver um sistema que obtenha informações da rede CAN por meio de hardware baseado em ESP32, armazene os dados e permita acompanhá-los em um aplicativo. A proposta é apresentar informações e gráficos que ajudem o motorista a conhecer o comportamento habitual do veículo e perceber alterações que motivem uma avaliação em oficina.

## Objetivo geral

Desenvolver um sistema de monitoramento veicular que integre coleta de dados da rede CAN, armazenamento e visualização em aplicativo, apoiando o acompanhamento do funcionamento do veículo.

## Objetivos específicos

- Capturar mensagens da rede CAN e obter os parâmetros de interesse.
- Interpretar e armazenar os dados coletados.
- Disponibilizar as informações para consulta pelo aplicativo.
- Exibir parâmetros e histórico de funcionamento ao motorista.
- Documentar as etapas de desenvolvimento e os testes do sistema.

## Dados de interesse

| Parâmetro | Significado |
| --- | --- |
| RPM | Rotação do motor |
| Velocidade | Velocidade do veículo |
| Temperatura | Temperatura do líquido de arrefecimento |
| Ignição | Estado da chave/ignição |

A disponibilidade e a forma de obtenção de cada parâmetro deverão ser verificadas durante o desenvolvimento.

## Público-alvo

Motoristas que desejam acompanhar informações de funcionamento do veículo por meio de uma interface acessível, sem precisar interpretar diretamente as mensagens da rede CAN.

## Justificativa e ODS

A proposta busca ampliar o acesso ao acompanhamento veicular com hardware aberto e de baixo custo. Na sprint 1, o grupo relacionou o projeto ao ODS 9 (Indústria, Inovação e Infraestrutura), pela democratização da telemetria e modernização da frota, e ao ODS 11 (Cidades e Comunidades Sustentáveis), pelo potencial de apoiar uma mobilidade mais sustentável.

Essas contribuições são objetivos da proposta; impactos sobre manutenção e emissões ainda não foram medidos.

## Estado da proposta

Este documento registra o escopo apresentado na sprint 1. A sprint 2 está em desenvolvimento e suas entregas serão documentadas a partir das informações e evidências do grupo.

## Evolução do escopo na sprint 2

O firmware recebido contempla também nível de combustível, freio e classificação do estado do motor. Foram definidos no código ESP32, MCP2515, envio por Wi-Fi e armazenamento no Firebase Realtime Database. O aplicativo está em desenvolvimento no Android Studio.

Essas informações atualizam a proposta sem alterar o objetivo geral. A implementação e suas limitações estão em [Desenvolvimento](03-Desenvolvimento.md); os resultados de testes ainda precisam de evidências.
