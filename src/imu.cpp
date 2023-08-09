#include "imu.h"

void IMU::init_gyro()
{
    _lsm->Enable_G();
    delay(500);
    if(!this->_gyr_calibrated)
  {
    this->_offset_gx = 0.0;
    this->_offset_gy = 0.0;
    this->_offset_gz = 0.0;
    int n = 10;
    for(int i=0 ; i<n ; i = i+1)
    {
      _lsm->Get_G_Axes(this->_gyr);
      this->_offset_gx += (float)_gyr[0];
      this->_offset_gy += (float)_gyr[1];
      this->_offset_gz += (float)_gyr[2];
    }

    this->_offset_gx = (float)(this->_offset_gx/n);
    this->_offset_gy = (float)(this->_offset_gy/n);
    this->_offset_gz = (float)(this->_offset_gz/n);
    this->_gyr_calibrated = true;

  }

  //temporary
  this->_theta_x = 0.0 ; 
  this->_theta_y = 0.0 ; 
  this->_theta_z = 0.0 ; 

}

void IMU::update_ang_pos()
{
    _lsm->Get_G_Axes(this->_gyr);
    uint32_t temp_millis = millis();
    double delta_time = static_cast<double>(temp_millis - this->_last_millis);
    this->_last_millis = temp_millis;

    this->_theta_x = this->_theta_x + (((float)_gyr[0]-this->_offset_gx)/1000)*(delta_time/1000);
    this->_theta_y = this->_theta_y + (((float)_gyr[1]-this->_offset_gy)/1000)*(delta_time/1000);
    this->_theta_z = this->_theta_z + (((float)_gyr[2]-this->_offset_gz)/1000)*(delta_time/1000);
    
}

