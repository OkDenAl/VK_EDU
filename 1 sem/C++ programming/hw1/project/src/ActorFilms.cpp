#include "ActorFilms.h"

#include <iostream>
#include <sstream>

#define NEED_TITLE_TYPE "movie"
#define NOT_FOR_ADULTS "0"
#define NEED_MALE_PERSON_CATEGORY "actor"
#define NEED_FEMALE_PERSON_CATEGORY "actress"
#define NEED_LANGUAGE "ru"
#define NEED_REGION "RU"

void ActorFilms::person_t::scan(std::istream &ss) {
  std::getline(ss, nconst, '\t');
  std::getline(ss, primaryName, '\t');
}
void ActorFilms::persons_film_t::scan(std::istream &ss) {
  std::getline(ss, tconst, '\t');
  std::getline(ss, ordering, '\t');
  std::getline(ss, nconst, '\t');
  std::getline(ss, category, '\t');
}
void ActorFilms::common_film_t::scan(std::istream &ss) {
  std::getline(ss, filmId, '\t');
  std::getline(ss, titleType, '\t');
  std::getline(ss, primaryTitle, '\t');
  std::getline(ss, originalTitle, '\t');
  std::getline(ss, isAdult, '\t');
}

void ActorFilms::region_film_t::scan(std::istream &ss) {
  std::getline(ss, filmId, '\t');
  std::getline(ss, ordering, '\t');
  std::getline(ss, title, '\t');
  std::getline(ss, region, '\t');
  std::getline(ss, language, '\t');
}

std::unordered_map<std::string, std::string> ActorFilms::getMoviesWithActor() {
  return movies;
}

int ActorFilms::createListOfFilms(std::istream &nameBasics,
                                  std::istream &principals,
                                  std::istream &titleBasics, std::istream &akas,
                                  const std::string &actor) {
  if (getPersonId(nameBasics, actor)) {
    return 1;
  }
  if (getAllFilmsWithPerson(principals)) {
    return 1;
  }
  if (checkFilms(titleBasics)) {
    return 1;
  }
  if (getRuNames(akas)) {
    return 1;
  }
  return 0;
}

int ActorFilms::getPersonId(std::istream &nameBasics,
                            const std::string &personName) {
  std::string line;
  while (std::getline(nameBasics, line)) {
    std::istringstream ss(line);
    person_t persData;
    persData.scan(ss);

    if (persData.nconst.empty() || persData.primaryName.empty()) {
      return 1;
    }
    if (persData.primaryName == personName) {
      personIds.insert(persData.nconst);
    }
  }
  return 0;
}

int ActorFilms::getAllFilmsWithPerson(std::istream &principals) {
  std::string line;

  while (std::getline(principals, line)) {
    std::istringstream ss(line);
    persons_film_t personsFilmData;
    personsFilmData.scan(ss);

    if (personsFilmData.tconst.empty() | personsFilmData.nconst.empty() |
        personsFilmData.category.empty()) {
      return 1;
    }
    if (personIds.find(personsFilmData.nconst) != personIds.end() &&
        (personsFilmData.category == NEED_FEMALE_PERSON_CATEGORY ||
         personsFilmData.category == NEED_MALE_PERSON_CATEGORY)) {
      movies[personsFilmData.tconst] = "";
    }
  }
  return 0;
}

int ActorFilms::checkFilms(std::istream &titleBasics) {
  std::string line;
  size_t i = 0;

  while (std::getline(titleBasics, line)) {
    std::istringstream ss(line);
    common_film_t commonFilmData;
    commonFilmData.scan(ss);

    if (i > movies.size()) {
      break;
    }
    if (commonFilmData.filmId.empty() || commonFilmData.isAdult.empty() ||
        commonFilmData.titleType.empty()) {
      return 1;
    }
    if (movies.find(commonFilmData.filmId) != movies.end() &&
        (commonFilmData.isAdult != NOT_FOR_ADULTS ||
         commonFilmData.titleType != NEED_TITLE_TYPE)) {
      movies.erase(commonFilmData.filmId);
    } else {
      i++;
    }
  }
  return 0;
}

int ActorFilms::getRuNames(std::istream &akas) {
  std::string line;
  size_t i = 0;
  while (std::getline(akas, line)) {
    std::istringstream ss(line);
    region_film_t regionFilmData;
    regionFilmData.scan(ss);

    if ((regionFilmData.region.empty() || regionFilmData.filmId.empty() ||
         regionFilmData.title.empty())) {
      return -1;
    }
    if (i > movies.size()) {
      break;
    }
    if (movies.find(regionFilmData.filmId) != movies.end() &&
        movies[regionFilmData.filmId].empty() &&
        (regionFilmData.region == NEED_REGION ||
         regionFilmData.language == NEED_LANGUAGE)) {
      movies[regionFilmData.filmId] = regionFilmData.title;
      i++;
    }
  }
  return 0;
}
