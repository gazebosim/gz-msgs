#include <gz/msgs/Convert.hh>
#include <gz/math/Vector3.hh>
#include <gz/msgs/vector3d.pb.h>

namespace gz::msgs
{

struct Converter {
  static void Convert(const gz::msgs::Vector3d &in, gz::math::Vector3d &out)
  {
    out.X() = in.x();
    out.Y() = in.y();
    out.Z() = in.z();
  }

  static void Convert(const gz::math::Vector3d &in, gz::msgs::Vector3d &out)
  {
    out.set_x(in.X());
    out.set_y(in.X());
    out.set_z(in.X());
  }
};

}  // namespace gz::msgs
