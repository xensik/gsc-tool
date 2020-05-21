#include "stdinc.hpp"

long flength(FILE* fp)
{
	long i = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long ret = ftell(fp);
	fseek(fp, i, SEEK_SET);
	return ret;
}

void fsave(const std::string& name, const std::vector<std::uint8_t>& data)
{
	FILE* fp = fopen(name.data(), "wb");
	fwrite(data.data(), 1, data.size(), fp);
	fclose(fp);
}

byte_buffer::byte_buffer()
{
	m_data.resize(0x100000);
	std::fill(m_data.begin(), m_data.end(), 0);
	m_size = m_data.size();
	m_pos = 0;
}

byte_buffer::byte_buffer(std::size_t size)
{
	m_data.resize(size);
	std::fill(m_data.begin(), m_data.end(), 0);
	m_size = size;
	m_pos = 0;
}

byte_buffer::byte_buffer(std::shared_ptr<std::vector <std::uint8_t>> buffer)
{
	// move the buffer
	m_size = buffer->size();
	m_pos = 0;
}

byte_buffer::byte_buffer(std::string filename)
{
	m_size = 0;
	m_pos = 0;

	FILE* fp = fopen(filename.c_str(), "rb");
	if (fp)
	{
		long len = flength(fp);
		m_data.resize(len);
		fread(m_data.data(), len, 1, fp);
		fclose(fp);
		m_size = len;
	}
	else
	{
		printf("Couldn't open file %s!\n", filename.data());
		std::exit(-1);
	}
}

byte_buffer::~byte_buffer()
{
	m_data.clear();
	m_pos = 0;
}

void byte_buffer::clear()
{
	std::fill(m_data.begin(), m_data.end(), 0);
}

bool byte_buffer::is_avail()
{
	if (m_pos < m_data.size()) return true;
	return false;
}

void byte_buffer::seek(std::size_t pos)
{
	m_pos += pos;
}
void byte_buffer::seek_neg(std::size_t pos)
{
	m_pos -= pos;
}

void byte_buffer::write_cpp_string(const std::string& data)
{
	strcpy(reinterpret_cast<char*>(m_data.data() + m_pos), data.data());
	m_pos += data.size();
}

void byte_buffer::write_string(const std::string& data)
{
	//printf("string: '%s'\n", data.c_str());
	strcpy(reinterpret_cast<char*>(m_data.data() + m_pos), data.data());
	m_pos += data.size() + 1;
}

void byte_buffer::write_opaque_string(std::uint16_t id, const std::string& data)
{

}

std::string byte_buffer::read_string()
{
	auto ret = std::string(reinterpret_cast<const char*>(m_data.data() + m_pos));
	m_pos += ret.size() + 1;
	return ret;
}

std::string byte_buffer::read_opaque_string()
{
	auto temp = this->read<std::uint16_t>();

	if (!temp)
	{
		return this->read_string();
	}

	return std::to_string(temp);
}

std::string byte_buffer::get_bytes_print(std::size_t index, std::size_t count)
{
	std::string shit = "";
	for (int i = index; i < index + count; i++)
	{
		shit = va("%s %02X", shit.data(), (*reinterpret_cast<std::uint8_t*>(m_data.data() + i)));
	}
	return shit;
}

std::size_t byte_buffer::get_pos()
{
	return m_pos;
}

std::vector<std::uint8_t>& byte_buffer::get_buffer()
{
	return m_data;
}

std::string ReadFile(std::string file)
{
	std::string buffer;

	std::ifstream stream(file, std::ios::binary);
	if (stream.good())
	{
		if (!stream.is_open()) return buffer;

		stream.seekg(0, std::ios::end);
		std::streamsize size = stream.tellg();
		stream.seekg(0, std::ios::beg);

		if (size > -1)
		{
			buffer.clear();
			buffer.resize(static_cast<uint32_t>(size));

			stream.read(const_cast<char*>(buffer.data()), size);
		}

		stream.close();
	}

	return buffer;
}

void SaveFile(std::string file, std::vector<std::uint8_t> buffer)
{
	fsave(file, buffer);
}