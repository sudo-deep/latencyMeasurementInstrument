const int buttonPin = 2;      // Pin where the button is connected
const int micPin = A0;        // Pin where the microphone sensor is connected
const int threshold = 10;    // Threshold value for detecting audio signal
const int errorThreshold = 30; // (ms) Sometimes the audio will have glitches, causing false positives, hence a minimum latency approximate is set to avoid printing these values
// Suggestion: Set errorThreshold to the minimum delay of the frame input, eg: 30FPS: 1000/30 --> 33ms

unsigned long buttonPressTime;
unsigned long audioDetectTime;
bool buttonPressed = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  Serial.begin(9600);               // Initialize serial communication
}

void loop() {
  // Check if button is pressed
  if (digitalRead(buttonPin) == LOW && !buttonPressed) {
    buttonPressTime = millis();  // Record the time when the button is pressed
    buttonPressed = true;        // Set flag to true
  }
    int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 100; ++i) {
    int val = analogRead(micPin);
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;
  // Check if audio signal is detected
  if (buttonPressed) {
//    int d = analogRead(micPin); // Read the microphone sensor value
    if (delta > threshold) {
      audioDetectTime = millis();       // Record the time when the audio is detected
      unsigned long delayTime = audioDetectTime - buttonPressTime; // Calculate delay
      
      if (delayTime > errorThreshold){  
        Serial.print("Delay between button press and audio detection: ");
      Serial.print(delayTime);
      Serial.println(" ms \n");
      }
      buttonPressed = false;            // Reset flag for next measurement
    }
  }
}
