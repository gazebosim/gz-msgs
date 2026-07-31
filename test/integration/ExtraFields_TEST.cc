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
#include <gtest/gtest.h>

#include <google/protobuf/empty.pb.h>

#include <gz/msgs/boolean.pb.h>
#include <gz/msgs/discovery.pb.h>
#include <gz/msgs/header.pb.h>
#include <gz/msgs/int32.pb.h>
#include <gz/msgs/int64.pb.h>
#include <gz/msgs/stringmsg.pb.h>
#include <gz/msgs/time.pb.h>
#include <gz/msgs/uint32.pb.h>
#include <gz/msgs/uint64.pb.h>

#include "gz/msgs/ExtraFields.hh"

using namespace gz;

/////////////////////////////////////////////////
/// \brief When the schema knows the field number, the helpers route
/// through the real field.
TEST(ExtraFields, KnownFieldRouting)
{
  msgs::StringMsg stringMsg;
  msgs::SetExtraField(stringMsg, 2, std::string("hello"));
  EXPECT_EQ(stringMsg.data(), "hello");
  EXPECT_EQ(msgs::ExtraFieldString(stringMsg, 2).value_or(""), "hello");

  msgs::Int64 intMsg;
  msgs::SetExtraField(intMsg, 2, static_cast<uint64_t>(7));
  EXPECT_EQ(intMsg.data(), 7);
  EXPECT_EQ(msgs::ExtraFieldUInt(intMsg, 2).value_or(0), 7u);

  // A message valued field known by the schema.
  msgs::Header header;
  header.mutable_stamp()->set_sec(5);
  msgs::SetExtraField(stringMsg, 1, header);
  EXPECT_EQ(stringMsg.header().stamp().sec(), 5);

  msgs::Header headerOut;
  EXPECT_TRUE(msgs::ExtraFieldMessage(stringMsg, 1, headerOut));
  EXPECT_EQ(headerOut.stamp().sec(), 5);
}

/////////////////////////////////////////////////
/// \brief When the schema does not know the field number, the helpers
/// round trip through unknown fields and serialization.
TEST(ExtraFields, UnknownFieldRoundTrip)
{
  google::protobuf::Empty holder;
  msgs::SetExtraField(holder, 100, static_cast<uint64_t>(42));
  msgs::SetExtraField(holder, 101, std::string("abc"));

  google::protobuf::Empty reparsed;
  ASSERT_TRUE(reparsed.ParseFromString(holder.SerializeAsString()));
  EXPECT_EQ(msgs::ExtraFieldUInt(reparsed, 100).value_or(0), 42u);
  EXPECT_EQ(msgs::ExtraFieldString(reparsed, 101).value_or(""), "abc");
  EXPECT_FALSE(msgs::ExtraFieldUInt(reparsed, 999).has_value());
}

/////////////////////////////////////////////////
/// \brief A schema that knows a field and a schema that does not produce
/// the same bytes and read each other. This simulates a stable branch
/// interoperating with a newer schema.
TEST(ExtraFields, CrossSchema)
{
  // Newer schema writes through the generated field, older schema reads
  // through the unknown fields.
  msgs::StringMsg newerSchema;
  newerSchema.set_data("hello");

  google::protobuf::Empty olderSchema;
  ASSERT_TRUE(olderSchema.ParseFromString(newerSchema.SerializeAsString()));
  EXPECT_EQ(msgs::ExtraFieldString(olderSchema, 2).value_or(""), "hello");

  // Older schema writes through the unknown fields, newer schema reads
  // through the generated field. The bytes are identical.
  google::protobuf::Empty olderWriter;
  msgs::SetExtraField(olderWriter, 2, std::string("hello"));
  EXPECT_EQ(olderWriter.SerializeAsString(),
    newerSchema.SerializeAsString());

  msgs::StringMsg newerReader;
  ASSERT_TRUE(newerReader.ParseFromString(olderWriter.SerializeAsString()));
  EXPECT_EQ(newerReader.data(), "hello");
}

