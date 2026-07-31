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
#include "gz/msgs/ExtraFields.hh"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include <iostream>

using google::protobuf::FieldDescriptor;
using google::protobuf::UnknownField;
using google::protobuf::UnknownFieldSet;

namespace
{
//////////////////////////////////////////////////
/// \brief Get the field descriptor when the schema knows the field number.
const FieldDescriptor *KnownField(const google::protobuf::Message &_msg,
    int _fieldNumber)
{
  return _msg.GetDescriptor()->FindFieldByNumber(_fieldNumber);
}

//////////////////////////////////////////////////
/// \brief Remove all the entries of a field number from an unknown field
/// set.
void RemoveNumber(UnknownFieldSet &_set, int _fieldNumber)
{
  UnknownFieldSet kept;
  for (int i = 0; i < _set.field_count(); ++i)
  {
    const auto &field = _set.field(i);
    if (field.number() == _fieldNumber)
      continue;

    switch (field.type())
    {
      case UnknownField::TYPE_VARINT:
        kept.AddVarint(field.number(), field.varint());
        break;
      case UnknownField::TYPE_FIXED32:
        kept.AddFixed32(field.number(), field.fixed32());
        break;
      case UnknownField::TYPE_FIXED64:
        kept.AddFixed64(field.number(), field.fixed64());
        break;
      case UnknownField::TYPE_LENGTH_DELIMITED:
        kept.AddLengthDelimited(field.number(), field.length_delimited());
        break;
      case UnknownField::TYPE_GROUP:
        kept.AddGroup(field.number())->MergeFrom(field.group());
        break;
      default:
        break;
    }
  }
  _set.Clear();
  _set.MergeFrom(kept);
}

//////////////////////////////////////////////////
/// \brief Find the last entry of a field number and type in an unknown
/// field set. The last entry wins, matching the parser semantics.
const UnknownField *LastUnknown(const UnknownFieldSet &_set,
    int _fieldNumber, UnknownField::Type _type)
{
  const UnknownField *result = nullptr;
  for (int i = 0; i < _set.field_count(); ++i)
  {
    const auto &field = _set.field(i);
    if (field.number() == _fieldNumber && field.type() == _type)
      result = &field;
  }
  return result;
}
}  // namespace

