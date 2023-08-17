#include <gz/msgs/vector3d.pb.h>
#include <gz/custom_msgs/vector3d.pb.h>

#include <google/protobuf/text_format.h>

// A simple example that demonstrates the use of the message factory
//
// Usage:
// Print text description of original and custom Vector3d msgs.
//   ./generating_custom_messages
int main(int argc, char** argv)
{
  (void) argc;
  (void) argv;
  // Print the text description of the original message
  gz::msgs::Vector3d original;
  {
    auto descriptor = original.GetDescriptor();
    auto fileDescriptor = descriptor->file();
    std::cout << "Name: " << descriptor->full_name() << std::endl;
    std::cout << "File: " << fileDescriptor->name() << std::endl << std::endl;
    std::cout << descriptor->DebugString() << std::endl;
  }

  // Print the text description of the custom message
  gz::custom_msgs::Vector3d custom;
  {
    auto descriptor = custom.GetDescriptor();
    auto fileDescriptor = descriptor->file();
    std::cout << "Name: " << descriptor->full_name() << std::endl;
    std::cout << "File: " << fileDescriptor->name() << std::endl << std::endl;
    std::cout << descriptor->DebugString() << std::endl;
  }
}