/////////////////////////////////////////////////
/// \brief A schema-less nested message round trips through serialization
/// and bridges into generated messages.
TEST(ExtraFields, NestedExtraMessage)
{
  msgs::ExtraMessage snapshot;
  snapshot.Set(1, static_cast<uint64_t>(4));
  snapshot.Set(2, static_cast<uint64_t>(42));

  google::protobuf::Empty holder;
  msgs::SetExtraField(holder, 8, snapshot);

  google::protobuf::Empty reparsed;
  ASSERT_TRUE(reparsed.ParseFromString(holder.SerializeAsString()));
  auto nested = msgs::ExtraFieldNested(reparsed, 8);
  ASSERT_TRUE(nested.has_value());
  EXPECT_EQ(nested->UInt(1).value_or(0), 4u);
  EXPECT_EQ(nested->UInt(2).value_or(0), 42u);

  // Bridge a schema-less message into a known generated field: build a
  // Header {stamp {sec: 5}} by field numbers and set it on a StringMsg.
  msgs::ExtraMessage stamp;
  stamp.Set(1, static_cast<uint64_t>(5));
  msgs::ExtraMessage header;
  header.Set(1, stamp);

  msgs::StringMsg stringMsg;
  msgs::SetExtraField(stringMsg, 1, header);
  EXPECT_EQ(stringMsg.header().stamp().sec(), 5);

  // And read a known generated field as a schema-less message.
  auto headerBack = msgs::ExtraFieldNested(stringMsg, 1);
  ASSERT_TRUE(headerBack.has_value());
  auto stampBack = headerBack->Nested(1);
  ASSERT_TRUE(stampBack.has_value());
  EXPECT_EQ(stampBack->UInt(1).value_or(0), 5u);
}

/////////////////////////////////////////////////
/// \brief A generated message can be stored and read through a field the
/// schema does not know.
TEST(ExtraFields, TypedMessageValue)
{
  msgs::Time time;
  time.set_sec(9);
  time.set_nsec(11);

  google::protobuf::Empty holder;
  msgs::SetExtraField(holder, 50, time);

  google::protobuf::Empty reparsed;
  ASSERT_TRUE(reparsed.ParseFromString(holder.SerializeAsString()));
  msgs::Time timeOut;
  ASSERT_TRUE(msgs::ExtraFieldMessage(reparsed, 50, timeOut));
  EXPECT_EQ(timeOut.sec(), 9);
  EXPECT_EQ(timeOut.nsec(), 11);
}

/////////////////////////////////////////////////
/// \brief Setting a field twice keeps a single value, and clearing
/// removes it.
TEST(ExtraFields, SetTwiceAndClear)
{
  google::protobuf::Empty holder;
  msgs::SetExtraField(holder, 100, static_cast<uint64_t>(1));
  msgs::SetExtraField(holder, 100, static_cast<uint64_t>(2));

  const auto &unknown =
    holder.GetReflection()->GetUnknownFields(holder);
  int entries = 0;
  for (int i = 0; i < unknown.field_count(); ++i)
  {
    if (unknown.field(i).number() == 100)
      ++entries;
  }
  EXPECT_EQ(entries, 1);
  EXPECT_EQ(msgs::ExtraFieldUInt(holder, 100).value_or(0), 2u);

  msgs::ClearExtraField(holder, 100);
  EXPECT_FALSE(msgs::ExtraFieldUInt(holder, 100).has_value());

  // Clear also works on known fields.
  msgs::StringMsg stringMsg;
  stringMsg.set_data("hello");
  msgs::ClearExtraField(stringMsg, 2);
  EXPECT_TRUE(stringMsg.data().empty());
}

