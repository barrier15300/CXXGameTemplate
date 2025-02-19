#pragma once
#include "_structhelper.h"

struct DateData {
	
	DateData() : __datedata{} {}

	union {
		struct {
			int Year;
			int Mon;
			int Day;
			int Hour;
			int Min;
			int Sec;
		};
		struct {
			std::array<int, 6> __arr;
		};
		struct {
			DATEDATA __datedata;
		};
	};

	static DateData NowDateTime() {
		DateData ret;
		return ret.Update();
	}

	DateData Update() {
		GetDateTime(&__datedata);
		return *this;
	}

	std::string ToString() {
		return fmt::format("{}/{}/{} {:>2d}:{:>2d}:{:>2d}", Year, Mon, Day, Hour, Min, Sec);
	}
};

TO_JSON(,DateData,{
	j = v.__arr;
	});
FROM_JSON(,DateData,{
	for (size_t i = 0, size = v.__arr.size(); i < size; ++i) {
		j.at(i).get_to(v.__arr.at(i));
	}
	});