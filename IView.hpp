//
//  View.hpp
//  Assignment4
//
//  Created by rick gessner on 2/22/21.
//

#ifndef IView_hpp
#define IView_hpp

#include <stdio.h>
#include <iostream>
#include "Calendar.hpp"

namespace ECE141 {
    
  class IView {
  public:
    virtual void show(std::ostream &anOutput)=0;
  };

  class View : public IView {
    public:
    View(Events someEvents):events(someEvents){}
    void show(std::ostream &anOutput) {
      if(!events.empty()) {
        anOutput << "|-----------------------|-----------------------|-----------------------|-----------------------|\n";
        anOutput << "| Title                 | Date                  | Time                  | With                  |\n";
        anOutput << "|-----------------------|-----------------------|-----------------------|-----------------------|\n";
        for(auto * event : events) {
          outputLine(anOutput, event->title, event->date, event->time, event->with);
        }
        anOutput << "|-----------------------|-----------------------|-----------------------|-----------------------|\n";
      } else {
        anOutput << "No scheduled events found \n";
      }
      
    }

    //helper function to output a line in format
    void outputLine(std::ostream &anOutput, std::string title, std::string date, std::string time,std::string with) {
      anOutput << "| " << title;
      int space;
      space = 22 - title.size();
      for(int i = 0; i < space; i++) {
        anOutput << " ";
      }

      anOutput << "| " << date;
      space = 22 - date.size();
      for(int i = 0; i < space; i++) {
        anOutput << " ";
      }

      anOutput << "| " << time;
      space = 22 - time.size();
      for(int i = 0; i < space; i++) {
        anOutput << " ";
      }

      anOutput << "| " << with;
      space = 22 - with.size();
      for(int i = 0; i < space; i++) {
        anOutput << " ";
      }

      anOutput << "|\n";
    }
    Events events;
  };

}

#endif /* IView_hpp */
