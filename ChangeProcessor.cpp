//
//  ChangeProcessor.cpp
//  Assignment4
//
//  Created by rick gessner on 2/24/21.
//

#include "ChangeProcessor.hpp"


namespace ECE141 {

  ChangeProcessor::ChangeProcessor(CommandProcessor *aNext)
    : CommandProcessor(aNext) {}

  ChangeProcessor::~ChangeProcessor() {}

  bool ChangeProcessor::recognizes(Tokenizer &aTokenizer) {
    return aTokenizer.skipTo(Keywords::change_kw);
  }

  Command* ChangeProcessor::makeCommand(Tokenizer &aTokenizer) {
    changeCommand * command = new changeCommand();

    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::change_kw) && aTokenizer.next() && aTokenizer.more()){
      Token token = aTokenizer.current();

      //if title of event to be changed is specified
      if(token.type == TokenType::string){
        command->boolTitle = true;
        command->title = token.data;

        //update token for id=value check
        if(aTokenizer.next() && aTokenizer.more()) {token = aTokenizer.current();}
      }

      // keep getting id= phrase or with= phrases after Change keyword
      while((token.type == TokenType::identifier || token.type == TokenType::keyword)
            && aTokenizer.next() && aTokenizer.skipIf('=')) {

        //title = "XXXX"
        if(token.data == std::string("title") && aTokenizer.more()) {
          command->boolNewTitle = true;
          command->newTitle = aTokenizer.current().data;
        }

        //date = 2021-XX-XX
        if(token.data == std::string("date") && aTokenizer.more()) {
          command->boolNewDate = true;
          command->newFromDate = aTokenizer.current().data;
        }

        //time = XX:XXpm
        if(token.data == std::string("time") && aTokenizer.more()) {
          command->boolNewTime = true;
          command->newFromTime = aTokenizer.current().data;
        }

        //with = "personName"
        if(token.keyword == Keywords::with_kw && aTokenizer.more()) {
          command->boolNewWith = true;
          command->newWith = aTokenizer.current().data;
        }
        if(aTokenizer.next() && aTokenizer.more()) {token = aTokenizer.current();}
      }
    }

    //check for date condition
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::on_kw) && aTokenizer.next() && aTokenizer.more()) {
      command->boolFromDate = true;
      command->fromDate = aTokenizer.current().data;

      //check if there's until keyword
      if(aTokenizer.next() && aTokenizer.skipIf(Keywords::until_kw) && aTokenizer.more()) {
        command->boolToDate = true;
        command->toDate = aTokenizer.current().data;
      }
    }

    //check for time condition
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::at_kw) && aTokenizer.next() && aTokenizer.more()) {
      command->boolFromTime = true;
      command->fromDate = aTokenizer.current().data;

      //until condition
      if(aTokenizer.next() && aTokenizer.skipIf(Keywords::until_kw) && aTokenizer.more()) {
        command->boolToTime = true;
        command->toDate = aTokenizer.current().data;
      }
    }

    //check for if conditions
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::if_kw) && aTokenizer.next()) {
      Token token = aTokenizer.current();

      while((token.type == TokenType::identifier || token.type == TokenType::keyword)
            && aTokenizer.next() && aTokenizer.skipIf('=')) {

        //title = "XXXX"
        if(token.data == std::string("title") && aTokenizer.more() && aTokenizer.current().type == TokenType::string) {
          command->boolTitle = true;
          command->title = aTokenizer.current().data;
        }

        //date = 2021-XX-XX
        if(token.data == std::string("date") && aTokenizer.more() && aTokenizer.current().type == TokenType::timedate) {
          command->boolFromDate = true;
          command->fromDate = aTokenizer.current().data;
        }

        //time = XX:XXpm
        if(token.data == std::string("time") && aTokenizer.more() && aTokenizer.current().type == TokenType::timedate) {
          command->boolFromTime = true;
          command->fromTime = aTokenizer.current().data;
        }

        //with = "personName"
        if(token.keyword == Keywords::with_kw && aTokenizer.more() && aTokenizer.current().type == TokenType::string) {
          command->boolWith = true;
          command->with = aTokenizer.current().data;
        }

        //get the next token
        if(aTokenizer.next() && aTokenizer.more()) {token = aTokenizer.current();}
      }
    }

    return command;
  }

  int ChangeProcessor::run(Command *aCommand, Calendar &aCal) {
    changeCommand * cmd = (changeCommand *)aCommand;
    Events list = aCal.getEvents();

    //title filter
    if(cmd->boolTitle) {
      std::string str = cmd->title;
      Events list2;
      for(auto * event : list) {
          if(event->title == str) list2.push_back(event);
      }
      list = list2;
    }

    //date filter
    if(cmd->boolFromDate) {
      std::string str = cmd->boolToDate ? cmd->fromDate + "-" + cmd->toDate : cmd->fromDate;
      Events list2;
      for(auto * event : list) {
        if(event->date == str) list2.push_back(event);
      }
      list = list2;
    }

    //time filter
    if(cmd->boolFromTime) {
      std::string str = cmd->boolToTime ? cmd->fromTime + "-" + cmd->toTime : cmd->fromTime;
      Events list2;
      for(auto * event : list) {
        if(event->time == str) list2.push_back(event);
      }
      list = list2;
    }

    //with filter
    if(cmd->boolWith) {
      Events list2;
      for(auto * event : list) {
        if(event->with == cmd->with) {
          list2.push_back(event);
        }
      }
      list = list2;
    }

    //change attributes of events in the filtered list
    for(auto * event : list) {
      if(cmd->boolNewTitle) event->title = cmd->newTitle;
      if(cmd->boolNewDate) event->date = cmd->newFromDate;
      if(cmd->boolNewTime) event->time = cmd->newFromTime;
      if(cmd->boolNewWith) event->with = cmd->newWith;
            
    }

    return kNoError;
  }

}
