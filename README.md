# YADRO task for the kvadraOS team # 4

## Description

This repository contains a solution for the YADRO kvadraOS #4 Team's techinacal assesment.

>Основное задание:
>
>Написать приложение на языке С++ под Linux, которое через равные интервалы времени будет обходить домашний каталог и находить в нем мультимедийные файлы (изображения, аудио, видео) и формировать файл в домашнем каталоге .media_files в формате json следующего вида:
>{ "audio": [ "111.mp3", "222.wav" ], "video": [ "333.mpg" ] "images": [ "444.jpeg", "555.png" ] }
>
>К коду должен прилагаться скрипт любой системы сборки (make, cmake, etc., но не shell-скрипт).
>
>Код должен быть выложен на git-репозиторий, содержать build-скрипт (make, cmake, etc) и readme-файл с инструкцией по построению и запуску.
>
>Решение присылать в виде ссылки на репозиторий и sha-commit'а/tag'а.
>
>Дополнительные задания (опционально):
>
> - Периодичность с которой отслеживается каталог и путь до каталога настраиваются при запуске
>
> - Результирующий json-файл не создается на файловой системе, вместо этого он доступен через HTTP по адресу http://localhost:1234/media_files через GET-запрос

A small C++ Linux application that periodically scans a directory for multimedia files and generates a JSON list of found audio, video and image files.

By default scans the users home director. The scan path and interval can be configured with cmd args. The generated json can alse be saved to ".media_files".

The optional requirements are covered:
1. Scan interval and directory path are configurable at startup (-i, -p).
2. The resulting JSON is available over HTTP at http://localhost:1234/media_files via a GET request, file output can be enabled with -f when needed.

## Requirements
- C++ 17 or higher
- CMake 3.10

## Build and run 

### Build using CMake:

```text
cmake -B build -DCMAKE_BUILD_TYPE=release
cmake --build build
```

### Run:
```text
./build/media_scanner
```

## Usage:

```text
./media_scanner [args]
```
### Cli arguments:
| Argument | Description | Default |
| -------- | ----------- | ------- |
| `-p <path>`     | Sets the directory to scan| `~/`|
| `-i <seconds>`     | Sets the scan interval in seconds| 5 |
| `-f`     | Saves the generated JSON to `.media_files`| false|


## Example

``` text
./media_scanner -p ~/media -i 5 -f
```

The JSON is available at:

``` text
http://localhost:1234/media_files
```
