# Telemetria CAN e Firebase

Base: código enviado por Gabriela e [documentação técnica do grupo](Anexos/documentacao_telemetria_veicular_can_firebase.pdf). Os índices dos bytes abaixo começam em zero.

## Sinais interpretados

| Campo | ID CAN | Origem e interpretação implementada |
| --- | --- | --- |
| painel.ignicao | 0x3C3 | Byte 0 igual a 0x20 ou 0xA0; expira após 2,5 s |
| painel.combustivel_pct | 0x6E3 | Byte 4; valores acima de 100 ignorados |
| motor.rpm | 0x281 | ((byte 4 & 0x3F) << 8) \| byte 5 |
| motor.velocidade_kmh | 0x180 | bruto = (byte 1 << 8) \| byte 2; zero até 24576; acima disso, (bruto - 24576)/16, com divisão inteira |
| motor.tempArref_c | 0x380 | Byte 3 sem conversão adicional |
| motor.freio | 0x180 | Bit 7 do byte 0 |
| motor.status | Derivado | desligado, partida ou em_funcionamento |

Os IDs, escalas e unidades correspondem à interpretação do código enviado, não a uma tabela universal para qualquer veículo. A temperatura é tratada como °C na implementação; a escala precisa ser confirmada no veículo.

## Ar-condicionado: não testado

O código também calcula `motor.arCondicionado` a partir do bit 7 do byte 2 do ID 0x281 e envia esse campo ao Firebase. O PDF o omite por falta de testes. A versão publicada preserva esse comportamento, mas o campo não deve ser apresentado como validado.

## Formato e armazenamento

- `timestamp`: texto DD/MM/AAAA HH:MM:SS, com NTP em UTC-3.
- `/telemetria/atual`: substituição pelo estado mais recente via set.
- `/telemetria/historico`: novas amostras por push.
- Intervalo de envio: 1 segundo, quando o Firebase está pronto.
- Monitor Serial: aproximadamente 250 ms.
- [JSON ilustrativo completo](../DB/telemetria.example.json), com valores fictícios.

## Regras de estado

- O código inicia o estado partida ao detectar passagem de RPM zero para RPM ≥ 300, quando não está em partida.
- Após mais de 2 s em partida com leitura positiva, classifica como em_funcionamento.
- RPM zero por mais de 1,2 s leva ao estado desligado.
- Mais de 2,5 s sem heartbeat válido desativa a ignição.
- Ignição desligada ou timeout de RPM acima de 1,5 s após algum pacote zera RPM/velocidade e desativa freio/ar-condicionado.
- Temperatura e combustível não são zerados por esse timeout.

Ausência de comunicação pode ser classificada como desligamento. Valores mantidos em memória não comprovam leitura recente. Não há indicadores de frescor por sinal nesta versão.
