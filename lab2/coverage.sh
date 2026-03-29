#!/bin/bash
GREEN='\033[0;32m'
NC='\033[0m'

echo "--- Полная очистка и пересборка ---"
rm -rf build && mkdir build && cd build
cmake -DCMAKE_CXX_FLAGS="--coverage" .. > /dev/null
make > /dev/null

echo "--- Запуск тестов ---"
./run_tests > /dev/null

echo -e "${GREEN}--- ФИНАЛЬНЫЙ ОТЧЕТ ПОКРЫТИЯ (COVERAGE) ---${NC}"

find . -name "*.gcda" -exec gcov -pb {} + | grep -E "File '.*src/.*'|Lines executed" | sed "s/File '.*src\//Файл: /" | sed "s/Lines executed:/Покрытие: /"

echo -e "${GREEN}-------------------------------------------${NC}"
