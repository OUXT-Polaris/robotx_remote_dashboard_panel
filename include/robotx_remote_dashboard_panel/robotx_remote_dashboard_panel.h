#ifndef ROBOTX_REMOTE_DASHBOARD_PANEL_ROBOTX_REMOTE_DASHBOARD_PANEL_H_INCLUDED
#define ROBOTX_REMOTE_DASHBOARD_PANEL_ROBOTX_REMOTE_DASHBOARD_PANEL_H_INCLUDED

/**
 * @file robotx_remote_dashboard_panel.h
 * @author Masaya Kataoka (ms.kataoka@gmail.com)
 * @brief definition of remote dashboard class
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef Q_MOC_RUN
    #include <ros/ros.h>
    #include <rviz/panel.h>
#endif

// Headers in ROS
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/BatteryState.h>
#include <usv_control_msgs/AzimuthThrusterCatamaranDriveStamped.h>
#include <geographic_msgs/GeoPose.h>

// Headers in Boost
#include <boost/optional.hpp>

// Headers in Qt
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QtSvg/QSvgRenderer>
#include <QString>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QPalette>
#include <QPaintEvent>

namespace robotx_remote_dashboard_panel
{
    class RobotXRemoteDashboardPanel : public rviz::Panel
    {
    Q_OBJECT
    public:
        RobotXRemoteDashboardPanel(QWidget* parent = 0 );
        virtual void load( const rviz::Config& config );
        virtual void save( rviz::Config config ) const;
    public Q_SLOTS:
        void draw();
    protected:
        QGraphicsView dashboard_view_;
        QGraphicsScene scene_;
    private:
        ros::Subscriber imu_sub_;
        boost::optional<sensor_msgs::Imu> imu_data_;
        void imuCallback(const sensor_msgs::Imu::ConstPtr msg);
        ros::Subscriber motor_battery_state_sub_;
        boost::optional<sensor_msgs::BatteryState> motor_battery_state_data_;
        void motorBatteryStateCallback(const sensor_msgs::BatteryState::ConstPtr msg);
        ros::Subscriber control_battery_state_sub_;
        boost::optional<sensor_msgs::BatteryState> control_battery_state_data_;
        void controlBatteryStateCallback(const sensor_msgs::BatteryState::ConstPtr msg);
        ros::Subscriber motor_command_sub_;
        boost::optional<usv_control_msgs::AzimuthThrusterCatamaranDriveStamped> motor_command_data_;
        void motorCommandCallback(const usv_control_msgs::AzimuthThrusterCatamaranDriveStamped::ConstPtr msg);
        ros::Subscriber geopose_sub_;
        boost::optional<geographic_msgs::GeoPose> geopose_data_;
        void geoPoseCallback(const geographic_msgs::GeoPose::ConstPtr msg);
        ros::NodeHandle nh_;
    };
}

#endif  //ROBOTX_REMOTE_DASHBOARD_PANEL_ROBOTX_REMOTE_DASHBOARD_PANEL_H_INCLUDED