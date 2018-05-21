/*
 * Copyright 2018 Open Source Robotics Foundation
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

#ifndef IGNITION_MSGS_FILESYSTEM_HH_
#define IGNITION_MSGS_FILESYSTEM_HH_

#include <memory>
#include <string>

#include <ignition/msgs/Export.hh>
#include <ignition/msgs/SuppressWarning.hh>

namespace ignition
{
  namespace msgs
  {
    /// \brief Options for how to handle errors that occur in functions that
    /// manipulate the filesystem.
    enum FilesystemWarningOp
    {
      /// \brief Errors that occur during filesystem manipulation should be
      /// logged as warnings using ignwarn. (Recommended)
      FSWO_LOG_WARNINGS = 0,

      /// \brief Errors that occur during filesystem manipulation should not be
      /// logged. The user will be responsible for checking the system's error
      /// flags.
      FSWO_SUPPRESS_WARNINGS
    };

    // /// \internal
    class DirIterPrivate;

    /// \class DirIter Filesystem.hh
    /// \brief A class for iterating over all items in a directory.
    class IGNITION_MSGS_VISIBLE DirIter
    {
      /// \brief Constructor.
      /// \param[in] _in  Directory to iterate over.
      public: explicit DirIter(const std::string &_in);

      /// \brief Constructor for end element.
      public: DirIter();

      /// \brief Dereference operator; returns current directory record.
      /// \return A string representing the entire path of the directory record.
      public: std::string operator*() const;

      /// \brief Pre-increment operator; moves to next directory record.
      /// \return This iterator.
      public: const DirIter& operator++();

      /// \brief Comparison operator to see if this iterator is at the
      ///        same point as another iterator.
      /// \param[in] _other  The other iterator to compare against.
      /// \return true if the iterators are equal, false otherwise.
      public: bool operator!=(const DirIter &_other) const;

      /// \brief Destructor
      public: ~DirIter();

      /// \brief Move to the next directory record, skipping . and .. records.
      private: void Next();

      /// \brief Set the internal variable to the empty string.
      private: void SetInternalEmpty();

      /// \brief Close an open directory handle.
      private: void CloseHandle();

      IGN_MSGS_WARN_IGNORE__DLL_INTERFACE_MISSING
      /// \brief Private data.
      private: std::unique_ptr<DirIterPrivate> dataPtr;
      IGN_MSGS_WARN_RESUME__DLL_INTERFACE_MISSING
    };
  }
}

#endif
