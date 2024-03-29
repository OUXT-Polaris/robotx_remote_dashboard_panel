/**
 * @file robotx_remote_dashboard_panel.cpp
 * @author Masaya Kataoka (ms.kataoka@gmail.com)
 * @brief Remote Implimentation of remote dashboard class
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <robotx_remote_dashboard_panel/robotx_remote_dashboard_panel.h>

// Headers in Qt
#include <QTimer>

namespace robotx_remote_dashboard_panel
{
    RobotXRemoteDashboardPanel::RobotXRemoteDashboardPanel(QWidget* parent)
    :
    	meter12v_min(11.7),/*V*/
		meter12v_low(11.9),/*V*/
		meter12v_max(12.2),/*V*/
		meter24v_min(23.0),/*V*/
		meter24v_low(24.0),/*V*/
		meter24v_max(27.0)/*V*/
    {
        std::string azimuthfig_path = ros::package::getPath("robotx_remote_dashboard_panel")+"png/azimuth_78x200.png";
        azimuthfig_ = QImage(QString::fromStdString(azimuthfig_path));
        std::string rollfig_path = ros::package::getPath("robotx_remote_dashboard_panel")+"png/roll_156x52.png";
        rollfig_ = QImage(QString::fromStdString(rollfig_path));
        std::string pitchfig_path = ros::package::getPath("robotx_remote_dashboard_panel")+"png/pitch_156x32.png";
        pitchfig_ = QImage(QString::fromStdString(pitchfig_path));
        std::string hdgfig_path = ros::package::getPath("robotx_remote_dashboard_panel")+"png/hdg_150x48.png";
        hdgfig_ = QImage(QString::fromStdString(hdgfig_path));
        std::string svgpath = ros::package::getPath("robotx_remote_dashboard_panel")+"svg/panel.svg";
        //front_panel_handler_ = new QSvgRenderer(QString::fromStdString(svgpath));

        QVBoxLayout* dashboard_layout = new QVBoxLayout;
        dashboard_layout->addWidget(&dashboard_view_);
        setLayout(dashboard_layout);

        imu_sub_ = nh_.subscribe("/imu/data",1,&RobotXRemoteDashboardPanel::imuCallback,this);
        motor_battery_state_sub_ = nh_.subscribe("/battery_state/motor",1,&RobotXRemoteDashboardPanel::motorBatteryStateCallback,this);
        control_battery_state_sub_ = nh_.subscribe("/battery_state/control",1,&RobotXRemoteDashboardPanel::controlBatteryStateCallback,this);
        motor_command_sub_ = nh_.subscribe("/motor_command",1,&RobotXRemoteDashboardPanel::motorCommandCallback,this);

        QTimer* draw_timer = new QTimer(this);
        draw_timer->setInterval(100);
        draw_timer->setSingleShot(false);
        connect(draw_timer,SIGNAL(timeout()),SLOT(RobotXRemoteDashboardPanel::draw()));
        draw_timer->start();
    }

    RobotXRemoteDashboardPanel::~RobotXRemoteDashboardPanel()
    {
        delete front_panel_handler_;
    }

    void RobotXRemoteDashboardPanel::draw()
    {
        return;
    }

    void RobotXRemoteDashboardPanel::load( const rviz::Config& config )
    {
        return;
    }

    void RobotXRemoteDashboardPanel::save( rviz::Config config ) const
    {
        rviz::Panel::save(config);
        return;
    }

    void RobotXRemoteDashboardPanel::imuCallback(const sensor_msgs::Imu::ConstPtr msg)
    {
        imu_data_ = *msg;
        return;
    }

    void RobotXRemoteDashboardPanel::motorBatteryStateCallback(const sensor_msgs::BatteryState::ConstPtr msg)
    {
        motor_battery_state_data_ = *msg;
        return;
    }

    void RobotXRemoteDashboardPanel::controlBatteryStateCallback(const sensor_msgs::BatteryState::ConstPtr msg)
    {
        control_battery_state_data_ = *msg;
        return;
    }

    void RobotXRemoteDashboardPanel::motorCommandCallback(const usv_control_msgs::AzimuthThrusterCatamaranDriveStamped::ConstPtr msg)
    {
        motor_command_data_ = *msg;
        return;
    }

    void RobotXRemoteDashboardPanel::geoPoseCallback(const geographic_msgs::GeoPose::ConstPtr msg)
    {
        geopose_data_ = *msg;
        return;
    }
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(robotx_remote_dashboard_panel::RobotXRemoteDashboardPanel,rviz::Panel)