cxx=g++
cxx_flags=-Werror -Wpedantic -Wall -Wextra -std=c++2a -g
build_dir=build
sources=$(wildcard src/*.cpp)
raw_objects=$(patsubst %.cpp,%.o,$(notdir $(sources)))
objects=$(addprefix $(build_dir)/, $(raw_objects))
headers=$(wildcard headers/*.h)

ifeq ($(OS),Windows_NT)
	exe=risk.exe
	makedir=mdmake
else
	exe=risk
	makedir=mkdir -p
endif

$(build_dir)/$(exe): $(objects)
	$(cxx) $(cxx_flags) -o $@ $^

$(build_dir)/%.o: src/%.cpp $(headers) | $(build_dir)
	$(cxx) $(cxx_flags) -o $@ -c $< -I./headers

$(build_dir):
	$(makedir) $@
