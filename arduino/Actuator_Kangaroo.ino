// Kangaroo Name: K1
// Tuned for: Linear Actuator with feedback
// Load: No load
// Motor Driver: Sabertooth 2x25
// Absolute range: [100, 4494]
// Safe range: [143, 4450]

#include <SoftwareSerial.h>
#include <Kangaroo.h>
#define TX_PIN 11
#define RX_PIN 10
// Kangaroo might not function properly with the power supply device because the power drawn isn't stable, battery work just fine

// Independent mode channels on Kangaroo are, by default, '1' and '2'.
SoftwareSerial  SerialPort(RX_PIN, TX_PIN);
KangarooSerial  K(SerialPort);
KangarooChannel K1(K, '1');
KangarooChannel K2(K, '2');
KangarooStatus absP;
long Pos;
long lastPos;
long maximum;
long minimum;
int Speed = 500;
KangarooStatus LA_status;

void aSetup()
{
	SerialPort.begin(9600);
	SerialPort.listen();

	K1.start();
	K1.home().wait();
	minimum = K1.getMin().value();
	maximum = K1.getMax().value();
}

void aLoop()
{
	if (Pos != lastPos) {
		K1.p(Pos, Speed);
		lastPos = Pos;
	}
	LA_status = K1.getP();
	if (LA_status.done())
		K1.powerDown();
	
	//Serial.println("Min :"+ String(minimum)+ " Max :" + String(maximum) + " Current; "+ String(absP.value()));

//	Serial.println(abs.value());

//	K1.p(maximum);
	//{@Plot.Position.SetPosition.Red Pos}, {@Plot.Position.CurrentPosition.Green absP.value()}, Pos is {Pos =?}, Speed is {Speed =?}
	
}

int getPos() {

	return K1.getP().value();
}