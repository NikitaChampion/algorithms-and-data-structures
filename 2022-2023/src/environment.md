# Как настроить окружение на своем компьютере

## Введение

С недавнего времени на сервере используется новая схема тестирования решений, а точнее, отлавливается большее число ошибок за счет использования других ключей компиляции. Цель этой заметки &mdash; помочь вам получить такой же эффект на своей системе.

Помимо этого, описанные здесь рекомендации позволят вам организовать более качественное тестирование кода.

На сервере компилируется 2 варианта вашего решения, а именно:

```bash
g++-8 solution.cpp -fuse-ld=gold -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O2 -Wall -Werror -Wsign-compare -o debug_solution
g++-8 solution.cpp -std=c++17 -O2 -o fast_solution
```

Здесь стоит отметить следующее:

1. `-Wall` и `-Werror`. Первый флаг заставляет компилятор выдавать дополнительные предупреждения, второй &mdash; трактовать любое предупреждение как ошибку компиляции. Таким образом, ваш код не должен давать ни одного предупреждения.
2. `-O2` включает оптимизации кода.
3. `-std=c++17` нужен для использования стандарта `C++17`.

Во втором случае решение компилируется с включенными *санитайзерами*. Любое обращение за пределы массива, знаковое переполнение целочисленных типов и любые подобные проявления некорректной работы с памятью и undefined behavior будут вызывать ошибку времени выполнения и приводить к вердикту Runtime Error на сервере, а не ситуации, когда ваша программа иногда работает, а иногда нет.

Любое обращение за пределы массива, знаковое переполнение целочисленных типов и любые подобные проявления некорректной работы с памятью и undefined behavior будут вызывать ошибку времени выполнения и приводить к вердикту Runtime Error на сервере, а не ситуации, когда ваша программа иногда работает, а иногда нет.

Обратите внимание, что `-fsanitize=address` также включает детектор утечек памяти. Поэтому, помимо контроля над тем, куда обращается ваша программа, на сервере также производится проверка, что в вашей программе нет утечек памяти (сделали `new` и не сделали `delete`). В подавляющем большинстве случаев вам вообще не нужно оперировать с динамической памятью вручную (например, для создания массивов используйте стандартные контейнеры вроде `std::vector`, которые правильно обращаются с памятью).

Поскольку санитайзеры вносят заметный оверхед в решение (значительно увеличивается потребляемая память и в несколько раз может возрасти время исполнения), то они используются только для запуска в задачах с большим потреблением памяти на маленьких тестах (обычно только на онлайн тестах), чтобы правильные решения не могли получить вердикты ML или TL.

Компилируется и запускается всё на `Intel(R) Xeon(R) CPU E5-2660 @ 2.20GHz, 20480KB cache, virtualizаtion on 1 core, 4GB RAM` с Linux-ом.

## Примеры кода

Давайте рассмотрим на примерах, как работает компилятор с указанным выше набором флагов. В этом разделе приведены комментарии по поведению `gcc` и `clang` в Linux с включенными санитайзерами. Про другие ОС см. секции ниже.

Здесь происходит знаковое переполнение при вычислении `BAD_MAX_INT`, что порождает соответствующее предупреждение. В десятой строке происходит сравнение `int` и `size_t`, что также порождает предупреждение. **Никогда** не игнорируйте это предупреждение: при таком сравнении `int` приводится к беззнаковому типу, таким образом, неравенство `-1 > size_t` всегда выполнено. Этот код не компилируется с флагом `-Werror`.

```cpp
#include <iostream>
#include <vector>

const int BAD_MAX_INT = (1 << 31) - 1;

int main() {
    size_t n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < data.size(); ++i) {
        std::cin >> data[i];
    }
    return 0;
}
```

В этом примере происходит очевидный выход за пределы массива. Если заменить динамический массив на `std::vector`, произойдет то же самое. И `gcc`, и `clang` успешно отловят данную ошибку с включенным флагом `-fsanitize=address`.

```cpp
#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    int *data = new int[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    std::cout << data[n] << '\n';
    delete[] data;
    return 0;
}
```

В этом примере есть утечка памяти (нет `delete[]`).

```cpp
#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    int *data = new int[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    return 0;
}
```

Здесь возникает `undefined behavior` при переполнении (введем `2000000000 2000000000`), который отловят и `clang`, и `gcc` с включенным флагом `-fsanitize=undefined`.

```cpp
#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
    return 0;
}
```

## Настройка на своей системе

Мы рекомендуем использовать среду CLion для разработки. Всем студентам ВШЭ предоставляется бесплатная лицензия. Вы можете работать из любой ОС, однако добиться поведения, описанного выше, можно только на Linux и Mac OS. Опыт показывает, что **отлавливать ошибки c обращениями за пределы массива, знаковым переполнением целочисленных типов и любыми подобными проявлениями некорректной работы с памятью и undefined behavior с использованием Windows достаточно мучительно**, поэтому лучше заранее озаботиться установкой Linux. Самый удобный вариант &mdash; развернуть VirtualBox. Если же у вас Windows 10, то еще одним вариантом будет установка [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) и [его интеграция с CLion](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-clion.html).

