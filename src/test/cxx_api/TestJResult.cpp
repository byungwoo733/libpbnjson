// Copyright (c) 2015-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>

#include <pbnjson.hpp>

extern "C" {
#include "../../pbnjson_c/jerror_internal.h"
}

struct TestResult : public pbnjson::JResult
{
	TestResult() = default;

	TestResult(const char* str)
	{
		jerror_set(&error, JERROR_TYPE_INTERNAL, str);
	}

	const jerror* GetError() const
	{
		return error;
	}
};

TEST(TestJResult, Copy)
{
	TestResult res("TEST");
	TestResult copy = res;

	EXPECT_NE(res.GetError(), copy.GetError());
	EXPECT_EQ(res.errorString(), copy.errorString());
}

TEST(TestJResult, Move)
{
	TestResult res("TEST");
	TestResult move = std::move(res);

	EXPECT_EQ(res.GetError(), nullptr);
	EXPECT_NE(move.GetError(), nullptr);
	EXPECT_EQ(move.errorString(), std::string("Internal error. TEST"));
}
