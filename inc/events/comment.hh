/*
**  Copyright 2009 MERETHIS
**  This file is part of CentreonBroker.
**
**  CentreonBroker is free software: you can redistribute it and/or modify it
**  under the terms of the GNU General Public License as published by the Free
**  Software Foundation, either version 2 of the License, or (at your option)
**  any later version.
**
**  CentreonBroker is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
**  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
**  for more details.
**
**  You should have received a copy of the GNU General Public License along
**  with CentreonBroker.  If not, see <http://www.gnu.org/licenses/>.
**
**  For more information : contact@centreon.com
*/

#ifndef EVENTS_COMMENT_HH_
# define EVENTS_COMMENT_HH_

# include <time.h>         // for time_t
# include <string>
# include "events/event.h"

namespace              Events
{
  /**
   *  @class comment comment.hh "events/comment.hh"
   *  @brief Represents a comment inside Nagios.
   *
   *  Some user can make a comment on whatever objects he wants.
   */
  class                comment : public Event
  {
   private:
    void               _internal_copy(comment const& c);

   public:
    std::string        author;
    std::string        data;
    time_t             deletion_time;
    time_t             entry_time;
    short              entry_type;
    time_t             expire_time;
    bool               expires;
    std::string        host_name;
    std::string        instance_name;
    int                internal_id;
    bool               persistent;
    std::string        service_description;
    short              source;
    short              type;
                       comment();
                       comment(comment const& c);
                       ~comment();
    comment&           operator=(comment const& c);
    int                GetType() const;
  };
}

#endif /* !EVENTS_COMMENT_HH_ */