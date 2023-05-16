//
//  Command.cpp
//  Assignment4
//
//  Created by rick gessner on 2/20/21.
//

#include "Command.hpp"
#include <cstring>

namespace ECE141 {
    
    addCommand::addCommand(const std::string &aTitle, const std::string &aDate, 
    const std::string &aTime, const std::string &aPerson) : Command(cmdType::addCmd) {
      title = aTitle;
      date = aDate;
      fromTime = aTime;
      person = aPerson;
    }

    changeCommand::changeCommand(bool b) : Command(cmdType::changeCmd), 
      boolTitle(b), boolFromTime(b), boolToTime(b), boolFromDate(b), boolToDate(b), boolWith(b),
      boolNewTitle(b), boolNewWith(b), boolNewDate(b), boolNewTime(b){}

    deleteCommand::deleteCommand(bool b) : Command(cmdType::deleteCmd),
    boolTitle(b), boolFromTime(b), boolToTime(b), boolFromDate(b), boolToDate(b), boolWith(b) {}

    showCommand::showCommand(bool b): Command(cmdType::showCmd),
      boolTitle(b), boolFromTime(b), boolToTime(b), boolFromDate(b), boolToDate(b), boolWith(b) {}

    quitCommand::quitCommand(): Command(cmdType::quitCmd){}
  
}
