/*
 * Copyright (C) 2026 Open Source Robotics Foundation
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
#ifndef GZ_MSGS_EXTRAFIELDS_HH_
#define GZ_MSGS_EXTRAFIELDS_HH_

#include <google/protobuf/message.h>
#include <google/protobuf/unknown_field_set.h>

#include <cstdint>
#include <optional>
#include <string>

#include "gz/msgs/config.hh"
#include "gz/msgs/Export.hh"

namespace gz::msgs
{
  // Inline bracket to help doxygen filtering.
  inline namespace GZ_MSGS_VERSION_NAMESPACE {

  /// \brief Forward compatible field access.
  ///
  /// These helpers write and read message fields that the schema compiled
  /// into this library may not know yet, keeping the wire bytes identical
  /// to a schema that does know them. When the runtime schema knows the
  /// field number, the value flows through the real field; otherwise it is
  /// encoded as a protobuf unknown field.
  ///
  /// This allows a stable branch to interoperate with fields added to a
  /// message in a newer version, without modifying the proto definition,
  /// the generated classes, or the library ABI.
  ///
  /// Usage rules:
  /// * The field number and its type are a contract with the newer schema:
  ///   they must match the proto definition where the field exists.
  /// * Do not target members of a oneof.
  /// \class ExtraMessage ExtraFields.hh gz/msgs/ExtraFields.hh
  /// \brief A schema-less message value: numbered fields without a
  /// generated class. Used for fields whose message type does not exist in
  /// the schema compiled into this library.
  class GZ_MSGS_VISIBLE ExtraMessage
  {
    /// \brief Constructor.
    public: ExtraMessage() = default;

    /// \brief Copy constructor.
    /// \param[in] _other Message to copy.
    public: ExtraMessage(const ExtraMessage &_other);

    /// \brief Assignment operator.
    /// \param[in] _other Message to copy.
    /// \return A reference to this message.
    public: ExtraMessage &operator=(const ExtraMessage &_other);

    /// \brief Set a varint field (uint, int, bool or enum).
    /// \param[in] _fieldNumber Field number.
    /// \param[in] _value Value to set.
    public: void Set(int _fieldNumber, uint64_t _value);

    /// \brief Set a string or bytes field.
    /// \param[in] _fieldNumber Field number.
    /// \param[in] _value Value to set.
    public: void Set(int _fieldNumber, const std::string &_value);

    /// \brief Set a nested schema-less message field.
    /// \param[in] _fieldNumber Field number.
    /// \param[in] _value Value to set.
    public: void Set(int _fieldNumber, const ExtraMessage &_value);

    /// \brief Set a nested message field from a generated message.
    /// \param[in] _fieldNumber Field number.
    /// \param[in] _value Value to set.
    public: void Set(int _fieldNumber,
        const google::protobuf::Message &_value);

    /// \brief Get a varint field.
    /// \param[in] _fieldNumber Field number.
    /// \return The value or std::nullopt if the field is not present.
    public: std::optional<uint64_t> UInt(int _fieldNumber) const;

    /// \brief Get a string or bytes field.
    /// \param[in] _fieldNumber Field number.
    /// \return The value or std::nullopt if the field is not present.
    public: std::optional<std::string> String(int _fieldNumber) const;

    /// \brief Get a nested schema-less message field.
    /// \param[in] _fieldNumber Field number.
    /// \return The value or std::nullopt if the field is not present.
    public: std::optional<ExtraMessage> Nested(int _fieldNumber) const;

    /// \brief Parse a nested message field into a generated message.
    /// \param[in] _fieldNumber Field number.
    /// \param[out] _out Message to parse into.
    /// \return True when the field is present and parses.
    public: bool ToMessage(int _fieldNumber,
        google::protobuf::Message &_out) const;

    /// \brief Serialize to the protobuf wire format.
    /// \return The serialized bytes.
    public: std::string Serialize() const;

    /// \brief Parse from the protobuf wire format.
    /// \param[in] _data Serialized bytes.
    /// \return True when the bytes parse.
    public: bool Parse(const std::string &_data);

    /// \brief The numbered fields.
    private: google::protobuf::UnknownFieldSet fields;
  };

  /// \brief Set a varint field (uint, int, bool or enum) on a message,
  /// routed through the real field when the schema knows the field number.
  /// \param[in, out] _msg Message to modify.
  /// \param[in] _fieldNumber Field number.
  /// \param[in] _value Value to set.
  void GZ_MSGS_VISIBLE SetExtraField(google::protobuf::Message &_msg,
      int _fieldNumber, uint64_t _value);

  /// \brief Set a string or bytes field on a message.
  /// \param[in, out] _msg Message to modify.
  /// \param[in] _fieldNumber Field number.
  /// \param[in] _value Value to set.
  void GZ_MSGS_VISIBLE SetExtraField(google::protobuf::Message &_msg,
      int _fieldNumber, const std::string &_value);

  /// \brief Set a message field on a message from a generated message.
  /// \param[in, out] _msg Message to modify.
  /// \param[in] _fieldNumber Field number.
  /// \param[in] _value Value to set.
  void GZ_MSGS_VISIBLE SetExtraField(google::protobuf::Message &_msg,
      int _fieldNumber, const google::protobuf::Message &_value);

  /// \brief Set a message field on a message from a schema-less message.
  /// \param[in, out] _msg Message to modify.
  /// \param[in] _fieldNumber Field number.
  /// \param[in] _value Value to set.
  void GZ_MSGS_VISIBLE SetExtraField(google::protobuf::Message &_msg,
      int _fieldNumber, const ExtraMessage &_value);

  /// \brief Get a varint field from a message.
  /// \param[in] _msg Message to read.
  /// \param[in] _fieldNumber Field number.
  /// \return The value or std::nullopt if the field is not present.
  std::optional<uint64_t> GZ_MSGS_VISIBLE ExtraFieldUInt(
      const google::protobuf::Message &_msg, int _fieldNumber);

  /// \brief Get a string or bytes field from a message.
  /// \param[in] _msg Message to read.
  /// \param[in] _fieldNumber Field number.
  /// \return The value or std::nullopt if the field is not present.
  std::optional<std::string> GZ_MSGS_VISIBLE ExtraFieldString(
      const google::protobuf::Message &_msg, int _fieldNumber);

  /// \brief Parse a message field into a generated message.
  /// \param[in] _msg Message to read.
  /// \param[in] _fieldNumber Field number.
  /// \param[out] _out Message to parse into.
  /// \return True when the field is present and parses.
  bool GZ_MSGS_VISIBLE ExtraFieldMessage(
      const google::protobuf::Message &_msg, int _fieldNumber,
      google::protobuf::Message &_out);

  /// \brief Get a message field as a schema-less message.
  /// \param[in] _msg Message to read.
  /// \param[in] _fieldNumber Field number.
  /// \return The value or std::nullopt if the field is not present.
  std::optional<ExtraMessage> GZ_MSGS_VISIBLE ExtraFieldNested(
      const google::protobuf::Message &_msg, int _fieldNumber);

  /// \brief Clear a field, known or not by the schema.
  /// \param[in, out] _msg Message to modify.
  /// \param[in] _fieldNumber Field number.
  void GZ_MSGS_VISIBLE ClearExtraField(google::protobuf::Message &_msg,
      int _fieldNumber);
  }
}

#endif