namespace gz::msgs
{
inline namespace GZ_MSGS_VERSION_NAMESPACE {

//////////////////////////////////////////////////
ExtraMessage::ExtraMessage(const ExtraMessage &_other)
{
  this->fields.MergeFrom(_other.fields);
}

//////////////////////////////////////////////////
ExtraMessage &ExtraMessage::operator=(const ExtraMessage &_other)
{
  if (this != &_other)
  {
    this->fields.Clear();
    this->fields.MergeFrom(_other.fields);
  }
  return *this;
}

//////////////////////////////////////////////////
void ExtraMessage::Set(int _fieldNumber, uint64_t _value)
{
  RemoveNumber(this->fields, _fieldNumber);
  this->fields.AddVarint(_fieldNumber, _value);
}

//////////////////////////////////////////////////
void ExtraMessage::Set(int _fieldNumber, const std::string &_value)
{
  RemoveNumber(this->fields, _fieldNumber);
  this->fields.AddLengthDelimited(_fieldNumber, _value);
}

//////////////////////////////////////////////////
void ExtraMessage::Set(int _fieldNumber, const ExtraMessage &_value)
{
  this->Set(_fieldNumber, _value.Serialize());
}

//////////////////////////////////////////////////
void ExtraMessage::Set(int _fieldNumber,
    const google::protobuf::Message &_value)
{
  this->Set(_fieldNumber, _value.SerializeAsString());
}

//////////////////////////////////////////////////
std::optional<uint64_t> ExtraMessage::UInt(int _fieldNumber) const
{
  const auto *field = LastUnknown(this->fields, _fieldNumber,
    UnknownField::TYPE_VARINT);
  if (!field)
    return std::nullopt;
  return field->varint();
}

//////////////////////////////////////////////////
std::optional<std::string> ExtraMessage::String(int _fieldNumber) const
{
  const auto *field = LastUnknown(this->fields, _fieldNumber,
    UnknownField::TYPE_LENGTH_DELIMITED);
  if (!field)
    return std::nullopt;
  return field->length_delimited();
}

//////////////////////////////////////////////////
std::optional<ExtraMessage> ExtraMessage::Nested(int _fieldNumber) const
{
  const auto *field = LastUnknown(this->fields, _fieldNumber,
    UnknownField::TYPE_LENGTH_DELIMITED);
  if (!field)
    return std::nullopt;

  ExtraMessage result;
  if (!result.Parse(field->length_delimited()))
    return std::nullopt;
  return result;
}

//////////////////////////////////////////////////
bool ExtraMessage::ToMessage(int _fieldNumber,
    google::protobuf::Message &_out) const
{
  const auto *field = LastUnknown(this->fields, _fieldNumber,
    UnknownField::TYPE_LENGTH_DELIMITED);
  if (!field)
    return false;
  return _out.ParseFromString(field->length_delimited());
}

//////////////////////////////////////////////////
std::string ExtraMessage::Serialize() const
{
  std::string result;
  google::protobuf::io::StringOutputStream sos(&result);
  google::protobuf::io::CodedOutputStream cos(&sos);

  for (int i = 0; i < this->fields.field_count(); ++i)
  {
    const auto &field = this->fields.field(i);
    switch (field.type())
    {
      case UnknownField::TYPE_VARINT:
        cos.WriteVarint32((field.number() << 3) | 0);
        cos.WriteVarint64(field.varint());
        break;
      case UnknownField::TYPE_FIXED32:
        cos.WriteVarint32((field.number() << 3) | 5);
        cos.WriteLittleEndian32(field.fixed32());
        break;
      case UnknownField::TYPE_FIXED64:
        cos.WriteVarint32((field.number() << 3) | 1);
        cos.WriteLittleEndian64(field.fixed64());
        break;
      case UnknownField::TYPE_LENGTH_DELIMITED:
        cos.WriteVarint32((field.number() << 3) | 2);
        cos.WriteVarint32(field.length_delimited().size());
        cos.WriteRaw(field.length_delimited().data(),
          field.length_delimited().size());
        break;
      default:
        break;
    }
  }
  return result;
}

//////////////////////////////////////////////////
bool ExtraMessage::Parse(const std::string &_data)
{
  UnknownFieldSet parsed;
  google::protobuf::io::CodedInputStream cis(
    reinterpret_cast<const uint8_t *>(_data.data()), _data.size());

  uint32_t tag;
  while ((tag = cis.ReadTag()) != 0)
  {
    const int number = tag >> 3;
    if (number == 0)
      return false;

    switch (tag & 7)
    {
      case 0:
      {
        uint64_t value;
        if (!cis.ReadVarint64(&value))
          return false;
        parsed.AddVarint(number, value);
        break;
      }
      case 1:
      {
        uint64_t value;
        if (!cis.ReadLittleEndian64(&value))
          return false;
        parsed.AddFixed64(number, value);
        break;
      }
      case 2:
      {
        uint32_t size;
        std::string value;
        if (!cis.ReadVarint32(&size) || !cis.ReadString(&value, size))
          return false;
        parsed.AddLengthDelimited(number, value);
        break;
      }
      case 5:
      {
        uint32_t value;
        if (!cis.ReadLittleEndian32(&value))
          return false;
        parsed.AddFixed32(number, value);
        break;
      }
      default:
        return false;
    }
  }

  this->fields.Clear();
  this->fields.MergeFrom(parsed);
  return true;
}

//////////////////////////////////////////////////
void SetExtraField(google::protobuf::Message &_msg, int _fieldNumber,
    uint64_t _value)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    const auto *reflection = _msg.GetReflection();
    switch (fd->cpp_type())
    {
      case FieldDescriptor::CPPTYPE_UINT64:
        reflection->SetUInt64(&_msg, fd, _value);
        break;
      case FieldDescriptor::CPPTYPE_UINT32:
        reflection->SetUInt32(&_msg, fd, static_cast<uint32_t>(_value));
        break;
      case FieldDescriptor::CPPTYPE_INT64:
        reflection->SetInt64(&_msg, fd, static_cast<int64_t>(_value));
        break;
      case FieldDescriptor::CPPTYPE_INT32:
        reflection->SetInt32(&_msg, fd, static_cast<int32_t>(_value));
        break;
      case FieldDescriptor::CPPTYPE_BOOL:
        reflection->SetBool(&_msg, fd, _value != 0);
        break;
      case FieldDescriptor::CPPTYPE_ENUM:
        reflection->SetEnumValue(&_msg, fd, static_cast<int>(_value));
        break;
      default:
        std::cerr << "SetExtraField: field " << _fieldNumber
                  << " is not a varint field" << std::endl;
        break;
    }
    return;
  }

  auto *unknown = _msg.GetReflection()->MutableUnknownFields(&_msg);
  RemoveNumber(*unknown, _fieldNumber);
  unknown->AddVarint(_fieldNumber, _value);
}

//////////////////////////////////////////////////
void SetExtraField(google::protobuf::Message &_msg, int _fieldNumber,
    const std::string &_value)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    if (fd->cpp_type() == FieldDescriptor::CPPTYPE_STRING)
      _msg.GetReflection()->SetString(&_msg, fd, _value);
    else
    {
      std::cerr << "SetExtraField: field " << _fieldNumber
                << " is not a string field" << std::endl;
    }
    return;
  }

  auto *unknown = _msg.GetReflection()->MutableUnknownFields(&_msg);
  RemoveNumber(*unknown, _fieldNumber);
  unknown->AddLengthDelimited(_fieldNumber, _value);
}

//////////////////////////////////////////////////
void SetExtraField(google::protobuf::Message &_msg, int _fieldNumber,
    const google::protobuf::Message &_value)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    if (fd->cpp_type() == FieldDescriptor::CPPTYPE_MESSAGE)
    {
      _msg.GetReflection()->MutableMessage(&_msg, fd)->ParseFromString(
        _value.SerializeAsString());
    }
    else
    {
      std::cerr << "SetExtraField: field " << _fieldNumber
                << " is not a message field" << std::endl;
    }
    return;
  }

  auto *unknown = _msg.GetReflection()->MutableUnknownFields(&_msg);
  RemoveNumber(*unknown, _fieldNumber);
  unknown->AddLengthDelimited(_fieldNumber, _value.SerializeAsString());
}

