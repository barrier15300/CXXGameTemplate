#pragma once
#include <vector>
#include <string>
#include <cstdlib>

class string_expr2val {
public:

	string_expr2val() {};

	struct exprobj {
		struct expr {
			enum type {
				add,
				mul,
				div,
				rem
			} et = add;
			std::vector<expr> objs{};
			double val = 0;
			expr invoke(type t, expr &rhs) {
				expr ret{t, {}, 0};
				for (size_t i = 0, size = objs.size(); i < size; ++i) {
					auto &obj = objs[i];
				}

				// "-(1 + 2) - (3 * (4 / 5))"
			}
			double invoke_expr(const expr &rhs) const {
				if (rhs.et == add) {
					return val + rhs.val;
				}
				if (rhs.et == mul) {
					return val * rhs.val;
				}
				if (rhs.et == div) {
					return val / rhs.val;
				}
				if (rhs.et == rem) {
					return fmod(val, rhs.val);
				}
			}
		};

		expr _expr{};

		void parse(std::string_view str) {
			
		}

		expr _parse(std::string_view str) {
			expr ret;
			int sign = 1;

			for (size_t i = 0, size = str.size(); i < size; ++i) {
				char c = str[i];
				switch (c) {
					case '+':
						ret.et = expr::add;
						sign = 1;
						break;
					case '-':
						sign = -1;
						break;
					case '*':
						ret.et = expr::mul;
						break;
					case '/':
						ret.et = expr::div;
						break;
					case '%':
						ret.et = expr::rem;
						break;
				}
				if (std::isdigit(c)) {
					ret.val = std::stod(str.substr(i).data(), &i) * sign;
					
				}
			}
		}

		
	};

	void Parse(const std::string &str) {

		
	}

	
	
	
	
};