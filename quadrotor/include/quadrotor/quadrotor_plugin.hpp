#ifndef QUADROTOR_PLUGIN_H
#define QUADROTOR_PLUGIN_H

#include <gazebo/common/Plugin.hh>

#include <iostream>
#include <memory>

namespace gazebo
{
class QuadrotorPluginPrivate;

class QuadrotorPlugin: public ModelPlugin
{
public:
    QuadrotorPlugin();

    virtual ~QuadrotorPlugin();

    void Load(physics::ModelPtr model, sdf::ElementPtr sdf) override;

private:
    std::unique_ptr<QuadrotorPluginPrivate> impl_;

};
#endif
}
