#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

struct CameraCalibration
{
  unsigned camera_id;
  float focal_length;
  float principal_point_x;
  float principal_point_y;
  float distortion;
  float q0;
  float q1;
  float q2;
  float q3;
  float tx;
  float ty;
  float tz;
  float derived_camera_world_tx;
  float derived_camera_world_ty;
  float derived_camera_world_tz;
};

#endif