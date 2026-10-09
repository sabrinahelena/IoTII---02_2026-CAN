# Testes do projeto

## Evidências disponíveis

Foram recebidos código-fonte e documentação dos campos. Esses materiais demonstram a lógica implementada, mas não comprovam gravação no Firebase, precisão dos sinais ou integração do aplicativo. Não foram enviados logs, capturas de gravações ou resultados de testes nesta atualização.

A compilação e a execução do firmware no hardware não foram realizadas nesta preparação. O aplicativo está em desenvolvimento no Android Studio.

## Plano de validação

| Teste | Resultado esperado | Situação |
| --- | --- | --- |
| Compilação | Dependências e tipos do cliente SSL resolvidos | Pendente |
| Leitura CAN | Receber IDs esperados com o hardware configurado | Evidência pendente |
| Sinais do veículo | Comparar RPM, velocidade, temperatura, combustível e freio com referência | Evidência pendente |
| Estados/timeout | Verificar partida, funcionamento, RPM zero e perda de heartbeat | Evidência pendente |
| Firebase | Confirmar atualização de atual e novas entradas no histórico | Evidência pendente |
| Falha Wi-Fi/Firebase | Registrar comportamento e perda de amostras | Pendente |
| NTP indisponível | Identificar timestamp inválido | Pendente |
| Autorização | Negar acessos indevidos conforme regras do banco | Regras e teste pendentes |
| Certificado TLS | Validar servidor com configuração apropriada | Correção e teste pendentes |
| Aplicativo | Executar e consultar informações | Em desenvolvimento |
| Ar-condicionado | Confirmar sinal no veículo | Não testado, conforme documentação |

Para cada teste, registrar data, ambiente, procedimento, resultado observado e evidência sem credenciais. A mensagem “telemetria enviada” ocorre após agendar operações: conferir callbacks e registros do banco antes de afirmar sucesso.
