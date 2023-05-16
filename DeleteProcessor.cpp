//
//  DeleteProcessor.cpp
//  Assignment4
//
//  Created by rick gessner on 2/24/21.
//

#include "DeleteProcessor.hpp"


namespace ECE141 {


  DeleteProcessor::DeleteProcessor(CommandProcessor *aNext)
    : CommandProcessor(aNext) {}

  DeleteProcessor::~DeleteProcessor() {}

  bool DeleteProcessor::recognizes(Tokenizer &aTokenizer) {
    return aTokenizer.skipTo(Keywords::delete_kw);
  }

  Command* DeleteProcessor::makeCommand(Tokenizer &aTokenizer) {
    deleteCommand * command = new deleteCommand(false);

    //Change "titleName" condition
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::delete_kw) && aTokenizer.next() && aTokenizer.more()){
      if(aTokenizer.current().type == TokenType::string){
        command->boolTitle = true;
        command->title = aTokenizer.current().data;
      }
    }

    //check for date condition
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::on_kw) && aTokenizer.next() && aTokenizer.more()) {
      if(aTokenizer.current().type == TokenType::timedate) {
        command->boolFromDate = true;
        command->fromDate = aTokenizer.current().data;
      }

      //check if there's until keyword
      if(aTokenizer.next() && aTokenizer.skipIf(Keywords::until_kw) && aTokenizer.more()) {
        if(aTokenizer.current().type == TokenType::timedate) {
          command->boolToDate = true;
          command->toDate = aTokenizer.current().data;
        }
      }
    }

    //check for time condition
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::at_kw) && aTokenizer.next() && aTokenizer.more()) {
      if(aTokenizer.current().type == TokenType::timedate) {
        command->boolFromTime = true;
        command->fromDate = aTokenizer.current().data;
      }
      
      //until condition
      if(aTokenizer.next() && aTokenizer.skipIf(Keywords::until_kw) && aTokenizer.more()) {
        if(aTokenizer.current().type == TokenType::timedate) {
          command->boolToTime = true;
          command->toDate = aTokenizer.current().data;
        }
      }
    }

    //check for if conditions
    aTokenizer.restart();
    if(aTokenizer.skipTo(Keywords::if_kw) && aTokenizer.next() && aTokenizer.more()) {
      Token token = aTokenizer.current();

      while((token.type == TokenType::identifier || token.type == TokenType::keyword)
            && aTokenizer.next() && aTokenizer.skipIf('=')) {

        //title = "XXXX"
        if(token.data == std::string("title") && aTokenizer.more()) {
          command->boolTitle = true;
          command->title = aTokenizer.current().data;
        }

        //date = 20XX-XX-XX
        if(token.data == std::string("date") && aTokenizer.more()) {
          command->boolFromDate = true;
          command->fromDate = aTokenizer.current().data;
        }

        //time = XX:XXpm
        if(token.data == std::string("time") && aTokenizer.more()) {
          command->boolFromTime = true;
          command->fromTime = aTokenizer.current().data;
        }

        //with = "personName"
        if(token.keyword == Keywords::with_kw && aTokenizer.more()) {
          command->boolWith = true;
          command->with = aTokenizer.current().data;
        }

        //get the next token
        if(aTokenizer.next() && aTokenizer.more()) {token = aTokenizer.current();}
      }
    }  

    return command;
  }

  int DeleteProcessor::run(Command *aCommand, Calendar &aCal) {
    deleteCommand * cmd = (deleteCommand *)aCommand;
    Events list = aCal.getEvents();

    //attribute filters
    if(cmd->boolTitle) {
      std::string str = cmd->title;
      Events list2;
      for(auto * event : list) {
          if(event->title == str) list2.push_back(event);
      }
      list = list2;
    }
    if(cmd->boolFromDate) {
        std::string str = cmd->boolToDate ? (cmd->fromDate + "-" + cmd->toDate) : cmd->fromDate;
        Events list2;
        for(auto * event : list) {
          if(event->date == str) list2.push_back(event);
        }
        list = list2;
    }
    if(cmd->boolFromTime) {
        std::string str = cmd->boolToTime ? cmd->fromTime + "-" + cmd->toTime : cmd->fromTime;
        Events list2;
        for(auto * event : list) {
          if(event->time == str) list2.push_back(event);
        }
        list = list2;
    }
    if(cmd->boolWith) {
      Events list2;
      for(auto * event : list) {
        if(event->with == cmd->with) list2.push_back(event);
      }
      list = list2;  
    }

    //iterate through and delete events the filtered list
    for(auto * event : list) {
        aCal.removeEvent(event);
    }

    return kNoError;
  }

}
