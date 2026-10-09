# Banco de dados

## Firebase Realtime Database

O firmware usa uma estrutura JSON:

| Caminho | Operação | Finalidade |
| --- | --- | --- |
| /telemetria/atual | set | Substituir a amostra atual |
| /telemetria/historico | push | Adicionar amostras com chave gerada pelo Firebase |

[telemetria.example.json](telemetria.example.json) exemplifica uma amostra com valores fictícios. O histórico contém várias amostras desse formato, cada uma sob uma chave de push.

O timestamp é texto em UTC-3, não um valor Unix. O código não define identificação por veículo ou retenção do histórico.

## Acesso e segurança

Há autenticação por e-mail/senha no firmware. As regras de leitura/escrita não foram fornecidas e não se deve pressupor que estejam restritas. A integração de leitura pelo app ainda será implementada e documentada.

Detalhes dos campos: [Telemetria](../Documentacao/08-Telemetria-CAN-Firebase.md).
