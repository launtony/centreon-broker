/*
**  Copyright 2010 MERETHIS
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

#include "events/event_handler.hh"

using namespace Events;

/**************************************
*                                     *
*           Private Methods           *
*                                     *
**************************************/

/**
 *  Copy internal data members.
 *
 *  @param[in] eh Object to copy.
 */
void event_handler::_internal_copy(event_handler const& eh) {
  command_args   = eh.command_args;
  command_line   = eh.command_line;
  early_timeout  = eh.early_timeout;
  end_time       = eh.end_time;
  execution_time = eh.execution_time;
  host_id        = eh.host_id;
  output         = eh.output;
  return_code    = eh.return_code;
  service_id     = eh.service_id;
  start_time     = eh.start_time;
  state          = eh.state;
  state_type     = eh.state_type;
  timeout        = eh.timeout;
  type           = eh.type;
  return ;
}

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  Default constructor.
 */
event_handler::event_handler()
  : early_timeout(0),
    end_time(0),
    execution_time(0),
    host_id(0),
    return_code(0),
    service_id(0),
    start_time(0),
    state(0),
    state_type(0),
    timeout(0),
    type(0) {}

/**
 *  Copy constructor.
 *
 *  @param[in] eh Object to copy.
 */
event_handler::event_handler(event_handler const& eh) : Event(eh) {
  _internal_copy(eh);
}

/**
 *  Destructor.
 */
event_handler::~event_handler() {}

/**
 *  Assignment operator.
 *
 *  @param[in] eh Object to copy.
 *
 *  @return This object.
 */
event_handler& event_handler::operator=(event_handler const& eh) {
  Event::operator=(eh);
  _internal_copy(eh);
  return (*this);
}

/**
 *  Get the type of this event.
 *
 *  @return EVENTHANDLER.
 */
int event_handler::GetType() const {
  return (EVENTHANDLER);
}