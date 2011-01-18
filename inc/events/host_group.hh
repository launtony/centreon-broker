/*
** Copyright 2009-2010 MERETHIS
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

#ifndef EVENTS_HOST_GROUP_HH_
# define EVENTS_HOST_GROUP_HH_

# include "events/group.hh"

namespace       events {
  /**
   *  @class host_group host_group.hh "events/host_group.hh"
   *  @brief Represents a group of hosts within Nagios.
   *
   *  A group of hosts within Nagios.
   */
  class         host_group : public group {
   public:
                host_group();
                host_group(host_group const& hg);
                ~host_group();
    host_group& operator=(host_group const& hg);
    int         get_type() const;
  };
}

#endif /* !EVENTS_HOST_GROUP_HH_ */