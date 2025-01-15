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
    gazebo::physics::JointPtr belt_joint_;

    double limit_;

    double max_velocity_;
    
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
    impl_->ros_node_ = gazebo_ros::Node::Get(sdf);
    RCLCPP_INFO_ONCE(impl_->ros_node_->get_logger(), "CODY");

//    impl_->belt_joint_ = model->GetJoint("belt_joint");

    //if (!impl_belt_joint_) {
     //   RCLCPP_ERROR(impl_->ros_node_->get_logger(), "Joint not found, unable to start plugin");
//	return;
 //   }

    impl_->max_velocity_ = sdf->GetElement("max_velocity")->Get<double>();

    //model->GetLink("base_link")->SetLinearVel({0, 1, 0});

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
    // model->GetLink("link")->SetLinearVel({v_x, v_y, v_x});
    // model->GetLink("link")->SetAngularVel({w_x, w_y, w_x});
}

GZ_REGISTER_MODEL_PLUGIN(QuadrotorPlugin)
}