Ниже приведена инструкция для CLion.

<details>
<summary>Windows</summary>

На Windows без использования WSL санитайзеры не работают. Вы точно так же можете использовать CLion, но поддержки ASan там не будет (если только вы не настроили интеграцию с WSL, см. ссылки выше).

</details>

<details>
<summary>Linux</summary>

Создайте новый проект. Зайдите в File -> Settings -> Build, Execution, Deployment -> CMake. Изначально там будет только один профиль Debug. Когда вы нажмете + добавится профиль Release, который пригодится в дальнейшем. Добавьте еще один профиль, назовите его ASAN. В CMake Options запишите

```bash
-DCMAKE_BUILD_TYPE=ASAN
```

Отредактируйте ваш `CMakeLists.txt`. Он будет выглядеть примерно так:

```cmake
cmake_minimum_required(VERSION 3.24)
project(your_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_executable(your_project main.cpp)
```

Теперь вы легко можете переключаться между разными видами сборок: Debug для пошагового дебага, Release для тестирования производительности, ASan для запуска
с санитайзерами.

</details>

<details>
<summary>Mac OS</summary>

По сравнению с Linux, на маке необходимо произвести ряд дополнительных действий, чтобы получить такое же поведение, как и там.

Создайте новый проект. Зайдите в CLion -> Preferences -> Build, Execution, Deployment -> CMake. Изначально там будет только один профиль Debug. Когда вы нажмете + добавится профиль Release, который пригодится в дальнейшем. Добавьте еще два профиля, назовите их ASAN и UBSAN. В CMake Options запишите

```bash
-DCMAKE_BUILD_TYPE=ASAN
```

и

```bash
-DCMAKE_BUILD_TYPE=UBSAN
```

соответственно.

Отредактируйте ваш `CMakeLists.txt`. Он будет выглядеть примерно так:

```cmake
cmake_minimum_required(VERSION 3.24)
project(your_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

set(CMAKE_CXX_FLAGS_UBSAN "-g -fsanitize=undefined"
        CACHE STRING "Compiler flags in ubsan build"
        FORCE)

add_executable(your_project main.cpp)
```

Далее, по умолчанию на маке стоит `clang`. Также `gcc` симлинкается на `clang`. Но системный `clang`, к сожалению, не поддерживает санитайзеры (при запуске ASAN / UBSAN) упадет с ошибкой "detect_leaks is not supported on this platform". Поэтому нам нужно будет установить собственные компиляторы. Далее приведен гайд, как это можно сделать:

