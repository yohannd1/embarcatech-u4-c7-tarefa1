# Tarefa U4.C7.1

Link do vídeo: https://www.youtube.com/watch?v=D1y20AART6k

Esta tarefa envolveu o uso do PWM para controlar a rotação em um
servomotor, via simulação no Wokwi.

Inicialmente eu tive uma dificuldade com a equação de frequência, e
passei duas horas tentando encontrar uma maneira flexível de usar ela:

```
freq = clock_freq / (clock_div * (wrap + 1))
```

Mas eventualmente, depois de muito debug (utilizando em especial o
monitor Logic do simulador do Wokwi, que cria um arquivo `.vcd` que pode
ser lido pelo `pulseview`) consegui encontrar uma configuração que
gerasse um pulso a 50Hz, e que permitisse eu especificar duty cycles com
algumas casas decimais de precisão, que foi necessário para controlar
este servomotor em específico.

## Execução

Para rodar este código, é possível utilizar o CMake para a compilação.
Para simular, é recomendado usar o simulador do Wokwi pelo VSCode. Note
que desta vez este programa não recebe input nenhum.

## Teste na placa

Como a placa BitDogLab não possui um servomotor, a alternativa mais
próxima é trocar o `SERVO_PWM_PIN` para 12, que vai redirecionar o
comportamento do PWM para o azul do LED RGB que fica no meio da placa.

Como o ciclo de PWM nunca está maior que 12%, a luz ficou longe de seu
brilho máximo. Apesar disso, ainda foi possível ver que ela começou com
uma luz específica (12%), depois escureceu um pouco mais (7.35%), e
depois chegou em seu brilho mínimo (2.5%). Depois disso, quando ela
chegou no loop infinito onde o servomotor estaria rotacionando
lentamente, ela começou a mudar de brilho lentamente, indo do mínimo
para o máximo e vice-versa.
