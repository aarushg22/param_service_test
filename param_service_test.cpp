#include <param_service_test.hpp>
#include <rclcpp/parameter.hpp>
#include <chrono>
namespace agv_task_manager {
  ATM::ATM() : Node("Agv_Task_Manager") {

    rclcpp::Node::SharedPtr sptr = std::enable_shared_from_this<ATM>::shared_from_this();
    auto parameters_client = std::make_shared<rclcpp::SyncParametersClient>(sptr);
    while (!parameters_client->wait_for_service(std::chrono::seconds(1))) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
        exit (EXIT_FAILURE);
      }
      RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
    }

    this->manipulator_sequence = parameters_client->get_parameter<std::vector<int64_t>>("manipulator_sequence");
    this->ee_sequence = parameters_client->get_parameter<std::vector<int64_t>>("ee_sequence");
    std::reverse((this->manipulator_sequence).begin(),(this->manipulator_sequence).end());
    std::reverse((this->ee_sequence).begin(),(this->ee_sequence).end());

    RCLCPP_INFO(this->get_logger(), "manipulator value set '%d'",(this->manipulator_sequence).front());
    RCLCPP_INFO(this->get_logger(), "EE value set '%d'",(this->ee_sequence).front());
  }
}
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  std::cout<< "Initializing agv_task_manager package" <<'\n';

  auto node = std::make_shared<agv_task_manager::ATM>();

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}