Для начала установите [homebrew](https://brew.sh/), если он у вас еще не установлен.

Затем выберите каким компилятором вы будете пользоваться: `gcc` или `clang` (лично я использую и рекомендую устанавливать оба; `gcc` на M1 не будет запускаться с санитайзерами). Дебагать в `clang`-е гораздо удобнее. `gcc`, в свою очередь, вам придется использовать во многих задачах со взломами, где вам потребуется покопаться в кишках `gcc`.

<details>
<summary>clang</summary>

Выполните команду

```bash
brew install llvm
```

Далее вам нужно найти путь до `clang`-а, который вместе с `llvm` из brew приехал. С этим вам помогут команды

```bash
brew info llvm  # выведет информацию про установленный пакет
```

```bash
brew --prefix llvm  # выведет путь до директории, на Intel маках обычно /usr/local/bin/llvm, на M1 маках – /opt/homebrew/opt/llvm
```

Вас интересует `clang`. Зайдите в папку `bin`, в ней должен лежать `clang`.

Далее необходимо прописать путь к компилятору в настройках CLion. Для этого зайдите в CLion -> Preferences -> Build, Execution, Deployment -> Toolchains и в C++ compiler пропишите полный путь к компилятору.

</details>

<details>
<summary>gcc</summary>

Выполните команду

```bash
brew install gcc
```

Чтобы посмотреть на версию установленного компилятора, выполните команду

```bash
brew info gcc  # выведет информацию про установленный пакет
```

Чтобы проверить, что `gcc` установился правильно, выполните (12 нужно заменить на версию `gсс`, установленную `brew`):

```bash
g++-12 --version  # выведет полную версию g++
which g++-12  # выведет полный путь к компилятору, например /usr/local/bin/g++-12 или /opt/homebrew/bin/g++-12
```

Далее необходимо прописать путь к компилятору в настройках CLion. Для этого зайдите в CLion -> Preferences -> Build, Execution, Deployment -> Toolchains и в C++ compiler пропишите полный путь к компилятору.

</details>

Далее, **обратите внимание**, что по умолчанию под маком ASan не включает проверку на утечки памяти. Чтобы этого избежать, зайдите в CLion -> Preferences -> Build, Execution, Deployment -> Dynamic Analysis Tools -> Sanitizers и в конце строчки AddressSanitizer (если там что-то уже написано, то через пробел) допишите строчку

```bash
detect_leaks=1
```

Теперь вы легко можете переключаться между разными видами сборок: Debug для пошагового дебага, Release для тестирования производительности, ASan для отлавливаний ошибок с памятью (в том числе и `memory leak`-ов) и UBSan для отлавливаний `undefined behavior`.

</details>

## Проверка на соответствие стайлгайду и форматирование кода

Инструкция ниже для Linux и Mac OS.

Вам понадобятся утилиты clang-format и clang-tidy, они обычно есть в стандартных репозиториях (`apt-get install` или `brew install`). Для clang-format вы можете взять конфиг [отсюда](https://raw.githubusercontent.com/NikitaChampion/algorithms-and-data-structures/main/2022-2023/codestyle/.clang-format), а для clang-tidy
[отсюда](https://raw.githubusercontent.com/NikitaChampion/algorithms-and-data-structures/main/2022-2023/codestyle/.clang-tidy).

Положите эти файлы в директорию с кодом или в домашнюю директорию.

Для форматирования кода выполните

```bash
clang-format -i main.cpp
```

Вы также можете настроить автоматическое форматирование кода с помощью этой утилиты в [CLion](https://www.jetbrains.com/help/clion/clangformat-as-alternative-formatter.html).

Для дополнительных проверок на именование переменных, функций и прочего выполните

```bash
clang-tidy main.cpp -- -std=c++17
```

По умолчанию, когда лежит .clang-tidy в директории с кодом или в домашней директории, CLion подсвечивает неправильное именование переменных, функций и прочего как ошибки.

## Полезное

### Автоматический сбор файла из нескольких файлов

Допустим, у вас имеется два файла:

```cpp
// tree.cpp
#include <iostream>

class Tree {
    // your code
};

// solution.cpp
#include <iostream>
#include "tree.cpp"

int main() {
    // your code
}
```

В задаче требуется отправить лишь один файл, который должен содержать несколько различных реализованных классов. И мы хотим сделать так, чтобы писать объявление каждого класса отдельно от реализации. К счастью, возможно автоматически собрать файл, который будет содержать весь необходимый код.

Для этого

1. Создайте директорию `system-headers`.

2. Создайте файл `system-headers/iostream` с следующим содержимым:

    ```cpp
    #ifndef SYSTEM_HEADERS_iostream
    #define SYSTEM_HEADERS_iostream
    _include_ <iostream>
    #endif
    ```

3. Выполните следующую команду:

    ```bash
    g++-12 -std=c++17 -E -P -C -nostdinc -nostdinc++ -I system-headers -D _include_=#include solution.cpp -o output.cpp
    ```

    Здесь стоит отметить следующее:
    1. `-std=c++17` нужен для использования стандарта `C++17`. Если вы не особо обращаете внимание на используемый стандарт, то можете продолжать это делать и писать, как раньше. Остальные могут использовать все фишки нового стандарта.
    2. `-E` отвечает за то, чтобы останавливаться после этапа препроцессинга (без дальнейшей компиляции и запуска). Возвращает предварительно обработанный исходный код, который отправляется на стандартный вывод.
    3. `-P` запрещает компилятору добавлять номера строк во время препроцессинга.
    4. `-C` отвечает за то, чтобы оставить комментарии. Обычно они вырезаются на этапе препроцессинга, но мы их хотим оставить.
    5. `-nostdinc -nostdinc++` запрещает компилятору искать заголовочные файлы (в угловых скобках) в своих папках.
    6. `-I system-headers` объясняет компилятору, что искать объявления наших заголовочных файлов надо в нашей папке `system-headers`.
    7. `-D _include_=#include` заменяет во всём коде текст `_include_` на `#include`. Если хочется давать переменным такое имя, то решение легко адаптируется.

    При необходимости, замените путь `solution.cpp` и `output.cpp`

4. Отформатируйте полученный файл: `clang-format -i output.cpp`. Практически гарантированно, что без этого контест его не примет.

5. Рекомендую проверить, что `output.cpp` компилируется и работает. После этого можно загружать его в контест.

В случае, если вы используете какие-то другие заголовочные файлы (кроме `<iostream>`), то нужно создавать аналогичные файлы в директории `system-headers`. Важны несколько моментов:

- Имя файла должно в точности совпадать с именем подключаемого заголовочника. Если подключаете `<math.h>`, то надо создать `system-headers/math.h`
- В этом файле пишется `_include_ <…>` **без решёток**.
- include guard хотя и не обязателен, но крайне желателен. Он позволяет избежать дублирования инклюдов в результирующем файле.
