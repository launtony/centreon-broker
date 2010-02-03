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

#include "db/query.h"

using namespace CentreonBroker::DB;

/**************************************
*                                     *
*          Protected Methods          *
*                                     *
**************************************/

/**
 *  \brief Query default constructor.
 *
 *  Initialize members to their default values.
 */
Query::Query() throw () {}

/**
 *  \brief Query copy constructor.
 *
 *  Build the new instance by copying data from the given object.
 *
 *  \param[in] query Object to copy data from.
 */
Query::Query(const Query& query) throw ()
{
  (void)query;
}

/**
 *  \brief Overload of the assignment operator.
 *
 *  Copy data from the given object to the current instance.
 *
 *  \param[in] query Object to copy data from.
 *
 *  \return *this
 */
Query& Query::operator=(const Query& query) throw ()
{
  (void)query;
  return (*this);
}

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  \brief Query destructor.
 *
 *  Release previously allocated ressources.
 */
Query::~Query() {}