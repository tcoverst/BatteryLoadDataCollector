#include <SparkFunBQ27441.h>
const unsigned int BATTERY_CAPACITY = 1200; // e.g. 850mAh battery


int MOS1 = 2;
int MOS2 = 3;
int MOS3 = 4;
int MOS4 = 5;
int MOS5 = 6;
int MOS6 = 7;
int MOS7 = 8;
int MOS8 = 9;
unsigned long time_now = 0;
int period = 5000;
unsigned long i = 0;

void setupBQ27441(void)
{
  // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
  // connected and communicating.
  if (!lipo.begin()) // begin() will return true if communication is successful
  {
  // If communication fails, print an error message and loop forever.
    Serial.println("Error: Unable to communicate with BQ27441.");
    Serial.println("  Check wiring and try again.");
    Serial.println("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  Serial.println("Connected to BQ27441!");
  
  // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
  // of your battery.
  lipo.setCapacity(BATTERY_CAPACITY);
  Serial.println("[MOSFET, state-of-charge (%), battery voltage (mV), average current (mA), full capacity (mAh), remaining capacity (mAh), average power draw (mW), state-of-health (%)]");
  
}

void printBatteryStats()
{
  // Read battery stats from the BQ27441-G1A
  unsigned int soc = lipo.soc();  // Read state-of-charge (%)
  unsigned int volts = lipo.voltage(); // Read battery voltage (mV)
  int current = lipo.current(AVG); // Read average current (mA)
  unsigned int fullCapacity = lipo.capacity(FULL); // Read full capacity (mAh)
  unsigned int capacity = lipo.capacity(REMAIN); // Read remaining capacity (mAh)
  int power = lipo.power(); // Read average power draw (mW)
  int health = lipo.soh(); // Read state-of-health (%)

  // Now print out those values:
  
  String toPrint = "[" + String(i) + ", ";
  toPrint += String(soc) + ", ";
  toPrint += String(volts) + ", ";
  toPrint += String(current) + ", ";
  toPrint += String(capacity) + ", ";
  toPrint += String(fullCapacity) + ", ";
  toPrint += String(power) + ", ";
  toPrint += String(health) + "], ";
  
  Serial.println(toPrint);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupBQ27441();
  
  pinMode(MOS1, OUTPUT);
  pinMode(MOS2, OUTPUT);
  pinMode(MOS3, OUTPUT);
  pinMode(MOS4, OUTPUT);
  pinMode(MOS5, OUTPUT);
  pinMode(MOS6, OUTPUT);
  pinMode(MOS7, OUTPUT);
  pinMode(MOS8, OUTPUT);

  digitalWrite(MOS1, LOW);  
  digitalWrite(MOS2, LOW);   
  digitalWrite(MOS3, LOW);   
  digitalWrite(MOS4, LOW);   
  digitalWrite(MOS5, LOW);   
  digitalWrite(MOS6, LOW);   
  digitalWrite(MOS7, LOW);   
  digitalWrite(MOS8, LOW);  

}

void loop() {
  // put your main code here, to run repeatedly:
  if (i%8 == 0){
    digitalWrite(MOS1, HIGH);  
  }
  else if (i%8 == 1){
    digitalWrite(MOS2, HIGH); 
  }
  else if (i%8 == 2){
    digitalWrite(MOS3, HIGH);  
  }
  else if (i%8 == 3){
    digitalWrite(MOS4, HIGH); 
  }
  else if (i%8 == 4){
    digitalWrite(MOS5, HIGH); 
  }
  else if (i%8 == 5){
    digitalWrite(MOS6, HIGH); 
  }
  else if (i%8 == 6){
    digitalWrite(MOS7, HIGH); 
  }
  else if (i%8 == 7){
    digitalWrite(MOS8, HIGH);      
  }

  for (int cyclesStatus = 0; cyclesStatus < 5; cyclesStatus++) {
    time_now = millis();
    while(millis() < time_now + period){
        //wait approx. [period] ms    
    } 
    printBatteryStats();

  }
  
  
  digitalWrite(MOS1, LOW);  
  digitalWrite(MOS2, LOW);   
  digitalWrite(MOS3, LOW);   
  digitalWrite(MOS4, LOW);   
  digitalWrite(MOS5, LOW);   
  digitalWrite(MOS6, LOW);   
  digitalWrite(MOS7, LOW);   
  digitalWrite(MOS8, LOW);   
  i++;
  if (i == 8){
    i = 0;
  }
  
}
