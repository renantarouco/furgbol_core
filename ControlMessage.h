class ControlMessage {
  uint8 robotID; // 0 -> 255
  float vx, vy; // -floatMin -> +floatMax
  float av; // -floatMin -> +floatMax
  int8 dribblerVel;
  uint8 kickPower;
}



class RobotFeedback {
  uint8 robotID;
  uint8 battery;
  float vx, vy, vz;
  float ax, ay, az;
  float yaw;
  
}
