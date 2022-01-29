///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2013, PAL Robotics S.L.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of PAL Robotics S.L. nor the names of its
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

/// \author Adolfo Rodriguez Tsouroukdissian

#include <exception>
#include <string>
#include <gtest/gtest.h>
#include <pluginlib/class_loader.hpp>
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "hardware_interface/component_parser.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "transmission_interface/simple_transmission.hpp"
#include "transmission_interface/simple_transmission_loader.hpp"
#include "transmission_interface/transmission_loader.hpp"

using namespace transmission_interface;
using namespace hardware_interface;

struct TransmissionPluginLoader
{
  std::shared_ptr<TransmissionLoader> create(const std::string& type)
  {
    try
    {
      return class_loader_.createUniqueInstance(type);
    }
    catch(std::exception& ex) {
      std::cout << ex.what() << std::endl;
    
    return std::shared_ptr<TransmissionLoader>();}
  }

private:
  //must keep it alive because instance destroyers need it
  pluginlib::ClassLoader<TransmissionLoader> class_loader_ = {"transmission_interface", "transmission_interface::TransmissionLoader"};
};


TEST(SimpleTransmissionLoaderTest, FullSpec)
{
  // Parse transmission info

  std::string urdf_to_test =
    R"(
  <?xml version="1.0" encoding="utf-8"?>
  <!-- =================================================================================== -->
  <!-- |    This document was autogenerated by xacro from minimal_robot.urdf.xacro       | -->
  <!-- |    EDITING THIS FILE BY HAND IS NOT RECOMMENDED                                 | -->
  <!-- =================================================================================== -->
  <robot name="MinimalRobot">
    <!-- Used for fixing robot -->
    <link name="world"/>
    <joint name="base_joint" type="fixed">
      <origin rpy="0 0 0" xyz="0 0 0"/>
      <parent link="world"/>
      <child link="base_link"/>
    </joint>
    <link name="base_link">
      <inertial>
        <mass value="0.01"/>
        <origin xyz="0 0 0"/>
        <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
      </inertial>
      <visual>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="0.2" radius="0.1"/>
        </geometry>
        <material name="DarkGrey">
          <color rgba="0.4 0.4 0.4 1.0"/>
        </material>
      </visual>
      <collision>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
      </collision>
    </link>
    <joint name="joint1" type="revolute">
      <origin rpy="-1.57079632679 0 0" xyz="0 0 0.2"/>
      <parent link="base_link"/>
      <child link="link1"/>
      <limit effort="0.1" lower="-3.14159265359" upper="3.14159265359" velocity="0.2"/>
    </joint>
    <link name="link1">
      <inertial>
        <mass value="0.01"/>
        <origin xyz="0 0 0"/>
        <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
      </inertial>
      <visual>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
        <material name="DarkGrey">
          <color rgba="0.4 0.4 0.4 1.0"/>
        </material>
      </visual>
      <collision>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
      </collision>
    </link>
    <joint name="joint2" type="revolute">
      <origin rpy="1.57079632679 0 0" xyz="0 0 0.9"/>
      <parent link="link1"/>
      <child link="link2"/>
      <limit effort="0.1" lower="-3.14159265359" upper="3.14159265359" velocity="0.2"/>
    </joint>
    <link name="link2">
      <inertial>
        <mass value="0.01"/>
        <origin xyz="0 0 0"/>
        <inertia ixx="0.001" ixy="0.0" ixz="0.0" iyy="0.001" iyz="0.0" izz="0.001"/>
      </inertial>
      <visual>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
        <material name="DarkGrey">
          <color rgba="0.4 0.4 0.4 1.0"/>
        </material>
      </visual>
      <collision>
        <origin rpy="0 0 0" xyz="0 0 0"/>
        <geometry>
          <cylinder length="1" radius="0.1"/>
        </geometry>
      </collision>
    </link>
    <joint name="tool_joint" type="fixed">
      <origin rpy="0 0 0" xyz="0 0 1"/>
      <parent link="link2"/>
      <child link="tool_link"/>
    </joint>
    <link name="tool_link">
    </link>
    <ros2_control name="RRBotModularJoint1" type="actuator">
      <hardware>
        <plugin>ros2_control_demo_hardware/VelocityActuatorHardware</plugin>
        <param name="example_param_write_for_sec">1.23</param>
        <param name="example_param_read_for_sec">3</param>
      </hardware>
      <joint name="joint1">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
      <transmission name="transmission1">
        <plugin>transmission_interface/SimpleTransmission</plugin>
        <joint name="joint1" role="joint1">
          <mechanical_reduction>325.949</mechanical_reduction>
        </joint>
      </transmission>
    </ros2_control>
    <ros2_control name="RRBotModularJoint2" type="actuator">
      <hardware>
        <plugin>ros2_control_demo_hardware/VelocityActuatorHardware</plugin>
        <param name="example_param_write_for_sec">1.23</param>
        <param name="example_param_read_for_sec">3</param>
      </hardware>
      <joint name="joint2">
        <command_interface name="velocity">
          <param name="min">-1</param>
          <param name="max">1</param>
        </command_interface>
        <state_interface name="velocity"/>
      </joint>
    </ros2_control>
    <ros2_control name="RRBotModularPositionSensorJoint1" type="sensor">
      <hardware>
        <plugin>ros2_control_demo_hardware/PositionSensorHardware</plugin>
        <param name="example_param_read_for_sec">2</param>
      </hardware>
      <joint name="joint1">
        <state_interface name="position"/>
      </joint>
    </ros2_control>
    <ros2_control name="RRBotModularPositionSensorJoint2" type="sensor">
      <hardware>
        <plugin>ros2_control_demo_hardware/PositionSensorHardware</plugin>
        <param name="example_param_read_for_sec">2</param>
      </hardware>
      <joint name="joint2">
        <state_interface name="position"/>
      </joint>
    </ros2_control>
  </robot>
  )";

  
  std::vector<HardwareInfo> infos = parse_control_resources_from_urdf(urdf_to_test);
  ASSERT_EQ(1lu, infos[0].transmissions.size());

  for (int i = 0; i < (int)infos.size(); ++i) {
    for (int j = 0; j < (int)infos[i].transmissions.size(); ++j) {
        std::cout << infos[i].transmissions[j].type << std::endl;
    }
  }
  // Transmission loader
  TransmissionPluginLoader loader;
  std::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos[0].transmissions[0].type);
  ASSERT_TRUE(nullptr != transmission_loader);

  std::shared_ptr<Transmission> transmission;
  const TransmissionInfo& info = infos[0].transmissions[0];
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(nullptr != transmission);
  ASSERT_STREQ(infos[0].transmissions[0].joints[0].role.c_str(),"joint1");

  // Validate transmission
  SimpleTransmission* simple_transmission = dynamic_cast<SimpleTransmission*>(transmission.get());
  ASSERT_TRUE(nullptr != simple_transmission);
  EXPECT_EQ(325.949, simple_transmission->get_actuator_reduction());
  EXPECT_EQ( 0.0, simple_transmission->get_joint_offset());
}

