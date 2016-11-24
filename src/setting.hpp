#pragma once
#include <string>
#include <json/json.h>
#include <json/writer.h>
#include <json/value.h>
#include <json/forwards.h>
#include <fstream>
#include <iostream>

enum class GameLevel : unsigned char {Easy, Normal, Hard};

class Settings
{

public:
  Settings() = default;
  Settings(std::string const & name, GameLevel level)
   : m_name(name), m_level(level) {}
  void SetName(std::string const & name) { m_name = name; }
  void SetLevel(GameLevel const & level) { m_level = level;}
  void SetSound(unsigned sound) { m_sound = sound;}
  void Save()
  {
    Json::Value settings;
    auto & root = settings["settings"];
    root["game"]["UserName"] = m_name;
    root["game"]["GameLevel"] = static_cast<unsigned char> (m_level);
    root["game"]["GameSound"] = m_sound;

    std::ofstream settingsFile;
    settingsFile.open("settings.json");
    if (settingsFile.is_open())
    {
      Json::StyledWriter styledWriter;
      settingsFile << styledWriter.write(settings);
      settingsFile.close();
    }
  }

  void Read()
  {
    Json::Value settings;
    std::ifstream file("settings.json");
    if (file.is_open())
    {
      file >> settings;
      file.close();
    }
    auto & game = settings["settings"]["game"];
    m_name = game["UserName"].asString();
    m_level = static_cast<GameLevel> (game["GameLevel"].asInt());
    m_sound = game["GameSound"].asInt();
  }

  std::string const & GetName() const { return m_name; }
  GameLevel const & GetLevel() const { return m_level; }
  unsigned const & GetSound() const { return m_sound; }
private:
  std::string m_name = "";
  GameLevel m_level = GameLevel::Easy;
  unsigned m_sound = 100;
};