/////////////////////////////////////////////////
/// \brief Every varint compatible field type routes through the real field.
TEST(ExtraFields, KnownFieldAllVarintTypes)
{
  msgs::UInt64 u64;
  msgs::SetExtraField(u64, 2, static_cast<uint64_t>(64));
  EXPECT_EQ(u64.data(), 64u);
  EXPECT_EQ(msgs::ExtraFieldUInt(u64, 2).value_or(0), 64u);

  msgs::UInt32 u32;
  msgs::SetExtraField(u32, 2, static_cast<uint64_t>(32));
  EXPECT_EQ(u32.data(), 32u);
  EXPECT_EQ(msgs::ExtraFieldUInt(u32, 2).value_or(0), 32u);

  msgs::Int32 i32;
  msgs::SetExtraField(i32, 2, static_cast<uint64_t>(31));
  EXPECT_EQ(i32.data(), 31);
  EXPECT_EQ(msgs::ExtraFieldUInt(i32, 2).value_or(0), 31u);

  msgs::Boolean boolean;
  msgs::SetExtraField(boolean, 2, static_cast<uint64_t>(1));
  EXPECT_TRUE(boolean.data());
  EXPECT_EQ(msgs::ExtraFieldUInt(boolean, 2).value_or(0), 1u);

  // An enum field known by the schema (Discovery.type, field 4).
  msgs::Discovery discovery;
  msgs::SetExtraField(discovery, 4,
    static_cast<uint64_t>(msgs::Discovery::ADVERTISE));
  EXPECT_EQ(discovery.type(), msgs::Discovery::ADVERTISE);
  EXPECT_EQ(msgs::ExtraFieldUInt(discovery, 4).value_or(0),
    static_cast<uint64_t>(msgs::Discovery::ADVERTISE));
}

/////////////////////////////////////////////////
/// \brief A type mismatch on a known field is rejected without modifying
/// the message.
TEST(ExtraFields, KnownFieldTypeMismatch)
{
  msgs::StringMsg stringMsg;
  msgs::Int32 intMsg;
  msgs::Time time;

  // Varint value into a string field.
  msgs::SetExtraField(stringMsg, 2, static_cast<uint64_t>(1));
  EXPECT_TRUE(stringMsg.data().empty());

  // String value into an int field.
  msgs::SetExtraField(intMsg, 2, std::string("nope"));
  EXPECT_EQ(intMsg.data(), 0);

  // Message values into a string field.
  msgs::SetExtraField(stringMsg, 2, time);
  msgs::ExtraMessage extra;
  msgs::SetExtraField(stringMsg, 2, extra);
  EXPECT_TRUE(stringMsg.data().empty());

  // Mismatched getters return no value.
  EXPECT_FALSE(msgs::ExtraFieldUInt(stringMsg, 2).has_value());
  EXPECT_FALSE(msgs::ExtraFieldString(intMsg, 2).has_value());
  EXPECT_FALSE(msgs::ExtraFieldMessage(intMsg, 2, time));
  EXPECT_FALSE(msgs::ExtraFieldNested(intMsg, 2).has_value());

  // A message field that is known but not set.
  EXPECT_FALSE(msgs::ExtraFieldMessage(stringMsg, 1, time));
  EXPECT_FALSE(msgs::ExtraFieldNested(stringMsg, 1).has_value());
}

/////////////////////////////////////////////////
/// \brief The remaining ExtraMessage API: assignment, strings, generated
/// message values and absent fields.
TEST(ExtraFields, ExtraMessageApi)
{
  msgs::ExtraMessage original;
  original.Set(1, static_cast<uint64_t>(7));
  original.Set(2, std::string("text"));

  msgs::Time time;
  time.set_sec(3);
  original.Set(3, time);

  msgs::ExtraMessage assigned;
  assigned = original;
  EXPECT_EQ(assigned.UInt(1).value_or(0), 7u);
  EXPECT_EQ(assigned.String(2).value_or(""), "text");

  msgs::Time timeOut;
  ASSERT_TRUE(assigned.ToMessage(3, timeOut));
  EXPECT_EQ(timeOut.sec(), 3);

  // Absent fields.
  EXPECT_FALSE(assigned.UInt(9).has_value());
  EXPECT_FALSE(assigned.String(9).has_value());
  EXPECT_FALSE(assigned.Nested(9).has_value());
  EXPECT_FALSE(assigned.ToMessage(9, timeOut));

  // Self assignment.
  assigned = assigned;
  EXPECT_EQ(assigned.UInt(1).value_or(0), 7u);
}

