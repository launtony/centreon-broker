/*
** Copyright 2009-2011 MERETHIS
** This file is part of Centreon Broker.
**
** Centreon Broker is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Broker is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Broker. If not, see
** <http://www.gnu.org/licenses/>.
**
** For more information: contact@centreon.com
*/

#ifndef MULTIPLEXING_SUBSCRIBER_H_
# define MULTIPLEXING_SUBSCRIBER_H_

# include <queue>
# include <time.h>
# include "concurrency/condition_variable.hh"
# include "concurrency/mutex.hh"
# include "interface/destination.hh"
# include "interface/source.hh"

namespace                      multiplexing {
  /**
   *  @class subscriber subscriber.hh "multiplexing/subscriber.hh"
   *  @brief Receive events from publishers and make them available
   *         through the interface::source interface.
   *
   *  This class is used as a cornerstone in event multiplexing. Each
   *  output willing to receive events will request a subscriber object.
   *  All publisher objects broadcast events they receive to every
   *  subscriber objects.
   *
   *  @see publisher
   */
  class                        subscriber : public interface::destination,
                                            public interface::source {
   private:
    mutable concurrency::condition_variable
                               _cv;
    std::queue<events::event*> _events;
    mutable concurrency::mutex _mutex;
                               subscriber(subscriber const& s);
    subscriber&                operator=(subscriber const& s);
    void                       clean();

   public:
                               subscriber();
                               ~subscriber();
    void                       close();
    events::event*             event();
    events::event*             event(time_t deadline);
    void                       event(events::event* e);
  };
}

#endif /* !MULTIPLEXING_SUBSCRIBER_H_ */