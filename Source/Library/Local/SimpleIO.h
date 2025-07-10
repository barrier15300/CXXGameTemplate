#pragma once
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

class CommandLine {

	std::vector<const char*> args;

public:
	
	CommandLine(std::initializer_list<const char*>&& _args) {
		args.reserve(_args.size());
		std::copy(_args.begin(), _args.end(), std::back_inserter(args));
	}

	operator std::string() {
		std::string ret;
		size_t length = 0;
		for (auto&& arg : args) {
			length += std::strlen(arg) + 1;
		}
		ret.reserve(length);
		for (std::string arg : args) {
			ret += arg;
			ret += ' ';
		}
		ret.pop_back();
		return ret;
	}
};

class SimpleIO {

	SimpleIO() {}
	SimpleIO(const SimpleIO&) = delete;
	SimpleIO(SimpleIO&&) = delete;

	SimpleIO& operator=(const SimpleIO&) = delete;
	SimpleIO& operator=(SimpleIO&&) = delete;

	/// <summary>
	/// Simple Nameless Pipe Object
	/// </summary>
	class PipeObject {

		friend SimpleIO;

		PipeObject(const std::string& cmd, const std::string& mode) {
			m_pipe = _popen(cmd.c_str(), mode.c_str());
		}
		FILE* m_pipe = nullptr;

	public:

		~PipeObject() {
			if (!IsNull()) {
				_pclose(m_pipe);
			}
		}

		PipeObject(PipeObject&&) = default;
		PipeObject& operator=(PipeObject&&) = default;

		PipeObject(const PipeObject&) = delete;
		PipeObject& operator=(const PipeObject&) = delete;

		bool IsNull() {
			return m_pipe == nullptr;
		}

		size_t Write(const void* buf, size_t bytenum) {
			if (IsNull()) {
				return 0;
			}
			return fwrite(buf, 1, bytenum, m_pipe);
		}

		size_t Read(void* buf, size_t bytenum) {
			if (IsNull()) {
				return 0;
			}
			return fread(buf, 1, bytenum, m_pipe);
		}
	};

	/// <summary>
	/// Simple a Console Object
	/// </summary>
	class ConsoleObject : public std::ofstream {
		
		friend SimpleIO;

		using std::ofstream::basic_ofstream;

		ConsoleObject() {
			Open();
		}
		~ConsoleObject() {
			Close();
		}

		bool openflag = false;

		ConsoleObject& operator=(const ConsoleObject&) = default;
		ConsoleObject& operator=(ConsoleObject&&) = default;

	public:

		ConsoleObject(const ConsoleObject&) = delete;
		ConsoleObject(ConsoleObject&&) = delete;
		
		void Open() {
			if (IsOpen()) {
				return;
			}
			AllocConsole();
			this->open("CONOUT$");
			if (!this->is_open()) {
				FreeConsole();
				return;
			}
			openflag = true;
		}

		void Close() {
			if (!IsOpen()) {
				return;
			}
			FreeConsole();
			this->close();
			openflag = false;
		}

		bool IsOpen() {
			return openflag;
		}
	};

public:

	static SimpleIO& GetInstance() {
		static SimpleIO instance;
		return instance;
	}

	void SwitchFastStdIO() {
		std::ios::sync_with_stdio(false);
		std::cin.tie(nullptr);
	}
	
	PipeObject MakePipe(const std::string& cmd, const std::string& mode) {
		return PipeObject(cmd, mode);
	}

	ConsoleObject& ViewConsole() {
		static ConsoleObject instance;
		return instance;
	}

};