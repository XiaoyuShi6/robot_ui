//
// Created by leo on 18-6-1.
//

#ifndef PROJECT_ROBOT_UI_H
#define PROJECT_ROBOT_UI_H

#include <ros/ros.h>
#include <rviz/panel.h>
#include <ros/console.h>
#include <geometry_msgs/Twist.h>
#include <pan_tilt_driver/PanTiltCmd.h>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

namespace robot_ui
{
    class RobotBaseUI : public rviz::Panel
    {
        Q_OBJECT
    public:
        RobotBaseUI(QWidget *parent = 0);

        //重载rviz::Panel中的函数，用于保存、加载配置文件中的数据，在这个plugin中，数据就是topic的名称
        virtual void load(const rviz::Config &config);
        virtual void save(rviz::Config config) const;

    protected Q_SLOTS:
        void sendsignal();    //发送角度速度值
        void update_yaw();    //偏航
        void update_pitch();  //俯仰
        void update_speed();//速度

    protected:
        ros::NodeHandle node;
        ros::Publisher robot_base_ui_pub;
        ros::Publisher pan_tilt_pub;

        QPushButton *move_forward_button;
        QPushButton *move_back_button;
        QPushButton *move_left_button;
        QPushButton *move_right_button;
        QPushButton *turn_left_button;
        QPushButton *turn_right_button;

        QPushButton *blanck_button_1;
        QPushButton *blanck_button_2;
        QPushButton *blanck_button_3;
        QPushButton *blanck_button_4;
        QPushButton *blanck_button_5;

        //云台
        //yaw输入框
        QLineEdit* yaw_editor;
        QString* yaw_output;

        //pitch
        QLineEdit* pitch_editor;
        QString* pitch_output;

        //velocity
        QLineEdit* speed_editor;
        QString* velocity_output;

        float yaw_;
        float pitch_;
        int speed_;

//云台
//        QPushButton *yaw_left_pan_tilt_button;
//        QPushButton *yaw_right_pan_tilt_button;
//        QPushButton *pitch_up_pan_tilt_button;
//        QPushButton *pitch_down_pan_tilt_button;
//        QPushButton *pan_tilt_speed_up;
//        QPushButton *pan_tilt_slow_down;
//
//        QPushButton *blanck_button_6;
//        QPushButton *blanck_button_7;
//        QPushButton *blanck_button_8;
//        QPushButton *blanck_button_9;
//        QPushButton *blanck_button_10;


        QTimer *timer;
        geometry_msgs::Twist command_base;
        pan_tilt_driver::PanTiltCmd command_pan_tilt;

    private Q_SLOTS:
        void on_MoveForwardButton_clicked();
        void on_MoveLeftButton_clicked();
        void on_MoveRightButton_clicked();
        void on_MoveBackButton_clicked();
        void on_TurnLeftButton_clicked();
        void on_TurnRightButton_clicked();

//        void on_YawLeftButton_clicked();
//        void on_YawRightButton_clicked();
//        void on_PitchUpButton_clicked();
//        void on_PitchDownButton_clicked();
//        void on_pan_tilt_speed_up();
//        void on_pan_tilt_slow_down();



        void Update();

    };
}

#endif //PROJECT_ROBOT_UI_H