//////////////////////////////////////////////////
void SetExtraField(google::protobuf::Message &_msg, int _fieldNumber,
    const ExtraMessage &_value)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    if (fd->cpp_type() == FieldDescriptor::CPPTYPE_MESSAGE)
    {
      _msg.GetReflection()->MutableMessage(&_msg, fd)->ParseFromString(
        _value.Serialize());
    }
    else
    {
      std::cerr << "SetExtraField: field " << _fieldNumber
                << " is not a message field" << std::endl;
    }
    return;
  }

  auto *unknown = _msg.GetReflection()->MutableUnknownFields(&_msg);
  RemoveNumber(*unknown, _fieldNumber);
  unknown->AddLengthDelimited(_fieldNumber, _value.Serialize());
}

//////////////////////////////////////////////////
std::optional<uint64_t> ExtraFieldUInt(
    const google::protobuf::Message &_msg, int _fieldNumber)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    const auto *reflection = _msg.GetReflection();
    switch (fd->cpp_type())
    {
      case FieldDescriptor::CPPTYPE_UINT64:
        return reflection->GetUInt64(_msg, fd);
      case FieldDescriptor::CPPTYPE_UINT32:
        return reflection->GetUInt32(_msg, fd);
      case FieldDescriptor::CPPTYPE_INT64:
        return static_cast<uint64_t>(reflection->GetInt64(_msg, fd));
      case FieldDescriptor::CPPTYPE_INT32:
        return static_cast<uint64_t>(reflection->GetInt32(_msg, fd));
      case FieldDescriptor::CPPTYPE_BOOL:
        return reflection->GetBool(_msg, fd) ? 1u : 0u;
      case FieldDescriptor::CPPTYPE_ENUM:
        return static_cast<uint64_t>(reflection->GetEnumValue(_msg, fd));
      default:
        return std::nullopt;
    }
  }

  const auto *field = LastUnknown(
    _msg.GetReflection()->GetUnknownFields(_msg), _fieldNumber,
    UnknownField::TYPE_VARINT);
  if (!field)
    return std::nullopt;
  return field->varint();
}

//////////////////////////////////////////////////
std::optional<std::string> ExtraFieldString(
    const google::protobuf::Message &_msg, int _fieldNumber)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    if (fd->cpp_type() == FieldDescriptor::CPPTYPE_STRING)
      return _msg.GetReflection()->GetString(_msg, fd);
    return std::nullopt;
  }

  const auto *field = LastUnknown(
    _msg.GetReflection()->GetUnknownFields(_msg), _fieldNumber,
    UnknownField::TYPE_LENGTH_DELIMITED);
  if (!field)
    return std::nullopt;
  return field->length_delimited();
}

//////////////////////////////////////////////////
bool ExtraFieldMessage(const google::protobuf::Message &_msg,
    int _fieldNumber, google::protobuf::Message &_out)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    if (fd->cpp_type() != FieldDescriptor::CPPTYPE_MESSAGE ||
        !_msg.GetReflection()->HasField(_msg, fd))
    {
      return false;
    }
    return _out.ParseFromString(
      _msg.GetReflection()->GetMessage(_msg, fd).SerializeAsString());
  }

  const auto *field = LastUnknown(
    _msg.GetReflection()->GetUnknownFields(_msg), _fieldNumber,
    UnknownField::TYPE_LENGTH_DELIMITED);
  if (!field)
    return false;
  return _out.ParseFromString(field->length_delimited());
}

//////////////////////////////////////////////////
std::optional<ExtraMessage> ExtraFieldNested(
    const google::protobuf::Message &_msg, int _fieldNumber)
{
  ExtraMessage result;
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    if (fd->cpp_type() != FieldDescriptor::CPPTYPE_MESSAGE ||
        !_msg.GetReflection()->HasField(_msg, fd))
    {
      return std::nullopt;
    }
    if (!result.Parse(
        _msg.GetReflection()->GetMessage(_msg, fd).SerializeAsString()))
    {
      return std::nullopt;
    }
    return result;
  }

  const auto *field = LastUnknown(
    _msg.GetReflection()->GetUnknownFields(_msg), _fieldNumber,
    UnknownField::TYPE_LENGTH_DELIMITED);
  if (!field || !result.Parse(field->length_delimited()))
    return std::nullopt;
  return result;
}

//////////////////////////////////////////////////
void ClearExtraField(google::protobuf::Message &_msg, int _fieldNumber)
{
  if (const auto *fd = KnownField(_msg, _fieldNumber))
  {
    _msg.GetReflection()->ClearField(&_msg, fd);
    return;
  }

  RemoveNumber(*_msg.GetReflection()->MutableUnknownFields(&_msg),
    _fieldNumber);
}
}
}