/////////////////////////////////////////////////
/// \brief Fixed width fields round trip through Parse() and Serialize(),
/// and survive RemoveNumber() when another field is replaced.
TEST(ExtraFields, FixedWidthFields)
{
  // Craft bytes: field 20 fixed32 (7), field 21 fixed64 (9), field 1
  // varint (5).
  std::string bytes;
  bytes += "\xa5\x01";              // Tag: field 20, wire type 5.
  bytes += std::string("\x07\x00\x00\x00", 4);
  bytes += "\xa9\x01";              // Tag: field 21, wire type 1.
  bytes += std::string("\x09\x00\x00\x00\x00\x00\x00\x00", 8);
  bytes += "\x08\x05";              // Tag: field 1, wire type 0, value 5.

  msgs::ExtraMessage parsed;
  ASSERT_TRUE(parsed.Parse(bytes));
  EXPECT_EQ(parsed.UInt(1).value_or(0), 5u);

  // Serialize preserves the fixed width fields: parse the output again.
  msgs::ExtraMessage reparsed;
  ASSERT_TRUE(reparsed.Parse(parsed.Serialize()));
  EXPECT_EQ(reparsed.UInt(1).value_or(0), 5u);

  // Replacing the varint field keeps the fixed width fields.
  reparsed.Set(1, static_cast<uint64_t>(6));
  msgs::ExtraMessage again;
  ASSERT_TRUE(again.Parse(reparsed.Serialize()));
  EXPECT_EQ(again.UInt(1).value_or(0), 6u);
  EXPECT_EQ(again.Serialize().size(), reparsed.Serialize().size());
}

/////////////////////////////////////////////////
/// \brief Malformed payloads are rejected by Parse().
TEST(ExtraFields, ParseFailures)
{
  msgs::ExtraMessage extra;

  // Truncated varint value.
  EXPECT_FALSE(extra.Parse(std::string("\x08", 1)));

  // Field number zero.
  EXPECT_FALSE(extra.Parse(std::string("\x05", 1)));

  // Unsupported wire type (group start).
  EXPECT_FALSE(extra.Parse(std::string("\x0b", 1)));

  // Truncated length delimited value.
  EXPECT_FALSE(extra.Parse(std::string("\x12\x05" "abc", 5)));

  // Truncated fixed width values.
  EXPECT_FALSE(extra.Parse(std::string("\xa5\x01\x07\x00", 4)));
  EXPECT_FALSE(extra.Parse(std::string("\xa9\x01\x09\x00", 4)));

  // A nested field that does not parse is not returned.
  google::protobuf::Empty holder;
  msgs::SetExtraField(holder, 60, std::string("\x0b", 1));
  EXPECT_FALSE(msgs::ExtraFieldNested(holder, 60).has_value());

  msgs::ExtraMessage badNested;
  badNested.Set(5, std::string("\x0b", 1));
  EXPECT_FALSE(badNested.Nested(5).has_value());

  // Absent unknown fields for the remaining getters.
  msgs::Time time;
  EXPECT_FALSE(msgs::ExtraFieldString(holder, 999).has_value());
  EXPECT_FALSE(msgs::ExtraFieldMessage(holder, 999, time));
}

/////////////////////////////////////////////////
/// \brief Group entries in the unknown field set are preserved by
/// RemoveNumber() and skipped by Serialize().
TEST(ExtraFields, GroupEntriesPreserved)
{
  google::protobuf::Empty holder;
  holder.GetReflection()->MutableUnknownFields(&holder)->AddGroup(70);
  msgs::SetExtraField(holder, 71, static_cast<uint64_t>(1));
  msgs::SetExtraField(holder, 71, static_cast<uint64_t>(2));

  const auto &unknown = holder.GetReflection()->GetUnknownFields(holder);
  bool groupKept = false;
  for (int i = 0; i < unknown.field_count(); ++i)
  {
    if (unknown.field(i).number() == 70 &&
        unknown.field(i).type() ==
        google::protobuf::UnknownField::TYPE_GROUP)
    {
      groupKept = true;
    }
  }
  EXPECT_TRUE(groupKept);
  EXPECT_EQ(msgs::ExtraFieldUInt(holder, 71).value_or(0), 2u);
}
