const int microphonePin = A0;
const int threshold = 10;

void setup() {
  Serial.begin(9600);
}

void loop(){
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 100; ++i) {
    int val = analogRead(microphonePin);
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;

  Serial.println(delta);
  delay(100);
  if (delta > threshold) {
    Serial.println("detected");
    delay(100);
  }
}
