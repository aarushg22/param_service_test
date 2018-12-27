#ifndef AGV_TASK_MANAGER_HPP
#define AGV_TASK_MANAGER_HPP

#include <cstdio>
#include <memory>
#include <std_msgs/msg/string.hpp>
#include <rclcpp/rclcpp.hpp>

namespace agv_task_manager {
  class ATM : public rclcpp::Node, public std::enable_shared_from_this<ATM> {
  public:
    ATM();

  private:
    std::vector<int64_t> manipulator_sequence;
    std::vector<int64_t> ee_sequence;

  };
}

#endif
