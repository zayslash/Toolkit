const int x1 = A0;
const int y2 = A1;
const int x2 = A2;
const int y1 = A3;

byte noteON = 144;

void setup()
{
Serial.begin(9600);
}

int readX()
{
pinMode(y1, INPUT);
pinMode(x2, OUTPUT);
pinMode(y2, INPUT);
pinMode(x1, OUTPUT);
digitalWrite(x2, LOW);
digitalWrite(x1, HIGH);
delay(5); //pause to allow lines to power up
return analogRead(y1);
}


int readY()
{
pinMode(y1, OUTPUT);
pinMode(x2, INPUT);
pinMode(y2, OUTPUT);
pinMode(x1, INPUT);
digitalWrite(y1, LOW);
digitalWrite(y2, HIGH); 
delay(5); //pause to allow lines to power up
return analogRead(x2);
}


void loop()
{
  
int y = readY();
int x = readX();

if(x !=0 || y != 0)
{
    Serial.print("X: "); Serial.print(x);
    Serial.print("Y: "); Serial.println(y);
    byte note = map(x, 0, 1023, 0, 127);
    byte velocity = map(y, 0, 1023, 0, 127);
    MIDImessage(noteON, note, velocity);
    delay(500);
    MIDImessage(noteON, note, 0);
  }
}

void MIDImessage(byte command, byte data1, byte data2) 
{
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}
