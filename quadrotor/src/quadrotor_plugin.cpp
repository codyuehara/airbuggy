#include <gazebo/physics/Model.hh>
#include <gazebo/physics/Link.hh>
#include <quadrotor/quadrotor_plugin.hpp>
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <gazebo/physics/physics.hh>

namespace gazebo {

class QuadrotorPluginPrivate
{
public:
    event::ConnectionPtr update_connection_;
    rclcpp::Node::SharedPtr ros_node_;
    physics::ModelPtr model;

    void OnUpdate();

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
    impl_->model = model;

    impl_->ros_node_ = gazebo_ros::Node::Get(sdf);
    RCLCPP_INFO_ONCE(impl_->ros_node_->get_logger(), "CODY");
    //this->node = std::make_shared<rclcpp::Node>("quadrotor_plugin");
    impl_->update_connection_ = gazebo::event::Events::ConnectWorldUpdateBegin(std::bind(&QuadrotorPluginPrivate::OnUpdate, impl_.get()));
}

void QuadrotorPluginPrivate::OnUpdate()
{
    //printf("OnUpdate called \n");

    // a = g + 1/m R(q)f_T
    // q_dot = 1/2q o [0 w]^T
    //
    // x_dot = [v_x, v_y, v_z, a_x, a_y, a_z, q_w, q_x, q_y, q_z, w_x, w_y, w_z] 
    //
    // integrate with runge kutta 4 to get:
    // states = [x, y, z, v_x, v_y, v_z, p, q, r, w_x, w_y, w_z]
    //
    model->GetLink("base_link")->AddRelativeForce(ignition::math::Vector3d(1, 0, 5));
}

GZ_REGISTER_MODEL_PLUGIN(QuadrotorPlugin)
}
