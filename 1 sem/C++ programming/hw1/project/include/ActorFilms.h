#ifndef PROJECT_INCLUDE_ACTORFILMS_H_
#define PROJECT_INCLUDE_ACTORFILMS_H_

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class ActorFilms {
 public:
  ActorFilms() = default;
  std::unordered_map<std::string, std::string> getMoviesWithActor();
  int createListOfFilms(std::istream &nameBasics, std::istream &principals,
                        std::istream &titleBasics, std::istream &akas,
                        const std::string &actor);

 private:
  struct person_t {
    std::string nconst;
    std::string primaryName;
    void scan(std::istream &ss);
  };

  struct persons_film_t {
    std::string tconst;
    std::string ordering;
    std::string nconst;
    std::string category;
    void scan(std::istream &ss);
  };

  struct common_film_t {
    std::string filmId;
    std::string titleType;
    std::string primaryTitle;
    std::string originalTitle;
    std::string isAdult;
    void scan(std::istream &ss);
  };

  struct region_film_t {
    std::string filmId;
    std::string ordering;
    std::string title;
    std::string region;
    std::string language;
    void scan(std::istream &ss);
  };

  std::unordered_map<std::string, std::string> movies;
  std::set<std::string> personIds;
  int checkFilms(std::istream &titleBasics);
  int getPersonId(std::istream &nameBasics, const std::string &personName);
  int getAllFilmsWithPerson(std::istream &principals);
  int getRuNames(std::istream &akas);
};

#endif  // PROJECT_INCLUDE_ACTORFILMS_H_
