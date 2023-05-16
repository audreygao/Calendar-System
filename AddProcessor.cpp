//
//  AddProcessor.cpp
//  Assignment4
//
//  Created by rick gessner on 2/19/21.
//

#include "AddProcessor.hpp"

namespace ECE141 {

  AddProcessor::AddProcessor(CommandProcessor *aNext)
    : CommandProcessor(aNext) {}

  AddProcessor::~AddProcessor() {}

  bool AddProcessor::recognizes(Tokenizer &aTokenizer) {
    return aTokenizer.skipTo(Keywords::add_kw);
  }

  Command* AddProcessor::makeCommand(Tokenizer &aTokenizer) {
    
    std::string title, date, time, person;

    //extract the title
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::add_kw) && aTokenizer.next() && aTokenizer.more()) {
      if(aTokenizer.current().type == TokenType::string) title = aTokenizer.current().data;
    }

    //extract date on
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::on_kw) && aTokenizer.next() && aTokenizer.more()) {
      if(aTokenizer.current().type == TokenType::timedate) date = aTokenizer.current().data;

      //append until date if there's until keyword
      if(aTokenizer.next() && aTokenizer.skipIf(Keywords::until_kw) && aTokenizer.more()) {
        if(aTokenizer.current().type == TokenType::timedate) date = date + "-" + aTokenizer.current().data;
      }
    }

    //extract time at
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::at_kw) && aTokenizer.next() && aTokenizer.more()) {
      if(aTokenizer.current().type == TokenType::timedate) time = aTokenizer.current().data;

      //append until time if there's until keyword
      if(aTokenizer.next() && aTokenizer.skipIf(Keywords::until_kw) && aTokenizer.more()) {
        if(aTokenizer.current().type == TokenType::timedate) time = time + "-" + aTokenizer.current().data;
      }
    }

    //extract the person with
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::with_kw) && aTokenizer.next() && aTokenizer.more()) {
      if(aTokenizer.current().type == TokenType::string) person = aTokenizer.current().data;
    }
    
    addCommand * cmd = new addCommand(title, date, time, person);
    return cmd;
  }

  int AddProcessor::run(Command *aCommand, Calendar &aCal) {
    addCommand * cmd = (addCommand *)aCommand;
    Event * event = new Event(cmd->title, cmd->date, cmd->fromTime, cmd->person);
    aCal.addEvent(event);
    return kNoError;
  }

}
