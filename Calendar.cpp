//
//  Calendar.cpp
//  Assignment4
//
//  Created by rick gessner on 2/20/21.
//

#include "Calendar.hpp"

namespace ECE141 {

  Calendar::Calendar(std::ostream &aStream)
    : stream(aStream) {}

  Calendar::~Calendar() {
    for(auto event: events) {
      delete event;
    }
    if(Event::leaks) {
      std::cout << "(" << Event::leaks << " events leaked) ";
    }
  }

  bool Calendar::addEvent(Event *anEvent) {
    events.push_back(anEvent);
    return true;
  }

  bool Calendar::removeEvent(Event *anEvent) {

    //iterate through the event list to match the event to be deleted
    Events::iterator it;
    for(it = events.begin(); it != events.end(); it++) {
      if(*it == anEvent) {
        delete *it;
        events.erase(it);
        return true;
      }
    }
    return false;
  }

}
