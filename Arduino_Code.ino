/*------------------------------------------------------*/
/*           Coded by: Konredus                         */
/*           Date: May 2018                             */
/*           Instagram: @konredus                       */
/*           Youtube:   @konredus                       */
/*           Homepage: www.konredus.com                  */
/*------------------------------------------------------*/

#define trigger   2
#define echo      3
#define buzzer    5
#define maximo    60
#define minimo    10
#define frec_min  400
#define frec_max  1000

int vector[5];
int cont = 0;

/*------------------------------------------------------*/

void setup()
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
}

/*------------------------------------------------------*/

void loop()
{
  long duration, cm;

  //activo el trigger
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger, LOW);

  //espero al echo

  duration = pulseIn(echo, HIGH);
  
  //invierto la distancia
  vector[cont] = maximo - microsecondsToCentimeters(duration);
  cont++;
  if (cont > 5)
    cont = 0;

  //promedio 3 mediciones para evitar falsas mediciones

  cm = (vector[0] + vector[1] + vector[2] + vector[3] + vector[4]) / 5;
  Serial.println(cm);  //envio por puerto serial para chequear

  //aca es donde defino los maximos
  if ( (cm < maximo) and (cm > minimo))
  {
    //dentro de la funcion map defino frecuencias maximas y minimas
    tone(buzzer, map(cm, minimo, maximo, frec_min, frec_max), 7); //emito sonido
  }
}

//funcion que me calcula tiempo en centimetros
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
