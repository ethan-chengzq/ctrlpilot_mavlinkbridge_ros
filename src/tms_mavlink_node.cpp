#include <memory>
#include <string>

#include "ament_index_cpp/get_package_share_directory.hpp"
#include "rclcpp/rclcpp.hpp"

#include "sealien_ctrlpilot_mavlinkbridge/mavlink_bridge_core.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  const auto share_dir =
    ament_index_cpp::get_package_share_directory("sealien_ctrlpilot_mavlinkbridge");
  auto node = std::make_shared<sealien_ctrlpilot_mavlinkbridge::MavlinkBridgeCore>(
    "tms_mavlink_node",
    share_dir + "/config/sealien_mavlink_tms.yaml",
    "tms");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
