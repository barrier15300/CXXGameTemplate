#pragma once
#include "Common.h"

template<size_t _size>
struct MultiInt {

	using word_t = uint64_t;

	static constexpr size_t WordSize = _size;
	static constexpr size_t WordTypeBitSize = sizeof(word_t) * 8;
	static constexpr size_t BitSize = _size * WordTypeBitSize;

	MultiInt() = default;
	MultiInt(word_t word) : m_bits(word) {}


	union {
		struct {
			std::array<word_t, WordSize> m_words{};
		};
		struct {
			std::bitset<BitSize> m_bits;
		};
	};

	constexpr bool IsZero() const noexcept {
		for (const auto& word : m_words) {
			if (word != 0) return false;
		}
		return true;
	}
	constexpr bool BitCheck(size_t idx) const {
		return m_bits[idx];
	}
	constexpr size_t GetnBit() const {
		for (size_t i = WordSize; i-- > 0;) {
			if (m_words[i] != 0) {
				return i * WordTypeBitSize + std::bit_width(m_words[i]);
			}
		}
		return BitSize;
	}



	constexpr bool AssignAddModule(word_t lhs, word_t* dest, bool carry) {
		return _addcarryx_u64(carry, lhs, *dest, dest);

	}
	constexpr MultiInt& AssignAdd(const MultiInt& rhs) {
		bool carry = false;
		for (size_t i = 0; i < WordSize; ++i) {
			carry = AssignAddModule(
				rhs.m_words[i],
				m_words.data() + i,
				carry
			);
		}
		return *this;
	}
	constexpr MultiInt& AssignSub(const MultiInt& rhs) {
		bool borrow = true;
		for (size_t i = 0; i < WordSize; ++i) {
			borrow = AssignAddModule(
				~rhs.m_words[i],
				m_words.data() + i,
				borrow
			);
		}
		return *this;
	}
	constexpr word_t AssignMulModule(word_t lhs, word_t *dest, word_t carry) {
		word_t high = 0, low = _umul128(lhs, *dest, &high);
		high += AssignAddModule(carry, &low, 0);
		*dest = low;
		return high;
	}
	constexpr MultiInt& AssignMul(const MultiInt& rhs) {
		word_t carry = 0;
		for (size_t i = 0; i < WordSize; ++i) {
			carry = AssignMulModule(
				rhs.m_words[i],
				m_words.data() + i,
				carry
			);
		}
		return *this;
	}
	
};
