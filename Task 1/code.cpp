// Takes in height data through serial instead of any sensor
//
const int totalReads=10; //Number of readings to average
int readings[totalReads]; //Array of readings
int input; 
long heights[2]; //last two heights to compare
int readnums=0; //Number of readings taken
int total;
long avg;
int index=0;
void setup()
{
   Serial.begin(9600);
  heights[0]=0; //Initializing first height as 0
}

void loop()
{
  while(Serial.available() == 0) { } //Wait for serial input. Not required if sensor was present
        input = Serial.parseInt();
  		readnums++;
//Serial.print(input);
  Serial.print("\n");

  Serial.print("Current height:");
  heights[1]=average(); //Add new height to array
  Serial.print(heights[1]); 
  Serial.print("\n");
  State();
}

long average(){ //moving average function

  if (readnums<=totalReads){ //add new data since array not fully filled
    readings[index]=input;
    total=total+readings[index];;
    avg=total/(index+1);}
  else{ //remove oldest data and add new data in place
    total=total-readings[index];
    readings[index]=input;
    total=total+readings[index];
    avg=total/totalReads;}
    index++;
  if (index>totalReads-1){ //reset index back to  0 if array filled
    index=0;}
   return avg;
  }

void State(){ // Checking state of cansat
  int delta;
  delta=heights[1]-heights[0]; //height difference between last two readings
  if(delta>30){
    Serial.print("Ascent");}
    else if (delta<-10){
      Serial.print("Descent");}
      else{
        Serial.print("Stationary");}
   Serial.print("\n");
   heights[0]=heights[1]; //Making the latest height the reference height
      }
  