TEST(SimpleTransmissionLoaderTest, MinimalSpec)
{
std::string urdf_to_test = R"(
  <?xml version="1.0"?>

<robot name="robot" xmlns="http://www.ros.org">
  <ros2_control>
  <transmission name="simple_trans">
    <type>transmission_interface/SimpleTransmission</type>
    <joint name="foo_joint">
      <hardwareInterface>hardware_interface/PositionJointInterface</hardwareInterface>
    </joint>
    <actuator name="foo_actuator">
      <!--<mechanicalReduction>50</mechanicalReduction>--> <!--Unspecified element -->
    </actuator>
  </transmission>

  <transmission name="simple_trans">
    <type>transmission_interface/SimpleTransmission</type>
    <transmissionInterface>transmission_interface/ActuatorToJointStateInterface</transmissionInterface>
    <joint name="foo_joint">
      <hardwareInterface>hardware_interface/PositionJointInterface</hardwareInterface>
    </joint>
    <actuator name="foo_actuator">
      <mechanicalReduction>fifty</mechanicalReduction> <!-- Not a number -->
    </actuator>
  </transmission>

  <transmission name="simple_trans">
    <type>transmission_interface/SimpleTransmission</type>
    <transmissionInterface>transmission_interface/ActuatorToJointStateInterface</transmissionInterface>
    <joint name="foo_joint">
      <offset>zero</offset> <!-- Not a number -->
      <hardwareInterface>hardware_interface/PositionJointInterface</hardwareInterface>
    </joint>
    <actuator name="foo_actuator">
      <mechanicalReduction>50</mechanicalReduction>
    </actuator>
  </transmission>

  <transmission name="simple_trans">
    <type>transmission_interface/SimpleTransmission</type>
    <transmissionInterface>transmission_interface/ActuatorToJointStateInterface</transmissionInterface>
    <joint name="foo_joint">
      <hardwareInterface>hardware_interface/PositionJointInterface</hardwareInterface>
    </joint>
    <actuator name="foo_actuator">
      <mechanicalReduction>0</mechanicalReduction> <!-- Invalid value -->
    </actuator>
  </transmission>
  </ros2_control>
</robot>
)";
  // Parse transmission info
  std::vector<HardwareInfo> infos = parse_control_resources_from_urdf(urdf_to_test);
  ASSERT_EQ(1lu, infos[0].transmissions.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  std::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos[0].transmissions[0].type);
  ASSERT_TRUE(nullptr != transmission_loader);

  std::shared_ptr<Transmission> transmission;
  const TransmissionInfo& info = infos[0].transmissions[0];
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(nullptr != transmission);

  // Validate transmission
  SimpleTransmission* simple_transmission = dynamic_cast<SimpleTransmission*>(transmission.get());
  ASSERT_TRUE(nullptr != simple_transmission);
  EXPECT_EQ(50.0, simple_transmission->get_actuator_reduction());
  EXPECT_EQ( 0.0, simple_transmission->get_joint_offset());
}

/*
TEST(SimpleTransmissionLoaderTest, InvalidSpec)
{
  // Parse transmission info
  std::vector<HardwareInfo> infos = parse_control_resources_from_urdf("test/urdf/simple_transmission_loader_invalid.urdf");
  ASSERT_EQ(4lu, infos[0].transmissions.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  std::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos[0].transmissions[0].type);
  ASSERT_TRUE(nullptr != transmission_loader);

  for (const auto& info : infos[0].transmissions)
  {
    std::shared_ptr<Transmission> transmission;
    transmission = transmission_loader->load(info);
    ASSERT_TRUE(nullptr == transmission);
  }
}
*/
int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
