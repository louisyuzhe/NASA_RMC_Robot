int X_PIN = A0;
int Y_PIN = A1;
int Z_PIN = A2;
double aX = 0;
double aY = 0;
double aZ = 0;

double uX = 0;
double vX = 0;

long lastTime=0;


void setup() {
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(Z_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  aX = analogRead(X_PIN);
  aY = analogRead(Y_PIN);
  aZ = analogRead(Z_PIN);
  aX = 9.81*((5*aX/1023)-1.66)/0.333;
  aY = 9.81*((5*aY/1023)-1.66)/0.333;
  aZ = 9.81*((5*aZ/1023)-1.66)/0.333;
  long newTime=millis();
  if(abs(aX) < .9)
  aX=0;
  vX = vX + aX * (newTime - lastTime)/1000;

lastTime=newTime;
  Serial.println(aX); 
}

