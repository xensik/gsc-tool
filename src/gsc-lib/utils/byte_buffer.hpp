#pragma once

class byte_buffer
{
private:
	std::vector<std::uint8_t>	m_data;
	std::size_t					m_size;
	std::size_t					m_pos;

public:
	byte_buffer();
	byte_buffer(std::size_t size);
	byte_buffer(std::string filename);
	byte_buffer(std::shared_ptr<std::vector <std::uint8_t>> buffer);
	~byte_buffer();

	void clear();
	bool is_avail();
	void seek(std::size_t pos);
	void seek_neg(std::size_t pos);

	template <typename T> T read()
	{
		auto ret = *reinterpret_cast<T*>(m_data.data() + m_pos);
		m_pos += sizeof(T);
		return ret;
	}

	template <typename T> T* write(T data)
	{
		T* mem = reinterpret_cast<T*>(m_data.data() + m_pos);
		memcpy(mem, &data, sizeof(T));

		m_pos += sizeof(T);

		return mem;
	}

	void write_cpp_string(const std::string& data);
	void write_string(const std::string& data);
	void write_opaque_string(std::uint16_t id, const std::string& data = nullptr);
	std::string read_string();
	std::string read_opaque_string();
	std::string get_bytes_print(std::size_t index, std::size_t count);
	std::size_t get_pos();
	std::vector<std::uint8_t>& get_buffer();
};
