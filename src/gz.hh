/*
 * Copyright (C) 2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef GZ_MSGS_GZ_HH_
#define GZ_MSGS_GZ_HH_

#include <cstring>
#include "gz/msgs/Export.hh"

/// \brief External hook to execute 'gz msg -i' from the command line.
/// \param[in] _msg Message type name.
extern "C" GZ_MSGS_VISIBLE void cmdMsgInfo(const char *_msg);

/// \brief External hook to execute 'gz msg -l' from the command line.
extern "C" GZ_MSGS_VISIBLE void cmdMsgList();

/// \brief External hook to read the library version.
/// \return C-string representing the version. Ex.: 0.1.2
extern "C" GZ_MSGS_VISIBLE const char *gzMsgsVersion();

#endif
