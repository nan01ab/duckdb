//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/matcher/type_matcher.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/types.hpp"

namespace duckdb {

//! The TypeMatcher class contains a set of matchers that can be used to pattern match TypeIds for Rules
class TypeMatcher {
public:
	virtual ~TypeMatcher() {
	}

	virtual bool Match(const LogicalType &type) = 0;
};

//! The SpecificTypeMatcher class matches only a single specified type
class SpecificTypeMatcher : public TypeMatcher {
public:
	explicit SpecificTypeMatcher(LogicalType type) : type(std::move(type)) {
	}

	bool Match(const LogicalType &type_p) override {
		return type_p == this->type;
	}

private:
	LogicalType type;
};
//! The SpecificTypeMatcher class matches only a type out of a set of types
class SetTypesMatcher : public TypeMatcher {
public:
	explicit SetTypesMatcher(vector<LogicalType> types_p) : types(std::move(types_p)) {
	}

	bool Match(const LogicalType &type_p) override {
		for (auto &type : types) {
			if (type == type_p) {
				return true;
			}
		}
		return false;
	}

private:
	vector<LogicalType> types;
};

//! The NumericTypeMatcher class matches any numeric type (DECIMAL, INTEGER, etc...)
class NumericTypeMatcher : public TypeMatcher {
public:
	bool Match(const LogicalType &type) override {
		return type.IsNumeric();
	}
};

//! The IntegerTypeMatcher class matches only integer types (INTEGER, SMALLINT, TINYINT, BIGINT)
class IntegerTypeMatcher : public TypeMatcher {
public:
	bool Match(const LogicalType &type) override {
		return type.IsIntegral();
	}
};

} // namespace duckdb
