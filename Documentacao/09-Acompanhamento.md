# Acompanhamento do projeto

## Estado em 09/10/2026

A consulta ao GitHub confirmou commits com documentação da proposta e da sprint 1. Não foram encontradas issues cadastradas. O quadro GitHub Projects não foi confirmado. As tarefas abaixo são modelos para cadastro, não cards já publicados.

Não atribuir conclusão pela existência de código: registrar testes e evidências antes de encerrar as tarefas. Responsáveis e prazos serão definidos pelo grupo.

## Desenvolver aplicativo Android

Implementar o app no Android Studio para apresentar dados e histórico do veículo.

- [ ] Executar o projeto no ambiente Android.
- [ ] Registrar telas e instruções de execução.
- [ ] Exibir os campos confirmados pelo grupo.
- [ ] Tratar ausência de dados e erros.

## Salvar informações CAN no Firebase

Validar a persistência implementada no firmware.

- [ ] Compilar e executar o firmware com configuração local.
- [ ] Comprovar set em /telemetria/atual e push em /telemetria/historico.
- [ ] Registrar resultados dos callbacks e amostras sem credenciais.
- [ ] Definir regras de escrita e testar acessos permitidos/negados.

## Disponibilizar informações para consulta

Definir o acesso do app ao Firebase; API própria não está confirmada.

- [ ] Definir a estratégia de autenticação e consulta.
- [ ] Documentar o contrato dos campos.
- [ ] Configurar e testar regras de leitura.
- [ ] Registrar exemplo de consulta sem identificadores privados.

## Coletar informações pelo aplicativo

Integrar o app à consulta dos dados do Firebase.

- [ ] Consultar estado atual e histórico.
- [ ] Apresentar os dados nas telas.
- [ ] Tratar carregamento, falhas e falta de dados.
- [ ] Registrar evidência do fluxo integrado.

## Documentar projeto e sprints

Manter código, arquitetura, campos e evidências coerentes.

- [ ] Publicar firmware sem configurações privadas e anexar documentação técnica.
- [ ] Registrar limitações de TLS, sinais não testados e testes pendentes.
- [ ] Atualizar evidências e resultados da sprint 2.
- [ ] Cadastrar issues e organizar quadro com responsáveis definidos pelo grupo.

## Pendência técnica de segurança

Corrigir e testar validação do certificado TLS antes de considerar a segurança de comunicação concluída. Documentar regras do Firebase. Esses itens também devem ser acompanhados pelo grupo.
