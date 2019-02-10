#include <CurieIMU.h>
#include <MadgwickAHRS.h>
#include <math.h>

Madgwick filter;
unsigned long microsPerReading, microsPrevious;
float accelScale, gyroScale;

float prevYaw[11];
float prevPitch[11];
float prevRoll[11];
float diffPitch=0.0;
float diffRoll=0.0;
float diffYaw=0.0;
int p=0;
int k=0;
int q=0;
int w=0;
int e=0;


float findSD(float prevValues[]) {
  float total=0.0;
  float totalSquared=0.0;
  for (int x=0;x<11;x++){
    total=total+prevValues[x];
  }
  for(int x=0;x<11;x++){
    totalSquared=totalSquared+(prevValues[x]*prevValues[x]);
  }
  float StandardDev;
  StandardDev=(totalSquared/11)-(((total)/11)*((total)/11));
  return StandardDev;
}

float findD(float prevValues[]){
  float total=0.0;
  for(int i=0;i<10;i++){
    total=total+prevValues[i];
  }
  total=total/10;
  return prevValues[10]-total;
}



void setup() {
  Serial.begin(9600);

  // start the IMU and filter
  CurieIMU.begin();
  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  filter.begin(25);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);

  // initialize variables to pace updates to correct rate
  microsPerReading = 2000000/ 25;
  microsPrevious = micros();
  
  
}

void loop() {
 
  int aix, aiy, aiz;
  int gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
  unsigned long microsNow;

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

    // read raw data from CurieIMU
    CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);

    // update the filter, which computes orientation
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    
    if(p<11){
      prevYaw[p]=heading;
      prevRoll[p]=roll;
      prevPitch[p]=pitch;
    }
    else{
      if(k<1)
      {
        diffPitch=findSD(prevPitch);
        if(findSD(prevYaw)<0)
        {
          diffYaw=(-1)*findSD(prevYaw);
        }
        else
        {
          diffYaw=findSD(prevYaw);
        }
        diffRoll=findSD(prevRoll);
        k=k+1;
      }
      else
      {
      }
      float yaw = findSD(prevYaw)-diffYaw;
      float pitch = findSD(prevPitch)-diffPitch;
      if(yaw>35 && findD(prevYaw)<0)
      {
        Serial.println("LEFT");
        q=1;
      }
      else if(yaw<35 && q==1)
      {
        q=0;
      }
      if(yaw>35 && findD(prevYaw)>0)
      {
        Serial.println("RIGHT");
        q=1;
      }
      if(yaw<35 && q==1)
      {
        q=0;
      }
      if(pitch>35 && findD(prevPitch)>0)
      {
        Serial.println("DOWN");
        w=1;
      }
      if(pitch<35 && w==1)
      {
        w=0;
      }
      if(pitch>35 && findD(prevPitch)<0)
      {
        Serial.println("UP");
        w=1;
      }
      if(pitch<35 && w==1)
      {
        w=0;
      }
      p=0;
      
    }
 
    /*
    Serial.print(heading);
    Serial.print(";");
    Serial.print(pitch);
    Serial.print(";");
    Serial.println(roll);
    */

    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
    p=p+1;
  }
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  float g = (gRaw * 250.0) / 32768.0;
  return g;
}
