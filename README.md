# Monitoramento Veicular utilizando Rede CAN

**Disciplina:** IoT II  
**Semestre:** 2º semestre de 2026  
**Campus/unidade, curso e orientador:** a confirmar.

## Integrantes

- Gabriela Almeida
- Victoria Barbosa
- Sabrina Ferreira

## Resumo

O projeto propõe um sistema de monitoramento veicular que coleta informações da rede CAN por meio de hardware baseado em ESP32, armazena os dados e os disponibiliza em um aplicativo. Os parâmetros de interesse são rotação do motor (RPM), velocidade, temperatura do líquido de arrefecimento e estado da ignição.

O objetivo é oferecer ao motorista uma visão acessível do funcionamento diário do veículo e de seu histórico. O acompanhamento poderá ajudar a perceber alterações no comportamento do carro e apoiar a procura por manutenção preventiva.

## Arquitetura proposta

**Veículo (rede CAN) → Hardware → Armazenamento dos dados → Monitoramento via aplicativo**

O hardware previsto inclui cabo OBD-II, regulador de tensão, módulo CAN, conversor de nível lógico e ESP32. Os modelos dos componentes, protocolos de comunicação, banco de dados e tecnologias do aplicativo serão registrados conforme forem definidos e validados pelo grupo.

## Situação do projeto


| Etapa    | Situação                                                                 |
| -------- | ------------------------------------------------------------------------ |
| Sprint 1 | Apresentada: problema, proposta, arquitetura e funcionalidades previstas |
| Sprint 2 | Em desenvolvimento; atualizações e evidências a registrar                |
| Sprint 3 | Registro futuro                                                          |


A documentação atual descreve a proposta apresentada na sprint 1. Funcionalidades previstas não representam, por si só, implementações concluídas ou testadas.

## Objetivos

- Coletar mensagens e obter os parâmetros de interesse da rede CAN.
- Interpretar e armazenar as informações coletadas.
- Disponibilizar as informações para consulta pelo aplicativo.
- Apresentar os dados e seu histórico de forma compreensível ao motorista.



## Organização do repositório

A estrutura original da disciplina foi mantida.


| Área                                                       | Conteúdo                                        |
| ---------------------------------------------------------- | ----------------------------------------------- |
| [Código do equipamento](Codigo/README.md)                  | Firmware e código do hardware                   |
| [BackEnd](Back/README.md)                                  | Serviços de acesso às informações               |
| [FrontEnd](Front/README.md)                                | Código de interface, conforme a solução adotada |
| [Aplicativo](App/README.md)                                | Aplicativo para smartphone                      |
| [Banco de dados](DB/README.md)                             | Modelagem e scripts                             |
| [Manual de utilização](Manual/manual%20de%20utilização.md) | Instruções de uso                               |




## Apresentações

- [Sprint 1](Apresentacao/Sprint%201/README.md)
- [Sprint 2](Apresentacao/Sprint%202/README.md)
- [Sprint 3](Apresentacao/Sprint%203/README.md)
- [Vídeos e fotos do projeto](Apresentacao/Videos_fotos/README.md)



## Documentação

- [Introdução e proposta](Documentacao/01-Introducão.md)
- [Metodologias ágeis](Documentacao/02-Metodologias%20Ágeis.md)
- [Desenvolvimento e arquitetura](Documentacao/03-Desenvolvimento.md)
- [Testes](Documentacao/04-Testes.md)
- [Conclusão](Documentacao/05-Conclusão.md)
- [Referências](Documentacao/06-Referências.md)



## Acompanhamento

As tarefas do grupo serão acompanhadas pelas [issues do repositório](https://github.com/sabrinahelena/IoTII---02_2026-CAN/issues). O Git registra o histórico das alterações. O uso de GitHub Projects foi proposto na sprint 1; a configuração do quadro permanece a confirmar.
