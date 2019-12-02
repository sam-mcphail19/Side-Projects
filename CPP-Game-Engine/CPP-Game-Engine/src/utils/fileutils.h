#pragma once

#include <string>

namespace sam_engine {

	std::string read_file(const char* filepath) {

		FILE* file = fopen(filepath, "rb");

		if (file == nullptr) {

			perror("fopen");
			return (std::string) NULL;

		}
			
		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		std::string result(length, 0);
		fseek(file, 0, SEEK_SET);
		fread(&result[0], 1, length, file);
		fclose(file);

		return result;

	}

}