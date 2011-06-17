/*
** Copyright 2009-2011 Merethis
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
*/

#include "events/custom_variable_status.hh"

using namespace com::centreon::broker::events;

/**************************************
*                                     *
*           Private Methods           *
*                                     *
**************************************/

/**
 *  Copy internal data members.
 *
 *  @param[in] cvs Object to copy.
 */
void custom_variable_status::_internal_copy(custom_variable_status const& cvs) {
  host_id = cvs.host_id;
  modified = cvs.modified;
  name = cvs.name;
  service_id = cvs.service_id;
  update_time = cvs.update_time;
  value = cvs.value;
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
custom_variable_status::custom_variable_status()
  : host_id(0),
    modified(true),
    service_id(0),
    update_time(time(NULL)) {}

/**
 *  Copy constructor.
 *
 *  @param[in] cvs Object to copy.
 */
custom_variable_status::custom_variable_status(custom_variable_status const& cvs)
  : event(cvs) {
  _internal_copy(cvs);
}

/**
 *  Destructor.
 */
custom_variable_status::~custom_variable_status() {}

/**
 *  Assignment operator.
 *
 *  @param[in] cvs Object to copy.
 *
 *  @return This object.
 */
custom_variable_status& custom_variable_status::operator=(custom_variable_status const& cvs) {
  event::operator=(cvs);
  _internal_copy(cvs);
  return (*this);
}

/**
 *  Get the type of this event.
 *
 *  @return CUSTOMVARIABLESTATUS.
 */
unsigned int custom_variable_status::type() const {
  return (CUSTOMVARIABLESTATUS);
}