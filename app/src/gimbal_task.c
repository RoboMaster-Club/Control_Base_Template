#include "gimbal_task.h"
#include "dji_motor.h"
#include "robot.h"
#include "remote.h"
#include "imu_task.h"
#include "user_math.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
extern IMU_t g_imu;
DJI_Motor_Handle_t *g_yaw, *g_pitch;
Gimbal_Target_t g_gimbal_target;

void Gimbal_Task_Init()
{
    Motor_Config_t yaw_motor_config = {
        .can_bus = 1,
        .speed_controller_id = 3,
        .offset = 3690,
        .control_mode = POSITION_CONTROL,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .use_imu_feedback = 1,
        .imu_dir = 1,
        .angle_feedback = &g_imu.rad.yaw,
        .velocity_feedback = &(g_imu.bmi088_raw.gyro[2]),
        .angle_pid =
            {
                .kp = 20000.0f,
                .kd = 1000000.0f,
                .output_limit = GM6020_MAX_CURRENT,
            },
        .velocity_pid =
            {
                .kp = 500.0f,
                .output_limit = GM6020_MAX_CURRENT,
            },
    };

    Motor_Config_t pitch_motor_config = {
        .can_bus = 2,
        .speed_controller_id = 2,
        .offset = 1500,
        .use_imu_feedback = 1,
        .imu_dir = -1,
        .angle_feedback = &g_imu.rad.roll, // pitch
        .velocity_feedback = &(g_imu.bmi088_raw.gyro[0]),
        .control_mode = VELOCITY_CONTROL | POSITION_CONTROL,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .angle_pid =
            {
                .kp = 30.0f,
                .kd = 180.0f,
                .output_limit = 50.0f,
            },
        .velocity_pid =
            {
                .kp = 4500.0f,
                .ki = 1.2f,
                .integral_limit = 4000.0f,
                .output_limit = GM6020_MAX_CURRENT,
            },
    };

    g_yaw = DJI_Motor_Init(&yaw_motor_config, GM6020);
    g_pitch = DJI_Motor_Init(&pitch_motor_config, GM6020);
}

void Gimbal_Ctrl_Loop()
{
    if (g_robot_state.enabled)
    {

        g_gimbal_target.pitch -= g_remote.controller.right_stick.y / 100000.0f;
        g_gimbal_target.yaw_angle -= g_remote.controller.right_stick.x / 100000.0f;
        __MAX_LIMIT(g_gimbal_target.pitch, -0.45f, 0.5f);
        DJI_Motor_Set_Angle(g_pitch, g_gimbal_target.pitch);
        DJI_Motor_Set_Angle(g_yaw, g_gimbal_target.yaw_angle);
    }
    else
    {
        DJI_Motor_Disable(g_yaw);
        DJI_Motor_Disable(g_pitch);
    }
}
