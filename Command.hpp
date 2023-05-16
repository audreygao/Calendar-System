//
//  Command.hpp
//  Assignment4
//
//  Created by rick gessner on 2/20/21.
//

#ifndef Command_hpp
#define Command_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "Tokenizer.hpp"

namespace ECE141 {

  //Store cmd-related information in this object..
  //Make any changes you want...
  enum class cmdType {addCmd, changeCmd, deleteCmd, quitCmd, showCmd};

  class Command {
  public:
    
    Command(cmdType aType) : type(aType) {} 
    
    cmdType type;
  };

  class addCommand : public Command {
  public:

    addCommand(const std::string &aTitle, const std::string &aDate, const std::string &aTime, const std::string &aPerson); 
    std::string title;
    std::string date;
    std::string fromTime;
    std::string person;
  };

  class changeCommand : public Command {
  public:
    changeCommand(bool b=false);
    bool boolTitle, boolFromTime, boolToTime, boolFromDate, boolToDate, boolWith;
    bool boolNewTitle, boolNewWith, boolNewDate, boolNewTime;
    std::string title, fromTime, toTime, with, fromDate, toDate;
    std::string newTitle, newFromTime, newToTime, newWith, newFromDate, newToDate;
  };

  class deleteCommand : public Command {
  public:
    deleteCommand(bool b=false);
    bool boolTitle, boolFromTime, boolToTime, boolFromDate, boolToDate, boolWith;
    std::string title, fromTime, toTime, with, fromDate, toDate;
  };

  class showCommand : public Command {
  public:
    showCommand(bool b=false);
    bool boolTitle, boolFromTime, boolToTime, boolFromDate, boolToDate, boolWith;
    std::string title, fromTime, toTime, with, fromDate, toDate;

  };

  class quitCommand : public Command {
  public:
    quitCommand();
  };

}

#endif /* Command_hpp */
