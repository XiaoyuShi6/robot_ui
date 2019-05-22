//
// Created by leo on 18-6-1.
//

#include "robot_ui.h"

namespace robot_ui
{
    RobotBaseUI::RobotBaseUI(QWidget *parent) : rviz::Panel(parent),yaw_(0.0),pitch_(0.0),speed_(0)

    {
        //底盘运动操作面板
        QHBoxLayout *HLayout1 = new QHBoxLayout;
        QHBoxLayout *HLayout2 = new QHBoxLayout;
        QHBoxLayout *HLayout3 = new QHBoxLayout;
        QHBoxLayout *HLayout4 = new QHBoxLayout;

        blanck_button_1 = new QPushButton(this);
        HLayout1->addWidget(blanck_button_1);
        move_forward_button = new QPushButton("Forward",this);
        HLayout1->addWidget(move_forward_button);
        blanck_button_2 = new QPushButton(this);
        HLayout1->addWidget(blanck_button_2);

        move_left_button = new QPushButton("Left",this);
        HLayout2->addWidget(move_left_button);
        blanck_button_3 = new QPushButton(this);
        HLayout2->addWidget(blanck_button_3);
        move_right_button = new QPushButton("Right",this);
        HLayout2->addWidget(move_right_button);

        blanck_button_4 = new QPushButton(this);
        HLayout3->addWidget(blanck_button_4);
        move_back_button = new QPushButton("Back",this);
        HLayout3->addWidget(move_back_button);
        blanck_button_5 = new QPushButton(this);
        HLayout3->addWidget(blanck_button_5);

        turn_left_button = new QPushButton("Turn Left",this);
        HLayout4->addWidget(turn_left_button);
        turn_right_button = new QPushButton("Turn Right",this);
        HLayout4->addWidget(turn_right_button);


        //云台控制面板
//        QHBoxLayout *HLayout5 = new QHBoxLayout;
//        QHBoxLayout *HLayout6 = new QHBoxLayout;
//        QHBoxLayout *HLayout7 = new QHBoxLayout;
//        QHBoxLayout *HLayout8 = new QHBoxLayout;
//
//        blanck_button_6 = new QPushButton(this);
//        HLayout5->addWidget(blanck_button_6);
//        pitch_up_pan_tilt_button = new QPushButton("Pitch_up",this);
//        HLayout5->addWidget(pitch_up_pan_tilt_button);
//        blanck_button_7 = new QPushButton(this);
//        HLayout5->addWidget(blanck_button_7);
//
//        blanck_button_8 = new QPushButton(this);
//        yaw_left_pan_tilt_button= new QPushButton("Yaw_left",this);
//        yaw_right_pan_tilt_button=new QPushButton("Yaw_right",this);
//        HLayout6->addWidget(yaw_left_pan_tilt_button);
//        HLayout6->addWidget(blanck_button_8);
//        HLayout6->addWidget(yaw_right_pan_tilt_button);
//
//        blanck_button_9 = new QPushButton(this);
//        blanck_button_10 = new QPushButton(this);
//        pitch_down_pan_tilt_button = new QPushButton("Pitch_down",this);
//        HLayout7->addWidget(blanck_button_9);
//        HLayout7->addWidget(pitch_down_pan_tilt_button);
//        HLayout7->addWidget(blanck_button_10);
//
//
//        pan_tilt_speed_up=new QPushButton("Speed_up",this);
//        pan_tilt_slow_down=new QPushButton("Slow_down",this);
//        HLayout8->addWidget(pan_tilt_speed_up);
//        HLayout8->addWidget(pan_tilt_slow_down);



        QVBoxLayout *VLayout = new QVBoxLayout;
        VLayout->addLayout(HLayout1);
        VLayout->addLayout(HLayout2);
        VLayout->addLayout(HLayout3);
        VLayout->addLayout(HLayout4);
//        VLayout->addLayout(HLayout5);
//        VLayout->addLayout(HLayout6);
//        VLayout->addLayout(HLayout7);
//        VLayout->addLayout(HLayout8);
        VLayout->addWidget(new QLabel("Yaw"));
        yaw_editor=new QLineEdit;
        VLayout->addWidget(yaw_editor);

        VLayout->addWidget(new QLabel("Pitch"));
        pitch_editor=new QLineEdit;
        VLayout->addWidget(pitch_editor);

        VLayout->addWidget(new QLabel("Speed"));
        speed_editor=new QLineEdit;
        VLayout->addWidget(speed_editor);


        setLayout(VLayout);


        move_forward_button->setAutoRepeat(true);
        move_left_button->setAutoRepeat(true);
        move_right_button->setAutoRepeat(true);
        move_back_button->setAutoRepeat(true);
        turn_left_button->setAutoRepeat(true);
        turn_right_button->setAutoRepeat(true);

//        yaw_left_pan_tilt_button->setAutoRepeat(true);
//        yaw_right_pan_tilt_button->setAutoRepeat(true);
//        pitch_up_pan_tilt_button->setAutoRepeat(true);
//        pitch_down_pan_tilt_button->setAutoRepeat(true);
//        pan_tilt_speed_up->setAutoRepeat(true);
//        pan_tilt_slow_down->setAutoRepeat(true);


        connect(move_forward_button, SIGNAL(pressed()), this, SLOT(on_MoveForwardButton_clicked()));
        connect(move_left_button, SIGNAL(pressed()), this, SLOT(on_MoveLeftButton_clicked()));
        connect(move_right_button, SIGNAL(pressed()), this, SLOT(on_MoveRightButton_clicked()));
        connect(move_back_button, SIGNAL(pressed()), this, SLOT(on_MoveBackButton_clicked()));
        connect(turn_left_button, SIGNAL(pressed()), this, SLOT(on_TurnLeftButton_clicked()));
        connect(turn_right_button, SIGNAL(pressed()), this, SLOT(on_TurnRightButton_clicked()));

//        connect(yaw_left_pan_tilt_button, SIGNAL(pressed()), this, SLOT(on_YawLeftButton_clicked()));
//        connect(yaw_right_pan_tilt_button, SIGNAL(pressed()), this, SLOT(on_YawRightButton_clicked()));
//        connect(pitch_up_pan_tilt_button, SIGNAL(pressed()), this, SLOT(on_PitchUpButton_clicked()));
//        connect(pitch_down_pan_tilt_button, SIGNAL(pressed()), this, SLOT(on_PitchDownButton_clicked()));
//        connect(pan_tilt_speed_up, SIGNAL(pressed()), this, SLOT(on_pan_tilt_speed_up()));
//        connect(pan_tilt_slow_down, SIGNAL(pressed()), this, SLOT(on_pan_tilt_slow_down()));
        connect(yaw_editor, SIGNAL(editingFinished()), this, SLOT(update_yaw()));
        connect(pitch_editor, SIGNAL(editingFinished()), this, SLOT(update_pitch()));
        connect(speed_editor, SIGNAL(editingFinished()), this, SLOT(update_speed()));

        //定时器
        timer = new QTimer;
        connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
        timer->start(100);

        //发布
        robot_base_ui_pub = node.advertise<geometry_msgs::Twist>("/NMotionCtrlTopic/GeoTwistSetInstantVelocity",1000);
        pan_tilt_pub = node.advertise<pan_tilt_driver::PanTiltCmd>("/PanTiltDriverNode/pan_tilt_cmd",1000);
    }

