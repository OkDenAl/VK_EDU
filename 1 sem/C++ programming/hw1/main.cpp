#include <getopt.h>

#include <fstream>
#include <iostream>

#include "ActorFilms.h"
#include "InputData.h"

void printUsageForm() {
  std::cout
      << "Usage: ./films_actor --actor-name <Name> --actor-surname <Surname> "
         "--title-principals-path path/to/title.principals.tsv "
         "--title-basics-path path/to/title.basics.tsv "
         "--name-basics-path path/to/name.basics.tsv --title-akas-path "
         "path/to/title.akas.tsv"
      << std::endl;
}

int parseFlags(int argc, char *argv[], InputData *data) {
  if (data == nullptr) {
    return 1;
  }
  static struct option long_options[] = {
      {"actor-name", required_argument, nullptr, 'n'},
      {"actor-surname", required_argument, nullptr, 's'},
      {"title-principals-path", required_argument, nullptr, 'p'},
      {"title-basics-path", required_argument, nullptr, 't'},
      {"name-basics-path", required_argument, nullptr, 'b'},
      {"title-akas-path", required_argument, nullptr, 'a'},
      {0, 0, 0, 0}};
  int c;

  while ((c = getopt_long(argc, argv, "an:as:p:tb:nb:a", long_options,
                          nullptr)) != -1) {
    if (c == 'n') {
      data->actor = optarg;
    } else if (c == 's') {
      data->actor += " " + std::string(optarg);
    } else if (c == 'p') {
      data->principalsFilename = optarg;
    } else if (c == 't') {
      data->titleBasicsFilename = optarg;
    } else if (c == 'b') {
      data->nameBasicsFilename = optarg;
    } else if (c == 'a') {
      data->akasFilename = optarg;
    } else {
      return 1;
    }
  }
  return 0;
}

void closeFiles(std::ifstream &nameBasics, std::ifstream &principals,
                std::ifstream &titleBasics, std::ifstream &akas) {
  nameBasics.close();
  principals.close();
  titleBasics.close();
  akas.close();
}

int main(int argc, char *argv[]) {
  if (argc != 13) {
    std::cerr << "Argument count is invalid" << std::endl;
    printUsageForm();
    return 1;
  }

  InputData data;

  if (parseFlags(argc, argv, &data) == -1) {
    std::cerr << "Cant parse flags" << std::endl;
    printUsageForm();
  }

  std::cout << data.actor << std::endl;

  std::ifstream nameBasics(data.nameBasicsFilename);
  std::ifstream principals(data.principalsFilename);
  std::ifstream titleBasics(data.titleBasicsFilename);
  std::ifstream akas(data.akasFilename);

  if (!nameBasics.is_open() || !principals.is_open() ||
      !titleBasics.is_open() || !akas.is_open()) {
    std::cerr << "Cant open files specified" << std::endl;
    closeFiles(nameBasics, principals, titleBasics, akas);
    return 1;
  }

  ActorFilms movies;
  if (movies.createListOfFilms(nameBasics, principals, titleBasics, akas,
                               data.actor)) {
    std::cerr << "Cant create a list of films" << std::endl;
    closeFiles(nameBasics, principals, titleBasics, akas);
    return 1;
  }

  auto res = movies.getMoviesWithActor();
  for (const auto &i : res) {
    if (!i.second.empty()) {
      std::cout << i.second << "\n";
    }
  }

  closeFiles(nameBasics, principals, titleBasics, akas);
  return 0;
}
