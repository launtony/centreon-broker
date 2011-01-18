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

#include "events/host_parent.hh"

using namespace events;

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  Default constructor.
 */
host_parent::host_parent() : host_id(0), parent_id(0) {}

/**
 *  Copy constructor.
 *
 *  @param[in] hp Object to copy.
 */
host_parent::host_parent(host_parent const& hp)
  : event(hp), host_id(hp.host_id), parent_id(hp.parent_id) {}

/**
 *  Destructor.
 */
host_parent::~host_parent() {}

/**
 *  Assignment operator.
 *
 *  @param[in] hp Object to copy.
 *
 *  @return This object.
 */
host_parent& host_parent::operator=(host_parent const& hp) {
  event::operator=(hp);
  host_id = hp.host_id;
  parent_id = hp.parent_id;
  return (*this);
}

/**
 *  Get the type of this event (event::HOSTPARENT).
 *
 *  @return event::HOSTPARENT
 */
int host_parent::get_type() const {
  return (HOSTPARENT);
}