    //
    void RobotBaseUI::update_yaw()
    {
        QString temp_string=yaw_editor->text();//获取输入框中的数据
        yaw_=temp_string.toFloat();

    }
    void RobotBaseUI::update_pitch()
    {
        QString temp_string=pitch_editor->text();
        pitch_=temp_string.toFloat();
    }
    void RobotBaseUI::update_speed()
    {
        QString temp_string=speed_editor->text();
        speed_=temp_string.toInt();
    }


    void RobotBaseUI::Update()
    {
        robot_base_ui_pub.publish(command_base);

        //每次循环都执行清零操作，如果停止按键则发送零速度
        command_base.angular.x = 0;
        command_base.angular.y = 0;
        command_base.angular.z = 0;
        command_base.linear.x = 0;
        command_base.linear.y = 0;
        command_base.linear.z = 0;


        if( ros::ok() && pan_tilt_pub )
        {
            command_pan_tilt.yaw=yaw_;
            command_pan_tilt.pitch=pitch_;
            command_pan_tilt.speed=speed_;
            pan_tilt_pub.publish(command_pan_tilt);
        }



    }


    void RobotBaseUI::on_MoveForwardButton_clicked()
    {
        command_base.linear.x = 0.05;
    }

    void RobotBaseUI::on_MoveLeftButton_clicked()
    {
        command_base.linear.y = 0.05;
    }

    void RobotBaseUI::on_MoveRightButton_clicked()
    {
        command_base.linear.y = -0.05;
    }

    void RobotBaseUI::on_MoveBackButton_clicked()
    {
        command_base.linear.x = -0.05;
    }

    void RobotBaseUI::on_TurnLeftButton_clicked()
    {
        command_base.angular.z = 0.05;
    }

    void RobotBaseUI::on_TurnRightButton_clicked()
    {
        command_base.angular.z = -0.05;
    }


        //云台
//    void RobotBaseUI::on_YawLeftButton_clicked()
//    {
//        command_pan_tilt.yaw++;
//    }
//    void RobotBaseUI::on_YawRightButton_clicked()
//    {
//        command_pan_tilt.yaw--;
//    }
//    void RobotBaseUI::on_PitchUpButton_clicked()
//    {
//        command_pan_tilt.pitch++;
//    }
//    void RobotBaseUI::on_PitchDownButton_clicked()
//    {
//        command_pan_tilt.pitch--;
//    }
//    void RobotBaseUI::on_pan_tilt_speed_up()
//    {
//        command_pan_tilt.speed++;
//    }
//    void RobotBaseUI::on_pan_tilt_slow_down()
//    {
//        command_pan_tilt.speed--;
//    }




    //save和load是rviz固定的接口
    void RobotBaseUI::save(rviz::Config config) const
    {
        rviz::Panel::save(config);
    }

    void RobotBaseUI::load(const rviz::Config &config)
    {
        rviz::Panel::load(config);
    }
}

//申明此类是rviz的一个插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(robot_ui::RobotBaseUI, rviz::Panel);
