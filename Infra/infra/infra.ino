// Analog pin connected to your sensor
const int xpin = A4;
const int ypin = A5;
const int uppin = 14;
const int downpin = 15;
const int rightpin = 16;
const int leftpin = 17;
int* xvector[2];
int* yvector[2];
int min, max;
int def = 1;
bool temp1, temp2, temp3, temp4;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  for (int x=0; x<2; x++){
    xvector[x] = 0;
    yvector[x] = 0;
  }
  pinMode(uppin, OUTPUT); // Set the pin as an output
  pinMode(downpin, OUTPUT); // Set the pin as an output
  pinMode(rightpin, OUTPUT); // Set the pin as an output
  pinMode(leftpin, OUTPUT); // Set the pin as an output
}

void loop() {
  def=1;

  xvector[0] = xvector[1];
  yvector[0] = yvector[1];

  // Read the analog value from the sensor
  xvector[1] = analogRead(xpin);
  yvector[1] = analogRead(ypin);

  if((xvector[0]-xvector[1])>100)
    xvector[0] = xvector[1]-1;
  if((yvector[0]-yvector[1])>100)
    yvector[0] = yvector[1]-1;
  if((xvector[1]-xvector[0])>100)
    xvector[0] = xvector[1]+1;
  if((yvector[1]-yvector[0])>100)
    yvector[0] = yvector[1]+1;

  

  if (xvector[1] > xvector[0] && abs(xvector[1]-xvector[0])>5){
    Serial.println("right");
    def = def * 2;
  }
  else if (xvector[1] < xvector[0] && abs(xvector[1]-xvector[0])>5){
    Serial.println("left");
    def = def * 3;
  }

  if (yvector[1] > yvector[0] && abs(yvector[1]-yvector[0])>5){
    Serial.println("up");
    def = def * 5;
  }
  else if (yvector[1] < yvector[0] && abs(yvector[1]-yvector[0])>5){
    Serial.println("down");
    def = def * 7;
  }

  temp1 = LOW;
  temp2 = LOW;
  temp3 = LOW;
  temp4 = LOW;

  if (def % 2 == 0){
    temp1 = HIGH;
  }
  if (def % 3 == 0){
    temp1 = HIGH;
  }
  if (def % 5 == 0){
    temp3 = HIGH;
  }
  if (def % 7 == 0){
    temp4 = HIGH;
  }

    digitalWrite(rightpin, temp1);
    digitalWrite(leftpin, temp2);
    digitalWrite(uppin, temp3);
    digitalWrite(downpin, temp4);

  Serial.print("\n\n---\n\n");

  delay(100); 
}
