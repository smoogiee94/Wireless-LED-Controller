#define D0 7
#define D3 12
//#define D4 11
#define D5 13
#define D7 15
#define D8 16
#define D9 17
#define D10 18
#define redPin 10
#define greenPin 11
#define bluePin 9
#define flashSpeed 500
#define fadeSpeed 15

//Brightness is inversed
int defaultBrightness = 255;
int brightness = 0;
int redValue = 255;
bool redFlag = false;
int greenValue = 255;
bool greenFlag = false;
int blueValue = 255;
bool blueFlag = false;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), increaseBrightness, RISING);
  attachInterrupt(digitalPinToInterrupt(3), decreaseBrightness, RISING);
  
  pinMode(D0, INPUT);
  pinMode(D3, INPUT);
  pinMode(D5, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);
}

void loop() {
  digitalWrite(19, HIGH);
  //ON
  if (digitalRead(D0) == HIGH){

    //Fade Colors
    if (digitalRead(D3) == HIGH){
      //Start on blue
      redValue = 0;
      greenValue = 0;
      blueValue = defaultBrightness - brightness;
      writePins();

      //fade to violet
      for (redValue = 0; redValue < defaultBrightness - brightness && digitalRead(D3) == HIGH && digitalRead(D0) == HIGH; ++redValue){
        writePins();
        delay(fadeSpeed);
      }

      //fade to red
      for (blueValue = defaultBrightness - brightness; blueValue > 0 && digitalRead(D3) == HIGH && digitalRead(D0) == HIGH; --blueValue){
        writePins();
        delay(fadeSpeed);
      }

      //fade to yellow
      for (greenValue = 0; greenValue < defaultBrightness - brightness && digitalRead(D3) == HIGH && digitalRead(D0) == HIGH; ++greenValue){
        writePins();
        delay(fadeSpeed);
      }

      //fade to green
      for (redValue = defaultBrightness - brightness; redValue > 0 && digitalRead(D3) == HIGH && digitalRead(D0) == HIGH; --redValue){
        writePins();
        delay(fadeSpeed);
      }

      //fade to teal
      for (blueValue = 0; blueValue < defaultBrightness - brightness && digitalRead(D3) == HIGH && digitalRead(D0) == HIGH; ++blueValue){
        writePins();
        delay(fadeSpeed);
      }

      //fade to blue
      for (greenValue = defaultBrightness - brightness; greenValue > 0 && digitalRead(D3) == HIGH && digitalRead(D0) == HIGH; --greenValue){
        writePins();
        delay(fadeSpeed);
      }
    }
    
    //Flash Random while On
    int randomColor = 0;
    while(digitalRead(D5) == HIGH && digitalRead(D0) == HIGH){
      int previousColor = randomColor;
      while(previousColor == randomColor){
        randomColor = random(7);
      }
      switch (randomColor){

        //Blue
        case 0: redValue = 0;
                greenValue = 0;
                blueValue = defaultBrightness - brightness;
                break;
        //Violet              
        case 1: redValue = defaultBrightness - brightness;
                greenValue = 0; 
                blueValue = defaultBrightness - brightness;
                break;
        //Red
        case 2: redValue = defaultBrightness - brightness;
                greenValue = 0;
                blueValue = 0;
                break;
        //Yellow
        case 3: redValue = defaultBrightness - brightness;
                greenValue = defaultBrightness - brightness;
                blueValue = 0;
                break;
        //Green
        case 4: redValue = 0;
                greenValue = defaultBrightness - brightness;
                blueValue = 0;
                break;
        //Teal
        case 5: redValue = 0;
                greenValue = defaultBrightness - brightness;
                blueValue = defaultBrightness - brightness;
                break;
        //White
        default: redValue = defaultBrightness - brightness;
                 greenValue = defaultBrightness - brightness;
                 blueValue = defaultBrightness - brightness;
                 break;
      }
      writePins();
      delay(flashSpeed);
    }

    //Red
    if (digitalRead(D7) == HIGH){
      redValue = defaultBrightness - brightness;
      greenValue = 0;
      blueValue = 0;
    } 

    //Green
    else if (digitalRead(D8) == HIGH){
      redValue = 0;
      greenValue = defaultBrightness - brightness;
      blueValue = 0;
    }

    //Blue
    else if (digitalRead(D9) == HIGH){
      redValue = 0;
      greenValue = 0;
      blueValue = defaultBrightness - brightness;
    }

    //White
    else if (digitalRead(D10) == HIGH){
      redValue = defaultBrightness - brightness;
      greenValue = defaultBrightness - brightness;
      blueValue =  defaultBrightness - brightness;
    }

    //Default color is white
    else{
      redValue = 255;
      greenValue = 255;
      blueValue = 255;
    }
    writePins();
  }
  //OFF
  else{
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}

void writePins(){
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void decreaseBrightness(){
  brightness + 50 <= 200 ? brightness += 50 : brightness = brightness; //50 * 4 + 55 = 255. This gives us 4 different brightness levels
}

void increaseBrightness(){
  brightness - 50 >= 0 ? brightness -= 50 : brightness = brightness;
}

