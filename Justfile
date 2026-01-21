_default:
    @just --list

configure preset:
    cmake --preset {{preset}}

build preset:
    cmake --build --preset {{preset}}

fmt:
    find src -type f \( -name "*.cpp" -o -name "*.h" \) -not -path '*/.*' -print0 | xargs -0 clang-format -i

iwyu:
    iwyu_tool.py -p . -- -Xiwyu --cxx17ns | fix_includes.py

lint:
    cppcheck --project=compile_commands.json -itests --enable=all --suppress=missingIncludeSystem
