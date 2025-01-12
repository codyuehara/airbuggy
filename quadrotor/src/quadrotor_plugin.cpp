#include <gazebo/physics/Model.hh>
#include <gazebo/physics/Joint.hh>
#include <quadrotor/quadrotor_plugin.hpp>
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>

namespace gazebo {

class QuadrotorPluginPrivate
{
public:
    gazebo::event::ConnectionPtr update_connection_;
    gazebo_ros::Node::SharedPtr ros_node_;
    gazebo::physics::JointPtr joint;

    double max_velocity;

};

QuadrotorPlugin::QuadrotorPlugin() : impl_(std::make_unique<QuadrotorPluginPrivate>())
{
    printf("Initiated quadrotor plugin\n");
}

QuadrotorPlugin::~QuadrotorPlugin()
{
}

void QuadrotorPlugin::Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf)
{
    impl_->ros_node_ = gazebo_ros::Node::Get(sdf);
    RCLCPP_INFO_ONCE(impl_->ros_node_->get_logger(), "CODY");
}

GZ_REGISTER_MODEL_PLUGIN(QuadrotorPlugin)
}
