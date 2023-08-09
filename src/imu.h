
#ifndef IMU_H
#define IMU_H

#include <LSM6DSLSensor.h>

class IMU
{
    public:
        IMU(); //default
        IMU(LSM6DSLSensor *imu):_lsm(imu)
        {
            _lsm->begin();
            this->_gyr_calibrated = false;
        };

        void init_gyro();
        void init_acc(){_lsm->Enable_X();};
        void update_ang_pos();
        void get_ang_pos(float angles[3])
        {
            angles[0] = this->_theta_x;
            angles[1] = this->_theta_y;
            angles[2] = this->_theta_z;
        }
        void is_gyr_calibrated(float offsets[4])
        {
            offsets[0] = this->_gyr_calibrated;
            offsets[1] = this->_offset_gx;
            offsets[2] = this->_offset_gy;
            offsets[3] = this->_offset_gz;
        }

    private :
        int32_t _acc[3];
        int32_t _gyr[3];
        LSM6DSLSensor *_lsm;

        bool _gyr_calibrated;
        
        float _offset_gx;
        float _offset_gy;
        float _offset_gz;

        float _theta_x;
        float _theta_y;
        float _theta_z;

        uint32_t _last_millis;        
};

#endif //IMU_H