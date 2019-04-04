\page cppgetstarted C++ Get Started

## Overview

This tutorial describes how to get started using Ignition Msgs with C++.

We will run through a simple example that populates a message and prints it.
Start by creating a bare-bones main file using the editor of your choice.

```{.cpp}
int main()
{
  return 0;
}
```

The easiest way to include Ignition Msgs is through the `ignition/msgs.hh`
header file. Alternatively, you can include only the header files you need.
For this example, we'll take the short and easy approach.

At this point your main file should look like

```{.cpp}
#include <ignition/msgs.hh>

int main()
{
  return 0;
}
```

Now let's create a message to store three points with arbitrary values.
We will use the `ignition::msgs::Vector3` class to store these points and the
function `DebugString()` to print the content on the terminal.


```{.cpp}
#include <iostream>
#include <ignition/msgs.hh>

int main()
{
  ignition::msgs::Vector3d point1;
  point1.set_x(1);
  point1.set_y(3);
  point1.set_z(5);
  ignition::msgs::Vector3d point2;
  point2.set_x(2);
  point2.set_y(4);
  point2.set_z(6);

  std::cout << "Point1:\n" << point1.DebugString() << std::endl;
  std::cout << "Point2:\n" << point2.DebugString() << std::endl;

  return 0;
}
```
