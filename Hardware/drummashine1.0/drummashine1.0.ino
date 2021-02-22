#include "ardumidi.h"


#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6

#define noteON  144
#define noteOFF 128

#define MIDI_C            60
#define MIDI_D            62
#define MIDI_E            64
#define MIDI_F            65
#define MIDI_G            67
#define MIDI_A            69
#define MIDI_B            71


const int PIN_ARRAY[5]={PIN_2,PIN_3, PIN_4,PIN_5,PIN_6};
const byte MIDI_NOTE[5] = {MIDI_C,MIDI_D,MIDI_E,MIDI_F,MIDI_G};

int velocity = 100;
void MIDI_OUT(int note, int MIDIstate,  int velocity, int channel){
  
//  Serial.write(MIDIstate);
//  Serial.write(velocity);
//  Serial.write(note);
//  
  if (MIDIstate == noteON){
       midi_note_on(channel, note, velocity);
    }
  
   midi_note_off(channel, note, velocity);
     
  }
                        
void buttonClick(const int PIN_ARRAY[5]){
      int buttonState =0;
       for (int i=0 ; i<5 ; i++){
            buttonState = digitalRead(PIN_ARRAY[i]);
              if (buttonState == HIGH){
                int onRelease = 0;
//                Serial.print("Button ");
//                Serial.print(PIN_ARRAY[i]);
//                Serial.print(" IN \n");
                 // MIDI_OUT(MIDI_NOTE[i],noteON,100,0);
                  // midi_note_on(0, MIDI_NOTE[i], 100);

                  byte noteOnStatus = 144; 
                  byte noteNumber = 60; //Middle C
                  byte velocity = 100;
                  Serial.write(noteOnStatus); 
                  Serial.write(noteNumber);
                  Serial.write(velocity);
                  
 
                  onRelease = digitalRead(PIN_ARRAY[i]);
                  
                  if (onRelease == LOW){
//                      Serial.print("Button ");
//                      Serial.print(PIN_ARRAY[i]);
//                      Serial.print(" OUT \n");
                        //MIDI_OUT(MIDI_NOTE[i],noteOFF,100,0);
                        midi_note_off(0, MIDI_NOTE[i], 100);
                    }
                
                break;
             }
        }
  }

void setup() {
    Serial.begin(31250);
    pinMode(PIN_2, INPUT);
    pinMode(PIN_3, INPUT);
    pinMode(PIN_4, INPUT);
    pinMode(PIN_5, INPUT);
    pinMode(PIN_6, INPUT);
//    Serial.begin(9600);
//    Serial.begin(115200);
//  
    
}

void loop() {
   buttonClick(PIN_ARRAY);
    
}
