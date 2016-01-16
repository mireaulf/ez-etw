#include <etw_test/utils.h>
#include <Windows.h>
#ifdef max
#undef max
#endif

using namespace test_utils::process;
#include <iostream>

namespace test_utils {
	namespace process {
		bool launch(const std::string& filename, uintptr_t& process_handle) {
			STARTUPINFO startup_info = { 0 };
			PROCESS_INFORMATION process_info = { 0 };
			startup_info.cb = sizeof(startup_info);
			bool is_launched = 
				CreateProcessA(filename.c_str(), 
					nullptr, 
					nullptr, 
					nullptr,
					false,
					CREATE_NEW_CONSOLE,
					nullptr,
					nullptr,
					&startup_info,
					&process_info) != FALSE;
			if(is_launched) {
				process_handle = reinterpret_cast<uintptr_t>(process_info.hProcess);
			}
			return is_launched;
		}
		bool terminate(const uintptr_t& process_handle) {
			bool success = TerminateProcess(
				reinterpret_cast<HANDLE>(process_handle), 
				std::numeric_limits<UINT>::max()) != 0;
			std::cout << "last error: " << GetLastError() << std::endl;
			return success;
		}
	}
}
