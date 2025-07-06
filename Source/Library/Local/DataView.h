#pragma once

template<class T>
class ByteDataView {
public:

	ByteDataView() = default;
	ByteDataView(T* data, size_t size) : m_data(data), m_size(size) {}
	ByteDataView(const ByteDataView&) = default;
	ByteDataView& operator=(const ByteDataView&) = default;

	auto begin() {
		return m_data;
	}
	auto begin() const {
		return m_data;
	}
	auto end() {
		return m_data + m_size;
	}
	auto end() const {
		return m_data + m_size;
	}
	auto rbegin() {
		return std::reverse_iterator<T*>(end());
	}
	auto rbegin() const {
		return std::reverse_iterator<T*>(end());
	}
	auto rend() {
		return std::reverse_iterator<T*>(begin());
	}
	auto rend() const {
		return std::reverse_iterator<T*>(begin());
	}

	size_t size() const {
		return m_size;
	}
	T* data() {
		return m_data;
	}
	const T* data() const {
		return m_data;
	}
	
	void* bytedata() {
		return static_cast<void*>(m_data);
	}
	size_t byteSize() const {
		return m_size * typesize;
	}

	T& operator[](size_t index) {
		return m_data[index];
	}
	const T& operator[](size_t index) const {
		return m_data[index];
	}

private:

	T* m_data = nullptr;
	size_t m_size = 0;
	static constexpr size_t typesize = sizeof(T);

};