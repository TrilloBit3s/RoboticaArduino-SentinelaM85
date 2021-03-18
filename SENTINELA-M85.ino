//SENTINELA-M85
//Michael Moraes Sabino
//estuartyy@gmail.com
//27/05/2015 

//inclusão das bibliotecas
  #include <Servo.h>//biblioteca para o servo motor.  
  #include <NewPing.h>//biblioteca para o sonar.
  
  //posicao sonar
  #define TRIGGER_PIN A0//acionar o pino do sensor de ultra-som .
  #define ECHO_PIN A1//ecoar pino no sensor de ultra-som .
  #define MAX_DISTANCE 130//distância máxima do sensor é 400-500cm.
   
  NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  
  Servo myservo;//criar o objeto servo. Para controlar um servo.
  
  int distance = 0;//distância inicializada em 0.
  int stepsize = 3;//tamanho do passo 3.
  int detect = 0;//detecção inicializada em 0.
  int pos = 0;//variável para armazenar a posição do servo. 
  int port = 0;//variável para armazenar os dados do analógico.
  const int led =  8;//pino do led 8.
  const int botao = 4;//pino do botão 4.
  int estadoBotao = 0;//variável para armazenar a posição do botão.
    
  void setup(){ 
    Serial.begin(115200);//monitor serial em 115200. 
    myservo.attach(10);//atribui o servo no pino 9 do objeto do servo.
    pinMode(led,OUTPUT);//pino do led desligado. 
    pinMode(botao,INPUT);//pino do botão ligado.
  } 

  void loop(){ 
  
   //comente ou descomente para inicializar qualquer uma das das funçoes.
    
         // detectarPosicaoSonar();//faz com que a arma se movimente pelo sonar.  
          automovimentar();//faz com que a arma se movimente em varredura.
          Controle();
         Serial.println(distance);//mostra na tela os dados da distância.
  } 

  void automovimentar(){
    for(pos = 0; pos <= 180; pos += 1){//vai de 0 a 180 graus em incrementos de 1 grau.                                   
      myservo.write(pos);//servo dizer para ir para a posição em ' pos ' variável.
      Atirar(120);
      delay(15);//espera 15ms para o servo para alcançar a posição.
       } 
          for(pos = 180; pos>=0; pos-=1){//vai de 180 graus para 0 graus.                                
            myservo.write(pos);//servo vai para a posição em ' pos ' variável. 
            Atirar(120);//Atira em 60cm.
            delay(15);// espera 15ms para o servo para alcançar a posição. 
            } 
        }

  void Controle(){    
    Serial.begin(115200);//mostra na tela dados do controle.
    int val = analogRead(A2);//val recebe dados do joystick A2.
    port = map(val,0,1023,0,180);//mapeia os dados (Quase uma regra de 3).    
    myservo.write(port);//servo movimenta com dados mapeados do joystick.
    Serial.println(estadoBotao);//mostra na tela dados do botão. 
   }

  void Atirar(int num){
    unsigned int uS = sonar.ping(); 
    distance = uS / US_ROUNDTRIP_CM;//ping em microssegundos (EUA).
        if (distance > num){ 
          digitalWrite(led,HIGH);//fazer o led acender.
          int MotorPin = 11;//pino do motor 11.
          pinMode(MotorPin, OUTPUT);//saida do pino do motor.
          digitalWrite(MotorPin, HIGH);//motor ligado.
          delay(500);//atraso no tempo de meio segundo.
          digitalWrite(MotorPin, LOW);//motor desligado.
         } 
          else
         {
           digitalWrite(led,LOW);//led desligado
         } 
     }
  
  void detectarPosicaoSonar(){
      delay(30);//29ms deve ser o menor atraso entre pings.
      unsigned int uS = sonar.ping(); 
      distance = uS / US_ROUNDTRIP_CM;//ping em microssegundos (EUA).
         if (distance <= 4) {    
              detect = 0;//Nada detectado        
              pos = pos + stepsize;//Move esquerda
              myservo.write(pos);
                  if (pos > 200){
                    pos = 200;
                  }
              Atirar(120);
            }
            else
            {
                detect = 1;//Algo nao detectada
                pos = pos - stepsize;//Mover para a direita   
                myservo.write(pos);
                    if (pos < 20) {
                      pos = 20;
                    }
                 Atirar(120);
              }
      }//finaliza programa
